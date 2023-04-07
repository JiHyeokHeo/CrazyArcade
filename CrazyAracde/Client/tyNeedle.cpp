#include "tyNeedle.h"
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
	Needle::Needle()
	{
	}
	Needle::Needle(ItemType type)
	{
	}
	Needle::~Needle()
	{
	}
	void Needle::Initialize()
	{
		Image* mNeedle = Resources::Load<Image>(L"mNeedle", L"..\\Resources\\Items\\needle.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"Needle", mNeedle, Vector2::Zero, 2, 1, 2, Vector2(0.0f, -10.0f), 0.2);
		mAnimator->Play(L"Needle", true);

		Collider* Col = AddComponent<Collider>();
		Col->SetCenter(Vector2(20.0f, 20.0f));
		Col->SetSize(Vector2(20.0f, 20.0f));
		GameObject::Initialize();
	}
	void Needle::Update()
	{
	}
	void Needle::Render(HDC hdc)
	{
	}
	void Needle::Release()
	{
	}
	void Needle::OnCollisionEnter(Collider* other)
	{
		isHit++;
		if (other->GetOwner()->GetName() == L"Bazzi")
		{
			SceneManager::GetBazzi()->SetIsNeedleOn(true);
			
			object::Destroy(this);
		}

		if (other->GetOwner()->GetName() == L"BombEffect" && isHit == 2)
		{
			object::Destroy(this);
		}
	}
	void Needle::OnCollisionStay(Collider* other)
	{
	}
	void Needle::OnCollisionExit(Collider* other)
	{
	}
}