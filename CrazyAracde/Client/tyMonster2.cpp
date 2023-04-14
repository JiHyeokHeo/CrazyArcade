#include "tyMonster2.h"
#include "tyTime.h"
#include "tySceneManager.h"
#include "tyinput.h"
#include "tyResources.h"
#include "tyTransform.h"
#include "tyAnimator.h"
#include "tyCollider.h"
#include "tyBaseBomb.h"
#include "tyObject.h"
#include "tyTileBomb.h"
#include "tyPlayScene.h"

namespace ty
{
	Monster2::Monster2()
	{
	}
	Monster2::~Monster2()
	{
	}
	void Monster2::Initialize()
	{
		SetName(L"Monster");
		Transform* tr = GetComponent<Transform>();
		mPos = tr->GetPos();
		//tr->SetPos(Vector2(400.0f, 500.0f));
		tr->SetScale(Vector2(1.1f, 1.1f));

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Monster\\Pirate2\\Up", Vector2(Vector2(10.0f, 5.0f)), 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Monster\\Pirate2\\Right", Vector2(Vector2(10.0f, 5.0f)), 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Monster\\Pirate2\\Left", Vector2(Vector2(10.0f, 5.0f)), 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Monster\\Pirate2\\Down", Vector2(Vector2(10.0f, 5.0f)), 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Monster\\Pirate2\\Die", Vector2(Vector2(10.0f, 5.0f)), 0.1f);
		mAnimator->Play(L"Pirate2Down", true);

		collider = AddComponent<Collider>();
		collider->SetCenter(Vector2::Zero);
		collider->SetSize(Vector2(60.0f, 60.0f));
		mState = eMonster2State::Idle;
		GameObject::Initialize();
	}
	void Monster2::Update()
	{
		tr = GetComponent<Transform>();
		mPos = tr->GetPos();
		Vector2 midmPos = mPos + Vector2(TILE_SIZE_X / 2, TILE_SIZE_Y / 2);
		ColRIdx = TileBomb::SetColIndex(midmPos + Vector2(32.0f, 0.0f));
		ColLIdx = TileBomb::SetColIndex(midmPos + Vector2(-32.0f, 0.0f));
		ColUIdx = TileBomb::SetColIndex(midmPos + Vector2(0.0f, -32.0f));
		ColDIdx = TileBomb::SetColIndex(midmPos + Vector2(0.0f, +32.0f));

		mTime += Time::DeltaTime();
		if (ColRIdx.x > 14)
			ColRIdx.x = 14;
		if (ColLIdx.x > 14)
			ColLIdx.x = 14;
		if (ColUIdx.x > 14)
			ColUIdx.x = 14;
		if (ColDIdx.x > 14)
			ColDIdx.x = 14;

		if (ColRIdx.y > 12)
			ColRIdx.y = 12;
		if (ColLIdx.y > 12)
			ColLIdx.y = 12;
		if (ColUIdx.y > 12)
			ColUIdx.y = 12;
		if (ColDIdx.y > 12)
			ColDIdx.y = 12;


		if (SceneManager::GetBazzi()->GetMapIndex()[ColLIdx.y][ColLIdx.x] >= 2
			&& SceneManager::GetBazzi()->GetMapIndex()[ColRIdx.y][ColRIdx.x] >= 2
			&& SceneManager::GetBazzi()->GetMapIndex()[ColUIdx.y][ColUIdx.x] >= 2) // 세 면에 무언가 있을때 하는 행동 
		{
			mState = eMonster2State::Down;
			colcnt++;
			animationCtr();
		}
		else if (SceneManager::GetBazzi()->GetMapIndex()[ColLIdx.y][ColLIdx.x] >= 2
			&& SceneManager::GetBazzi()->GetMapIndex()[ColRIdx.y][ColRIdx.x] >= 2
			&& SceneManager::GetBazzi()->GetMapIndex()[ColDIdx.y][ColDIdx.x] >= 2)
		{
			mState = eMonster2State::Up;
			colcnt++;
			animationCtr();
		}
		else if (SceneManager::GetBazzi()->GetMapIndex()[ColLIdx.y][ColLIdx.x] >= 2
			&& SceneManager::GetBazzi()->GetMapIndex()[ColUIdx.y][ColUIdx.x] >= 2
			&& SceneManager::GetBazzi()->GetMapIndex()[ColDIdx.y][ColDIdx.x] >= 2)
		{
			mState = eMonster2State::Right;
			colcnt++;
			animationCtr();
		}
		else if (SceneManager::GetBazzi()->GetMapIndex()[ColRIdx.y][ColRIdx.x] >= 2
			&& SceneManager::GetBazzi()->GetMapIndex()[ColUIdx.y][ColUIdx.x] >= 2
			&& SceneManager::GetBazzi()->GetMapIndex()[ColDIdx.y][ColDIdx.x] >= 2)
		{
			mState = eMonster2State::Left;
			colcnt++;
			animationCtr();
		}
		else if (SceneManager::GetBazzi()->GetMapIndex()[ColLIdx.y][ColLIdx.x] >= 2
			&& SceneManager::GetBazzi()->GetMapIndex()[ColRIdx.y][ColRIdx.x] >= 2)
		{
			mState = eMonster2State::Down;
			colcnt++;
			animationCtr();
		}
		else if (SceneManager::GetBazzi()->GetMapIndex()[ColDIdx.y][ColDIdx.x] >= 2
			&& SceneManager::GetBazzi()->GetMapIndex()[ColUIdx.y][ColUIdx.x] >= 2)
		{
			mState = eMonster2State::Right;
			colcnt++;
			animationCtr();
		}
		else if (SceneManager::GetBazzi()->GetMapIndex()[ColLIdx.y][ColLIdx.x] >= 2 || SceneManager::GetBazzi()->GetMapIndex()[ColLIdx.y][ColLIdx.x] == 1 || mPos.x <= 30.0f)
		{
			mState = eMonster2State::Right;
			colcnt++;
			animationCtr();
		}
		else if (
			SceneManager::GetBazzi()->GetMapIndex()[ColRIdx.y][ColRIdx.x] >= 2 || SceneManager::GetBazzi()->GetMapIndex()[ColRIdx.y][ColRIdx.x] == 1 || mPos.x >= 900.0f)
		{
			mState = eMonster2State::Left;
			colcnt++;
			animationCtr();
		}
		else if (
			SceneManager::GetBazzi()->GetMapIndex()[ColUIdx.y][ColUIdx.x] >= 2 || SceneManager::GetBazzi()->GetMapIndex()[ColUIdx.y][ColUIdx.x] == 1 || mPos.y <= 60.0f)
		{
			mState = eMonster2State::Down;
			colcnt++;
			animationCtr();
		}
		else if (
			SceneManager::GetBazzi()->GetMapIndex()[ColDIdx.y][ColDIdx.x] >= 2 || SceneManager::GetBazzi()->GetMapIndex()[ColDIdx.y][ColDIdx.x] == 1 || mPos.y >= 840.0f)
		{
			mState = eMonster2State::Up;
			colcnt++;
			animationCtr();
		}

		/*	if (PlayScene::GetBazzi()->GetMapIndex()[ColLIdx.y][ColLIdx.x] == 2 && PlayScene::GetBazzi()->GetMapIndex()[ColRIdx.y][ColRIdx.x] == 2)
			{
				mState = eMonsterState::Up;
				animationCtr();
			}*/

		switch (mState)
		{
		case ty::Monster2::eMonster2State::Idle:
			idle();
			break;
		case ty::Monster2::eMonster2State::Left:
			left();
			break;
		case ty::Monster2::eMonster2State::Right:
			right();
			break;
		case ty::Monster2::eMonster2State::Up:
			up();
			break;
		case ty::Monster2::eMonster2State::Down:
			down();
			break;
		case ty::Monster2::eMonster2State::Die:
			die();
			break;
		default:
			break;
		}

		tr->SetPos(mPos);
		if (mTime >= 2.0f)
		{
			mState = eMonster2State::Idle();
			mTime = 0;
		}

		GameObject::Update();
	}
	void Monster2::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Monster2::Release()
	{
		GameObject::Release();
	}
	void Monster2::OnCollisionEnter(Collider* other)
	{
		if (other->GetOwner()->GetName() == L"Ground" || other->GetOwner()->GetName() == L"Monster")
		{
			switch (mState)
			{
			case eMonster2State::Left:
				mState = eMonster2State::Right;
				break;
			case eMonster2State::Right:
				mState = eMonster2State::Left;
				break;
			case eMonster2State::Up:
				mState = eMonster2State::Down;
				break;
			case eMonster2State::Down:
				mState = eMonster2State::Up;
				break;
			default:
				break;
			}
		}


		if (other->GetOwner()->GetName() == L"BombEffect")
		{
			mAnimator->Play(L"Pirate2Die", false);
			mState = eMonster2State::Die;
		}
		mTime = 0;
		if (other->GetOwner()->GetName() == L"Ground" || other->GetOwner()->GetName() == L"Monster")
		{
			animationCtr();
		}
	}

