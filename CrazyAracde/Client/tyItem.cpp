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
#include "tyBallon.h"

namespace ty
{
	Item::Item()
	{
	}
	Item::Item(ItemType type)
	{
	}
	Item::~Item()
	{
	}
	void Item::Initialize()
	{
		SetName(L"BaseBomb");

		Image* mPotion = Resources::Load<Image>(L"mPotion", L"..\\Resources\\Items\\potion.bmp");
		Image* mPotionMax = Resources::Load<Image>(L"mPotionMax", L"..\\Resources\\Items\\potionmax.bmp");
		Image* mSkate = Resources::Load<Image>(L"mSkate", L"..\\Resources\\Items\\skate.bmp");
		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector2::One);
		mAnimator = AddComponent<Animator>();
		//mAnimator->CreateAnimation(L"Bazziup", mUpImage, Vector2::Zero, 8, 1, 8, Vector2::Zero, 0.1);
		//mAnimator->CreateAnimation(L"Ballon", mBallon, Vector2::Zero, 2, 1, 2, Vector2::Zero, 0.2);
		mAnimator->CreateAnimation(L"Potion", mPotion, Vector2::Zero, 2, 1, 2, Vector2::Zero, 0.2);
		mAnimator->CreateAnimation(L"PotionMax", mPotionMax, Vector2::Zero, 2, 1, 2, Vector2::Zero, 0.2);
		mAnimator->CreateAnimation(L"Skate", mSkate, Vector2::Zero, 2, 1, 2, Vector2::Zero, 0.2);
		mAnimator->Play(L"Ballon", true);

		Collider* Col = AddComponent<Collider>();
		Col->SetCenter(Vector2(20.0f, 20.0f));
		Col->SetSize(Vector2(20.0f, 20.0f));

		GameObject::Initialize();
	}
	void Item::Update()
	{
		GameObject::Update();
	}
	void Item::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Item::Release()
	{
	}
	void Item::OnCollisionEnter(Collider* other)
	{
		int a = 0;
		if (other->GetOwner()->GetName() == L"Bazzi")
		{
			object::Destroy(this);
		}
	}
	void Item::OnCollisionStay(Collider* other)
	{
	}
	void Item::OnCollisionExit(Collider* other)
	{
	}
}