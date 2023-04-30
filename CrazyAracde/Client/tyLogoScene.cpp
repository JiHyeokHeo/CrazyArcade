#include "tyLogoScene.h"
#include "tyInput.h"
#include "tySceneManager.h"
#include "tyObject.h"
#include "tyTime.h"
#include "tyCamera.h"
#include "tySound.h"
#include "tyResources.h"

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
		Scene::Initialize();
		//object::Instantiate<AlphaBlender>(eLayerType::AlphaBlender);
		object::Instantiate<Logo_BG>(eLayerType::BG);
	}
	void LogoScene::Update()
	{
		mTime += Time::DeltaTime();
		if (mTime >= 6.0f)
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
		Sound* Logo
			= Resources::Load<Sound>(L"LogoTheme", L"..\\Resources\\Sound\\logo.wav");
		Logo->Play(false);
	}
	void LogoScene::OnExit()
	{
	}
}