#include "tyLoginScene.h"
#include "tyInput.h"
#include "tySceneManager.h"
#include "tyObject.h"
#include "tyAlphaBlender.h"
#include "tyCamera.h"

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
	}
	void LoginScene::Update()
	{
		Scene::Update();
		Vector2 temp = Input::GetMousePos();
		if (Input::GetKeyDown(eKeyCode::LBUTTON) && temp.y >= 78 && temp.y <= 302 && temp.x >= 480 && temp.x <= 700)
		{
			SceneManager::LoadScene(eSceneType::Lobby);
		}
		if (Input::GetKeyState(eKeyCode::T) == eKeyState::Down)
		{
			SceneManager::LoadScene(eSceneType::Tool);
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