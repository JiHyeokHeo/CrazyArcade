#include "tyTilePalatte.h"
#include "tyResources.h"
#include "tyinput.h"

namespace ty
{
	Image* TilePalatte::mImage = nullptr;
	std::unordered_map<UINT64, Tile*> mTiles = {};
	UINT TilePalatte::mIndex = -1;

	void TilePalatte::Initialize()
	{
		 mImage = Resources::Find<Image>(L"TileAtlas");
	}

	void TilePalatte::Update()
	{
	}
	void TilePalatte::Render(HDC hdc)
	{
	}
	void TilePalatte::CreateTile(int index, Vector2 pos)
	{
		Tile* test = object::Instantiate<Tile>(eLayerType::Tile);
		test->InitializeTile(mImage, index);

		Vector2 tilePos(pos.x * TILE_SIZE_X, pos.y * TILE_SIZE_Y);
		test->GetComponent<Transform>()->SetPos(tilePos);

	}
	void TilePalatte::CreateTiles(int index, UINT width, UINT height)
	{
	}
	void TilePalatte::Save()
	{
	}
	void TilePalatte::Load()
	{
	}
	Vector2 TilePalatte::GetTilePos(Vector2 mousePos)
	{
		int indexY = mousePos.y / TILE_SIZE_Y;
		int indexX = mousePos.x / TILE_SIZE_X;

		return Vector2(indexX, indexY);
	}
}