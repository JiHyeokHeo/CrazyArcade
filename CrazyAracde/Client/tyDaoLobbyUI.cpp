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
		if (SceneManager::GetActiveScene()->GetName() == L"Login")
		{
			object::Destroy(this);
		}
		Vector2 temp = Input::GetMousePos();

		if (Input::GetKeyDown(eKeyCode::LBUTTON) && temp.y >= 877 && temp.y <= 890 && temp.x >= 157 && temp.x <= 191)
		{
			object::Destroy(this);
		}
		if (Input::GetKeyDown(eKeyCode::LBUTTON) && temp.y >= 300 && temp.y <= 360 && temp.x >= 950 && temp.x <= 1040
			&& LobbyScene::GetFirstPicked() == true)
		{
			LobbyScene::SetisFirstPicked(false);
			object::Destroy(this);
		}

		if (Input::GetKeyDown(eKeyCode::RBUTTON) && temp.y >= 300 && temp.y <= 360 && temp.x >= 950 && temp.x <= 1040
			&& LobbyScene::GetSecondPicked() == true)
		{
			LobbyScene::SetisSecondPicked(false);
			object::Destroy(this);
		}
		GameObject::Update();
	}
	void DaoLobbyUI::Render(HDC hdc)
	{
		if (LobbyScene::GetFirstPicked() == true && SceneManager::GetFirstCharactorPick() == eCharactorPick::Dao)
		{
			TransparentBlt(hdc, 70, 180, mImage->GetWidth() * 1.5f, mImage->GetHeight() * 1.5f, mImage->GetHdc()
				, 0, 0, mImage->GetWidth(), mImage->GetHeight(), RGB(255, 0, 255));
		}
		if (LobbyScene::GetSecondPicked() == true && SceneManager::GetSecondCharactorPick() == eCharactorPick::Dao)
		{
			TransparentBlt(hdc, 235, 180, mImage->GetWidth() * 1.5f, mImage->GetHeight() * 1.5f, mImage->GetHdc()
				, 0, 0, mImage->GetWidth(), mImage->GetHeight(), RGB(255, 0, 255));
		}
		GameObject::Render(hdc);
	}
	void DaoLobbyUI::Release()
	{
	}
}