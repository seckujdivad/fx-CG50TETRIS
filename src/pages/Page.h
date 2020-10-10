#pragma once

#include "PageType.h"

class PageManager;

class Page
{
private:

protected:
	PageManager* m_page_manager;

	void* m_vtable_parent; //only one parent is needed for all virtual functions since there should only be one inheritance in the chain and all must be overridden
	void (*m_vfunc_FocusGained)(void*, PageType);
	void (*m_vfunc_FocusLost)(void*, PageType);
	void (*m_vfunc_Update)(void*);

public:
	Page(PageManager* page_manager);
	//there is no need for a virtual destructor system since pages will never be deleted (the program never exits)

	//non-virtual methods

	//virtual methods
	void FocusGained(PageType previous_page);
	void FocusLost(PageType new_page);

	void Update();
};