#include "tyBombEffect.h"
#include "tyTime.h"
#include "tySceneManager.h"
#include "tyinput.h"
#include "tyResources.h"
#include "tyTransform.h"
#include "tyAnimator.h"
#include "tyCollider.h"
#include "tyObject.h"
#include "tyBazzi.h"
#include "tyPlayScene.h"
#include "tyBaseBomb.h"
#include "tySound.h"
#include "tyResources.h"

namespace ty
{
	BombEffect::BombEffect()
	{
	}
	BombEffect::~BombEffect()
	{
	}
	void BombEffect::Initialize()
	{
		SetName(L"BombEffect");
		mBombEffect = Resources::Load<Sound>(L"mBombEffect", L"..\\Resources\\Sound\\wave.wav");
		Transform* tr = GetComponent<Transform>();
		EffectPos = tr->GetPos();
		//tr->SetPos(Vector2(400.0f, 400.0f));
		tr->SetScale(Vector2(1.5f, 1.5f));
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Bomb\\Downflow", Vector2::Zero, 0.16f);
		mAnimator->CreateAnimations(L"..\\Resources\\Bomb\\DownIdleflow", Vector2::Zero, 0.16f);
		mAnimator->CreateAnimations(L"..\\Resources\\Bomb\\Upflow", Vector2::Zero, 0.16f);
		mAnimator->CreateAnimations(L"..\\Resources\\Bomb\\UpIdleflow", Vector2::Zero, 0.16f);
		mAnimator->CreateAnimations(L"..\\Resources\\Bomb\\Rightflow", Vector2::Zero, 0.16f);
		mAnimator->CreateAnimations(L"..\\Resources\\Bomb\\RightIdleflow", Vector2::Zero, 0.16f);
		mAnimator->CreateAnimations(L"..\\Resources\\Bomb\\Leftflow", Vector2::Zero, 0.16f);
		mAnimator->CreateAnimations(L"..\\Resources\\Bomb\\LeftIdleflow", Vector2::Zero, 0.16f);
		mAnimator->CreateAnimations(L"..\\Resources\\Bomb\\Centerflow", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Bomb\\None", Vector2::Zero, 0.16f);
		mState = eBombEffectState::Idle;
		/*mAnimator->Play(L"BombUpflow", true);*/
		//mAnimator->GetEndEvent(L"BombDownflow") = std::bind(&BombEffect::bombCompleteEvent, this);
		//mAnimator->Play(L"BombUpflow", false);
		GameObject::Initialize();

	}
	void BombEffect::Update()
	{
		mTime += Time::DeltaTime();
		
		switch (mState)
		{
		case ty::BombEffect::eBombEffectState::Idle:
			idle();
			break;
		case ty::BombEffect::eBombEffectState::Bombed:
			bombed();
			break;
		default:
			break;
		}

		GameObject::Update();
	
		// 여기서 삭제시켜버려라
	}
	void BombEffect::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void BombEffect::Release()
	{
		GameObject::Release();
	}
	void BombEffect::OnCollisionEnter(Collider* other)
	{
		if (other->GetOwner()->GetName() == L"Ground")
		{
			object::Destroy(this);
		}
		if (other->GetOwner()->GetName() == L"Tile" && other->GetOwner()->GetState() == eState::Active)
		{
			object::Destroy(this);
		}
	
	}
	void BombEffect::OnCollisionStay(Collider* other)
	{
		if (other->GetOwner()->GetName() == L"Ground")
			object::Destroy(this);
	}
	void BombEffect::OnCollisionExit(Collider* other)
	{
	}
	void BombEffect::idle()
	{
		
			mBaseBombPos = mBaseBomb->GetComponent<Transform>()->GetPos();

			if (mBaseBombPos.x > EffectPos.x && mBaseBombPos.y == EffectPos.y)
			{
				mAnimator->Play(L"BombLeftflow", false);
			}
			else if (mBaseBombPos.x < EffectPos.x && mBaseBombPos.y == EffectPos.y)
			{
				mAnimator->Play(L"BombRightflow", false);
			}
			else if (mBaseBombPos.x == EffectPos.x && mBaseBombPos.y < EffectPos.y)
			{
				mAnimator->Play(L"BombDownflow", false);
			}
			else if (mBaseBombPos.x == EffectPos.x && mBaseBombPos.y > EffectPos.y)
			{
				mAnimator->Play(L"BombUpflow", false);
			}
			else if (mBaseBombPos.x == EffectPos.x && mBaseBombPos.y == EffectPos.y)
			{
				mAnimator->Play(L"BombCenterflow", false);
			}

			if (isMake == false)
			{
				mBombEffect->Play(false);
				Collider* collider = AddComponent<Collider>();
				collider->SetCenter(Vector2(15.00f, 15.00f));
				collider->SetSize(Vector2(30.0f, 30.0f));
				mState = eBombEffectState::Bombed;
				mTime = 0;
				isMake = true;
			}
		
	}
	void BombEffect::bombed()
	{
		if(mAnimator->isComplete() == true)
 		object::Destroy(this);
	}
}