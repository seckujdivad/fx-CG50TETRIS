#pragma once

#include "Page.h"

class Board;
class Tetronimo;

const int GAME_BOARD_ROWS = 30;
const int GAME_BOARD_COLUMNS = 10;

class GamePage : public Page
{
private:
	Board* m_board_main;
	Tetronimo* m_tetronimo_main;

	Board* m_board_nextbox;
	Tetronimo* m_tetronimo_nextbox;

	int m_rtc_last_move_down;

public:
	GamePage(PageManager* page_manager);

	void FocusGained(PageType previous_page);
	void FocusLost(PageType new_page);

	void Update();
};
