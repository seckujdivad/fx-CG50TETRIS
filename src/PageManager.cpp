#include "PageManager.h"

#include <fxcg/display.h>

#include "utilities.h"
#include "pages/MenuPage.h"
#include "pages/GamePage.h"

PageManager::PageManager()
{
	this->m_pages_count = 2;
	this->m_pages = new Page* [this->m_pages_count];

	this->GetPage(PageType::Menu) = new MenuPage(this);
	this->GetPage(PageType::Game) = new GamePage(this);

	this->SwitchPage(PageType::Menu);
}

void PageManager::Loop()
{
	while (true)
	{
		this->GetPage(this->m_pages_current)->Update();
	}
}

Page*& PageManager::GetPage(PageType type)
{
	if (type == PageType::None)
	{
		AUX_DisplayErrorMessage(22); //application error
		abort();
	}
	else
	{
		return this->m_pages[static_cast<int>(type) - 1];
	}
}

void PageManager::SwitchPage(PageType type)
{
	if (type != this->m_pages_current)
	{
		if (this->m_pages_current != PageType::None)
		{
			this->GetPage(this->m_pages_current)->FocusLost(type);
		}
		
		this->GetPage(type)->FocusGained(this->m_pages_current);

		this->m_pages_current = type;
	}
}