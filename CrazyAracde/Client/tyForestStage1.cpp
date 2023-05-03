#include "tyForestStage1.h"
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
#include "tyDevil.h"
#include "tyBird.h"
#include "tyNeedle.h"
#include "tyShield.h"
#include "tyTimer.h"
#include "tyGameStartUI.h"
#include "tyWinLose.h"
#include "tyTime.h"
#include "tyMonster2.h"
#include "tyForestTile.h"
#include "tyForestMonster.h"
#include "tyDao.h"
#include "tyLobbyScene.h"
#include "tyInGameBazziUI.h"
#include "tyIngameDaoUI.h"
#include "tyCheckCharactor.h"
#include "tySound.h"
namespace ty
{
	ForestStage1::ForestStage1()
	{
	}
	ForestStage1::~ForestStage1()
	{
	}
	void ForestStage1::Initialize()
	{
		Scene::Initialize();

		forestSound = Resources::Load<Sound>(L"iceStageTheme", L"..\\Resources\\Sound\\Map\\bg_2.wav");
		forestSound->SetVolume(20);
		// ------------------ 캐릭터 + 그림자 + 이펙트
		mBazzi = object::Instantiate<Bazzi>(eLayerType::Player);
		mBazzi->SetState(GameObject::eState::Pause);
		mDao = object::Instantiate<Dao>(eLayerType::Player);
		mDao->SetState(GameObject::eState::Pause);
		// 생성과 동시에 일단 Pause 상태로 진입
		mBazziUI = object::Instantiate<InGameBazziUI>(eLayerType::UI);
		mDaoUI = object::Instantiate<InGameDaoUI>(eLayerType::UI);
		mDao ->GetComponent<Transform>()->SetPos(Vector2(80.0f, 450.0f));
		mBazzi->GetComponent<Transform>()->SetPos(Vector2(80.0f, 300.0f));

		// ------------------ 시간 관련
		time[0] = object::Instantiate<Timer>(Vector2(1064.0f, 110.0f), eLayerType::UI);
		time[0]->SetTimeType(Timer::TimeType::TenMinutes);
		time[1] = object::Instantiate<Timer>(Vector2(1084.0f, 110.0f), eLayerType::UI);
		time[1]->SetTimeType(Timer::TimeType::Minutes);
		time[2] = object::Instantiate<Timer>(Vector2(1104.0f, 110.0f), eLayerType::UI);
		time[2]->SetTimeType(Timer::TimeType::None);
		time[3] = object::Instantiate<Timer>(Vector2(1124.0f, 110.0f), eLayerType::UI);
		time[3]->SetTimeType(Timer::TimeType::TenSeconds);
		time[4] = object::Instantiate<Timer>(Vector2(1144.0f, 110.0f), eLayerType::UI);	
		time[4]->SetTimeType(Timer::TimeType::Seconds);

		// ------------------ 아이템 테스트
		obj[0] = object::Instantiate<Devil>(Vector2(450.0f, 120.0f), eLayerType::Item);
		//obj[1] = object::Instantiate<Bird>(Vector2(690.0f, 420.0f), eLayerType::Item);
		obj[2] = object::Instantiate<Needle>(Vector2(630.0f, 420.0f), eLayerType::Item);
		obj[3] = object::Instantiate<Shield>(Vector2(570.0f, 420.0f), eLayerType::Item);

		// ------------------ 배경
		object::Instantiate<Play_BG>(eLayerType::BG);
		object::Instantiate<ForestTile>(eLayerType::BG);

		// ------------------ 충돌
		object::Instantiate<Ground>(Vector2(30.0f, -720.0f), eLayerType::Ground);
		object::Instantiate<Ground>(Vector2(30.0f, 840.0f), eLayerType::Ground);
		object::Instantiate<LRGround>(Vector2(-870.0f, 60.0f), eLayerType::Ground);
		object::Instantiate<LRGround>(Vector2(930.0f, 60.0f), eLayerType::Ground);

		// ------------------ 몬스터
		//object::Instantiate<Bazzi>(Vector2(80.0f, 100.0f), eLayerType::Player); // PlayerNum 과는 x축 플러스 25 y축 - 30유지
		//object::Instantiate<PirateBoss>(Vector2(690.0f, 380.0f), eLayerType::Monster);
		//object::Instantiate<SealBoss>(Vector2(510.0f, 380.0f), eLayerType::Monster);
		monster[0] = object::Instantiate<ForestMonster>(Vector2(450.0f, 120.0f), eLayerType::Monster);
		monster[1] = object::Instantiate<ForestMonster>(Vector2(450.0f, 720.0f), eLayerType::Monster);
		monster[2] = object::Instantiate<ForestMonster>(Vector2(510.0f, 420.0f), eLayerType::Monster);
		monster[3] = object::Instantiate<ForestMonster>(Vector2(570.0f, 420.0f), eLayerType::Monster);
		monster[4] = object::Instantiate<ForestMonster>(Vector2(750.0f, 420.0f), eLayerType::Monster);
		monster[5] = object::Instantiate<ForestMonster>(Vector2(810.0f, 420.0f), eLayerType::Monster);
	}
	void ForestStage1::Update()
	{
		CheckCharactor::Check(eSceneType::ForestStage2);

		Vector2 temp = Input::GetMousePos();
		if (Input::GetKeyDown(eKeyCode::LBUTTON) && temp.y >= 846 && temp.y <= 888 && temp.x >= 974 && temp.x <= 1180)
		{
			SceneManager::LoadScene(eSceneType::Lobby);
		}

		Scene::Update();
		CheckCharactor::Skip(eSceneType::ForestStage2); // Q누르면 스킵
	}
	void ForestStage1::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
	void ForestStage1::Release()
	{
		Scene::Release();
	}
	void ForestStage1::OnEnter()
	{
		monster[0]->SetState(GameObject::eState::Active);
		monster[1]->SetState(GameObject::eState::Active);
		monster[2]->SetState(GameObject::eState::Active);
		monster[3]->SetState(GameObject::eState::Active);
		monster[4]->SetState(GameObject::eState::Active);
		monster[5]->SetState(GameObject::eState::Active);
		forestSound->Play(true);
		// UI 상태 변환
		mBazziUI->SetState(GameObject::eState::Active);
		mDaoUI->SetState(GameObject::eState::Active);
		// 캐릭터 설정 + 시간 조절
		
		if (SceneManager::GetIsDuo() == false)
		{
			if (SceneManager::GetFirstCharactorPick() == eCharactorPick::Bazzi)
			{
				mBazzi->SetState(GameObject::eState::Active);
				SceneManager::SetBazzi(mBazzi);
			}

			if (SceneManager::GetFirstCharactorPick() == eCharactorPick::Dao)
			{
				mDao->SetState(GameObject::eState::Active);
				SceneManager::SetDao(mDao);
			}
		}
		else if (SceneManager::GetIsDuo() == true)
		{
			if (SceneManager::GetFirstCharactorPick() == eCharactorPick::Bazzi)
			{
				mBazzi->SetState(GameObject::eState::Active);
				SceneManager::SetBazzi(mBazzi);
				mBazzi->SetIs1P(true);
			}
			if (SceneManager::GetSecondCharactorPick() == eCharactorPick::Bazzi)
			{
				mBazzi->SetState(GameObject::eState::Active);
				SceneManager::SetBazzi(mBazzi);
				mBazzi->SetIs1P(false);
			}
			if (SceneManager::GetFirstCharactorPick() == eCharactorPick::Dao)
			{
				mDao->SetState(GameObject::eState::Active);
				mDao->SetIs1P(true);
				SceneManager::SetDao(mDao);
			}
			if (SceneManager::GetSecondCharactorPick() == eCharactorPick::Dao)
			{
				mDao->SetState(GameObject::eState::Active);
				mDao->SetIs1P(false);
				SceneManager::SetDao(mDao);
			}
		}

		SceneManager::SetMonsterCnt(6);
		GameStartUI* obj2 = object::Instantiate<GameStartUI>(Vector2(168.0f, 60.0f), eLayerType::UI);
		GameStartUI* obj3 = object::Instantiate<GameStartUI>(Vector2(450.0f, 840.0f), eLayerType::UI);

		for (int i = 0; i < 5; i++)
		{
			time[i]->ResetIsTimeOn();
		}
		SceneManager::SetmTime(240); // 4분 설정


		if (isLoad == true)
		{
			Scene::ChangeGameObjectState();
			monster[0]->GetComponent<Transform>()->SetPos(Vector2(450.0f, 120.0f));
			monster[1]->GetComponent<Transform>()->SetPos(Vector2(450.0f, 720.0f));
			monster[2]->GetComponent<Transform>()->SetPos(Vector2(510.0f, 420.0f));
			monster[3]->GetComponent<Transform>()->SetPos(Vector2(570.0f, 420.0f));
			monster[4]->GetComponent<Transform>()->SetPos(Vector2(750.0f, 420.0f));
			monster[5]->GetComponent<Transform>()->SetPos(Vector2(810.0f, 420.0f));
			
			
			
			
			
			for (int i = 0; i < 13; i++)
			{
				for (int j = 0; j < 15; j++)
				{
					SceneManager::GetMapIndex()[i][j] = PlayIndex[i][j];
				}
			}
		}

		if (isLoad == false)
		{
			TilePalatte::Load(L"101");
			for (int i = 0; i < 13; i++)
			{
				for (int j = 0; j < 15; j++)
				{
					PlayIndex[i][j] = SceneManager::GetMapIndex()[i][j];
				}
			}
			isLoad = true;
		}
		//mBlender = object::Instantiate<AlphaBlender>(eLayerType::AlphaBlender);
		//mBlender = object::Instantiate<AlphaBlender>(eLayerType::AlphaBlender);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::BombEffect, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Ground, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Tile, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Item, true);
		CollisionManager::SetLayer(eLayerType::Monster, eLayerType::BombEffect, true);
		CollisionManager::SetLayer(eLayerType::Monster, eLayerType::Ground, true);
		CollisionManager::SetLayer(eLayerType::Monster, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Monster, eLayerType::Tile, true);
		CollisionManager::SetLayer(eLayerType::BombEffect, eLayerType::Ground, true);
		CollisionManager::SetLayer(eLayerType::BombEffect, eLayerType::Bomb, true);
		CollisionManager::SetLayer(eLayerType::BombEffect, eLayerType::Item, true);
		CollisionManager::SetLayer(eLayerType::BombEffect, eLayerType::Tile, true);
		CollisionManager::SetLayer(eLayerType::Boss, eLayerType::BombEffect, true);
		CollisionManager::SetLayer(eLayerType::Boss, eLayerType::Ground, true);
		CollisionManager::SetLayer(eLayerType::Boss, eLayerType::Player, true);
		CollisionManager::SetLayer(eLayerType::Boss, eLayerType::Tile, true);
		CollisionManager::SetLayer(eLayerType::Boss, eLayerType::Bomb, true);
		//CollisionManager::SetLayer(eLayerType::BombEffect, eLayerType::Tile, true);

	}
	void ForestStage1::OnExit()
	{
		forestSound->Stop(true);
		monster[0]->SetState(GameObject::eState::Active);
		monster[1]->SetState(GameObject::eState::Active);
		monster[2]->SetState(GameObject::eState::Active);
		monster[3]->SetState(GameObject::eState::Active);
		monster[4]->SetState(GameObject::eState::Active);
		monster[5]->SetState(GameObject::eState::Active);
		TilePalatte::Clear();
		CollisionManager::Clear();
		for (int j = 0; j < 13; j++)
		{
			for (int i = 0; i < 15; i++)
			{
				SceneManager::GetMapIndex()[j][i] = 0;
				SceneManager::GetBombIndex()[j][i] = 0;
			}
		}

		if (SceneManager::GetIsDuo() == false)
		{
			if (SceneManager::GetFirstCharactorPick() == eCharactorPick::Bazzi)
			{
				mBazzi->GetComponent<Transform>()->SetPos(Vector2(80.0f, 300.0f)); // 화면 전환시 기능 추가
				mBazziUI->SetState(GameObject::eState::Pause);
				mBazzi->SetState(GameObject::eState::Pause);
				mBazzi->Reset();
			}
			else if (SceneManager::GetFirstCharactorPick() == eCharactorPick::Dao)
			{
				mDao->GetComponent<Transform>()->SetPos(Vector2(80.0f, 450.0f)); // 화면 전환시 기능 추가
				mDaoUI->SetState(GameObject::eState::Pause);
				mDao->SetState(GameObject::eState::Pause);
				mDao->Reset();
			}
		}
		else if (SceneManager::GetIsDuo() == true)
		{
			if (SceneManager::GetFirstCharactorPick() == eCharactorPick::Bazzi)
			{
				mBazzi->GetComponent<Transform>()->SetPos(Vector2(80.0f, 300.0f)); // 화면 전환시 기능 추가
				mBazziUI->SetState(GameObject::eState::Pause);
				mBazzi->SetState(GameObject::eState::Pause);
				mBazzi->Reset();
			}
			else if (SceneManager::GetFirstCharactorPick() == eCharactorPick::Dao)
			{
				mDao->GetComponent<Transform>()->SetPos(Vector2(80.0f, 450.0f)); // 화면 전환시 기능 추가
				mDaoUI->SetState(GameObject::eState::Pause);
				mDao->SetState(GameObject::eState::Pause);
				mDao->Reset();
			}

			if (SceneManager::GetSecondCharactorPick() == eCharactorPick::Bazzi)
			{
				mBazzi->GetComponent<Transform>()->SetPos(Vector2(80.0f, 300.0f)); // 화면 전환시 기능 추가
				mBazziUI->SetState(GameObject::eState::Pause);
				mBazzi->SetState(GameObject::eState::Pause);
				mBazzi->Reset();
			}
			else if (SceneManager::GetSecondCharactorPick() == eCharactorPick::Dao)
			{
				mDao->GetComponent<Transform>()->SetPos(Vector2(80.0f, 450.0f)); // 화면 전환시 기능 추가
				mDaoUI->SetState(GameObject::eState::Pause);
				mDao->SetState(GameObject::eState::Pause);
				mDao->Reset();
			}
		}
		SceneManager::SetmTime(240);
		//object::Destroy(mBlender);
	}
}