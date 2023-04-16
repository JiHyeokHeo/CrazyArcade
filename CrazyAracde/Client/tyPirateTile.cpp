#include "tyPirateTile.h"
#include "tySceneManager.h"
#include "tyResources.h"
#include "tyTransform.h"


namespace ty
{
	PirateTile::PirateTile()
	{
	}
	PirateTile::~PirateTile()
	{
	}
	void PirateTile::Initialize()
	{
		mImage = Resources::Load<Image>(L"PirateTile", L"..\\Resources\\Bg\\PirateTile.bmp");
	}
	void PirateTile::Update()
	{
	}
	void PirateTile::Render(HDC hdc)
	{
		BitBlt(hdc, 30, 60
			, mImage->GetWidth()
			, mImage->GetHeight()
			, mImage->GetHdc()
			, 0, 0
			, SRCCOPY
		);
	}
	void PirateTile::Release()
	{
	}
}