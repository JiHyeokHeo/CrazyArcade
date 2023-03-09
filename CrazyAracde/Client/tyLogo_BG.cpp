#include "tyLogo_BG.h"
#include "tySceneManager.h"
#include "tyResources.h"
#include "tyImage.h"

namespace ty
{
	Logo_BG::Logo_BG()
	{
	}
	Logo_BG::~Logo_BG()
	{
	}
	void Logo_BG::Initialize()
	{
		mImage = Resources::Load<Image>(L"Logo_BG", L"..\\Resources\\Bg\\Logo.bmp");

		GameObject::Initialize();
	}
	void Logo_BG::Update()
	{
		GameObject::Update();
	}
	void Logo_BG::Render(HDC hdc)
	{
		StretchBlt(hdc, 0, 0, mImage->GetWidth()*1.43f, mImage->GetHeight()*1.43f
			, mImage->GetHdc(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), SRCCOPY);
	}
	void Logo_BG::Release()
	{

	}
}