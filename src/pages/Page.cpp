#include "Page.h"

#include "../PageManager.h"

Page::Page(PageManager* page_manager) : m_page_manager(page_manager)
{

}

void Page::FocusGained(PageType previous_page)
{
	this->m_vfunc_FocusGained(this->m_vtable_parent, previous_page);
}

void Page::FocusLost(PageType new_page)
{
	this->m_vfunc_FocusLost(this->m_vtable_parent, new_page);
}

void Page::Update()
{
	this->m_vfunc_Update(this->m_vtable_parent);
}