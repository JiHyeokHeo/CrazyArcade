#include "tyLoginScene.h"
#include "tyInput.h"
#include "tySceneManager.h"
#include "tyObject.h"
#include "tyAlphaBlender.h"
#include "tyCamera.h"
#include "tyObject.h"
#include "tySinglePlayUI.h"
#include "tyDuoPlayUI.h"
#include "tySound.h"
#include "tyResources.h"


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
		SetName(L"Login");
		Scene::Initialize();
		Click = Resources::Load<Sound>(L"Click", L"..\\Resources\\Sound\\click.wav");
		Click->SetVolume(20);
		mouseMove = Resources::Load<Sound>(L"MouseMove", L"..\\Resources\\Sound\\pt_in_rect.wav");
		mouseMove->SetVolume(20);
		Login = Resources::Load<Sound>(L"LoginTheme", L"..\\Resources\\Sound\\login_scene.wav");
		Login->SetVolume(20);
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
			Click->Play(false);
			SceneManager::LoadScene(eSceneType::Lobby);
		}

		if (temp.y >= 143 && temp.y <= 250 && temp.x >= 354 && temp.x <= 446 && isPlayed == false)
		{
			isPlayed = true;
			mouseMove->Play(false);
		}
		
		if (temp.y <= 143 || temp.y >= 250 || temp.x <= 354 || temp.x >= 446)
		{
			isPlayed = false;
			
		}
		if (temp.y >= 143 && temp.y <= 250 && temp.x >= 726 && temp.x <= 816 && isPlayed == false)
		{
			isPlayed = true;
			mouseMove->Play(false);
		}

		if (temp.y <= 143 || temp.y >= 250 || temp.x <= 726 || temp.x >= 816)
		{
			isPlayed = false;
			
		}

		if (Input::GetKeyState(eKeyCode::T) == eKeyState::Down)
		{
			SceneManager::LoadScene(eSceneType::Tool);
		}

		if (Input::GetKeyDown(eKeyCode::LBUTTON) && temp.y >= 143 && temp.y <= 250 && temp.x >= 354 && temp.x <= 446)
		{
			Click->Play(false);
			SceneManager::SetIsDuo(false);
			isChecked = true;
		}

		if (Input::GetKeyDown(eKeyCode::LBUTTON) && temp.y >= 143 && temp.y <= 250 && temp.x >= 726 && temp.x <= 816)
		{
			Click->Play(false);
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
		Login->Play(true);
		//mBlender = object::Instantiate<AlphaBlender>(eLayerType::AlphaBlender);
	}
	void LoginScene::OnExit()
	{
		Login->Stop(true);
		//object::Destroy(mBlender);
	}
}