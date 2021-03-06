#include "Tetronimo.h"

#include "../utilities.h"

#include "Board.h"

Tetronimo::Tetronimo(int x, int y, Board* target, TileType tile_type, TetronimoType tetronimo_type) :
	m_target(target),
	m_x(x),
	m_y(y),
	m_tile_type(tile_type),
	m_tetronimo_type(tetronimo_type)
{
	this->Draw();
}

bool Tetronimo::CanRotate(Direction rotation) const
{
	return this->TestPosition(this->GetX(), this->GetY(), rotation);
}

void Tetronimo::Rotate(Direction rotation)
{
	Direction old_rotation = this->m_rotation;
	this->m_rotation = rotation;
	this->IncrementalDraw(this->GetX(), this->GetY(), old_rotation);
}

Direction Tetronimo::GetRotation() const
{
	return this->m_rotation;
}

bool Tetronimo::CanMove(Direction direction) const
{
	int potential_x = this->GetX();
	int potential_y = this->GetY();

	Translate(direction, potential_x, potential_y);

	return this->TestPosition(potential_x, potential_y, this->GetRotation());
}

void Tetronimo::Move(Direction direction)
{
	int x = this->GetX();
	int y = this->GetY();
	Translate(direction, x, y);
	this->JumpToPosition(x, y);
}

void Tetronimo::JumpToPosition(int x, int y)
{
	int old_x = this->GetX();
	int old_y = this->GetY();

	this->m_x = x;
	this->m_y = y;

	this->IncrementalDraw(old_x, old_y, this->GetRotation());
}

int Tetronimo::GetX() const
{
	return this->m_x;
}

int Tetronimo::GetY() const
{
	return this->m_y;
}

TetronimoLayout Tetronimo::GetTetronimo(int x, int y, Direction rotation) const
{
	if (this->GetType() == TetronimoType::I)
	{
		if ((this->GetRotation() == Direction::Up) || (this->GetRotation() == Direction::Down))
		{
			return {
				0, 0, 1, 0,
				0, 0, 1, 0,
				0, 0, 1, 0,
				0, 0, 1, 0
			};
		}
		else
		{
			return {
				0, 0, 0, 0,
				1, 1, 1, 1,
				0, 0, 0, 0,
				0, 0, 0, 0,
			};
		}
	}
	else if (this->GetType() == TetronimoType::T)
	{
		if (this->GetRotation() == Direction::Up)
		{
			return {
				0, 1, 0, 0,
				1, 1, 1, 0,
				0, 0, 0, 0,
				0, 0, 0, 0,
			};
		}
		else if (this->GetRotation() == Direction::Right)
		{
			return {
				0, 1, 0, 0,
				0, 1, 1, 0,
				0, 1, 0, 0,
				0, 0, 0, 0
			};
		}
		else if (this->GetRotation() == Direction::Down)
		{
			return {
				0, 0, 0, 0,
				1, 1, 1, 0,
				0, 1, 0, 0,
				0, 0, 0, 0
			};
		}
		else if (this->GetRotation() == Direction::Left)
		{
			return {
				0, 1, 0, 0,
				1, 1, 0, 0,
				0, 1, 0, 0,
				0, 0, 0, 0
			};
		}
	}
	else if (this->GetType() == TetronimoType::O)
	{
		return {
			0, 0, 0, 0,
			0, 1, 1, 0,
			0, 1, 1, 0,
			0, 0, 0, 0
		};
	}
	else if (this->GetType() == TetronimoType::J)
	{
		if (this->GetRotation() == Direction::Up)
		{
			return {
				0, 1, 0, 0,
				0, 1, 0, 0,
				1, 1, 0, 0,
				0, 0, 0, 0
			};
		}
		else if (this->GetRotation() == Direction::Right)
		{
			return {
				1, 0, 0, 0,
				1, 1, 1, 0,
				0, 0, 0, 0,
				0, 0, 0, 0
			};
		}
		else if (this->GetRotation() == Direction::Down)
		{
			return {
				0, 1, 1, 0,
				0, 1, 0, 0,
				0, 1, 0, 0,
				0, 0, 0, 0
			};
		}
		else if (this->GetRotation() == Direction::Left)
		{
			return {
				0, 0, 0, 0,
				1, 1, 1, 0,
				0, 0, 1, 0,
				0, 0, 0, 0
			};
		}
	}
	else if (this->GetType() == TetronimoType::L)
	{
		if (this->GetRotation() == Direction::Up)
		{
			return {
				0, 1, 0, 0,
				0, 1, 0, 0,
				0, 1, 1, 0,
				0, 0, 0, 0
			};
		}
		else if (this->GetRotation() == Direction::Right)
		{
			return {
				0, 0, 0, 0,
				1, 1, 1, 0,
				1, 0, 0, 0,
				0, 0, 0, 0
			};
		}
		else if (this->GetRotation() == Direction::Down)
		{
			return {
				1, 1, 0, 0,
				0, 1, 0, 0,
				0, 1, 0, 0,
				0, 0, 0, 0
			};
		}
		else if (this->GetRotation() == Direction::Left)
		{
			return {
				0, 0, 1, 0,
				1, 1, 1, 0,
				0, 0, 0, 0,
				0, 0, 0, 0
			};
		}
	}
	else if (this->GetType() == TetronimoType::S)
	{
		if ((this->GetRotation() == Direction::Up) || (this->GetRotation() == Direction::Down))
		{
			return {
				0, 0, 0, 0,
				0, 1, 1, 0,
				1, 1, 0, 0,
				0, 0, 0, 0
			};
		}
		else if ((this->GetRotation() == Direction::Right) || (this->GetRotation() == Direction::Left))
		{
			return {
				1, 0, 0, 0,
				1, 1, 0, 0,
				0, 1, 0, 0,
				0, 0, 0, 0
			};
		}
	}
	else if (this->GetType() == TetronimoType::Z)
	{
		if ((this->GetRotation() == Direction::Up) || (this->GetRotation() == Direction::Down))
		{
			return {
				0, 0, 0, 0,
				1, 1, 0, 0,
				0, 1, 1, 0,
				0, 0, 0, 0
			};
		}
		else if ((this->GetRotation() == Direction::Right) || (this->GetRotation() == Direction::Left))
		{
			return {
				0, 1, 0, 0,
				1, 1, 0, 0,
				1, 0, 0, 0,
				0, 0, 0, 0
			};
		}
	}

	return {
		1, 0, 1, 0,
		0, 1, 0, 1,
		1, 0, 1, 0,
		0, 1, 0, 1
	}; //error pattern, default (theoretically unreachable) state
}

