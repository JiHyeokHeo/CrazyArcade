#pragma once
#include "tyBazzi.h"

namespace ty::TileBomb
{
	Vector2 SetPos(Vector2 mPos)
	{
		int x = 30 + ((int)mPos.x / (TILE_SIZE_X)) * (TILE_SIZE_X);
		int y = 60 + ((int)mPos.y / (TILE_SIZE_Y)) * (TILE_SIZE_Y);
		return Vector2(x, y);
	}
	Vector2 SetIndex(Vector2 mPos)
	{
		int x = ((int)mPos.x / (TILE_SIZE_X + 0.01));
		int y = ((int)mPos.y / (TILE_SIZE_Y + 0.01));
		return Vector2((int)x, (int)y);
	}

	Vector2 SetColIndex(Vector2 mPos)
	{
		int x = (((int)mPos.x - 30) / (TILE_SIZE_X + 0.01));
		int y = (((int)mPos.y - 60) / (TILE_SIZE_Y + 0.01));
		return Vector2((int)x, (int)y);
	}
}