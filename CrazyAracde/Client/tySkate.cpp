#include "tySkate.h"
#include "tyItem.h"
#include "tyBazzi.h"
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
#include "tyBombEffect.h"
#include "tyTile.h"
#include "tyTileBomb.h"
#include "tyPlayScene.h"
#include "tyinput.h"

namespace ty
{
	Skate::Skate()
	{
	}
	Skate::Skate(ItemType type)
	{
	}
	Skate::~Skate()
	{
	}
	void Skate::Initialize()
	{
		Image* mSkate = Resources::Load<Image>(L"mSkate", L"..\\Resources\\Items\\skate.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"Skate", mSkate, Vector2::Zero, 2, 1, 2, Vector2::Zero, 0.2);
		mAnimator->Play(L"Skate", true);

		Collider* Col = AddComponent<Collider>();
		Col->SetCenter(Vector2(20.0f, 20.0f));
		Col->SetSize(Vector2(20.0f, 20.0f));
		GameObject::Initialize();
	}
	void Skate::Update()
	{
		GameObject::Update();
	}
	void Skate::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Skate::Release()
	{
	}
	void Skate::OnCollisionEnter(Collider* other)
	{
		isHit++;
		if (other->GetOwner()->GetName() == L"Bazzi")
		{
			float& Stat = PlayScene::GetBazzi()->GetmSpeed();
			Stat += 1.0f;
			object::Destroy(this);
		}

		if (other->GetOwner()->GetName() == L"BombEffect" && isHit == 2)
		{
			object::Destroy(this);
		}
	}
	void Skate::OnCollisionStay(Collider* other)
	{
	}
	void Skate::OnCollisionExit(Collider* other)
	{
	}
}