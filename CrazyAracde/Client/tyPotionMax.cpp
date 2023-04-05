#include "tyPotionMax.h"
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
	PotionMax::PotionMax()
	{
	}
	PotionMax::PotionMax(ItemType type)
	{
	}
	PotionMax::~PotionMax()
	{
	}
	void PotionMax::Initialize()
	{
		Image* mPotionMax = Resources::Load<Image>(L"mPotionMax", L"..\\Resources\\Items\\potionmax.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"PotionMax", mPotionMax, Vector2::Zero, 2, 1, 2, Vector2::Zero, 0.2);
		mAnimator->Play(L"PotionMax", true);

		Collider* Col = AddComponent<Collider>();
		Col->SetCenter(Vector2(20.0f, 20.0f));
		Col->SetSize(Vector2(20.0f, 20.0f));
		GameObject::Initialize();
	}
	void PotionMax::Update()
	{
		GameObject::Update();
	}
	void PotionMax::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void PotionMax::Release()
	{
	}
	void PotionMax::OnCollisionEnter(Collider* other)
	{
		isHit++;
		if (other->GetOwner()->GetName() == L"Bazzi")
		{
			int& WaterCourse = SceneManager::GetBazzi()->GetmWaterCourse();
			WaterCourse = SceneManager::GetBazzi()->GetMaxWaterCourse();
			object::Destroy(this);
		}

		if (other->GetOwner()->GetName() == L"BombEffect" && isHit == 2)
		{
			object::Destroy(this);
		}
	}
	void PotionMax::OnCollisionStay(Collider* other)
	{
	}
	void PotionMax::OnCollisionExit(Collider* other)
	{
	}
}