#include "tyForestMonster.h"
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
	ForestMonster::ForestMonster()
	{
	}
	ForestMonster::~ForestMonster()
	{
	}
	void ForestMonster::Initialize()
	{
		SetName(L"Monster");
		Transform* tr = GetComponent<Transform>();
		mPos = tr->GetPos();
		//tr->SetPos(Vector2(400.0f, 500.0f));
		tr->SetScale(Vector2(1.1f, 1.1f));

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Monster\\Forest\\Up", Vector2(Vector2(10.0f, 5.0f)), 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Monster\\Forest\\Right", Vector2(Vector2(10.0f, 5.0f)), 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Monster\\Forest\\Left", Vector2(Vector2(10.0f, 5.0f)), 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Monster\\Forest\\Down", Vector2(Vector2(10.0f, 5.0f)), 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Monster\\Forest\\Die", Vector2(Vector2(10.0f, 5.0f)), 0.1f);
		mAnimator->Play(L"ForestDown", false);

		collider = AddComponent<Collider>();
		collider->SetCenter(Vector2::Zero);
		collider->SetSize(Vector2(60.0f, 60.0f));
		mState = eMonsterState::Idle;
		GameObject::Initialize();
	}
	void ForestMonster::Update()
	{
		tr = GetComponent<Transform>();
		mPos = tr->GetPos();
		Vector2 midmPos = mPos + Vector2(TILE_SIZE_X / 2, TILE_SIZE_Y / 2);
		ColRIdx = TileBomb::SetColIndex(midmPos + Vector2(32.0f, 0.0f));
		ColLIdx = TileBomb::SetColIndex(midmPos + Vector2(-32.0f, 0.0f));
		ColUIdx = TileBomb::SetColIndex(midmPos + Vector2(0.0f, -32.0f));
		ColDIdx = TileBomb::SetColIndex(midmPos + Vector2(0.0f, +32.0f));

		mTime += Time::DeltaTime();
		mPlayTime += Time::DeltaTime();
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


		if (mPlayTime >= 1.5f)
		{
			switch (mState)
			{
			case ty::ForestMonster::eMonsterState::Idle:
				idle();
				break;
			case ty::ForestMonster::eMonsterState::Left:
				left();
				break;
			case ty::ForestMonster::eMonsterState::Right:
				right();
				break;
			case ty::ForestMonster::eMonsterState::Up:
				up();
				break;
			case ty::ForestMonster::eMonsterState::Down:
				down();
				break;
			case ty::ForestMonster::eMonsterState::Die:
				die();
				break;
			default:
				break;
			}
		}

		tr->SetPos(mPos);
		if (mTime >= 1.0f)
		{
			mState = eMonsterState::Idle();
			mTime = 0;
		}

		GameObject::Update();
	}
	void ForestMonster::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void ForestMonster::Release()
	{
		GameObject::Release();
	}
	void ForestMonster::OnCollisionEnter(Collider* other)
	{

		if (other->GetOwner()->GetName() == L"BombEffect")
		{
			mAnimator->Play(L"ForestDie", false);
			mState = eMonsterState::Die;
		}
		mTime = 0;
		/*	if (other->GetOwner()->GetName() == L"Ground" || other->GetOwner()->GetName() == L"Monster")
			{
				animationCtr();
			}*/
	}

	void ForestMonster::OnCollisionStay(Collider* other)
	{
	}
	void ForestMonster::OnCollisionExit(Collider* other)
	{
	}

	void ForestMonster::idle()
	{
		mState = (eMonsterState)((rand() % 5));
		colcnt = 0;
		animationCtr();
	}
	void ForestMonster::left()
	{
		if (SceneManager::GetMapIndex()[ColLIdx.y][ColLIdx.x] >= 2
			&& SceneManager::GetMapIndex()[ColRIdx.y][ColRIdx.x] >= 2)
		{
			mState = eMonsterState::Up;
			colcnt++;
			animationCtr();
		}
		else if (SceneManager::GetMapIndex()[ColRIdx.y][ColRIdx.x] >= 2 && mPos.x <= 35.0f)
		{
			mState = eMonsterState::Down;
			colcnt++;
			animationCtr();
		}
		else if (SceneManager::GetMapIndex()[ColLIdx.y][ColLIdx.x] >= 2 || SceneManager::GetMapIndex()[ColLIdx.y][ColLIdx.x] == 1 || mPos.x <= 35.0f)
		{
			mState = eMonsterState::Right;
			colcnt++;
			animationCtr();
		}
		else
		{
			colcnt = 0;
			mPos.x -= 60.0f * Time::DeltaTime();

		}
	}
	void ForestMonster::right()
	{
		if (SceneManager::GetMapIndex()[ColLIdx.y][ColLIdx.x] >= 2
			&& SceneManager::GetMapIndex()[ColRIdx.y][ColRIdx.x] >= 2)
		{
			mState = eMonsterState::Down;
			colcnt++;
			animationCtr();
		}
		else if (SceneManager::GetMapIndex()[ColLIdx.y][ColLIdx.x] >= 2 && mPos.x >= 870.0f)
		{
			mState = eMonsterState::Down;
			colcnt++;
			animationCtr();
		}
		else if (SceneManager::GetMapIndex()[ColRIdx.y][ColRIdx.x] >= 2 || SceneManager::GetMapIndex()[ColRIdx.y][ColRIdx.x] == 1 || mPos.x >= 870.0f)
		{
			mState = eMonsterState::Left;
			colcnt++;
			animationCtr();
		}
		else
		{
			colcnt = 0;
			mPos.x += 60.0f * Time::DeltaTime();
		}
	}
	void ForestMonster::up()
	{
		if (SceneManager::GetMapIndex()[ColDIdx.y][ColDIdx.x] >= 2
			&& SceneManager::GetMapIndex()[ColUIdx.y][ColUIdx.x] >= 2)
		{
			mState = eMonsterState::Right;
			colcnt++;
			animationCtr();
		}
		else if (SceneManager::GetMapIndex()[ColDIdx.y][ColDIdx.x] >= 2
			&& mPos.y <= 65.0f)
		{
			mState = eMonsterState::Right;
			colcnt++;
			animationCtr();
		}
		else if (SceneManager::GetMapIndex()[ColUIdx.y][ColUIdx.x] >= 2 || SceneManager::GetMapIndex()[ColUIdx.y][ColUIdx.x] == 1 || mPos.y <= 60.0f)
		{
			mState = eMonsterState::Down;
			colcnt++;
			animationCtr();
		}
		else
		{
			colcnt = 0;
			mPos.y -= 60.0f * Time::DeltaTime();

		}
	}
	void ForestMonster::down()
	{
		if (SceneManager::GetMapIndex()[ColDIdx.y][ColDIdx.x] >= 2
			&& SceneManager::GetMapIndex()[ColUIdx.y][ColUIdx.x] >= 2)
		{
			mState = eMonsterState::Left;
			colcnt++;
			animationCtr();
		}
		else if (SceneManager::GetMapIndex()[ColUIdx.y][ColUIdx.x] >= 2
			&& mPos.y >= 775.0f)
		{
			mState = eMonsterState::Left;
			colcnt++;
			animationCtr();
		}
		else if (SceneManager::GetMapIndex()[ColDIdx.y][ColDIdx.x] >= 2 || SceneManager::GetMapIndex()[ColDIdx.y][ColDIdx.x] == 1 || mPos.y >= 780.0f)
		{
			mState = eMonsterState::Up;
			colcnt++;
			animationCtr();
		}
		else
		{
			colcnt = 0;
			mPos.y += 60.0f * Time::DeltaTime();

		}
	}
	void ForestMonster::die()
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
	void ForestMonster::animationCtr()
	{
		switch (mState)
		{
		case ty::ForestMonster::eMonsterState::Idle:
			break;
		case ty::ForestMonster::eMonsterState::Left:
			mAnimator->Play(L"ForestLeft", true);
			break;
		case ty::ForestMonster::eMonsterState::Right:
			mAnimator->Play(L"ForestRight", true);
			break;
		case ty::ForestMonster::eMonsterState::Up:
			mAnimator->Play(L"ForestUp", true);
			break;
		case ty::ForestMonster::eMonsterState::Down:
			mAnimator->Play(L"ForestDown", true);
			break;
		default:
			break;
		}
	}
}