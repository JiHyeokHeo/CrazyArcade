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

namespace ty
{
	PirateBoss::PirateBoss()
		: Hp(1)
	{
	}
	PirateBoss::~PirateBoss()
	{
	}
	void PirateBoss::Initialize()
	{
		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector2(2.0f, 2.0f));
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Monster\\PirateBoss\\Up", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Monster\\PirateBoss\\Right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Monster\\PirateBoss\\Left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Monster\\PirateBoss\\Down", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Monster\\PirateBoss\\Bubble", Vector2::Zero, 0.3f);
		mAnimator->CreateAnimations(L"..\\Resources\\Monster\\PirateBoss\\Hit", Vector2::Zero, 0.3f);
		mAnimator->CreateAnimations(L"..\\Resources\\Monster\\PirateBoss\\Die", Vector2::Zero, 0.6f);

		mAnimator->GetCompleteEvent(L"PirateBossDie") = std::bind(&PirateBoss::bubbleCompleteEvent, this);


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
		if (isColl == false && Hp >=1)
		{
			mAnimator->Play(L"PirateBossHit", false);
			mState = ePirateMonsterState::Hit;
			isColl = true;
		}

		if (isColl == false && Hp <= 0)
		{
			mAnimator->Play(L"PirateBossBubble", false);
			mState = ePirateMonsterState::Bubble;
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
		mState = (ePirateMonsterState)((rand() % 6));
		animationCtr();
	}
	void PirateBoss::attack()
	{
		Transform* tr = GetComponent<Transform>();

		if (isAttack == true)
		{
			for (int i = 0; i < 7; i++)
			{
				ePirateMonsterState::Idle;
				object::Instantiate<BossBombEffect>(tr->GetPos() + Vector2(180 , 180 - (i * 60)), eLayerType::BombEffect);
				object::Instantiate<BossBombEffect>(tr->GetPos() + Vector2(180 - (i * 60), 180), eLayerType::BombEffect);
				object::Instantiate<BossBombEffect>(tr->GetPos() + Vector2(-180 + (i * 60), -180), eLayerType::BombEffect);
				object::Instantiate<BossBombEffect>(tr->GetPos() + Vector2(-180, 180 - (i * 60)), eLayerType::BombEffect);
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
				mInvincibility = 3;
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
		if (mAnimator->isComplete() == true)
		{
			object::Destroy(this);
		}
	}
}

