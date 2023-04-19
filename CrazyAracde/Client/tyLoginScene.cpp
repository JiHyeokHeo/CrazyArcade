#include "tyLoginScene.h"
#include "tyInput.h"
#include "tySceneManager.h"
#include "tyObject.h"
#include "tyAlphaBlender.h"
#include "tyCamera.h"
#include "tyObject.h"
#include "tySinglePlayUI.h"
#include "tyDuoPlayUI.h"

namespace ty
{
	LoginScene::LoginScene()
	{
	}
	LoginScene::~LoginScene()
	{
	}
	void LoginScene::Initialize()
	{
		Scene::Initialize();
		object::Instantiate<Login_BG>(eLayerType::BG);
		object::Instantiate<SinglePlayUI>(eLayerType::UI);
		object::Instantiate<DuoPlayUI>(eLayerType::UI);
	}
	void LoginScene::Update()
	{
		Scene::Update();
		Vector2 temp = Input::GetMousePos();
		if (Input::GetKeyDown(eKeyCode::LBUTTON) && temp.y >= 78 && temp.y <= 302 && temp.x >= 480 && temp.x <= 700 && isChecked == true)
		{
			SceneManager::LoadScene(eSceneType::Lobby);
		}

		if (Input::GetKeyState(eKeyCode::T) == eKeyState::Down)
		{
			SceneManager::LoadScene(eSceneType::Tool);
		}

		if (Input::GetKeyDown(eKeyCode::LBUTTON) && temp.y >= 143 && temp.y <= 250 && temp.x >= 354 && temp.x <= 446)
		{
			SceneManager::SetIsDuo(false);
			isChecked = true;
		}

		if (Input::GetKeyDown(eKeyCode::LBUTTON) && temp.y >= 143 && temp.y <= 250 && temp.x >= 726 && temp.x <= 816)
		{
			SceneManager::SetIsDuo(true);
			isChecked = true;
		}

	}
	void LoginScene::Render(HDC hdc)
	{
		/*Camera::Render(hdc);*/
		Scene::Render(hdc);
	}
	void LoginScene::Release()
	{
		Scene::Release();
	}
	void LoginScene::OnEnter()
	{
		//mBlender = object::Instantiate<AlphaBlender>(eLayerType::AlphaBlender);
	}
	void LoginScene::OnExit()
	{
		//object::Destroy(mBlender);
	}
}