void Tetronimo::Draw() const
{
	this->Draw(this->GetX(), this->GetY(), this->GetRotation(), this->GetTileType());
}

void Tetronimo::Draw(int x, int y, Direction rotation, TileType tile_type) const
{
	TetronimoLayout layout = this->GetTetronimo(x, y, rotation);

	for (int current_x = 0; current_x < 4; current_x++)
	{
		for (int current_y = 0; current_y < 4; current_y++)
		{
			if (QueryLayout(layout, current_x, current_y))
			{
				this->m_target->SetTile(x + current_x, y + current_y, tile_type);
			}
		}
	}
}

void Tetronimo::IncrementalDraw(int old_x, int old_y, Direction old_rotation) const
{
	if (!(
		(this->GetX() == old_x)
		&& (this->GetY() == old_y)
		&& (this->GetRotation() == old_rotation)
	))
	{
		this->Draw(old_x, old_y, old_rotation, this->m_blank_tile_type);
		this->Draw(this->GetX(), this->GetY(), this->GetRotation(), this->m_tile_type);
	}
}

TetronimoType Tetronimo::GetType() const
{
	return this->m_tetronimo_type;
}

bool Tetronimo::TestPosition(int x, int y, Direction rotation) const
{
	if ((x == this->GetX()) && (y == this->GetY()) && (rotation == this->GetRotation()))
	{
		return true;
	}
	else
	{
		TetronimoLayout new_layout = this->GetTetronimo(x, y, rotation);
		TetronimoLayout old_layout = this->GetTetronimo(this->GetX(), this->GetY(), this->GetRotation());

		int x_diff = x - this->GetX();
		int y_diff = y - this->GetY();

		int max_board_x = this->m_target->GetTileMaxX();
		int max_board_y = this->m_target->GetTileMaxY();

		for (int current_x = 0; current_x < 4; current_x++)
		{
			for (int current_y = 0; current_y < 4; current_y++)
			{
				if (QueryLayout(new_layout, current_x, current_y) && !QueryLayout(old_layout, current_x + x_diff, current_y + y_diff))
				{
					int query_x = x + current_x;
					int query_y = y + current_y;

					if ((query_x < 0) || (query_x >= max_board_x) || (query_y < 0) || (query_y >= max_board_y))
					{
						return false;
					}

					if (this->m_target->GetTile(query_x, query_y) != this->m_blank_tile_type)
					{
						return false;
					}
				}
			}
		}

		return true;
	}
}

constexpr bool QueryLayout(TetronimoLayout layout, int x, int y)
{
	return layout.data[(y * 4) + x];
}

TetronimoType GetTetronimoType()
{
	return static_cast<TetronimoType>(RTC_rand(7));
}

Direction GetDirection()
{
	return static_cast<Direction>(RTC_rand(4));
}

TileType Tetronimo::GetTileType() const
{
	return this->m_tile_type;
}

void Translate(Direction direction, int& x, int& y)
{
	switch (direction)
	{
		case Direction::Up:
			y--;
			break;
		
		case Direction::Down:
			y++;
			break;
		
		case Direction::Left:
			x--;
			break;
		
		case Direction::Right:
			x++;
			break;
		
		default:
			break;
	}
}

void Tetronimo::Erase() const
{
	this->Draw(this->GetX(), this->GetY(), this->GetRotation(), this->m_blank_tile_type);
}