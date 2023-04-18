#include "tySealBoss.h"
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
#include "tyTileBomb.h"

namespace ty
{
	SealBoss::SealBoss()
		: Hp(2)
	{
	}
	SealBoss::~SealBoss()
	{
	}
	void SealBoss::Initialize()
	{
		SetName(L"Boss");
		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector2(2.0f, 2.0f));

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Monster\\SealBoss\\Up", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Monster\\SealBoss\\Down", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Monster\\SealBoss\\Left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Monster\\SealBoss\\Right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Monster\\SealBoss\\Bubble", Vector2::Zero, 0.3f);
		mAnimator->CreateAnimations(L"..\\Resources\\Monster\\SealBoss\\Die", Vector2::Zero, 0.5f);
		mAnimator->CreateAnimations(L"..\\Resources\\Monster\\SealBoss\\Hit", Vector2::Zero, 0.3f);

		mAnimator->GetCompleteEvent(L"SealBossBubble") = std::bind(&SealBoss::bubbleCompleteEvent, this);
		mAnimator->Play(L"SealBossDown", false);

		Collider* collider = AddComponent<Collider>();
		collider->SetCenter(Vector2(30.0f, 50.0f));
		collider->SetSize(Vector2(140.0f, 180.0f));
		mState = eSealMonsterState::Idle;
		GameObject::Initialize();
	}

	void SealBoss::Update()
	{
		tr = GetComponent<Transform>();
		mPos = tr->GetPos();
		midmPos = mPos + Vector2(TILE_SIZE_X / 2, TILE_SIZE_Y / 2);
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


		mTime += Time::DeltaTime();
		TimeSpend += Time::DeltaTime();
		if (TimeSpend >= 1.5f)
		{
			switch (mState)
			{
			case ty::SealBoss::eSealMonsterState::Idle:
				idle();
				break;
			case ty::SealBoss::eSealMonsterState::Attack:
				attack();
				break;
			case ty::SealBoss::eSealMonsterState::Left:
				left();
				break;
			case ty::SealBoss::eSealMonsterState::Right:
				right();
				break;
			case ty::SealBoss::eSealMonsterState::Up:
				up();
				break;
			case ty::SealBoss::eSealMonsterState::Down:
				down();
				break;
			case ty::SealBoss::eSealMonsterState::Hit:
				hit();
				break;
			case ty::SealBoss::eSealMonsterState::Bubble:
				bubble();
				break;
			case ty::SealBoss::eSealMonsterState::Die:
				die();
				break;

			default:
				break;
			}
		}

		tr->SetPos(mPos);

		if (mTime >= 1 && mState != eSealMonsterState::Die && mState != eSealMonsterState::Hit && mState != eSealMonsterState::Bubble)
		{
			mState = eSealMonsterState::Idle;
			mTime = 0;
		}
		GameObject::Update();
	}
	void SealBoss::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void SealBoss::Release()
	{

	}
	void SealBoss::OnCollisionEnter(Collider* other)
	{
		if (other->GetOwner()->GetName() == L"Ground" || other->GetOwner()->GetName() == L"Monster")
		{
			switch (mState)
			{
			case eSealMonsterState::Left:
				mState = eSealMonsterState::Right;
				break;
			case eSealMonsterState::Right:
				mState = eSealMonsterState::Left;
				break;
			case eSealMonsterState::Up:
				mState = eSealMonsterState::Down;
				break;
			case eSealMonsterState::Down:
				mState = eSealMonsterState::Up;
				break;
			default:
				break;
			}
		}


		if (isColl == false && Hp >= 1 && other->GetOwner()->GetName() == L"BombEffect")
		{
			mAnimator->Play(L"SealBossHit", false);
			mState = eSealMonsterState::Hit;
			isColl = true;
		}

		if (isColl == false && Hp <= 0 && other->GetOwner()->GetName() == L"BombEffect" && mState != eSealMonsterState::Bubble)
		{
			mAnimator->Play(L"SealBossBubble", false);
			mState = eSealMonsterState::Bubble;
			isColl = true;
		}

		if (mState == eSealMonsterState::Bubble && other->GetOwner()->GetName() == L"Bazzi")
		{
			mAnimator->Play(L"SealBossDie", false);
			mState = eSealMonsterState::Die;
			isColl = true;
		}


	}
	void SealBoss::OnCollisionStay(Collider* other)
	{

	}
	void SealBoss::OnCollisionExit(Collider* other)
	{
	}
	void SealBoss::idle()
	{
		mState = (eSealMonsterState)((rand() % 6));
		animationCtr();
	}
	void SealBoss::attack()
	{
		//Transform* tr = GetComponent<Transform>();

		//if (isAttack == true)
		//{
		//	for (int i = 0; i < 7; i++)
		//	{
		//		ePirateMonsterState::Idle;
		//		object::Instantiate<BossBombEffect>(TileBomb::SetPos(midmPos + Vector2(180, 180 - (i * 60))), eLayerType::BombEffect);
		//		object::Instantiate<BossBombEffect>(TileBomb::SetPos(midmPos + Vector2(180 - (i * 60), 180)), eLayerType::BombEffect);
		//		object::Instantiate<BossBombEffect>(TileBomb::SetPos(midmPos + Vector2(-180 + (i * 60), -180)), eLayerType::BombEffect);
		//		object::Instantiate<BossBombEffect>(TileBomb::SetPos(midmPos + Vector2(-180, 180 - (i * 60))), eLayerType::BombEffect);
		//		isAttack = false;
		//	}
		//}

	}
	void SealBoss::left()
	{
		mPos.x -= 60.0f * Time::DeltaTime();
	}

	void SealBoss::right()
	{
		mPos.x += 60.0f * Time::DeltaTime();
	}
	void SealBoss::up()
	{
		mPos.y -= 60.0f * Time::DeltaTime();
	}
	void SealBoss::down()
	{
		mPos.y += 60.0f * Time::DeltaTime();
	}
	void SealBoss::hit()
	{

		mInvincibility -= Time::DeltaTime();
		if (mAnimator->isComplete() == true)
		{
			if (mInvincibility <= 0)
			{
				Hp--;
				mState = eSealMonsterState::Idle;
				isColl = false;
				mInvincibility = 3;
			}
		}
	}
	void SealBoss::bubble()
	{
		mInvincibility -= Time::DeltaTime();
		if (mAnimator->isComplete() == true)
		{
			mAnimator->Play(L"SealBossDie", false);
			eSealMonsterState::Die;
			mInvincibility = 3;
		}
	}
	void SealBoss::die()
	{
		if (mAnimator->isComplete() == true)
		{
			int monstercnt = SceneManager::GetMonsterCnt();
			monstercnt--;
			SceneManager::SetMonsterCnt(monstercnt);
			mState = eSealMonsterState::Idle;
			object::Pause(this);
		}
	}
	void SealBoss::animationCtr()
	{
		switch (mState)
		{
		case ty::SealBoss::eSealMonsterState::Idle:
			break;
		case ty::SealBoss::eSealMonsterState::Attack:
			isAttack = true;
			break;
		case ty::SealBoss::eSealMonsterState::Left:
			mAnimator->Play(L"SealBossLeft", true);
			break;
		case ty::SealBoss::eSealMonsterState::Right:
			mAnimator->Play(L"SealBossRight", true);
			break;
		case ty::SealBoss::eSealMonsterState::Up:
			mAnimator->Play(L"SealBossUp", true);
			break;
		case ty::SealBoss::eSealMonsterState::Down:
			mAnimator->Play(L"SealBossDown", true);
			break;
		default:
			break;
		}
	}
	void SealBoss::bubbleCompleteEvent()
	{
		mState = eSealMonsterState::Die;
	}
}