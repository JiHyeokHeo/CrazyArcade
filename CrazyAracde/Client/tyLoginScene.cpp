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
		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			SceneManager::LoadScene(eSceneType::Lobby);
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