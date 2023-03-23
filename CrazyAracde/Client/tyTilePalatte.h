#pragma once
#include "tyTile.h"
#include "tyImage.h"
#include "tyObject.h"

namespace ty
{
	union TileID
	{
		struct
		{
			UINT32 x;
			UINT32 y;
		};
		UINT64 id;
	};


	class TilePalatte
	{
	public:
		static void Initialize();
		static void Update();
		static void Render(HDC hdc);

		static void CreateTile(int index, Vector2 pos);
		static void CreateTiles(int index, UINT width, UINT height);
		static void Save();
		static void Load();

		static Vector2 GetTilePos(Vector2 mousePos);
		static void SetIndex(UINT index) { mIndex = index; }
		static UINT GetIndex() { return mIndex; }

	private:
		static std::unordered_map<UINT64, Tile*> mTiles;
		static std::unordered_map<UINT64, Tile*> mObjects;
		static Image* mImage;
		static UINT mIndex;
	};

}
