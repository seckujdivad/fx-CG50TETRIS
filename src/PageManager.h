#pragma once

#include "pages/PageType.h"

class Page;

class PageManager
{
private:
	Page** m_pages;
	int m_pages_count;
	PageType m_pages_current = PageType::None;

public:
	PageManager();

	void Loop();

	Page*& GetPage(PageType type);

	void SwitchPage(PageType type);
};