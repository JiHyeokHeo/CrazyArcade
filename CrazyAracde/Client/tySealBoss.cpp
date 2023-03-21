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

namespace ty
{
	SealBoss::SealBoss()
	{
	}
	SealBoss::~SealBoss()
	{
	}
	void SealBoss::Initialize()
	{
		
		mmAnimator = AddComponent<Animator>();
		mmAnimator->CreateAnimations(L"..\\Resources\\Monster\\Seal\\Attack", Vector2::Zero, 0.1f);
		mmAnimator->CreateAnimations(L"..\\Resources\\Monster\\Seal\\Die", Vector2::Zero, 0.1f);
		mmAnimator->CreateAnimations(L"..\\Resources\\Monster\\Seal\\Down", Vector2::Zero, 0.1f);
		mmAnimator->CreateAnimations(L"..\\Resources\\Monster\\Seal\\Up", Vector2::Zero, 0.1f);
		mmAnimator->CreateAnimations(L"..\\Resources\\Monster\\Seal\\Hit", Vector2::Zero, 0.1f);
		mmAnimator->CreateAnimations(L"..\\Resources\\Monster\\Seal\\Left", Vector2::Zero, 0.1f);
		mmAnimator->CreateAnimations(L"..\\Resources\\Monster\\Seal\\LeftRoll", Vector2::Zero, 0.1f);
		mmAnimator->CreateAnimations(L"..\\Resources\\Monster\\Seal\\Right", Vector2::Zero, 0.1f);
		mmAnimator->CreateAnimations(L"..\\Resources\\Monster\\Seal\\RightRoll", Vector2::Zero, 0.1f);
		//Image* mDieImage = Resources::Load<Image>(L"BazziDie", L"..\\Resources\\Bazzi\\die.bmp");
		//Image* mTrapeImage = Resources::Load<Image>(L"BazziTrap", L"..\\Resources\\Bazzi\\trap.bmp");


		mmAnimator->Play(L"SealDown", true);

		Collider* collider = AddComponent<Collider>();
		collider->SetCenter(Vector2::Zero);
		collider->SetSize(Vector2(44.0f, 44.0f));
		mState = eSealBossState::Idle;
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
		case ty::SealBoss::eSealBossState::Idle:
			idle();
			break;
		case ty::SealBoss::eSealBossState::Left:
			left();
			break;
		case ty::SealBoss::eSealBossState::Right:
			right();
			break;
		case ty::SealBoss::eSealBossState::Up:
			up();
			break;
		case ty::SealBoss::eSealBossState::Down:
			down();
			break;
		case ty::SealBoss::eSealBossState::Hit:
			hit();
			break;
		case ty::SealBoss::eSealBossState::Die:
			die();
			break;
		default:
			break;
		}

		tr->SetPos(mPos);

		if (mTime >= 1 && mState != eSealBossState::Die && mState != eSealBossState::Hit)
		{
			mState = eSealBossState::Idle;
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
		GameObject::Release();
	}
	void SealBoss::OnCollisionEnter(Collider* other)
	{
	}
	void SealBoss::OnCollisionStay(Collider* other)
	{
	}
	void SealBoss::OnCollisionExit(Collider* other)
	{
	}
	void SealBoss::idle()
	{
		//mState = (eSealBossState)((rand() % 5));
		//animationCtr();
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
	}
	void SealBoss::die()
	{
	}
	void SealBoss::animationCtr()
	{
		switch (mState)
		{
		case ty::SealBoss::eSealBossState::Idle:
			break;
		case ty::SealBoss::eSealBossState::Left:
			mmAnimator->Play(L"SealLeft", true);
			break;
		case ty::SealBoss::eSealBossState::Right:
			//mAnimator->Play(L"SealRight", true);
			break;
		case ty::SealBoss::eSealBossState::Up:
			mmAnimator->Play(L"SealUp", true);
			break;
		case ty::SealBoss::eSealBossState::Down:
			mmAnimator->Play(L"SealDown", true);
			break;
		default:
			break;
		}
	}
}