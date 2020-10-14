#include "Board.h"

#include <fxcg/display.h>

#include "../utilities.h"

Board::Board(int board_x, int board_y, int tile_x, int tile_y, int board_start_x, int board_start_y, int border_width) :
	m_board_x(board_x),
	m_board_y(board_y),
	m_board_start_x(board_start_x),
	m_board_start_y(board_start_y),
	m_tile_x(tile_x),
	m_tile_y(tile_y),
	m_border_width(border_width)
{
	this->m_tiles = new TileType [board_x * board_y];
}

Board::~Board()
{
	delete[] this->m_tiles;
}

void Board::SetTile(int x, int y, TileType type)
{
	if (this->GetTile(x, y) != type)
	{
		this->GetTile(x, y) = type;

		if (this->m_incremental_draw)
		{
			this->DrawTile(x, y);
		}
	}
}

TileType Board::GetTile(int x, int y) const
{
	return this->m_tiles[(x * this->m_board_x) + y]; 
}

TileType& Board::GetTile(int x, int y)
{
	return this->m_tiles[(x * this->m_board_x) + y];
}

void Board::DrawAll(bool copy_vram) const
{
	for (int x = 0; x < this->m_board_x; x++)
	{
		for (int y = 0; y < this->m_board_y; y++)
		{
			this->DrawTile(x, y, false); //draw each tile again, explicity don't copy the vram to the LCD on each tile and defer to the end if required
		}
	}

	if (copy_vram)
	{
		Bdisp_PutDisp_DD(); //copy pixel writes from vram to the LCD
	}
}

void Board::DrawTile(int x, int y, bool copy_vram) const
{
	int start_x = this->m_board_start_x + (x * this->m_tile_x);
	int end_x = start_x + this->m_tile_x;
	int start_y = this->m_board_start_y + (y * this->m_tile_y);
	int end_y = start_y + this->m_tile_y;

	color_t primary_colour;
	color_t secondary_colour;

	if (this->GetTile(x, y) == TileType::Red)
	{
		primary_colour = COLOR_RED;
		secondary_colour = COLOR_DARKRED;
	}

	switch (this->GetTile(x, y))
	{
		case TileType::Blank:
			primary_colour = COLOR_WHITE;
			secondary_colour = COLOR_WHITE;
			break;

		case TileType::Red:
			primary_colour = COLOR_RED;
			secondary_colour = COLOR_DARKRED;
			break;

		case TileType::Green:
			primary_colour = COLOR_GREEN;
			secondary_colour = COLOR_DARKGREEN;
			break;
		
		case TileType::Blue:
			primary_colour = COLOR_BLUE;
			secondary_colour = COLOR_DARKBLUE;
			break;
		
		default:
			primary_colour = COLOR_BLACK;
			secondary_colour = COLOR_BLACK;
			break;
	}

	for (int draw_y = max(start_y, 0); draw_y < min(end_y, LCD_HEIGHT_PX); draw_y++)
	{
		for (int draw_x = max(start_x, 0); draw_x < min(end_x, LCD_WIDTH_PX); draw_x++)
		{
			color_t colour;
			if (
				((start_x <= draw_x) && (draw_x < start_x + this->m_border_width))
				|| ((end_x - this->m_border_width <= draw_x) && (draw_x <= end_x))
				|| ((start_y <= draw_y) && (draw_y < start_y + this->m_border_width))
				|| ((end_y - this->m_border_width <= draw_y) && (draw_y <= end_y))
			)
			{
				colour = secondary_colour;
			}
			else
			{
				colour = primary_colour;
			}

			Bdisp_SetPoint_VRAM(draw_x, draw_y, colour);
		}
	}

	if (copy_vram)
	{
		Bdisp_PutDisp_DD(); //copy pixel writes from vram to the LCD
	}
}

void Board::SetIncrementalDraw(bool enable)
{
	this->m_incremental_draw = enable;
}

bool Board::IncrementalDrawEnabled() const
{
	return this->m_incremental_draw;
}

int Board::GetTileMaxX() const
{
	return this->m_board_x;
}

int Board::GetTileMaxY() const
{
	this->m_board_y;
}
