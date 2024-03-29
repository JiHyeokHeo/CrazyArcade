#include "tyTilePalatte.h"
#include "tyResources.h"
#include "tyinput.h"
#include <commdlg.h>
#include "tyCollider.h"
#include "tyBazzi.h"

namespace ty
{
	Image* TilePalatte::mImage = nullptr;
	std::unordered_map<UINT64, Tile*> TilePalatte:: mTiles = {};
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
		Vector2 mousPos = Input::GetMousePos();
		//if (mousPos.x >= 1200.0f || mousPos.x <= 0.0f)
		//	return;
		//if (mousPos.y >= 900.0f || mousPos.y <= 0.0f)
		//	return;

		
		Tile* tile = object::Instantiate<Tile>(eLayerType::Tile);
		tile->InitializeTile(mImage, index, pos);

		
		Vector2 tilePos(30.0f + pos.x * TILE_SIZE_X, 60.0f + pos.y * TILE_SIZE_Y);
		tile->GetComponent<Transform>()->SetPos(tilePos);
	/*	if (index == 4)
		{
			tile->AddComponent<Collider>();
			tile->GetComponent<Collider>()->SetPos(tilePos);
			tile->GetComponent<Collider>()->SetSize(Vector2(TILE_SIZE_X, TILE_SIZE_Y));
			
		}*/
		TileID id;
		id.x = (UINT32)pos.x; // 좌표값이 즉 id가 된다
		id.y = (UINT32)pos.y;

		mTiles.insert(std::make_pair(id.id, tile)); // 신기방구 Union 관련
		

	}
	void TilePalatte::CreateTiles(int index, UINT width, UINT height)
	{
	}
	void TilePalatte::Save()
	{
		// open a file name
		OPENFILENAME ofn = {};

		wchar_t szFilePath[256] = {};

		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = NULL;
		ofn.lpstrFile = szFilePath;
		ofn.lpstrFile[0] = '\0';
		ofn.nMaxFile = 256;
		ofn.lpstrFilter = L"Tile\0*.tile\0";
		ofn.nFilterIndex = 1;
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFileTitle = 0;
		ofn.lpstrInitialDir = NULL;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

		if (false == GetSaveFileName(&ofn))
			return;

		// 파일 입출력
		FILE* file = nullptr;

		// 쓰기 모드로 열기
		_wfopen_s(&file, szFilePath, L"wb");

		if (nullptr == file)
			return;
		
		std::unordered_map<UINT64, Tile*>::iterator iter = mTiles.begin();
		for (; iter != mTiles.end(); iter++)
		{
			int index = iter->second->Index();
			fwrite(&index, sizeof(int), 1, file);

			TileID id;
			id.id = iter->first;
			fwrite(&id.id, sizeof(TileID), 1, file);

		}

		fclose(file);
	}
	void TilePalatte::Load(const wchar_t* stagenum)
	{
		OPENFILENAME ofn = {};
		wchar_t szFilePath[256] = L"..\\MapSave\\Map_";

		size_t filePathLen = wcslen(szFilePath);
		size_t stageNumLen = wcslen(stagenum);

		if (filePathLen + stageNumLen + 1 > 256)
			return;
		
		
		wcscat_s(szFilePath, 256 - filePathLen, stagenum);
		FILE* file = nullptr;
		_wfopen_s(&file, szFilePath, L"rb");
		if (file == nullptr)
			return;
		
	
		
		while (true)
		{
			
			int index = -1;
			TileID id;

			if (fread(&index, sizeof(int), 1, file) == NULL)
				break;
			if (fread(&id.id, sizeof(TileID), 1, file) == NULL)
				break;
		
			// 여기에다가 조건 추가
			CreateTile(index, Vector2(id.x, id.y));
		}

		fclose(file);
	}
	Vector2 TilePalatte::GetTilePos(Vector2 mousePos)
	{
		int indexY = (mousePos.y - 60) / TILE_SIZE_Y;
		int indexX = (mousePos.x - 30) / TILE_SIZE_X;

		return Vector2(indexX, indexY);
	}

	void TilePalatte::Clear()
	{
		for (int i = 0; i < 13; i++)
		{
			for (int j = 0; j < 15; j++)
			{
				SceneManager::GetMapIndex()[i][j] = 0;
			}
		}
	}

	void TilePalatte::TargetClear(Vector2 pos)
	{
		for (int i = 0; i < 13; i++)
		{
			for (int j = 0; j < 15; j++)
			{
				SceneManager::GetMapIndex()[i][j] = 0;
			}
		}

		TileID id;
		id.x = (UINT32)pos.x; // 좌표값이 즉 id가 된다
		id.y = (UINT32)pos.y;

		std::unordered_map<UINT64, Tile*>::iterator iter = mTiles.begin();
		
		
		for (; iter != mTiles.end(); iter++)
		{
			if (id.id == iter->first)
			{
6;				object::Destroy(iter->second);
			}
		}
	}
}