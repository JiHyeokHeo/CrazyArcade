#pragma once
#include "tyBazzi.h"

namespace ty::TileBomb
{
	Vector2 SetPos(Vector2 mPos)
	{
		int x = 30 + ((int)mPos.x / (TILE_SIZE_X + 1)) * TILE_SIZE_X;
		int y = 60 + ((int)mPos.y / (TILE_SIZE_Y + 1)) * TILE_SIZE_Y;
		return Vector2(x, y);
	}
	/*Vector2 SetIndex(Vector2 mPos)
	{
		int x = 
	}*/
}