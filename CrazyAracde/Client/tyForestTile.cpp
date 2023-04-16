#include "tyForestTile.h"
#include "tySceneManager.h"
#include "tyResources.h"
#include "tyTransform.h"


namespace ty
{
	ForestTile::ForestTile()
	{
	}
	ForestTile::~ForestTile()
	{
	}
	void ForestTile::Initialize()
	{
		mImage = Resources::Load<Image>(L"ForestTile", L"..\\Resources\\Bg\\ForestTile.bmp");
	}
	void ForestTile::Update()
	{
	}
	void ForestTile::Render(HDC hdc)
	{
		BitBlt(hdc, 30, 60
			, mImage->GetWidth()
			, mImage->GetHeight()
			, mImage->GetHdc()
			, 0, 0
			, SRCCOPY
		);
	}
	void ForestTile::Release()
	{
	}
}