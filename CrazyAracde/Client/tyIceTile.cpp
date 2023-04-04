#include "tyIceTile.h"
#include "tySceneManager.h"
#include "tyResources.h"
#include "tyTransform.h"

namespace ty
{
	IceTile::IceTile()
	{
	}
	IceTile::~IceTile()
	{
	}
	void IceTile::Initialize()
	{
		mImage = Resources::Load<Image>(L"ICEScene", L"..\\Resources\\Bg\\ICETILE.bmp");
	}
	void IceTile::Update()
	{
	}
	void IceTile::Render(HDC hdc)
	{
		BitBlt(hdc, 30, 60
			, mImage->GetWidth()
			, mImage->GetHeight()
			, mImage->GetHdc()
			, 0, 0
			, SRCCOPY
			);
	}
	void IceTile::Release()
	{
	}
}