#include "tyLobby_BG.h"
#include "tySceneManager.h"
#include "tyResources.h"
#include "tyTransform.h"

namespace ty
{
	Lobby_BG::Lobby_BG()
	{
	}
	Lobby_BG::~Lobby_BG()
	{
	}
	void Lobby_BG::Initialize()
	{
		mImage = Resources::Load<Image>(L"Lobby_BG", L"..\\Resources\\Bg\\lobby_scene_bg.bmp");
		
		GameObject::Initialize();
	}
	void Lobby_BG::Update()
	{
		GameObject::Update();
	}
	void Lobby_BG::Render(HDC hdc)
	{
		StretchBlt(hdc, 210, 0, mImage->GetWidth()+100, mImage->GetHeight()+100, mImage->GetHdc()
			, 0, 0, mImage->GetWidth(), mImage->GetHeight(), SRCCOPY);
	}
	void Lobby_BG::Release()
	{
	}
}