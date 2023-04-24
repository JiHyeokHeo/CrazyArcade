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
		Vector2 temp = Input::GetMousePos();

		if (Input::GetKeyDown(eKeyCode::LBUTTON) && temp.y >= 300 && temp.y <= 360 && temp.x >= 730 && temp.x <= 825
			&& LobbyScene::GetFirstPicked() == true)
		{
			LobbyScene::SetisFirstPicked(false);
			object::Destroy(this);
		}
		if (Input::GetKeyDown(eKeyCode::RBUTTON) && temp.y >= 300 && temp.y <= 360 && temp.x >= 730 && temp.x <= 825
			&& LobbyScene::GetSecondPicked() == true)
		{
			LobbyScene::SetisSecondPicked(false);
			object::Destroy(this);
		}
		GameObject::Update();
	}
	void BazziLobbyUI::Render(HDC hdc)
	{
		if (LobbyScene::GetFirstPicked() == true && SceneManager::GetFirstCharactorPick() == eCharactorPick::Bazzi)
		{
			TransparentBlt(hdc, 70, 180, mImage->GetWidth() * 1.5f, mImage->GetHeight() * 1.5f, mImage->GetHdc()
				, 0, 0, mImage->GetWidth(), mImage->GetHeight(), RGB(255, 0, 255));
		}
		if(LobbyScene::GetSecondPicked() == true && SceneManager::GetSecondCharactorPick() == eCharactorPick::Bazzi)
		{
			TransparentBlt(hdc, 235, 180, mImage->GetWidth() * 1.5f, mImage->GetHeight() * 1.5f, mImage->GetHdc()
				, 0, 0, mImage->GetWidth(), mImage->GetHeight(), RGB(255, 0, 255));
		}
		GameObject::Render(hdc);
		
	}
	void BazziLobbyUI::Release()
	{
	}
}