#include "tyLogin_BG.h"
#include "tySceneManager.h"
#include "tyResources.h"


namespace ty
{
	Login_BG::Login_BG()
	{
	}
	Login_BG::~Login_BG()
	{
	}
	void Login_BG::Initialize()
	{
		mImage = Resources::Load<Image>(L"Login_BG", L"..\\Resources\\Bg\\login_scene_bg.bmp");
		//GameObject::Initialize();
	}
	void Login_BG::Update()
	{
		
	}
	void Login_BG::Render(HDC hdc)
	{
		StretchBlt(hdc, 0, 0, mImage->GetWidth() +160, mImage->GetHeight() +160, mImage->GetHdc()
			, 0, 0, mImage->GetWidth(), mImage->GetHeight(), SRCCOPY);
	}
	void Login_BG::Release()
	{
	}
}