#include "tyBGInstance.h"
#include "tyEnum.h"
#include "tyResources.h"
#include "tyImage.h"

namespace ty
{
	BGInstance::BGInstance(eBGType type)
		: mImage(nullptr)
		, mBGType(type)
	{
	}
	BGInstance::~BGInstance()
	{
	
	}
	void BGInstance::Initialize()
	{
		switch (mBGType)
		{
		case eBGType::Logo:
			mImage = Resources::Load<Image>(L"Lobby_BG", L"..\\Resources\\Bg\\Lobby.bmp");
			break;
		case eBGType::Lobby:
			mImage = Resources::Load<Image>(L"Lobby_BG", L"..\\Resources\\Bg\\Lobby.bmp");
			break;
		case eBGType::Login:
			mImage = Resources::Load<Image>(L"Login_BG", L"..\\Resources\\Bg\\login_scene_bg.bmp");
			break;
		case eBGType::Play:
			mImage = Resources::Load<Image>(L"Play_BG", L"..\\Resources\\Bg\\play.bmp");
			break;
		case eBGType::None:
			break;
		default:
			break;
		}
	}
	void BGInstance::Update()
	{
		//GameObject::Update();
	}
	void BGInstance::Render(HDC hdc)
	{
		StretchBlt(hdc, 0, 0, mImage->GetWidth() * 1.5f, mImage->GetHeight() * 1.5f, mImage->GetHdc()
			, 0, 0, mImage->GetWidth(), mImage->GetHeight(), SRCCOPY);
		//GameObject::Render(hdc);
	}
	void BGInstance::Release()
	{
	}
}