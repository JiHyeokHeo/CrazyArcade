#include "tyDevil.h"
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
	Devil::Devil()
	{
	}
	Devil::Devil(ItemType type)
	{
	}
	Devil::~Devil()
	{
	}
	void Devil::Initialize()
	{
		SetName(L"Devil");

		Image* mDevil = Resources::Load<Image>(L"mDevil", L"..\\Resources\\Items\\Devil.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"Devil", mDevil, Vector2::Zero, 2, 1, 2, Vector2(0.0f, -10.0f), 0.2);
		mAnimator->Play(L"Devil", true);

		Collider* Col = AddComponent<Collider>();
		Col->SetCenter(Vector2(20.0f, 20.0f));
		Col->SetSize(Vector2(20.0f, 20.0f));
		GameObject::Initialize();
	}
	void Devil::Update()
	{
		InvTime += Time::DeltaTime();
		GameObject::Update();
	}
	void Devil::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Devil::Release()
	{
	}
	void Devil::OnCollisionEnter(Collider* other)
	{
		
		if (other->GetOwner()->GetName() == L"Bazzi" && this->GetState() == eState::Active)
		{
			SceneManager::GetBazzi()->GetmSpeed() = SceneManager::GetBazzi()->GetMaxSpeed();
			SceneManager::GetBazzi()->SetIsPushPossible(true);
			object::Pause(this);
		}

		if (other->GetOwner()->GetName() == L"BombEffect" && InvTime >= 1.5f && this->GetState() == eState::Active)
		{
			object::Pause(this);
		}

		if (other->GetOwner()->GetName() == L"BossBombEffect" && InvTime >= 1.5f)
		{
			object::Destroy(this);
		}
	}
	void Devil::OnCollisionStay(Collider* other)
	{
	}
	void Devil::OnCollisionExit(Collider* other)
	{
	}
}