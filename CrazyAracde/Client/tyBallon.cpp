#include "tyBallon.h"
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
	/*Component::Component(eComponentType type)
		: mType(type)*/
	
	Ballon::Ballon()
	{
	}
	Ballon::Ballon(ItemType type)
		:Item(ItemType::Ballon)
	{
	}
	Ballon::~Ballon()
	{
	}
	void Ballon::Initialize()
	{
		Image* mBallon = Resources::Load<Image>(L"mBallon", L"..\\Resources\\Items\\ballon.bmp");
		eatSound =  Resources::Load<Sound>(L"eatsound", L"..\\Resources\\Sound\\eat_item.wav");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"Ballon", mBallon, Vector2::Zero, 2, 1, 2, Vector2(0.0f, -10.0f), 0.2);
		mAnimator->Play(L"Ballon", true);

		Collider* Col = AddComponent<Collider>();
		Col->SetCenter(Vector2(20.0f, 20.0f));
		Col->SetSize(Vector2(20.0f, 20.0f));
		GameObject::Initialize();
	}
	void Ballon::Update()
	{
		InvTime += Time::DeltaTime();
		if (SceneManager::GetActiveScene()->GetName() == L"Lobby")
		{
			object::Destroy(this);
		}
		GameObject::Update();
	}
	void Ballon::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Ballon::Release()
	{
	}
	void Ballon::OnCollisionEnter(Collider* other)
	{
		
		if (other->GetOwner()->GetName() == L"Bazzi")
		{
			eatSound->Play(false);
			SceneManager::GetBazzi()->GetmBomb()++;
			object::Destroy(this);
		}

		if (other->GetOwner()->GetName() == L"Dao")
		{
			eatSound->Play(false);
			SceneManager::GetDao()->GetmBomb()++;
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
	void Ballon::OnCollisionStay(Collider* other)
	{
	}
	void Ballon::OnCollisionExit(Collider* other)
	{
	}
}