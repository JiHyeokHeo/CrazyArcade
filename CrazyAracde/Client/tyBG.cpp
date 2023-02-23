#include "tyBG.h"
#include "tySceneManager.h"
#include "tyResources.h"
#include "tyImage.h"


namespace ty
{
	BG::BG()
	{
	}
	BG::~BG()
	{
	}
	void BG::Initialize()
	{
		mImage = Resources::Load<Image>(L"Play_bg", L"..\\Resources\\play_bg.bmp");

		GameObject::Initialize();
	}
	void BG::Update()
	{
		GameObject::Update();
	}
	void BG::Render(HDC hdc)
	{
		BitBlt(hdc, 250, 50, mImage->GetWidth(), mImage->GetHeight(), mImage->GetHdc(), 0, 0, SRCCOPY);
	}
	void BG::Release()
	{
	}
}