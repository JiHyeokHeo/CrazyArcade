#include "tyPlayScene.h"
#include "tyBazzi.h" // 전방 선언을 할 경우 cpp 파일에 헤더를 추가해야한다.
#include "tyInput.h"
#include "tySceneManager.h"
#include "tyMonster.h"
#include "tyCollisionManager.h"
#include "tyTransform.h"
#include "tyCamera.h"
#include "tyObject.h"
#include "tySealBoss.h"
#include "tyAlphaBlender.h"
#include "tyPirateBoss.h"
#include "tyTilePalatte.h"
#include "tyBossBombEffect.h"
#include "tyGround.h"
#include "tyLRGround.h"
#include "tyBaseBomb.h"
#include "tyShadow.h"
#include "tyPlayerNum.h"
#include "tyResources.h"
#include "tyIceTile.h"
#include "tyTile.h"
#include "tyStage2.h"

namespace ty
{
	//Bazzi* PlayScene::mBazzi;
	PlayScene::PlayScene()
		:monstercnt(0)
	{
	}
	PlayScene::~PlayScene()
	{
	}
	void PlayScene::Initialize()
	{
		Scene::Initialize();
		
		mBazzi = object::Instantiate<Bazzi>(eLayerType::Player);
		SceneManager::SetBazzi(mBazzi);
		mBazzi->GetComponent<Transform>()->SetPos(Vector2(80.0f, 100.0f));
		object::Instantiate<Shadow>(Vector2(20.0f, 40.0f), eLayerType::Shadow);
		
		//object::Instantiate<Bazzi>(Vector2(80.0f, 100.0f), eLayerType::Player); // PlayerNum 과는 x축 플러스 25 y축 - 30유지
		//object::Instantiate<PlayerNum>(Vector2(85.0f, 70.0f), eLayerType::Shadow);
		//Camera::SetTarget(mBazzi);
		object::Instantiate<Play_BG>(eLayerType::BG);
		object::Instantiate<IceTile>(eLayerType::BG);
		//object::Instantiate<PirateBoss>(Vector2(690.0f, 380.0f), eLayerType::Monster);
		//object::Instantiate<SealBoss>(Vector2(510.0f, 380.0f), eLayerType::Monster);
		object::Instantiate<Monster>(Vector2(450.0f, 120.0f), eLayerType::Monster);
		object::Instantiate<Monster>(Vector2(570.0f, 420.0f), eLayerType::Monster);
		object::Instantiate<Monster>(Vector2(630.0f, 420.0f), eLayerType::Monster);
		object::Instantiate<Monster>(Vector2(690.0f, 420.0f), eLayerType::Monster);
		object::Instantiate<Monster>(Vector2(750.0f, 420.0f), eLayerType::Monster);
		object::Instantiate<Ground>(Vector2(30.0f, -720.0f), eLayerType::Ground);
		object::Instantiate<Ground>(Vector2(30.0f, 840.0f), eLayerType::Ground);
		object::Instantiate<LRGround>(Vector2(-870.0f, 60.0f), eLayerType::Ground);
		object::Instantiate<LRGround>(Vector2(930.0f, 60.0f), eLayerType::Ground);
	}
	void PlayScene::Update()
	{
		
		//if (Input::GetKeyState(eKeyCode::T) == eKeyState::Down)
		//{
		//	SceneManager::LoadScene(eSceneType::Tool);
		//}
		
		Vector2 temp = Input::GetMousePos();
		if (Input::GetKeyDown(eKeyCode::LBUTTON) && temp.y >= 846 && temp.y <= 888 && temp.x >= 974 && temp.x <= 1180)
		{
			SceneManager::LoadScene(eSceneType::Lobby);
		}

		Scene::Update();
	}
	void PlayScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
	void PlayScene::Release()
	{
		Scene::Release();
	}
	void PlayScene::OnEnter()
	{
		//mBlender = object::Instantiate<AlphaBlender>(eLayerType::AlphaBlender);
		if (isLoad == false)
		{
			TilePalatte::Load(L"001");
			isLoad = true;
		}
		//mBlender = object::Instantiate<AlphaBlender>(eLayerType::AlphaBlender);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::BombEffect, true);
		CollisionManager::SetLayer(eLayerType::Monster, eLayerType::BombEffect, true);
		CollisionManager::SetLayer(eLayerType::Monster, eLayerType::Ground, true);
		CollisionManager::SetLayer(eLayerType::Monster, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Ground, true);
		CollisionManager::SetLayer(eLayerType::BombEffect, eLayerType::Ground, true);
		CollisionManager::SetLayer(eLayerType::BombEffect, eLayerType::Bomb, true);
		CollisionManager::SetLayer(eLayerType::BombEffect, eLayerType::Tile, true);
		CollisionManager::SetLayer(eLayerType::BombEffect, eLayerType::Item, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Tile, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Item, true);
		CollisionManager::SetLayer(eLayerType::Monster, eLayerType::Tile, true);
		//CollisionManager::SetLayer(eLayerType::BombEffect, eLayerType::Tile, true);
		
	}
	void PlayScene::OnExit()
	{
		TilePalatte::Clear();
		CollisionManager::Clear();
		for (int i = 0; i < 13; i++)
		{
			for (int j = 0; j < 15; j++)
			{
				mBazzi->GetMapIndex()[i][j] = 0;
			}
		}
		mBazzi->GetComponent<Transform>()->SetPos(Vector2(80.0f, 100.0f)); // 화면 전환시 기능 추가
		mBazzi->SetState(GameObject::eState::Active);
		mBazzi->Reset();
		//object::Destroy(mBlender);
	}
}