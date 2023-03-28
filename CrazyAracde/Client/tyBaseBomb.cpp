#include "tyBaseBomb.h"
#include "tyTransform.h"
#include "tyTime.h"
#include "tyCollider.h"
#include "tyGameObject.h"
#include "tyAnimator.h"
#include "tyObject.h"
#include "tyBombEffect.h"
#include "tyinput.h"
#include "tyPlayScene.h"
#include "tyBazzi.h"

namespace ty
{
	
	BaseBomb::BaseBomb()
		: mTime(0.0f)
		, maxWaterWave(7)
	{	
	
	}
	BaseBomb::~BaseBomb()
	{

	}
	void BaseBomb::Initialize()
	{
		SetName(L"BaseBomb");
		

    	Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector2(1.5f, 1.5f));
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Bomb\\Idle", Vector2(11.76f, 22.84f), 0.16f);
		mAnimator->Play(L"BombIdle", true);

		Collider* collider = AddComponent<Collider>();
		collider->SetCenter(Vector2(12.76f, 22.84f));
		collider->SetSize(Vector2(60.0f, 60.0f));
		for (int i = 1; i < 5; i++)
		{
			mBombEffect = object::Instantiate<BombEffect>(tr->GetPos() + Vector2((float)(i * 60.0f), 0.0f), eLayerType::BombEffect);
			mBombEffect->SetBomb(this);
			mBombEffect = object::Instantiate<BombEffect>(tr->GetPos() + Vector2(0.0f, float(i * 60.0f)), eLayerType::BombEffect);
			mBombEffect->SetBomb(this);
			mBombEffect = object::Instantiate<BombEffect>(tr->GetPos() - Vector2((float)(i * 60.0f), 0.0f), eLayerType::BombEffect);
			mBombEffect->SetBomb(this);
			mBombEffect = object::Instantiate<BombEffect>(tr->GetPos() - Vector2(0.0f, (float)(i * 60.0f)), eLayerType::BombEffect);
			mBombEffect->SetBomb(this);
			mBombEffect = object::Instantiate<BombEffect>(tr->GetPos(), eLayerType::BombEffect);
			mBombEffect->SetBomb(this);
		}

		
		mState = eBombState::Idle;
		
		GameObject::Initialize();
	}

	void BaseBomb::Update()
	{
		
		GameObject::Update();
		Transform* tr = GetComponent<Transform>();

		BazziPos = PlayScene::GetBazzi()->GetComponent<Transform>()->GetPos();

		mTime += Time::DeltaTime();

		switch (mState)
		{
		case ty::BaseBomb::eBombState::Idle:
			idle();
			break;
		case ty::BaseBomb::eBombState::Bombed:
			bombed();
			break;
		default:
			break;
		}
	
    }
	
	void BaseBomb::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void BaseBomb::Release()
	{
		GameObject::Release();
	}
	void BaseBomb::OnCollisionEnter(Collider* other)
	{
	}
	void BaseBomb::OnCollisionStay(Collider* other)
	{
	}
	void BaseBomb::OnCollisionExit(Collider* other)
	{
	}

	void BaseBomb::bombed()
	{
		object::Destroy(this);
	}

	void BaseBomb::idle()
	{
	
		if (mTime >= 3.0f)
		{
			
			mState = eBombState::Bombed;
		}
	}

}