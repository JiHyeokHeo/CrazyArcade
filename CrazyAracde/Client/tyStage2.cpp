#include "tyStage2.h"
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
	Stage2::Stage2()
	{
	}
	Stage2::~Stage2()
	{
	}
	void Stage2::Initialize()
	{
		Scene::Initialize();
		object::Instantiate<PirateBoss>(Vector2(690.0f, 380.0f), eLayerType::Monster);
		object::Instantiate<SealBoss>(Vector2(510.0f, 380.0f), eLayerType::Monster);
		object::Instantiate<Play_BG>(eLayerType::BG);
		object::Instantiate<Ground>(Vector2(30.0f, -720.0f), eLayerType::Ground);
		object::Instantiate<Ground>(Vector2(30.0f, 840.0f), eLayerType::Ground);
		object::Instantiate<LRGround>(Vector2(-870.0f, 60.0f), eLayerType::Ground);
		object::Instantiate<LRGround>(Vector2(930.0f, 60.0f), eLayerType::Ground);
	}
	void Stage2::Update()
	{
		Scene::Update();
	}
	void Stage2::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
	void Stage2::Release()
	{
		Scene::Release();
	}
	void Stage2::OnEnter()
	{
	}
	void Stage2::OnExit()
	{
	}
}