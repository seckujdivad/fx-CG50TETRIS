#include "TileType.h"

#include "../utilities.h"

TileType GetTileType()
{
	return static_cast<TileType>(RTC_rand(1, 4));
}