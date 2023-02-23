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
		mImage = Resources::Load<Image>(L"Play_BG", L"..\\Resources\\play_bg.bmp");

		GameObject::Initialize();
	}
	void Play_BG::Update()
	{
		GameObject::Update();
	}
	void Play_BG::Render(HDC hdc)
	{
		BitBlt(hdc, 0, 0, mImage->GetWidth(), mImage->GetHeight(), mImage->GetHdc(), 0, 0, SRCCOPY);
	}
	void Play_BG::Release()
	{
	}
}