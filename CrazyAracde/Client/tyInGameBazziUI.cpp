#include "tyInGameBazziUI.h"
#include "tySceneManager.h"
#include "tyResources.h"
#include "tyTransform.h"
#include "tyImage.h"
#include "tyinput.h"
#include "tyObject.h"
#include "tyLobbyScene.h"

namespace ty
{
	InGameBazziUI::InGameBazziUI()
	{
	}
	InGameBazziUI::~InGameBazziUI()
	{
	}
	void InGameBazziUI::Initialize()
	{
		mImage = Resources::Load<Image>(L"BazziIngameUI", L"..\\Resources\\UI\\IngameBazzi.bmp");
	}
	void InGameBazziUI::Update()
	{
		if (SceneManager::GetActiveScene()->GetName() == L"Lobby")
		{
			object::Destroy(this);
		}
		GameObject::Update();
	}
	void InGameBazziUI::Render(HDC hdc)
	{
		if (LobbyScene::GetFirstPicked() == true && SceneManager::GetFirstCharactorPick() == eCharactorPick::Bazzi)
		{
			TransparentBlt(hdc, 985, 150, mImage->GetWidth() * 0.8 , mImage->GetHeight() * 0.8 , mImage->GetHdc()
				, 0, 0, mImage->GetWidth(), mImage->GetHeight(), RGB(255, 0, 255));
		}
		if (LobbyScene::GetSecondPicked() == true && SceneManager::GetSecondCharactorPick() == eCharactorPick::Bazzi)
		{
			TransparentBlt(hdc, 985, 215, mImage->GetWidth() * 0.8, mImage->GetHeight() * 0.8, mImage->GetHdc()
				, 0, 0, mImage->GetWidth(), mImage->GetHeight(), RGB(255, 0, 255));
		}
		GameObject::Render(hdc);
	}
	void InGameBazziUI::Release()
	{
	}
}