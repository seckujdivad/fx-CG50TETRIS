#include "MenuPage.h"

#include <fxcg/display.h>
#include <fxcg/keyboard.h>

#include "../PageManager.h"
#include "../utilities.h"

MenuPage::MenuPage(PageManager* page_manager) : Page(page_manager)
{
	this->m_vtable_parent = this;
	this->m_vfunc_FocusGained = [](void* ptr, PageType previous_page){return static_cast<MenuPage*>(ptr)->FocusGained(previous_page);};
	this->m_vfunc_FocusLost = [](void* ptr, PageType new_page){return static_cast<MenuPage*>(ptr)->FocusLost(new_page);};
	this->m_vfunc_Update = [](void* ptr){return static_cast<MenuPage*>(ptr)->Update();};

	this->m_board = new Board(39, 22, 10, 10, 0, 0);

	for (int x = 0; x < 39; x++)
	{
		for (int y = 0; y < 22; y++)
		{
			this->m_board->SetTile(x, y, static_cast<TileType>(((x + (x * y) - (x / (y + 1))) % 3) + 1));
		}
	}
}

void MenuPage::FocusGained(PageType previous_page)
{
	EnableStatusArea(3); //disable the status bar at the top of the screen
	Bdisp_AllClr_VRAM();

	this->m_board->DrawAll();

	PrintXY(9, 3, "  TETRIS", TEXT_MODE_TRANSPARENT_BACKGROUND, TEXT_COLOR_WHITE);

	PrintXY(1, 6, "  1: Play", TEXT_MODE_TRANSPARENT_BACKGROUND, TEXT_COLOR_WHITE);
}

void MenuPage::FocusLost(PageType new_page)
{

}

void MenuPage::Update()
{
	int key;
	GetKey(&key);

	if (key == KEY_CHAR_1)
	{
		this->m_page_manager->SwitchPage(PageType::Game);
	}
}