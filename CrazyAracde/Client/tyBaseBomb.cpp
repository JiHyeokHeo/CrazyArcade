#include "tyBaseBomb.h"
#include "tyTransform.h"
#include "tyTime.h"
#include "tyCollider.h"
#include "tyGameObject.h"
#include "tyAnimator.h"
#include "tyObject.h"
#include "tyBombEffect.h"


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
    	Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector2(1.5f, 1.5f));

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Bomb\\Idle", Vector2(11.76f, 22.84f), 0.16f);
		mAnimator->Play(L"BombIdle", true);

		Collider* collider = AddComponent<Collider>();
		collider->SetCenter(Vector2(12.76f, 22.84f));
		collider->SetSize(Vector2(56.0f, 61.6f));

		mState = eBombState::Idle;

		GameObject::Initialize();
	}

	void BaseBomb::Update()
	{
		GameObject::Update();
		Transform* tr = GetComponent<Transform>();
		//Vector2 pos = tr->GetPos(); //+ Vector2::Vector2(6.0f, 10.0f); // 이쪽에서 뭔가 물풍선 밀거나 하는 조건을 걸 수 있을듯함
		////pos.x += 100.0f * Time::DeltaTime();
		//tr->SetPos(pos);
		//
		//Transform* tr = GetComponent<Transform>();

		//Vector2 dir = Vector2(1.0f, 1.0f);// - tr->GetPos();
		//dir.Normalize();
		///*float x = cosf(-PI / 4.0f);
		//float y = sinf(-PI / 4.0f);*/
		////float x = dir.x * cosf(PI / 5.0f) - dir.y * sinf(PI / 5.0f);
		////float y = dir.x * sinf(PI / 5.0f) + dir.y * cosf(PI / 5.0f);
		
		//Vector2 pos = tr->GetPos();
		//pos.x += 100.0f * dir.x * Time::DeltaTime();
		//pos.y += 100.0f * dir.y * Time::DeltaTime();

		//tr->SetPos(pos);

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