#include "tyIngameDaoUI.h"
#include "tySceneManager.h"
#include "tyResources.h"
#include "tyTransform.h"
#include "tyImage.h"
#include "tyinput.h"
#include "tyObject.h"
#include "tyLobbyScene.h"

namespace ty
{
	InGameDaoUI::InGameDaoUI()
	{
	}
	InGameDaoUI::~InGameDaoUI()
	{
	}
	void InGameDaoUI::Initialize()
	{
		mImage = Resources::Load<Image>(L"DaoIngameUI", L"..\\Resources\\UI\\IngameDao.bmp");
	}
	void InGameDaoUI::Update()
	{
		if (SceneManager::GetActiveScene()->GetName() == L"Lobby")
		{
			object::Destroy(this);
		}
		GameObject::Update();
	}
	void InGameDaoUI::Render(HDC hdc)
	{
		if (LobbyScene::GetFirstPicked() == true && SceneManager::GetFirstCharactorPick() == eCharactorPick::Dao)
		{
			TransparentBlt(hdc, 985, 150, mImage->GetWidth() * 0.8, mImage->GetHeight() * 0.8, mImage->GetHdc()
				, 0, 0, mImage->GetWidth(), mImage->GetHeight(), RGB(255, 0, 255));
		}
		if (LobbyScene::GetSecondPicked() == true && SceneManager::GetSecondCharactorPick() == eCharactorPick::Dao)
		{
			TransparentBlt(hdc, 985, 215, mImage->GetWidth() * 0.8, mImage->GetHeight() * 0.8, mImage->GetHdc()
				, 0, 0, mImage->GetWidth(), mImage->GetHeight(), RGB(255, 0, 255));
		}
		GameObject::Render(hdc);
	}
	void InGameDaoUI::Release()
	{
	}
}