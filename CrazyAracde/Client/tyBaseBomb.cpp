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
		//maxBomb++;
    	Transform* tr = GetComponent<Transform>();
		//tr->SetPos(Vector2(400.0f, 400.0f));
		tr->SetScale(Vector2(1.1f, 1.1f));
		////
		////Image* BombImage = Resources::Load<Image>(L"Bomb", L"..\\Resources\\Bomb\\bomb.bmp");
		//mAnimator = AddComponent<Animator>();

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Bomb\\Idle", Vector2(11.76f, 22.84f), 0.16f);
		mAnimator->Play(L"BombIdle", true);
		////mAnimator->CreateAnimation(L"bomb", BombImage, Vector2::Zero, 2, 1, 2, Vector2(11.76f, 22.84f), 0.16);
		////mAnimator->Play(L"bomb", true);
		//mAnimator->CreateAnimations(L"..\\Resources\\Bomb\\Idle", Vector2(11.76f, 22.84f), 0.16f);
		//mAnimator->Play(L"BombIdle", true);

		Collider* collider = AddComponent<Collider>();
		collider->SetCenter(Vector2(12.76f, 22.84f));
		collider->SetSize(Vector2(56.0f, 61.6f));
		

		//GameObject::Initialize();
	}

	void BaseBomb::Update()
	{
		Transform* tr = GetComponent<Transform>();
		//Vector2 pos = tr->GetPos(); //+ Vector2::Vector2(6.0f, 10.0f); // ���ʿ��� ���� ��ǳ�� �аų� �ϴ� ������ �� �� ��������
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

		GameObject::Update();
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
		
	}

	void BaseBomb::idle()
	{
		Transform* tr = GetComponent<Transform>();
		if (mTime >= 3)
		{
			for (int i = 1; i < 7; i++)
			{
				object::Instantiate<BombEffect>(tr->GetPos() + Vector2((i * 50), 0), eLayerType::Bomb);
				object::Instantiate<BombEffect>(tr->GetPos() + Vector2(0, (i * 50)), eLayerType::Bomb);
				object::Instantiate<BombEffect>(tr->GetPos() - Vector2((i * 50), 0), eLayerType::Bomb);
				object::Instantiate<BombEffect>(tr->GetPos() - Vector2(0, (i * 50)), eLayerType::Bomb);
			}
			object::Destroy(this);
		}
	}

}