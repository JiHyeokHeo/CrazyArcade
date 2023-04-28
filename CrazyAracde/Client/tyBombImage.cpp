#include "tyBombImage.h"
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
#include "tyBossBombEffect.h"
#include "tyTileBomb.h"

namespace ty
{
	BombImage::BombImage()
	{
	}
	BombImage::~BombImage()
	{
	}
	void BombImage::Initialize()
	{
		tr = GetComponent<Transform>();
		tr->SetScale(Vector2(1.5f, 1.5f));
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Bomb\\Idle", Vector2::Zero, 0.16f);
		mAnimator->CreateAnimations(L"..\\Resources\\Bomb\\None", Vector2::Zero, 0.16f);
		mAnimator->Play(L"BombIdle", true);
		StartPos = tr->GetPos();
	}
	void BombImage::Update()
	{	
		mTime += Time::DeltaTime();
		Vector2 mBombPos = tr->GetPos();

		if (mDifference <= 20.0f)
		{
			mBombPos.y += 240.0f * Time::DeltaTime();
		}


		if (mBombPos.y - StartPos.y > 120.0f)
		{
			isReached = true;
			object::Destroy(this);
		}

		
		tr->SetPos(mBombPos);

		if (isReached == true)
		{
			for (int i = 0; i < 3; i++)
			{
				object::Instantiate<BossBombEffect>(TileBomb::SetPos(Vector2(mBombPos.x - 60.0f, mBombPos.y + (i - 1) * 60.0f )), eLayerType::BombEffect);
				object::Instantiate<BossBombEffect>(TileBomb::SetPos(Vector2(mBombPos.x , mBombPos.y + (i - 1) * 60.0f)), eLayerType::BombEffect);
				object::Instantiate<BossBombEffect>(TileBomb::SetPos(Vector2(mBombPos.x + 60.0f, mBombPos.y + (i - 1) * 60.0f)), eLayerType::BombEffect);
			}

			isReached = false;
		}
		
		GameObject::Update();
	}
	void BombImage::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void BombImage::Release()
	{
	}
	void BombImage::OnCollisionEnter(Collider* other)
	{
	}
	void BombImage::OnCollisionStay(Collider* other)
	{
	}
	void BombImage::OnCollisionExit(Collider* other)
	{
	}
}