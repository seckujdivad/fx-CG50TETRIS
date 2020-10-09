#pragma once

#include "TileType.h"

class Board;

enum class TetronimoType
{
	I,
	O,
	T,
	J,
	L,
	S,
	Z
};

TetronimoType GetTetronimoType();

enum class Direction
{
	Up,
	Right,
	Down,
	Left
};

Direction GetDirection();
void Translate(Direction direction, int& x, int& y);

struct TetronimoLayout //literally just a wrapper to allow returning and direct assignment of a 4x4 array
{
	bool data[4 * 4];
};

constexpr bool QueryLayout(TetronimoLayout layout, int x, int y);

class Tetronimo
{
private:
	Board* m_target;

	int m_x;
	int m_y;

	TileType m_tile_type;
	TileType m_blank_tile_type = TileType::Blank;
	TetronimoType m_tetronimo_type;

	Direction m_rotation = Direction::Up;

	TetronimoLayout GetTetronimo(int x, int y, Direction rotation) const;

	void Draw() const;
	void Draw(int x, int y, Direction rotation, TileType tile_type) const;
	void IncrementalDraw(int old_x, int old_y, Direction old_rotation) const;

	bool TestPosition(int x, int y, Direction rotation) const;

public:
	Tetronimo(int x, int y, Board* target, TileType tile_type, TetronimoType tetronimo_type);

	TetronimoType GetType() const;
	
	TileType GetTileType() const;

	bool CanRotate(Direction rotation) const;
	void Rotate(Direction rotation);
	Direction GetRotation() const;

	bool CanMove(Direction direction) const;
	void Move(Direction direction);
	void JumpToPosition(int x, int y);
	int GetX() const;
	int GetY() const;

	void Erase() const;
};
