#include "tyBazziLobbyUI.h"
#include "tySceneManager.h"
#include "tyResources.h"
#include "tyTransform.h"
#include "tyImage.h"
#include "tyinput.h"
#include "tyObject.h"
#include "tyLobbyScene.h"

namespace ty
{
	BazziLobbyUI::BazziLobbyUI()
	{
	}
	BazziLobbyUI::~BazziLobbyUI()
	{
	}
	void BazziLobbyUI::Initialize()
	{
		mImage = Resources::Load<Image>(L"BazziLobbyUI", L"..\\Resources\\UI\\bazzi_LobbyUI.bmp");
	}
	void BazziLobbyUI::Update()
	{
		GameObject::Update();
	}
	void BazziLobbyUI::Render(HDC hdc)
	{
		TransparentBlt(hdc, 70, 180, mImage->GetWidth() * 1.5f, mImage->GetHeight() * 1.5f, mImage->GetHdc()
			, 0, 0, mImage->GetWidth(), mImage->GetHeight(), RGB(255, 0, 255));
		GameObject::Render(hdc);
		
	}
	void BazziLobbyUI::Release()
	{
	}
}