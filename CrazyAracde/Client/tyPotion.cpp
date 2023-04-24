#include "tyPotion.h"
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
#include "tyDao.h"

namespace ty
{
	Potion::Potion()
	{
	}
	Potion::Potion(ItemType type)
	{
	}
	Potion::~Potion()
	{
	}
	void Potion::Initialize()
	{
		Image* mPotion = Resources::Load<Image>(L"mPotion", L"..\\Resources\\Items\\potion.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"Potion", mPotion, Vector2::Zero, 2, 1, 2, Vector2(0.0f, -10.0f), 0.2);
		mAnimator->Play(L"Potion", true);

		Collider* Col = AddComponent<Collider>();
		Col->SetCenter(Vector2(20.0f, 20.0f));
		Col->SetSize(Vector2(20.0f, 20.0f));
		GameObject::Initialize();
	}
	void Potion::Update()
	{
		InvTime += Time::DeltaTime();
		if (SceneManager::GetActiveScene()->GetName() == L"Lobby")
		{
			object::Destroy(this);
		}
		GameObject::Update();
	}
	void Potion::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Potion::Release()
	{
	}
	void Potion::OnCollisionEnter(Collider* other)
	{
		
		if (other->GetOwner()->GetName() == L"Bazzi")
		{
			SceneManager::GetBazzi()->GetmWaterCourse()++;
			object::Destroy(this);
		}
		if (other->GetOwner()->GetName() == L"Dao")
		{
			SceneManager::GetDao()->GetmWaterCourse()++;
			object::Destroy(this);
		}
		if (other->GetOwner()->GetName() == L"BombEffect" && InvTime >= 1.5f)
		{
			object::Destroy(this);
		}

		if (other->GetOwner()->GetName() == L"BossBombEffect" && InvTime >= 1.5f)
		{
			object::Destroy(this);
		}
	}
	void Potion::OnCollisionStay(Collider* other)
	{
	}
	void Potion::OnCollisionExit(Collider* other)
	{
	}
}