	void Monster2::OnCollisionStay(Collider* other)
	{
	}
	void Monster2::OnCollisionExit(Collider* other)
	{
	}

	void Monster2::idle()
	{
		mState = (eMonster2State)((rand() % 5));
		colcnt = 0;
		animationCtr();
	}
	void Monster2::left()
	{
		if (SceneManager::GetBazzi()->GetMapIndex()[ColLIdx.y][ColLIdx.x] >= 2 || SceneManager::GetBazzi()->GetMapIndex()[ColLIdx.y][ColLIdx.x] == 1 || mPos.x <= 30.0f)
		{
			mState = eMonster2State::Right;
			colcnt++;
			animationCtr();
		}
		colcnt = 0;
		mPos.x -= 60.0f * Time::DeltaTime();
	}
	void Monster2::right()
	{
		if (SceneManager::GetBazzi()->GetMapIndex()[ColLIdx.y][ColLIdx.x] >= 2
			&& SceneManager::GetBazzi()->GetMapIndex()[ColRIdx.y][ColRIdx.x] >= 2)
		{
			mState = eMonster2State::Down;
			colcnt++;
			animationCtr();
		}
		else if (SceneManager::GetBazzi()->GetMapIndex()[ColRIdx.y][ColRIdx.x] >= 2 && mPos.x >= 895.0f)
		{
			mState = eMonster2State::Left;
			colcnt++;
			animationCtr();
		}
		else if (SceneManager::GetBazzi()->GetMapIndex()[ColRIdx.y][ColRIdx.x] >= 2 || SceneManager::GetBazzi()->GetMapIndex()[ColRIdx.y][ColRIdx.x] == 1 || mPos.x >= 900.0f)
		{
			mState = eMonster2State::Left;
			colcnt++;
			animationCtr();
		}
		colcnt = 0;
		mPos.x += 60.0f * Time::DeltaTime();
	}
	void Monster2::up()
	{
		if (SceneManager::GetBazzi()->GetMapIndex()[ColDIdx.y][ColDIdx.x] >= 2
			&& SceneManager::GetBazzi()->GetMapIndex()[ColUIdx.y][ColUIdx.x] >= 2)
		{
			mState = eMonster2State::Right;
			colcnt++;
			animationCtr();
		}
		else if (SceneManager::GetBazzi()->GetMapIndex()[ColDIdx.y][ColDIdx.x] >= 2
			&& mPos.y <= 65.0f)
		{
			mState = eMonster2State::Right;
			colcnt++;
			animationCtr();
		}
		else if (SceneManager::GetBazzi()->GetMapIndex()[ColUIdx.y][ColUIdx.x] >= 2 || SceneManager::GetBazzi()->GetMapIndex()[ColUIdx.y][ColUIdx.x] == 1 || mPos.y <= 60.0f)
		{
			mState = eMonster2State::Down;
			colcnt++;
			animationCtr();
		}
		colcnt = 0;
		mPos.y -= 60.0f * Time::DeltaTime();
	}
	void Monster2::down()
	{
		if (SceneManager::GetBazzi()->GetMapIndex()[ColDIdx.y][ColDIdx.x] >= 2 || SceneManager::GetBazzi()->GetMapIndex()[ColDIdx.y][ColDIdx.x] == 1 || mPos.y >= 840.0f)
		{
			mState = eMonster2State::Up;
			colcnt++;
			animationCtr();
		}
		colcnt = 0;
		mPos.y += 60.0f * Time::DeltaTime();
	}
	void Monster2::die()
	{
		if (mAnimator->isComplete() == true)
		{
			int monstercnt = SceneManager::GetMonsterCnt();
			monstercnt--;
			SceneManager::SetMonsterCnt(monstercnt);
			object::Destroy(this);
		}
	}
	void Monster2::animationCtr()
	{
		switch (mState)
		{
		case ty::Monster2::eMonster2State::Idle:
			break;
		case ty::Monster2::eMonster2State::Left:
			mAnimator->Play(L"Pirate2Left", true);
			break;
		case ty::Monster2::eMonster2State::Right:
			mAnimator->Play(L"Pirate2Right", true);
			break;
		case ty::Monster2::eMonster2State::Up:
			mAnimator->Play(L"Pirate2Up", true);
			break;
		case ty::Monster2::eMonster2State::Down:
			mAnimator->Play(L"Pirate2Down", true);
			break;
		default:
			break;
		}
	}
}