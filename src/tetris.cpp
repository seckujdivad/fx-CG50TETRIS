#include <fxcg/display.h>
#include <fxcg/keyboard.h>

#include "utilities.h"
#include "Board.h"
 
int main()
{
	Bdisp_EnableColor(1);

	int key;
	 
	Bdisp_AllClr_VRAM();
	Print_OS("Press EXE to exit", 0, 0);

	Board board(10, 10, 10, 10, 10, 30);
	board.SetTile(0, 0, TileType::Blue);
	board.SetTile(0, 1, TileType::Red);
	board.SetTile(9, 9, TileType::Green);
	Bdisp_PutDisp_DD();

	while (1) {
		GetKey(&key);

		if (key == KEY_CTRL_EXE) {
			break;
		}
	}
 
	return 0;
}
