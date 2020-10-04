#pragma once

#include "utilities.h"
#include "TileType.h"

class Board
{
private:
	int m_board_x;
	int m_board_y;

	int m_board_start_x;
	int m_board_start_y;

	int m_tile_x;
	int m_tile_y;

	TileType* m_tiles;
	bool m_incremental_draw = true;
	int m_border_width;

public:
	Board(int board_x, int board_y, int tile_x, int tile_y, int board_start_x, int board_start_y, int border_width = 3);

	void SetTile(int x, int y, TileType type);
	TileType GetTile(int x, int y) const;
	TileType& GetTile(int x, int y);

	void DrawAll(bool copy_vram = false) const;
	void DrawTile(int x, int y, bool copy_vram = false) const;
	
	void SetIncrementalDraw(bool enable);
	bool IncrementalDrawEnabled() const;
};
