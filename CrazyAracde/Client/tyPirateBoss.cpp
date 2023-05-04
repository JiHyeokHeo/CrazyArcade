#include "tyPirateBoss.h"
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
	PirateBoss::PirateBoss()
		: Hp(5)
	{
	}
	PirateBoss::~PirateBoss()
	{
	}
	void PirateBoss::Initialize()
	{
		SetName(L"Boss");
		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector2(2.0f, 2.0f));
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Monster\\PirateBoss\\Up", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Monster\\PirateBoss\\Right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Monster\\PirateBoss\\Left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Monster\\PirateBoss\\Down", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Monster\\PirateBoss\\Bubble", Vector2::Zero, 0.3f);
		mAnimator->CreateAnimations(L"..\\Resources\\Monster\\PirateBoss\\Hit", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Monster\\PirateBoss\\Die", Vector2::Zero, 0.6f);

		mAnimator->GetCompleteEvent(L"PirateBossBubble") = std::bind(&PirateBoss::bubbleCompleteEvent, this);


		mAnimator->Play(L"PirateBossDown", false);

		Collider* collider = AddComponent<Collider>();
		collider->SetCenter(Vector2(30.0f, 30.0f));
		collider->SetSize(Vector2(120.0f, 150.0f));
		mState = ePirateMonsterState::Idle;
		GameObject::Initialize();
	}
	void PirateBoss::Update()
	{
		tr = GetComponent<Transform>();
		mPos = tr->GetPos();
		midmPos = mPos + Vector2(TILE_SIZE_X / 2, TILE_SIZE_Y / 2);
		ColRIdx = TileBomb::SetColIndex(midmPos + Vector2(32.0f, 0.0f));
		ColLIdx = TileBomb::SetColIndex(midmPos + Vector2(-32.0f, 0.0f));
		ColUIdx = TileBomb::SetColIndex(midmPos + Vector2(0.0f, -32.0f));
		ColDIdx = TileBomb::SetColIndex(midmPos + Vector2(0.0f, +32.0f));

		mTime += Time::DeltaTime();
		if (ColRIdx.x > 14)
			ColRIdx.x = 14;
		if (ColLIdx.x > 14)
			ColLIdx.x = 14;
		if (ColUIdx.x > 14)
			ColUIdx.x = 14;
		if (ColDIdx.x > 14)
			ColDIdx.x = 14;

		if (ColRIdx.y > 12)
			ColRIdx.y = 12;
		if (ColLIdx.y > 12)
			ColLIdx.y = 12;
		if (ColUIdx.y > 12)
			ColUIdx.y = 12;
		if (ColDIdx.y > 12)
			ColDIdx.y = 12;


		mTime += Time::DeltaTime();
		TimeSpend += Time::DeltaTime();
		if (TimeSpend >= 1.5f)
		{
			switch (mState)
			{
			case ty::PirateBoss::ePirateMonsterState::Idle:
				idle();
				break;
			case ty::PirateBoss::ePirateMonsterState::Attack:
				attack();
				break;
			case ty::PirateBoss::ePirateMonsterState::Left:
				left();
				break;
			case ty::PirateBoss::ePirateMonsterState::Right:
				right();
				break;
			case ty::PirateBoss::ePirateMonsterState::Up:
				up();
				break;
			case ty::PirateBoss::ePirateMonsterState::Down:
				down();
				break;
			case ty::PirateBoss::ePirateMonsterState::Hit:
				hit();
				break;
			case ty::PirateBoss::ePirateMonsterState::Bubble:
				bubble();
				break;
			case ty::PirateBoss::ePirateMonsterState::Die:
				die();
				break;

			default:
				break;
			}
		}

		tr->SetPos(mPos);

		if (mTime >= 1 && mState != ePirateMonsterState::Die && mState != ePirateMonsterState::Hit && mState != ePirateMonsterState::Bubble)
		{
			mState = ePirateMonsterState::Idle;
			mTime = 0;
		}
		GameObject::Update();
	}
	void PirateBoss::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void PirateBoss::Release()
	{

	}
	void PirateBoss::OnCollisionEnter(Collider* other)
  	{
		if (other->GetOwner()->GetName() == L"Ground" || other->GetOwner()->GetName() == L"Monster")
		{
			switch (mState)
			{
			case ePirateMonsterState::Left:
				mState = ePirateMonsterState::Right;
				break;
			case ePirateMonsterState::Right:
				mState = ePirateMonsterState::Left;
				break;
			case ePirateMonsterState::Up:
				mState = ePirateMonsterState::Down;
				break;
			case ePirateMonsterState::Down:
				mState = ePirateMonsterState::Up;
				break;
			default:
				break;
			}
		}
		if (isColl == false && Hp >=1 && other->GetOwner()->GetName() == L"BombEffect")
		{
			mAnimator->Play(L"PirateBossHit", false);
			mState = ePirateMonsterState::Hit;
			isColl = true;
		}

		if (isColl == false && Hp <= 0 && other->GetOwner()->GetName() == L"BombEffect" && mState != ePirateMonsterState::Bubble)
		{
			mAnimator->Play(L"PirateBossBubble", false);
			mState = ePirateMonsterState::Bubble;
 			isColl = true;
		}

		if (mState == ePirateMonsterState::Bubble && other->GetOwner()->GetName() == L"Bazzi")
		{
			mAnimator->Play(L"PirateBossDie", false);
			mState = ePirateMonsterState::Die;
			isColl = true;
		}
	

	}
	void PirateBoss::OnCollisionStay(Collider* other)
	{
		
	}
	void PirateBoss::OnCollisionExit(Collider* other)
	{
	}
	void PirateBoss::idle()
	{
		mState = (ePirateMonsterState)((rand() % 5));
		animationCtr();
	}
	void PirateBoss::attack()
	{

		if (isAttack == true)
		{
			for (int i = 0; i < 7; i++)
			{
				ePirateMonsterState::Idle;
				object::Instantiate<BossBombEffect>(TileBomb::SetPos(midmPos + Vector2(180 , 180 - (i * 60))), eLayerType::BombEffect);
				object::Instantiate<BossBombEffect>(TileBomb::SetPos(midmPos + Vector2(180 - (i * 60), 180)), eLayerType::BombEffect);
				object::Instantiate<BossBombEffect>(TileBomb::SetPos(midmPos + Vector2(-180 + (i * 60), -180)), eLayerType::BombEffect);
				object::Instantiate<BossBombEffect>(TileBomb::SetPos(midmPos + Vector2(-180, 180 - (i * 60))), eLayerType::BombEffect);
				isAttack = false;
			}
		}
		
	}
	void PirateBoss::left()
	{
		mPos.x -= 60.0f * Time::DeltaTime();
	}

	void PirateBoss::right()
	{
		mPos.x += 60.0f * Time::DeltaTime();
	}
	void PirateBoss::up()
	{
		mPos.y -= 60.0f * Time::DeltaTime();
	}
	void PirateBoss::down()
	{
		mPos.y += 60.0f * Time::DeltaTime();
	}
	void PirateBoss::hit()
	{
		
		mInvincibility -= Time::DeltaTime();
		if (mAnimator->isComplete() == true)
		{
			if (mInvincibility <=0)
			{
				Hp--;
				mState = ePirateMonsterState::Idle;
				isColl = false;
				mInvincibility = 1;
			}
		}
	}
	void PirateBoss::bubble()
	{
		mInvincibility -= Time::DeltaTime();
		if (mAnimator->isComplete() == true)
		{
			mAnimator->Play(L"PirateBossDie", false);
			ePirateMonsterState::Die;
			mInvincibility = 3;
		}
	}
	void PirateBoss::die()
	{
		if (mAnimator->isComplete() == true)
		{
			int monstercnt = SceneManager::GetMonsterCnt();
			monstercnt--;
			SceneManager::SetMonsterCnt(monstercnt);
			mState = ePirateMonsterState::Idle;
			object::Pause(this);
		}
	}
	void PirateBoss::animationCtr()
	{
		switch (mState)
		{
		case ty::PirateBoss::ePirateMonsterState::Idle:
			break;
		case ty::PirateBoss::ePirateMonsterState::Attack:
			isAttack = true;
			break;
		case ty::PirateBoss::ePirateMonsterState::Left:
			mAnimator->Play(L"PirateBossLeft", true);
			break;
		case ty::PirateBoss::ePirateMonsterState::Right:
			mAnimator->Play(L"PirateBossRight", true);
			break;
		case ty::PirateBoss::ePirateMonsterState::Up:
			mAnimator->Play(L"PirateBossUp", true);
			break;
		case ty::PirateBoss::ePirateMonsterState::Down:
			mAnimator->Play(L"PirateBossDown", true);
			break;
		default:
			break;
		}
	}
	void PirateBoss::bubbleCompleteEvent()
	{
		mState = ePirateMonsterState::Die;
	}
}

