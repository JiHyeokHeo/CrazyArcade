#include "tyLoginScene.h"
#include "tyInput.h"
#include "tySceneManager.h"


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
		mLoginBG = new Login_BG();
		AddGameObject(mLoginBG, eLayerType::BG);
		Scene::Initialize();
	}
	void LoginScene::Update()
	{
		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			SceneManager::LoadScene(eSceneType::Lobby);
		}
		Scene::Update();
	}
	void LoginScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
	void LoginScene::Release()
	{
		Scene::Release();
	}
	void LoginScene::OnEnter()
	{
	}
	void LoginScene::OnExit()
	{
	}
}