#include "tySealBoss.h"
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

namespace ty
{
	SealBoss::SealBoss()
		: Hp(2)
	{
	}
	SealBoss::~SealBoss()
	{
	}
	void SealBoss::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Monster\\SealBoss\\Up", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Monster\\SealBoss\\Down", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Monster\\SealBoss\\Left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Monster\\SealBoss\\Right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Monster\\SealBoss\\Die", Vector2::Zero, 0.5f);
		mAnimator->CreateAnimations(L"..\\Resources\\Monster\\SealBoss\\Hit", Vector2::Zero, 0.3f);




		mAnimator->Play(L"SealBossDown", true);

		Collider* collider = AddComponent<Collider>();
		collider->SetCenter(Vector2::Zero);
		collider->SetSize(Vector2(44.0f, 44.0f));
		mState = eSealMonsterState::Idle;
		GameObject::Initialize();
	}
	void SealBoss::Update()
	{
		Transform* tr = GetComponent<Transform>();
		mPos = tr->GetPos();

		mTime += Time::DeltaTime();
		mInvincibility += Time::DeltaTime();
		switch (mState)
		{
		case ty::SealBoss::eSealMonsterState::Idle:
			idle();
			break;
		case ty::SealBoss::eSealMonsterState::Left:
			left();
			break;
		case ty::SealBoss::eSealMonsterState::Right:
			right();
			break;
		case ty::SealBoss::eSealMonsterState::Up:
			up();
			break;
		case ty::SealBoss::eSealMonsterState::Down:
			down();
			break;
		case ty::SealBoss::eSealMonsterState::Hit:
			hit();
			break;
		case ty::SealBoss::eSealMonsterState::Die:
			die();
			break;
		default:
			break;
		}

		tr->SetPos(mPos);

		if (mTime >= 1 && mState != eSealMonsterState::Die && mState != eSealMonsterState::Hit)
		{
			mState = eSealMonsterState::Idle;
			mTime = 0;
		}
		GameObject::Update();
	}
	void SealBoss::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void SealBoss::Release()
	{

	}
	void SealBoss::OnCollisionEnter(Collider* other)
	{
		if (isColl == false && Hp >= 1)
		{
			mAnimator->Play(L"SealBossHit", false);
			mState = eSealMonsterState::Hit;
			isColl = true;
			Hp--;
		}

		if (isColl == false && Hp <= 0)
		{
			mAnimator->Play(L"SealBossDie", false);
			mState = eSealMonsterState::Die;
			isColl = true;
		}


	}
	void SealBoss::OnCollisionStay(Collider* other)
	{
	}
	void SealBoss::OnCollisionExit(Collider* other)
	{
	}
	void SealBoss::idle()
	{
		mState = (eSealMonsterState)((rand() % 5));
		animationCtr();
	}
	void SealBoss::left()
	{
		mPos.x -= 50.0f * Time::DeltaTime();

	}

	void SealBoss::right()
	{
		mPos.x += 50.0f * Time::DeltaTime();
	}
	void SealBoss::up()
	{
		mPos.y -= 50.0f * Time::DeltaTime();
	}
	void SealBoss::down()
	{
		mPos.y += 50.0f * Time::DeltaTime();
	}
	void SealBoss::hit()
	{
		mInvincibility += Time::DeltaTime();
		if (mAnimator->isComplete() == true)
		{
			if (mInvincibility >= 3)
			{
				mState = eSealMonsterState::Idle;
				isColl = false;
				mInvincibility = 0;
			}
		}
	}
	void SealBoss::die()
	{
		mInvincibility += Time::DeltaTime();
		if (mAnimator->isComplete() == true)
		{
			object::Destroy(this);
			if (mInvincibility >= 3)
			{
				isColl = false;
				mInvincibility = 0;
			}
		}
	}
	void SealBoss::animationCtr()
	{
		switch (mState)
		{
		case ty::SealBoss::eSealMonsterState::Idle:
			break;
		case ty::SealBoss::eSealMonsterState::Left:
			mAnimator->Play(L"SealBossLeft", true);
			break;
		case ty::SealBoss::eSealMonsterState::Right:
			mAnimator->Play(L"SealBossRight", true);
			break;
		case ty::SealBoss::eSealMonsterState::Up:
			mAnimator->Play(L"SealBossUp", true);
			break;
		case ty::SealBoss::eSealMonsterState::Down:
			mAnimator->Play(L"SealBossDown", true);
			break;
		default:
			break;
		}
	}
}