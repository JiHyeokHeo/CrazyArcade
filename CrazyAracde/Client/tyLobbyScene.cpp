#include "tyLobbyScene.h"
#include "tySceneManager.h"
#include "tyInput.h"
#include "tyCollisionManager.h"
#include "tyTransform.h"
#include "tyCamera.h"
#include "tyObject.h"
#include "tySealBoss.h"
#include "tyAlphaBlender.h"
#include "tyMapSelect.h"
#include "tyIceSelect.h"
#include "tyIceMapSelect.h"

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
		//object::Instantiate<MapSelect>(eLayerType::UI);
	}
	void LobbyScene::Update()
	{
		Scene::Update();
		Vector2 temp = Input::GetMousePos();
		if (Input::GetKeyDown(eKeyCode::LBUTTON) && temp.y >= 647 && temp.y <= 716 && temp.x >= 970 && temp.x <= 1150)
		{
			object::Instantiate<MapSelect>(eLayerType::UI);
		}

		if (temp.y >= 290 && temp.y <= 350 && temp.x >= 950 && temp.x <= 1042)
		{
			object::Instantiate<MapSelect>(eLayerType::UI);
		}

		if (Input::GetKeyDown(eKeyCode::LBUTTON) && temp.y >= 368 && temp.y <= 384 && temp.x >= 525 && temp.x <= 906)
		{
			object::Instantiate<IceSelect>(eLayerType::UI);
			mMapSelect = object::Instantiate<IceMapSelect>(eLayerType::MapSelectUI);
			mSceneType = eSceneType::Play;
		}
		if (Input::GetKeyDown(eKeyCode::LBUTTON) && temp.y >= 442 && temp.y <= 458 && temp.x >= 525 && temp.x <= 906)
		{
			mSceneType = eSceneType::Stage2;
		}

		if (Input::GetKeyDown(eKeyCode::LBUTTON) && temp.y >= 750 && temp.y <= 820 && temp.x >= 780 && temp.x <= 1050)
		{
			SceneManager::LoadScene(mSceneType);
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
		//mBlender = object::Instantiate<AlphaBlender>(eLayerType::AlphaBlender);
	}
	void LobbyScene::OnExit()
	{
		//object::Destroy(mMapSelect);
		//object::Destroy(mBlender);
	}
}