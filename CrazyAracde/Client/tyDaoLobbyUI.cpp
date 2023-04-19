#include "tyDaoLobbyUI.h"
#include "tySceneManager.h"
#include "tyResources.h"
#include "tyTransform.h"
#include "tyImage.h"
#include "tyinput.h"
#include "tyObject.h"
#include "tyLobbyScene.h"

namespace ty
{
	DaoLobbyUI::DaoLobbyUI()
	{
	}
	DaoLobbyUI::~DaoLobbyUI()
	{
	}
	void DaoLobbyUI::Initialize()
	{
		mImage = Resources::Load<Image>(L"DaoLobbyUI", L"..\\Resources\\UI\\dao_LobbyUI.bmp");
	}
	void DaoLobbyUI::Update()
	{
	}
	void DaoLobbyUI::Render(HDC hdc)
	{
		TransparentBlt(hdc, 70, 180, mImage->GetWidth() * 1.5f, mImage->GetHeight() * 1.5f, mImage->GetHdc()
			, 0, 0, mImage->GetWidth(), mImage->GetHeight(), RGB(255, 0, 255));
		GameObject::Render(hdc);
	}
	void DaoLobbyUI::Release()
	{
	}
}