#include "tyToyTile.h"
#include "tySceneManager.h"
#include "tyResources.h"
#include "tyTransform.h"


namespace ty
{
	ToyTile::ToyTile()
	{
	}
	ToyTile::~ToyTile()
	{
	}
	void ToyTile::Initialize()
	{
		mImage = Resources::Load<Image>(L"ForestTile", L"..\\Resources\\Bg\\PirateTile.bmp");
	}
	void ToyTile::Update()
	{
	}
	void ToyTile::Render(HDC hdc)
	{
		BitBlt(hdc, 30, 60
			, mImage->GetWidth()
			, mImage->GetHeight()
			, mImage->GetHdc()
			, 0, 0
			, SRCCOPY
		);
	}
	void ToyTile::Release()
	{
	}
}