#include "tyMonster.h"
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
	Monster::Monster()
	{
	}
	Monster::~Monster()
	{
	}
	void Monster::Initialize()
	{
		SetName(L"Monster");
		Transform* tr = GetComponent<Transform>();
		mPos = tr->GetPos();
		//tr->SetPos(Vector2(400.0f, 500.0f));
		tr->SetScale(Vector2(1.1f, 1.1f));

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Monster\\Pirate\\Up", Vector2(Vector2(10.0f, 5.0f)), 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Monster\\Pirate\\Right", Vector2(Vector2(10.0f, 5.0f)), 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Monster\\Pirate\\Left", Vector2(Vector2(10.0f, 5.0f)), 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Monster\\Pirate\\Down", Vector2(Vector2(10.0f, 5.0f)), 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Monster\\Pirate\\Die", Vector2(Vector2(10.0f, 5.0f)), 0.1f);
		mAnimator->Play(L"PirateDown", true);
		
		collider = AddComponent<Collider>();
		collider->SetCenter(Vector2::Zero);
		collider->SetSize(Vector2(60.0f, 60.0f));
		mState = eMonsterState::Idle;
		GameObject::Initialize();
	}
	void Monster::Update()
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

	
			//if(SceneManager::GetBazzi()->GetMapIndex()[ColLIdx.y][ColLIdx.x] >= 2  
			//	&& SceneManager::GetBazzi()->GetMapIndex()[ColRIdx.y][ColRIdx.x] >= 2 
			//	&& SceneManager::GetBazzi()->GetMapIndex()[ColUIdx.y][ColUIdx.x] >= 2  ) // 세 면에 무언가 있을때 하는 행동 
			//{
			//	mState = eMonsterState::Down;
			//	colcnt++;
			//	animationCtr();
			//}
			//else if (SceneManager::GetBazzi()->GetMapIndex()[ColLIdx.y][ColLIdx.x] >= 2 
			//	&& SceneManager::GetBazzi()->GetMapIndex()[ColRIdx.y][ColRIdx.x] >= 2  
			//	&& SceneManager::GetBazzi()->GetMapIndex()[ColDIdx.y][ColDIdx.x] >= 2   )
			//{
			//	mState = eMonsterState::Up;
			//	colcnt++;
			//	animationCtr();
			//}
			//else if (SceneManager::GetBazzi()->GetMapIndex()[ColLIdx.y][ColLIdx.x] >= 2
			//	&& SceneManager::GetBazzi()->GetMapIndex()[ColUIdx.y][ColUIdx.x] >= 2
			//	&& SceneManager::GetBazzi()->GetMapIndex()[ColDIdx.y][ColDIdx.x] >= 2  )
			//{
			//	mState = eMonsterState::Right;
			//	colcnt++;
			//	animationCtr();
			//}
			//else if (SceneManager::GetBazzi()->GetMapIndex()[ColRIdx.y][ColRIdx.x] >= 2 
			//	&& SceneManager::GetBazzi()->GetMapIndex()[ColUIdx.y][ColUIdx.x] >= 2 
			//	&& SceneManager::GetBazzi()->GetMapIndex()[ColDIdx.y][ColDIdx.x] >= 2 )
			//{
			//	mState = eMonsterState::Left;
			//	colcnt++;
			//	animationCtr();
			//}
			//else if(SceneManager::GetBazzi()->GetMapIndex()[ColLIdx.y][ColLIdx.x] >= 2 
			//	&& SceneManager::GetBazzi()->GetMapIndex()[ColRIdx.y][ColRIdx.x] >= 2 )
			//{
			//	mState = eMonsterState::Down;
			//	colcnt++;
			//	animationCtr();
			//}
			//else if ( SceneManager::GetBazzi()->GetMapIndex()[ColDIdx.y][ColDIdx.x] >= 2 
			//	&& SceneManager::GetBazzi()->GetMapIndex()[ColUIdx.y][ColUIdx.x] >= 2 )
			//{
			//	mState = eMonsterState::Right;
			//	colcnt++;
			//	animationCtr();
			//}
			//else if (SceneManager::GetBazzi()->GetMapIndex()[ColLIdx.y][ColLIdx.x] >= 2 || SceneManager::GetBazzi()->GetMapIndex()[ColLIdx.y][ColLIdx.x] == 1 || mPos.x <= 30.0f)
			//{
			//	mState = eMonsterState::Right;
			//	colcnt++;
			//	animationCtr();
			//}
			//else if (
			//	SceneManager::GetBazzi()->GetMapIndex()[ColRIdx.y][ColRIdx.x] >= 2 || SceneManager::GetBazzi()->GetMapIndex()[ColRIdx.y][ColRIdx.x] == 1 || mPos.x >= 900.0f)
			//{
			//	mState = eMonsterState::Left;
			//	colcnt++;
			//	animationCtr();
			//}
			//else if (
			//	SceneManager::GetBazzi()->GetMapIndex()[ColUIdx.y][ColUIdx.x] >= 2 || SceneManager::GetBazzi()->GetMapIndex()[ColUIdx.y][ColUIdx.x] == 1 || mPos.y <= 60.0f)
			//{
			//	mState = eMonsterState::Down;
			//	colcnt++;
			//	animationCtr();
			//}
			//else if (
			//	SceneManager::GetBazzi()->GetMapIndex()[ColDIdx.y][ColDIdx.x] >= 2 || SceneManager::GetBazzi()->GetMapIndex()[ColDIdx.y][ColDIdx.x] == 1 || mPos.y >= 840.0f)
			//{
			//	mState = eMonsterState::Up;
			//	colcnt++;
			//	animationCtr();
			//}
	
	/*	if (PlayScene::GetBazzi()->GetMapIndex()[ColLIdx.y][ColLIdx.x] == 2 && PlayScene::GetBazzi()->GetMapIndex()[ColRIdx.y][ColRIdx.x] == 2)
		{
			mState = eMonsterState::Up;
			animationCtr();
		}*/

		switch (mState)
		{
		case ty::Monster::eMonsterState::Idle:
			idle();
			break;
		case ty::Monster::eMonsterState::Left:
			left();
			break;
		case ty::Monster::eMonsterState::Right:
			right();
			break;
		case ty::Monster::eMonsterState::Up:
			up();
			break;
		case ty::Monster::eMonsterState::Down:
			down();
			break;
		case ty::Monster::eMonsterState::Die:
			die();
			break;
		default:
			break;
		}
		
		tr->SetPos(mPos);
		if (mTime >= 2.0f)
		{
			mState = eMonsterState::Idle();
			mTime = 0;
		}
		
		GameObject::Update();
	}
	void Monster::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Monster::Release()
	{
		GameObject::Release();
	}
	void Monster::OnCollisionEnter(Collider* other)
	{
		if (other->GetOwner()->GetName() == L"Ground" || other->GetOwner()->GetName() == L"Monster")
		{
			switch (mState)
			{
			case eMonsterState::Left:
				mState = eMonsterState::Right;
				break;
			case eMonsterState::Right:
				mState = eMonsterState::Left;
				break;
			case eMonsterState::Up:
				mState = eMonsterState::Down;
				break;
			case eMonsterState::Down:
				mState = eMonsterState::Up;
				break;
			default:
				break;
			}
		}

			
		if (other->GetOwner()->GetName() == L"BombEffect")
		{
			mAnimator->Play(L"PirateDie", false);
			mState = eMonsterState::Die;
		}
		mTime = 0;
	/*	if (other->GetOwner()->GetName() == L"Ground" || other->GetOwner()->GetName() == L"Monster")
		{
			animationCtr();
		}*/
	}
	
	void Monster::OnCollisionStay(Collider* other)
	{
	}
	void Monster::OnCollisionExit(Collider* other)
	{
	}

	void Monster::idle()
	{
		mState = (eMonsterState)((rand()% 5));
		colcnt = 0;
		animationCtr();
	}
	void Monster::left()
	{
		if (SceneManager::GetBazzi()->GetMapIndex()[ColLIdx.y][ColLIdx.x] >= 2 || SceneManager::GetBazzi()->GetMapIndex()[ColLIdx.y][ColLIdx.x] == 1 || mPos.x <= 30.0f)
		{
			mState = eMonsterState::Right;
			colcnt++;
			animationCtr();
		}
		colcnt = 0;
		mPos.x -= 60.0f * Time::DeltaTime();
	}
	void Monster::right()
	{
		if (SceneManager::GetBazzi()->GetMapIndex()[ColLIdx.y][ColLIdx.x] >= 2
			&& SceneManager::GetBazzi()->GetMapIndex()[ColRIdx.y][ColRIdx.x] >= 2)
		{
			mState = eMonsterState::Down;
			colcnt++;
			animationCtr();
		}
		else if (SceneManager::GetBazzi()->GetMapIndex()[ColRIdx.y][ColRIdx.x] >= 2 && mPos.x >= 895.0f)
		{
			mState = eMonsterState::Left;
			colcnt++;
			animationCtr();
		}
		else if (SceneManager::GetBazzi()->GetMapIndex()[ColRIdx.y][ColRIdx.x] >= 2 || SceneManager::GetBazzi()->GetMapIndex()[ColRIdx.y][ColRIdx.x] == 1 || mPos.x >= 900.0f)
		{
			mState = eMonsterState::Left;
			colcnt++;
			animationCtr();
		}
		colcnt = 0;
		mPos.x += 60.0f * Time::DeltaTime();
	}
	void Monster::up()
	{
		if (SceneManager::GetBazzi()->GetMapIndex()[ColDIdx.y][ColDIdx.x] >= 2
			&& SceneManager::GetBazzi()->GetMapIndex()[ColUIdx.y][ColUIdx.x] >= 2)
		{
			mState = eMonsterState::Right;
			colcnt++;
			animationCtr();
		}
		else if (SceneManager::GetBazzi()->GetMapIndex()[ColDIdx.y][ColDIdx.x] >= 2
			&& mPos.y <= 65.0f)
		{
			mState = eMonsterState::Right;
			colcnt++;
			animationCtr();
		}
		else if (SceneManager::GetBazzi()->GetMapIndex()[ColUIdx.y][ColUIdx.x] >= 2 || SceneManager::GetBazzi()->GetMapIndex()[ColUIdx.y][ColUIdx.x] == 1 || mPos.y <= 60.0f)
		{
			mState = eMonsterState::Down;
			colcnt++;
			animationCtr();
		}

		colcnt = 0;
		mPos.y -= 60.0f * Time::DeltaTime();
	}
	void Monster::down()
	{
		if (SceneManager::GetBazzi()->GetMapIndex()[ColDIdx.y][ColDIdx.x] >= 2 || SceneManager::GetBazzi()->GetMapIndex()[ColDIdx.y][ColDIdx.x] == 1 || mPos.y >= 840.0f)
		{
			mState = eMonsterState::Up;
			colcnt++;
			animationCtr();
		}
		colcnt = 0;
		mPos.y += 60.0f * Time::DeltaTime();
	}
	void Monster::die()
 	{
		if (mAnimator->isComplete() == true)
		{
			int monstercnt = SceneManager::GetMonsterCnt();
			monstercnt--;
			SceneManager::SetMonsterCnt(monstercnt);
			mState = eMonsterState::Idle;
			object::Pause(this);
		}
	}
	void Monster::animationCtr()
	{
		switch (mState)
		{
		case ty::Monster::eMonsterState::Idle:
			break;
		case ty::Monster::eMonsterState::Left:
			mAnimator->Play(L"PirateLeft", true);
			break;
		case ty::Monster::eMonsterState::Right:
			mAnimator->Play(L"PirateRight", true);
			break;
		case ty::Monster::eMonsterState::Up:
			mAnimator->Play(L"PirateUp", true);
			break;
		case ty::Monster::eMonsterState::Down:
			mAnimator->Play(L"PirateDown", true);
			break;
		default:
			break;
		}
	}
}