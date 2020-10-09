#pragma once

#include "Page.h"

class GamePage : public Page
{
public:
	GamePage(PageManager* page_manager);

	void FocusGained(PageType previous_page);
	void FocusLost(PageType new_page);

	void Update();
};
