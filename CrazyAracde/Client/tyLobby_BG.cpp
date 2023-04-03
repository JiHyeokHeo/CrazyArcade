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
		mImage = Resources::Load<Image>(L"Lobby_BG", L"..\\Resources\\Bg\\Lobby.bmp");
		
		//GameObject::Initialize();
	}
	void Lobby_BG::Update()
	{
		GameObject::Update();
	}
	void Lobby_BG::Render(HDC hdc)
	{
		StretchBlt(hdc, 0, 0, mImage->GetWidth()*1.5f, mImage->GetHeight()*1.5f, mImage->GetHdc()
			, 0, 0, mImage->GetWidth(), mImage->GetHeight(), SRCCOPY);
		GameObject::Render(hdc);
	}
	void Lobby_BG::Release()
	{
	}
}