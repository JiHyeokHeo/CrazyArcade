#pragma once
#include "tyBazzi.h"

namespace ty::TileBomb
{
	Vector2 SetPos(Vector2 mPos)
	{
		int x = 21 + ((int)mPos.x / (TILE_SIZE_X)) * (TILE_SIZE_X - 0.5f);
		int y = 41 + ((int)mPos.y / (TILE_SIZE_Y)) * (TILE_SIZE_Y - 0.5f);
		return Vector2(x, y);
	}
	Vector2 SetIndex(Vector2 mPos)
	{
		int x = ((int)mPos.x / (TILE_SIZE_X));
		int y = ((int)mPos.y / (TILE_SIZE_Y));
		return Vector2((int)x, (int)y);
	}


}