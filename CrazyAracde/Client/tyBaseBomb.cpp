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
#include "tyTileBomb.h"

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
		mAnimator->CreateAnimations(L"..\\Resources\\Bomb\\None", Vector2(11.76f, 22.84f), 0.16f);
		mAnimator->Play(L"BombIdle", true);
		Bazzi::GetMapIndex();
		Collider* collider = AddComponent<Collider>();
		collider->SetCenter(Vector2(12.76f, 22.84f));
		collider->SetSize(Vector2(58.0f, 58.0f));

		Vector2 BombPos = TileBomb::SetPos(tr->GetPos());
		Vector2 BombIdx = TileBomb::SetIndex(BombPos);

		if (BombIdx.x < 14)
		{
			for (int i = 1; i < 5; i++)
			{
				if (BombIdx.x + i >= 15)
					break;
				mBombEffect.push_back(object::Instantiate<BombEffect>(TileBomb::SetPos(tr->GetPos()) + Vector2((float)(i * 60.0f), 0.0f), eLayerType::BombEffect)); // 우측
				if (Bazzi::GetMapIndex()[BombIdx.y][BombIdx.x + i] == 2)
					break;
			}
			for (int i = 1; i < 5; i++)
			{
				if (BombIdx.y + i >= 13)
					break;
				mBombEffect.push_back(object::Instantiate<BombEffect>(TileBomb::SetPos(tr->GetPos()) + Vector2(0.0f, float(i * 60.0f)), eLayerType::BombEffect)); // 하단
				if (Bazzi::GetMapIndex()[BombIdx.y + i][BombIdx.x] == 2)
					break;
			}
			for (int i = 1; i < 5; i++)
			{
				if (BombIdx.x - i <= -1)
					break;
				mBombEffect.push_back(object::Instantiate<BombEffect>(TileBomb::SetPos(tr->GetPos()) - Vector2((float)(i * 60.0f), 0.0f), eLayerType::BombEffect)); // 좌측
				if (Bazzi::GetMapIndex()[BombIdx.y][BombIdx.x - i] == 2)
					break;
			}
			for (int i = 1; i < 5; i++)
			{
				if (BombIdx.y - i <= -1)
					break;
				mBombEffect.push_back(object::Instantiate<BombEffect>(TileBomb::SetPos(tr->GetPos()) - Vector2(0.0f, (float)(i * 60.0f)), eLayerType::BombEffect)); // 상단
				if (Bazzi::GetMapIndex()[BombIdx.y - i][BombIdx.x] == 2)
					break;
			}
			mBombEffect.push_back(object::Instantiate<BombEffect>(TileBomb::SetPos(tr->GetPos()), eLayerType::BombEffect));
		}


		for (int i = 0; i < mBombEffect.size(); i++)
		{
			mBombEffect[i]->SetBomb(this);
		}

		mState = eBombState::Idle;
		
		GameObject::Initialize();
	}

	void BaseBomb::Update()
	{
		
		GameObject::Update();
		Transform* tr = GetComponent<Transform>();

		

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
		if (other->GetOwner()->GetName() == L"BombEffect")
		{
			for (int i = 0; i < mBombEffect.size(); i++)
			{
				mBombEffect[i]->SetTime(3.0f);
			}
			mAnimator->Play(L"BombNone", true);
		}
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
		if (mTime >= 3.0f)
		{
			Vector2 mPos = TileBomb::SetIndex(tr->GetPos());
			Bazzi::GetMapIndex()[mPos.y][mPos.x] = 0;
			object::Destroy(this);
		}
	}

}