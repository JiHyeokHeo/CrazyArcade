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

namespace ty
{
	PirateBoss::PirateBoss()
		: Hp(2)
	{
	}
	PirateBoss::~PirateBoss()
	{
	}
	void PirateBoss::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Monster\\PirateBoss\\Up", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Monster\\PirateBoss\\Right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Monster\\PirateBoss\\Left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Monster\\PirateBoss\\Down", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Monster\\PirateBoss\\Die", Vector2::Zero, 0.2f);
		mAnimator->CreateAnimations(L"..\\Resources\\Monster\\PirateBoss\\Hit", Vector2::Zero, 0.3f);




		mAnimator->Play(L"PirateBossDown", true);

		Collider* collider = AddComponent<Collider>();
		collider->SetCenter(Vector2::Zero);
		collider->SetSize(Vector2(44.0f, 44.0f));
		mState = ePirateMonsterState::Idle;
		GameObject::Initialize();
	}
	void PirateBoss::Update()
	{
		Transform* tr = GetComponent<Transform>();
		mPos = tr->GetPos();

		mTime += Time::DeltaTime();
		mInvincibility += Time::DeltaTime();
		switch (mState)
		{
		case ty::PirateBoss::ePirateMonsterState::Idle:
			idle();
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
		case ty::PirateBoss::ePirateMonsterState::Die:
			die();
			break;
		default:
			break;
		}

		tr->SetPos(mPos);

		if (mTime >= 1 && mState != ePirateMonsterState::Die && mState != ePirateMonsterState::Hit)
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
		if (isColl == false && Hp >=1)
		{
			mAnimator->Play(L"PirateBossHit", false);
			mState = ePirateMonsterState::Hit;
			isColl = true;
			Hp--;
		}

		if (isColl == false && Hp <= 0)
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
	void PirateBoss::left()
	{
		mPos.x -= 50.0f * Time::DeltaTime();

	}

	void PirateBoss::right()
	{
		mPos.x += 50.0f * Time::DeltaTime();
	}
	void PirateBoss::up()
	{
		mPos.y -= 50.0f * Time::DeltaTime();
	}
	void PirateBoss::down()
	{
		mPos.y += 50.0f * Time::DeltaTime();
	}
	void PirateBoss::hit()
	{
		mInvincibility += Time::DeltaTime();
		if (mAnimator->isComplete() == true)
		{
			if (mInvincibility >= 3)
			{
				mState = ePirateMonsterState::Idle;
				isColl = false;
				mInvincibility = 0;
			}
		}
	}
	void PirateBoss::die()
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
	void PirateBoss::animationCtr()
	{
		switch (mState)
		{
		case ty::PirateBoss::ePirateMonsterState::Idle:
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
}

