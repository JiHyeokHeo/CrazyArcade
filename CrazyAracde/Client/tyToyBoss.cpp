#include "tyToyBoss.h"
#include "tyTime.h"
#include "tySceneManager.h"
#include "tyinput.h"
#include "tyResources.h"
#include "tyTransform.h"
#include "tyAnimator.h"
#include "tyCollider.h"
#include "tyBaseBomb.h"
#include "tyScene.h"
#include "tyObject.h"
#include "tyBossBombEffect.h"
#include "tyTileBomb.h"

namespace ty
{
	ToyBoss::ToyBoss()
		: Hp(2)
		, mInvincibility(0)
	{
	}
	ToyBoss::~ToyBoss()
	{
	}
	void ToyBoss::Initialize()
	{
		SetName(L"Boss");
		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector2(2.0f, 2.0f));
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Monster\\ToyBoss\\Up", Vector2(20.0f, 0.0f), 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Monster\\ToyBoss\\Right", Vector2(20.0f, 0.0f), 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Monster\\ToyBoss\\Left", Vector2(20.0f, 0.0f), 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Monster\\ToyBoss\\Down", Vector2(20.0f, 0.0f), 0.1f);
		/*mAnimator->CreateAnimations(L"..\\Resources\\Monster\\PirateBoss\\Bubble", Vector2::Zero, 0.3f);
		mAnimator->CreateAnimations(L"..\\Resources\\Monster\\PirateBoss\\Hit", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Monster\\PirateBoss\\Die", Vector2::Zero, 0.6f);*/

		//mAnimator->GetCompleteEvent(L"PirateBossBubble") = std::bind(&ToyBoss::bubbleCompleteEvent, this);


		mAnimator->Play(L"ToyBossDown", false);
		tr = GetComponent<Transform>();
		mPos = tr->GetPos();
		midmPos = mPos + Vector2(TILE_SIZE_X / 2, TILE_SIZE_Y / 2);
		Collider* collider = AddComponent<Collider>();
		collider->SetCenter(Vector2(20.0f, 10.0f));
		collider->SetSize(Vector2(120.0f, 150.0f));
		mState = eToyBossState::Idle;
		GameObject::Initialize();
	}
	void ToyBoss::Update()
	{
		rand_num = dist(gen);
		//tr = GetComponent<Transform>();
		//mPos = tr->GetPos();
		//midmPos = mPos + Vector2(TILE_SIZE_X / 2, TILE_SIZE_Y / 2);
		//ColRIdx = TileBomb::SetColIndex(midmPos + Vector2(32.0f, 0.0f));
		//ColLIdx = TileBomb::SetColIndex(midmPos + Vector2(-32.0f, 0.0f));
		//ColUIdx = TileBomb::SetColIndex(midmPos + Vector2(0.0f, -32.0f));
		//ColDIdx = TileBomb::SetColIndex(midmPos + Vector2(0.0f, +32.0f));

		//mTime += Time::DeltaTime();
		//if (ColRIdx.x > 14)
		//	ColRIdx.x = 14;
		//if (ColLIdx.x > 14)
		//	ColLIdx.x = 14;
		//if (ColUIdx.x > 14)
		//	ColUIdx.x = 14;
		//if (ColDIdx.x > 14)
		//	ColDIdx.x = 14;

		//if (ColRIdx.y > 12)
		//	ColRIdx.y = 12;
		//if (ColLIdx.y > 12)
		//	ColLIdx.y = 12;
		//if (ColUIdx.y > 12)
		//	ColUIdx.y = 12;
		//if (ColDIdx.y > 12)
		//	ColDIdx.y = 12;


		mTime += Time::DeltaTime();
		TimeSpend += Time::DeltaTime();
		if (TimeSpend >= 1.5f)
		{
			switch (mState)
			{
			case ty::ToyBoss::eToyBossState::Idle:
				idle();
				break;
			case ty::ToyBoss::eToyBossState::Attack:
				attack();
				break;
			case ty::ToyBoss::eToyBossState::Hit:
				hit();
				break;
			case ty::ToyBoss::eToyBossState::Die:
				die();
				break;
			default:
				break;
			}
		}

		if (mTime >= 5 && mState != eToyBossState::Die && mState != eToyBossState::Hit && mState != eToyBossState::Bubble)
		{
			mState = eToyBossState::Idle;
		
			mTime = 0;
		}
	}
	void ToyBoss::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void ToyBoss::Release()
	{
	}
	void ToyBoss::OnCollisionEnter(Collider* other)
	{
		if (isColl == false && Hp >= 1 && other->GetOwner()->GetName() == L"BombEffect")
		{
			mState = eToyBossState::Hit;
		}

		if (isColl == false && Hp <= 0 && other->GetOwner()->GetName() == L"BombEffect" && mState != eToyBossState::Bubble)
		{
			mState = eToyBossState::Die;
		}

		if (mState == eToyBossState::Bubble && other->GetOwner()->GetName() == L"Bazzi")
		{
			
		}
	}
	void ToyBoss::OnCollisionStay(Collider* other)
	{
	}
	void ToyBoss::OnCollisionExit(Collider* other)
	{
	}
	void ToyBoss::idle()
	{
		mState = (eToyBossState)((rand() % 2));
		if (mState == eToyBossState::Attack)
		{
			isAttack = true;
		}
	}

	void ToyBoss::left()
	{
		mAnimator->Play(L"ToyBossLeft", false);
	}

	void ToyBoss::right()
	{
		mAnimator->Play(L"ToyBossRight", false);
	}

	void ToyBoss::up()
	{
		mAnimator->Play(L"ToyBossUp", false);
	}

	void ToyBoss::down()
	{
		mAnimator->Play(L"ToyBossDown", false);
	}

	void ToyBoss::hit()
	{
		mInvincibility -= Time::DeltaTime();
		if (mInvincibility <= 0)
			{
				Hp--;
				mState = eToyBossState::Idle;
				isColl = false;
				mInvincibility = 1;
		}
	}

	void ToyBoss::attack()
	{
		if (isAttack == true)
		{
			for (int i = 0; i < 7; i++)
			{
				eToyBossState::Idle;
				object::Instantiate<BossBombEffect>(TileBomb::SetPos(Vector2(450.0f,360.0f) + Vector2(180, 180 - (i * 60))), eLayerType::BombEffect); // 두개씩 증가
				object::Instantiate<BossBombEffect>(TileBomb::SetPos(Vector2(450.0f, 360.0f) + Vector2(180 - (i * 60), 180)), eLayerType::BombEffect);
				object::Instantiate<BossBombEffect>(TileBomb::SetPos(Vector2(450.0f, 360.0f) + Vector2(-180 + (i * 60), -180)), eLayerType::BombEffect);
				object::Instantiate<BossBombEffect>(TileBomb::SetPos(Vector2(450.0f, 360.0f) + Vector2(-180, 180 - (i * 60))), eLayerType::BombEffect);
				isAttack = false;
			}
			
			for (int i = 0; i < 9; i++)
			{
				object::Instantiate<BossBombEffect>(TileBomb::SetPos(Vector2(450.0f, 360.0f) + Vector2(240, 240 - (i * 60))), eLayerType::BombEffect); // 우측
				object::Instantiate<BossBombEffect>(TileBomb::SetPos(Vector2(450.0f, 360.0f) + Vector2(240 - (i * 60), 240)), eLayerType::BombEffect);
				object::Instantiate<BossBombEffect>(TileBomb::SetPos(Vector2(450.0f, 360.0f) + Vector2(-240 + (i * 60), -240)), eLayerType::BombEffect);
				object::Instantiate<BossBombEffect>(TileBomb::SetPos(Vector2(450.0f, 360.0f) + Vector2(-240, 240 - (i * 60))), eLayerType::BombEffect);
			}

			for (int i = 0; i < 11; i++)
			{
				object::Instantiate<BossBombEffect>(TileBomb::SetPos(Vector2(450.0f, 360.0f) + Vector2(300, 300 - (i * 60))), eLayerType::BombEffect); // 우측
				object::Instantiate<BossBombEffect>(TileBomb::SetPos(Vector2(450.0f, 360.0f) + Vector2(300 - (i * 60), 300)), eLayerType::BombEffect);
				object::Instantiate<BossBombEffect>(TileBomb::SetPos(Vector2(450.0f, 360.0f) + Vector2(-300 + (i * 60), -300)), eLayerType::BombEffect);
				object::Instantiate<BossBombEffect>(TileBomb::SetPos(Vector2(450.0f, 360.0f) + Vector2(-300, 300 - (i * 60))), eLayerType::BombEffect);
			}

			for (int i = 0; i < 13; i++)
			{
				object::Instantiate<BossBombEffect>(TileBomb::SetPos(Vector2(450.0f, 360.0f) + Vector2(360, 360 - (i * 60))), eLayerType::BombEffect); // 우측
				object::Instantiate<BossBombEffect>(TileBomb::SetPos(Vector2(450.0f, 360.0f) + Vector2(360 - (i * 60), 360)), eLayerType::BombEffect);
				object::Instantiate<BossBombEffect>(TileBomb::SetPos(Vector2(450.0f, 360.0f) + Vector2(-360 + (i * 60), -360)), eLayerType::BombEffect);
				object::Instantiate<BossBombEffect>(TileBomb::SetPos(Vector2(450.0f, 360.0f) + Vector2(-360, 300 - (i * 60))), eLayerType::BombEffect);
			}

			if (rand_num < 0.25f)
			{
				left();
			}
			else if (rand_num < 0.5f)
			{
				right();
			}
			else if (rand_num < 0.75f)
			{
				up();
			}
			else if (rand_num < 1.0f)
			{
				down();
			}
		}
	}
	void ToyBoss::bubble()
	{
	}
	void ToyBoss::die()
	{
	
			int monstercnt = SceneManager::GetMonsterCnt();
			monstercnt--;
			SceneManager::SetMonsterCnt(monstercnt);
			mState = eToyBossState::Idle;
			object::Pause(this);
	}
	void ToyBoss::animationCtr()
	{
	}
	void ToyBoss::bubbleCompleteEvent()
	{
	}
	void ToyBoss::attack2()
	{
	}
}