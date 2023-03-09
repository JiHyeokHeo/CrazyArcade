#include "tyLogoScene.h"
#include "tyInput.h"
#include "tySceneManager.h"
#include "tyObject.h"

namespace ty
{
	LogoScene::LogoScene()
	{
	}
	LogoScene::~LogoScene()
	{
	}
	void LogoScene::Initialize()
	{
		object::Instantiate<Logo_BG>(eLayerType::BG);
		Scene::Initialize();
	}
	void LogoScene::Update()
	{
		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			SceneManager::LoadScene(eSceneType::Login);
		}
		Scene::Update();
	}
	void LogoScene::Render(HDC hdc)
	{

		Scene::Render(hdc);
	}
	void LogoScene::Release()
	{
		Scene::Release();
	}
	void LogoScene::OnEnter()
	{
	}
	void LogoScene::OnExit()
	{
	}
}