#include "tyBird.h"
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
	Bird::Bird()
	{
	}
	Bird::Bird(ItemType type)
	{
	}
	Bird::~Bird()
	{
	}
	void Bird::Initialize()
	{
		SetName(L"Bird");

		Image* mDevil = Resources::Load<Image>(L"mBird", L"..\\Resources\\Items\\Bird.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"Bird", mDevil, Vector2::Zero, 2, 1, 2, Vector2(0.0f, -10.0f), 0.2);
		mAnimator->Play(L"Bird", true);

		Collider* Col = AddComponent<Collider>();
		Col->SetCenter(Vector2(20.0f, 20.0f));
		Col->SetSize(Vector2(20.0f, 20.0f));
		GameObject::Initialize();
	}
	void Bird::Update()
	{
		GameObject::Update();
	}
	void Bird::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Bird::Release()
	{
	}
	void Bird::OnCollisionEnter(Collider* other)
	{
		isHit++;
		if (other->GetOwner()->GetName() == L"Bazzi")
		{
			object::Destroy(this);
		}

		if (other->GetOwner()->GetName() == L"BombEffect" && isHit == 2)
		{
			object::Destroy(this);
		}
	}
	void Bird::OnCollisionStay(Collider* other)
	{
	}
	void Bird::OnCollisionExit(Collider* other)
	{
	}
}