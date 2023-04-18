#include "tyForestStage3.h"
#include "tyBazzi.h" // ���� ������ �� ��� cpp ���Ͽ� ����� �߰��ؾ��Ѵ�.
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

namespace ty
{
	ForestStage3::ForestStage3()
	{
	}
	ForestStage3::~ForestStage3()
	{
	}
	void ForestStage3::Initialize()
	{
		Scene::Initialize();

		// ------------------ ĳ���� + �׸��� + ����Ʈ
		mBazzi = object::Instantiate<Bazzi>(eLayerType::Player);
		//object::Instantiate<PlayerNum>(Vector2(85.0f, 70.0f), eLayerType::Shadow);
		mBazzi->GetComponent<Transform>()->SetPos(Vector2(460.0f, 720.0f));
		object::Instantiate<Shadow>(Vector2(20.0f, 40.0f), eLayerType::Shadow);

		// ------------------ �ð� ����
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

		// ------------------ ������ �׽�Ʈ
		object::Instantiate<Devil>(Vector2(90.0f, 120.0f), eLayerType::Item);
		//object::Instantiate<Bird>(Vector2(690.0f, 420.0f), eLayerType::Item);
		object::Instantiate<Shield>(Vector2(90.0f, 720.0f), eLayerType::Item);
		object::Instantiate<Shield>(Vector2(810.0f, 120.0f), eLayerType::Item);
		object::Instantiate<Needle>(Vector2(810.0f, 720.0f), eLayerType::Item);

		// ------------------ ���
		object::Instantiate<Play_BG>(eLayerType::BG);
		object::Instantiate<ForestTile>(eLayerType::BG);

		// ------------------ �浹
		object::Instantiate<Ground>(Vector2(30.0f, -720.0f), eLayerType::Ground);
		object::Instantiate<Ground>(Vector2(30.0f, 840.0f), eLayerType::Ground);
		object::Instantiate<LRGround>(Vector2(-870.0f, 60.0f), eLayerType::Ground);
		object::Instantiate<LRGround>(Vector2(930.0f, 60.0f), eLayerType::Ground);

		// ------------------ ����
		//object::Instantiate<Bazzi>(Vector2(80.0f, 100.0f), eLayerType::Player); // PlayerNum ���� x�� �÷��� 25 y�� - 30����
		//object::Instantiate<PirateBoss>(Vector2(690.0f, 380.0f), eLayerType::Monster);
		Bossmonster[0] = object::Instantiate<SealBoss>(Vector2(410.0f, 300.0f), eLayerType::Boss);
		monster3[0] = object::Instantiate<ForestMonster>(Vector2(90.0f, 120.0f), eLayerType::Monster);
		monster3[1] = object::Instantiate<ForestMonster>(Vector2(810.0f, 120.0f), eLayerType::Monster);
		monster3[2] = object::Instantiate<ForestMonster>(Vector2(90.0f, 720.0f), eLayerType::Monster);
		monster3[3] = object::Instantiate<ForestMonster>(Vector2(810.0f, 720.0f), eLayerType::Monster);
	}
	void ForestStage3::Update()
	{
		if (SceneManager::GetMonsterCnt() == 0)
		{
			if (isPlayed == false)
			{
				object::Instantiate<WinLose>(Vector2(350.0f, 400.0f), eLayerType::UI);
				isPlayed = true;
			}
			mTime += Time::DeltaTime();
			if (mTime >= 6.0f)
			{
				isPlayed = false;
				SceneManager::LoadScene(eSceneType::Lobby);
				mTime = 0;
			}
		}
		else if (SceneManager::GetBazzi()->GetPlayerHP() == -1)
		{
			object::Instantiate<WinLose>(Vector2(350.0f, 400.0f), eLayerType::UI);
			mTime += Time::DeltaTime();
			if (mTime >= 6.0f)
			{
				SceneManager::LoadScene(eSceneType::Lobby);
				mTime = 0;
			}
		}



		Vector2 temp = Input::GetMousePos();
		if (Input::GetKeyDown(eKeyCode::LBUTTON) && temp.y >= 846 && temp.y <= 888 && temp.x >= 974 && temp.x <= 1180)
		{
			Scene::ChangeMonsterState();
			SceneManager::LoadScene(eSceneType::Lobby);
		}

		Scene::Update();
	}
	void ForestStage3::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
	void ForestStage3::Release()
	{
	}
	void ForestStage3::OnEnter()
	{		// ĳ���� ���� + �ð� ����
		SceneManager::SetBazzi(mBazzi);
		SceneManager::SetMonsterCnt(5);
		GameStartUI* obj = object::Instantiate<GameStartUI>(Vector2(168.0f, 60.0f), eLayerType::UI);
		GameStartUI* obj2 = object::Instantiate<GameStartUI>(Vector2(450.0f, 840.0f), eLayerType::UI);

		for (int i = 0; i < 5; i++)
		{
			time[i]->ResetIsTimeOn();
		}
		SceneManager::SetmTime(240); // 4�� ����

		//monster3[0]->SetState(GameObject::eState::Active);
		//monster3[1]->SetState(GameObject::eState::Active);
		//monster3[2]->SetState(GameObject::eState::Active);
		//monster3[3]->SetState(GameObject::eState::Active);
		//monster3[4]->SetState(GameObject::eState::Active);

		if (isLoad == true)
		{
			Scene::ChangeGameObjectState();
			Bossmonster[0]->GetComponent<Transform>()->SetPos(Vector2(410.0f, 300.0f));
			//monster3[0]->GetComponent<Transform>()->SetPos(Vector2(90.0f, 120.0f));
			//monster3[1]->GetComponent<Transform>()->SetPos(Vector2(810.0f, 120.0f));
			//monster3[2]->GetComponent<Transform>()->SetPos(Vector2(90.0f, 720.0f));
			//monster3[3]->GetComponent<Transform>()->SetPos(Vector2(810.0f, 720.0f));
			
			for (int i = 0; i < 13; i++)
			{
				for (int j = 0; j < 15; j++)
				{
					SceneManager::GetBazzi()->GetMapIndex()[i][j] = PlayIndex[i][j];
				}
			}
		}

		if (isLoad == false)
		{
			TilePalatte::Load(L"103");
			for (int i = 0; i < 13; i++)
			{
				for (int j = 0; j < 15; j++)
				{
					PlayIndex[i][j] = SceneManager::GetBazzi()->GetMapIndex()[i][j];
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
	void ForestStage3::OnExit()
	{
		Bossmonster[0]->SetState(GameObject::eState::Active);
		TilePalatte::Clear();
		CollisionManager::Clear();
		for (int j = 0; j < 13; j++)
		{
			for (int i = 0; i < 15; i++)
			{
				SceneManager::GetBazzi()->GetMapIndex()[j][i] = 0;
			}
		}

		mBazzi->GetComponent<Transform>()->SetPos(Vector2(460.0f, 720.0f)); // ȭ�� ��ȯ�� ��� �߰�
		mBazzi->SetState(GameObject::eState::Active);
		mBazzi->Reset();
		SceneManager::SetmTime(240);
		SceneManager::SetBazzi(mBazzi);
		//object::Destroy(mBlender);
	}
}