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
		mImage = Resources::Load<Image>(L"Logo_BG", L"..\\Resources\\Logo.bmp");

		GameObject::Initialize();
	}
	void Logo_BG::Update()
	{
		GameObject::Update();
	}
	void Logo_BG::Render(HDC hdc)
	{
			TransparentBlt(hdc, 0, 0, 1600, 900, mImage->GetHdc(),
			0, 0, mImage->GetWidth(), mImage->GetHeight(), RGB(255, 0, 255));
	}
	void Logo_BG::Release()
	{

	}
}