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

namespace ty
{
	Bazzi* PlayScene::mBazzi;
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
		object::Instantiate<Shadow>(Vector2(20.0f, 40.0f), eLayerType::Shadow);
		
		mBazzi = object::Instantiate<Bazzi>(Vector2(80.0f, 40.0f), eLayerType::Player); // PlayerNum 과는 x축 플러스 25 y축 - 30유지
		//object::Instantiate<PlayerNum>(Vector2(85.0f, 70.0f), eLayerType::Shadow);
		//Camera::SetTarget(mBazzi);
		object::Instantiate<Play_BG>(eLayerType::BG);
		object::Instantiate<IceTile>(eLayerType::BG);
		//object::Instantiate<PirateBoss>(Vector2(690.0f, 380.0f), eLayerType::Monster);
	//	object::Instantiate<BaseBomb>(Vector2(30.0f, 60.0f), eLayerType::Ground);
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
		
		//mCuphead = object::Instantiate<Cuphead>(Vector2(500.0f, 400.0f), eLayerType::Player);
	/*	Cuphead* player = object::Instantiate<Cuphead>(Vector2(500.0f, 400.0f), eLayerType::Player);
		object::Instantiate<Monster>(Vector2(500.0f, 500.0f), eLayerType::Player);
		Ground* ground = object::Instantiate<Ground>(Vector2(0.0f, 0.0f), eLayerType::Ground);
		ground->SetPlayer(player)*/
		//CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster, true); // 이것이 콜라이더 설정하는 값이다.
		//CollisionManager::SetLayer(eLayerType::Player, eLayerType::Bomb, true);
		//CollisionManager::SetLayer(eLayerType::Monster, eLayerType::Bomb, true);
		//CollisionManager::SetLayer(eLayerType::Bomb, eLayerType::Bomb, true);

	}
	void PlayScene::Update()
	{
		Vector2 Pos = mBazzi->GetComponent<Transform>()->GetPos();
		

		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			SceneManager::LoadScene(eSceneType::Lobby);
		}

		if (Input::GetKeyState(eKeyCode::T) == eKeyState::Down)
		{
			SceneManager::LoadScene(eSceneType::Tool);
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
		TilePalatte::Load(L"001");
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
		mBazzi->GetComponent<Transform>()->SetPos(Vector2(120.0f, 60.0f)); // 화면 전환시 기능 추가
		mBazzi->SetState(GameObject::eState::Active);
		mBazzi->Reset();
		//object::Destroy(mBlender);
	}
}