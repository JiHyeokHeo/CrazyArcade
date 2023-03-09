#include "tyPlag_BG.h"
#include "tySceneManager.h"
#include "tyResources.h"



namespace ty
{
	Play_BG::Play_BG()
	{
	}
	Play_BG::~Play_BG()
	{
	}
	void Play_BG::Initialize()
	{
		mImage = Resources::Load<Image>(L"Play_BG", L"..\\Resources\\Bg\\play.bmp");

		GameObject::Initialize();
	}
	void Play_BG::Update()
	{
		GameObject::Update();
	}
	void Play_BG::Render(HDC hdc)
	{
		StretchBlt(hdc, 0, 0, mImage->GetWidth()*1.5f, mImage->GetHeight()*1.5f
			, mImage->GetHdc(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), SRCCOPY);
	}
	void Play_BG::Release()
	{
	}
}