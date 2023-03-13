#include "tyLobbyScene.h"
#include "tySceneManager.h"
#include "tyInput.h"
#include "tyCollisionManager.h"
#include "tyTransform.h"
#include "tyCamera.h"
#include "tyObject.h"
#include "tyBossMonster.h"

namespace ty
{
	LobbyScene::LobbyScene()
	{
	}
	LobbyScene::~LobbyScene()
	{
	}
	void LobbyScene::Initialize()
	{
		Scene::Initialize();
		object::Instantiate<Lobby_BG>(eLayerType::BG);
	}
	void LobbyScene::Update()
	{
		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			SceneManager::LoadScene(eSceneType::Play);
		}
		Scene::Update();
	}
	void LobbyScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
	void LobbyScene::Release()
	{
		Scene::Release();
	}
	void LobbyScene::OnEnter()
	{
	}
	void LobbyScene::OnExit()
	{
	}
}