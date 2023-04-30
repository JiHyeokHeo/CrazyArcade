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
#include "tyDao.h"
#include "tyResources.h"
#include "tySound.h"
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
		eatSound = Resources::Load<Sound>(L"eatsound", L"..\\Resources\\Sound\\eat_item.wav");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"PotionMax", mPotionMax, Vector2::Zero, 2, 1, 2, Vector2(0.0f, -10.0f), 0.2);
		mAnimator->Play(L"PotionMax", true);

		Collider* Col = AddComponent<Collider>();
		Col->SetCenter(Vector2(20.0f, 20.0f));
		Col->SetSize(Vector2(20.0f, 20.0f));
		GameObject::Initialize();
	}
	void PotionMax::Update()
	{
		InvTime += Time::DeltaTime();
		if (SceneManager::GetActiveScene()->GetName() == L"Lobby")
		{
			object::Destroy(this);
		}
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
		
		if (other->GetOwner()->GetName() == L"Bazzi")
		{
			eatSound->Play(false);
			int& WaterCourse = SceneManager::GetBazzi()->GetmWaterCourse();
			WaterCourse = SceneManager::GetBazzi()->GetMaxWaterCourse();
			object::Destroy(this);
		}

		if (other->GetOwner()->GetName() == L"Dao")
		{
			eatSound->Play(false);
			int& WaterCourse = SceneManager::GetDao()->GetmWaterCourse();
			WaterCourse = SceneManager::GetDao()->GetMaxWaterCourse();
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
	void PotionMax::OnCollisionStay(Collider* other)
	{
	}
	void PotionMax::OnCollisionExit(Collider* other)
	{
	}
}