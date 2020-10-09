#include <fxcg/display.h>

#include "PageManager.h"
 
int main()
{
	Bdisp_EnableColor(1);
	Bdisp_AllClr_VRAM();

	PageManager page_manager;
	page_manager.Loop(); //this should never return
 
	return 0; //this part of the program should never be reached or the addin won't reopen
}
