#include "tyPirateNormalTile.h"
#include "tySceneManager.h"
#include "tyResources.h"
#include "tyTransform.h"

namespace ty
{
	PirateNormalTile::PirateNormalTile()
	{
	}
	PirateNormalTile::~PirateNormalTile()
	{
	}
	void PirateNormalTile::Initialize()
	{
		mImage = Resources::Load<Image>(L"PirateNormTile", L"..\\Resources\\Bg\\PirateNormalTile.bmp");
	}
	void PirateNormalTile::Update()
	{
	}
	void PirateNormalTile::Render(HDC hdc)
	{
		BitBlt(hdc, 30, 60
			, mImage->GetWidth()
			, mImage->GetHeight()
			, mImage->GetHdc()
			, 0, 0
			, SRCCOPY
		);
	}
	void PirateNormalTile::Release()
	{
	}
}