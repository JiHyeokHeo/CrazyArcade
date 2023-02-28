#include "tyLobby_BG.h"
#include "tySceneManager.h"
#include "tyResources.h"


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
		mImage = Resources::Load<Image>(L"Lobby_BG", L"..\\Resources\\lobby_scene_bg.bmp");

		GameObject::Initialize();
	}
	void Lobby_BG::Update()
	{
		GameObject::Update();
	}
	void Lobby_BG::Render(HDC hdc)
	{
		//BitBlt(hdc, 0, 0, mImage->GetWidth(), mImage->GetHeight(), mImage->GetHdc(), 0, 0, SRCCOPY);
	}
	void Lobby_BG::Release()
	{
	}
}