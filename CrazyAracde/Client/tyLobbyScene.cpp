#include "tyLobbyScene.h"
#include "tySceneManager.h"
#include "tyInput.h"
#include "tyCollisionManager.h"
#include "tyTransform.h"
#include "tyCamera.h"
#include "tyObject.h"
#include "tySealBoss.h"
#include "tyAlphaBlender.h"

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
		Scene::Update();
		Vector2 temp = Input::GetMousePos();
		if (Input::GetKeyDown(eKeyCode::LBUTTON) && temp.y >= 750 && temp.y <= 820 && temp.x >= 780 && temp.x <= 1050)
		{
			SceneManager::LoadScene(eSceneType::Play);
		}
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
		mBlender = object::Instantiate<AlphaBlender>(eLayerType::AlphaBlender);
	}
	void LobbyScene::OnExit()
	{
		//object::Destroy(mBlender);
	}
}