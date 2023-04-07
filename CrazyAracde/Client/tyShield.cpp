#include "tyShield.h"
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
#include "tyShiledUI.h"

namespace ty
{
	Shield::Shield()
	{
	}
	Shield::Shield(ItemType type)
	{
	}
	Shield::~Shield()
	{
	}
	void Shield::Initialize()
	{
		Image* mShield = Resources::Load<Image>(L"mShield", L"..\\Resources\\Items\\shield.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"mShield", mShield, Vector2::Zero, 2, 1, 2, Vector2(0.0f, -10.0f), 0.2);
		mAnimator->Play(L"mShield", true);

		Collider* Col = AddComponent<Collider>();
		Col->SetCenter(Vector2(20.0f, 20.0f));
		Col->SetSize(Vector2(20.0f, 20.0f));
		GameObject::Initialize();
	}
	void Shield::Update()
	{
		GameObject::Update();
	}
	void Shield::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Shield::Release()
	{
	}
	void Shield::OnCollisionEnter(Collider* other)
	{
		isHit++;
		if (other->GetOwner()->GetName() == L"Bazzi")
		{
			SceneManager::GetBazzi()->SetItemState(eItemType::Shield);
			object::Instantiate<ShieldUI>(eLayerType::UI);
			object::Destroy(this);
		}

		if (other->GetOwner()->GetName() == L"BombEffect" && isHit == 2)
		{
			object::Destroy(this);
		}

	}
	void Shield::OnCollisionStay(Collider* other)
	{
	}
	void Shield::OnCollisionExit(Collider* other)
	{
	}
}