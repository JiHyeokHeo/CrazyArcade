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
		
		Transform* tr = GetComponent<Transform>();
		EffectPos = tr->GetPos();
		//tr->SetPos(Vector2(400.0f, 400.0f));
		tr->SetScale(Vector2(1.5f, 1.5f));
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Bomb\\Downflow", Vector2(11.76f, 22.84f), 0.16f);
		mAnimator->CreateAnimations(L"..\\Resources\\Bomb\\DownIdleflow", Vector2(11.76f, 22.84f), 0.16f);
		mAnimator->CreateAnimations(L"..\\Resources\\Bomb\\Upflow", Vector2(11.76f, 22.84f), 0.16f);
		mAnimator->CreateAnimations(L"..\\Resources\\Bomb\\UpIdleflow", Vector2(11.76f, 22.84f), 0.16f);
		mAnimator->CreateAnimations(L"..\\Resources\\Bomb\\Rightflow", Vector2(11.76f, 22.84f), 0.16f);
		mAnimator->CreateAnimations(L"..\\Resources\\Bomb\\RightIdleflow", Vector2(11.76f, 22.84f), 0.16f);
		mAnimator->CreateAnimations(L"..\\Resources\\Bomb\\Leftflow", Vector2(11.76f, 22.84f), 0.16f);
		mAnimator->CreateAnimations(L"..\\Resources\\Bomb\\LeftIdleflow", Vector2(11.76f, 22.84f), 0.16f);
		mAnimator->CreateAnimations(L"..\\Resources\\Bomb\\Centerflow", Vector2(11.76f, 22.84f), 0.16f);
		mAnimator->CreateAnimations(L"..\\Resources\\Bomb\\None", Vector2(11.76f, 22.84f), 0.16f);
		mState = eBombEffectState::Idle;
		
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
		if (mTime >= 3.0f)
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

			Collider* collider = AddComponent<Collider>();
			collider->SetCenter(Vector2(11.76f, 21.84f));
			collider->SetSize(Vector2(58.0f, 58.0f));
			mState = eBombEffectState::Bombed;
		}
	}
	void BombEffect::bombed()
	{
		if(mAnimator->isComplete() == true)
 		object::Destroy(this);
	}
}