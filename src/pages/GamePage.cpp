#include "GamePage.h"

#include <fxcg/display.h>
#include <fxcg/keyboard.h>
#include <fxcg/rtc.h>

#include "../utilities.h"

#include "../PageManager.h"

#include "../tetris/Board.h"
#include "../tetris/Tetronimo.h"

GamePage::GamePage(PageManager* page_manager) : Page(page_manager)
{
	this->m_vtable_parent = this;
	this->m_vfunc_FocusGained = [](void* ptr, PageType previous_page){return static_cast<GamePage*>(ptr)->FocusGained(previous_page);};
	this->m_vfunc_FocusLost = [](void* ptr, PageType new_page){return static_cast<GamePage*>(ptr)->FocusLost(new_page);};
	this->m_vfunc_Update = [](void* ptr){return static_cast<GamePage*>(ptr)->Update();};
}

void GamePage::FocusGained(PageType previous_page)
{
	EnableStatusArea(3); //disable the status bar at the top of the screen
	Bdisp_AllClr_VRAM();

	this->m_board_main = new Board(GAME_BOARD_COLUMNS, GAME_BOARD_ROWS, 10, 10, 10, 10);
	this->m_tetronimo_main = nullptr;

	this->m_board_nextbox = new Board(4, 4, 10, 10, 120, 10);
	this->m_tetronimo_main = nullptr;

	this->m_rtc_last_move_down = RTC_GetTicks() - 10000; //set to some time suitably in the past

	PrintXY(2, 2, "  Game", TEXT_MODE_NORMAL, TEXT_COLOR_BLACK);

	Bdisp_PutDisp_DD();
}

void GamePage::FocusLost(PageType new_page)
{
	delete this->m_board_main;
	delete this->m_tetronimo_main;
	delete this->m_board_nextbox;
	delete this->m_tetronimo_nextbox;
}

void GamePage::Update()
{
	const int rtc_ticks = RTC_GetTicks(); //cache result, used multiple times

	//handle key presses
	int key_column;
	int key_row;
	unsigned short key_code;

	const int keypress_type = GetKeyWait_OS(&key_column, &key_row, KEYWAIT_HALTON_TIMERON, 0, 0, &key_code);

	if (keypress_type == KEYREP_KEYEVENT)
	{
		if ((key_row == 0x08) && (key_column == 0x04)) //exit button
		{
			this->m_page_manager->SwitchPage(PageType::Menu);
		}
	}

	bool copy_vram = false;
	

	//generate new pieces if they don't exist
	if (this->m_tetronimo_nextbox == nullptr)
	{
		this->m_tetronimo_nextbox = new Tetronimo(0, 0, this->m_board_nextbox, GetTileType(), GetTetronimoType());

		copy_vram = true;
	}

	if (this->m_tetronimo_main == nullptr)
	{
		this->m_tetronimo_main = new Tetronimo(3, 0, this->m_board_main, this->m_tetronimo_nextbox->GetTileType(), this->m_tetronimo_nextbox->GetType());

		copy_vram = true;
	}

	//move current piece if required
	{
		const int rtc_move_down_elapsed = rtc_ticks - this->m_rtc_last_move_down;

		if (rtc_move_down_elapsed > 64) //0.5s
		{
			if (this->m_tetronimo_main->CanMove(Direction::Down))
			{
				this->m_tetronimo_main->Move(Direction::Down);
				copy_vram = true;
			}
			else
			{
				delete this->m_tetronimo_main;
				this->m_tetronimo_main = nullptr;

				bool complete_rows[GAME_BOARD_ROWS];

				//check for complete rows
				for (int y = 0; y < GAME_BOARD_ROWS; y++)
				{
					complete_rows[y] = true;
					for (int x = 0; x < GAME_BOARD_COLUMNS; x++)
					{
						if (this->m_board_main->GetTile(x, y) == TileType::Blank)
						{
							complete_rows[y] = false;
						}
					}
				}

				int row_count = 0;
				for (int i = 0; i < GAME_BOARD_ROWS; i++)
				{
					if (complete_rows[i])
					{
						//increment row counter
						row_count++;

						//move all rows above down by one
						for (int y = i - 1; y >= 0; y--)
						{
							for (int x = 0; x < GAME_BOARD_COLUMNS; x++)
							{
								this->m_board_main->SetTile(x, y + 1, this->m_board_main->GetTile(x, y));
							}
						}
					}
				}

				//TODO: increment score, session row counter
			}

			this->m_rtc_last_move_down = rtc_ticks;
		}
	}

	if (copy_vram)
	{
		Bdisp_PutDisp_DD();
	}
}