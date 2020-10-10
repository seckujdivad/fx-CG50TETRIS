#pragma once

#include "Page.h"

#include "../tetris/Board.h"

class MenuPage : public Page
{
private:
	Board* m_board;

public:
	MenuPage(PageManager* page_manager);

	void FocusGained(PageType previous_page);
	void FocusLost(PageType new_page);

	void Update();
};
