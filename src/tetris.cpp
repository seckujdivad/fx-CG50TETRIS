#include <fxcg/display.h>
#include <fxcg/keyboard.h>

#include "utilities.h"
#include "Board.h"
#include "Tetronimo.h"
 
int main()
{
	Bdisp_EnableColor(1);
	Bdisp_AllClr_VRAM();

	Board board(10, 10, 10, 10, 10, 30);
	board.SetIncrementalDraw(true);
	board.SetTile(0, 0, TileType::Blue);
	board.SetTile(0, 1, TileType::Red);
	board.SetTile(9, 9, TileType::Green);

	Tetronimo* tetronimo = new Tetronimo(3, 3, &board, TileType::Blue, GetTetronimoType());

	Bdisp_PutDisp_DD(); //copy vram to lcd

	int key;
	while (true)
	{
		GetKey(&key);
		if (key == KEY_CTRL_EXE)
		{
			tetronimo->Erase();
			delete tetronimo;

			tetronimo = new Tetronimo(3, 3, &board, static_cast<TileType>(RTC_rand(3) + 1), GetTetronimoType());
		}
	}
 
	return 0;
}
