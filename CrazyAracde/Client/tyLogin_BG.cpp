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
		mImage = Resources::Load<Image>(L"Login_BG", L"..\\Resources\\login_scene_bg.bmp");
		GameObject::Initialize();
	}
	void Login_BG::Update()
	{
		
		GameObject::Update();
	}
	void Login_BG::Render(HDC hdc)
	{
		TransparentBlt(hdc, 0, 0, 1600, 900, mImage->GetHdc(),
			0, 0, mImage->GetWidth(), mImage->GetHeight(), RGB(255, 0, 255));
	}
	void Login_BG::Release()
	{
	}
}