#include "GamePage.h"

#include <fxcg/display.h>
#include <fxcg/keyboard.h>

#include "../PageManager.h"

GamePage::GamePage(PageManager* page_manager) : Page(page_manager)
{
	this->m_vtable_parent = this;
	this->m_vfunc_FocusGained = [](void* ptr, PageType previous_page){return static_cast<GamePage*>(ptr)->FocusGained(previous_page);};
	this->m_vfunc_FocusLost = [](void* ptr, PageType new_page){return static_cast<GamePage*>(ptr)->FocusLost(new_page);};
	this->m_vfunc_Update = [](void* ptr){return static_cast<GamePage*>(ptr)->Update();};
}

void GamePage::FocusGained(PageType previous_page)
{
	Bdisp_AllClr_VRAM();

	PrintXY(2, 2, "  Game", TEXT_MODE_NORMAL, TEXT_COLOR_BLACK);
}

void GamePage::FocusLost(PageType new_page)
{

}

void GamePage::Update()
{
	int key;
	GetKey(&key);

	if (key == KEY_CHAR_0)
	{
		this->m_page_manager->SwitchPage(PageType::Menu);
	}
}