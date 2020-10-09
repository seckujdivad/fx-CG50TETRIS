#pragma once

#include "Page.h"

class MenuPage : public Page
{
public:
	MenuPage(PageManager* page_manager);

	void FocusGained(PageType previous_page);
	void FocusLost(PageType new_page);

	void Update();
};
