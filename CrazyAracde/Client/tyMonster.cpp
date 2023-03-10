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

		Transform* tr = GetComponent<Transform>();
		mPos = tr->GetPos();
		//tr->SetPos(Vector2(400.0f, 500.0f));
		//tr->SetScale(Vector2(1.18f, 1.18f));

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Monster\\Pirate\\Up", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Monster\\Pirate\\Right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Monster\\Pirate\\Left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Monster\\Pirate\\Down", Vector2::Zero, 0.1f);
		mAnimator->Play(L"PirateDown", true);
		
		Collider* collider = AddComponent<Collider>();
		collider->SetCenter(Vector2::Zero);
		collider->SetSize(Vector2(44.0f, 44.0f));
		mState = eMonsterState::Idle;
		//GameObject::Initialize();
	}
	void Monster::Update()
	{
		Transform* tr = GetComponent<Transform>();
		mPos = tr->GetPos();
		
		mTime += Time::DeltaTime();

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
		default:
			break;
		}
		
		tr->SetPos(mPos);

		if (mTime >= 1)
		{
			mState = eMonsterState::Idle;
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
		animationCtr();
	}
	void Monster::left()
	{
		
		mPos.x -= 50.0f * Time::DeltaTime();
	}
	void Monster::right()
	{
		
		mPos.x += 50.0f * Time::DeltaTime();
	}
	void Monster::up()
	{
		
		mPos.y -= 50.0f * Time::DeltaTime();
	}
	void Monster::down()
	{
		
		mPos.y += 50.0f * Time::DeltaTime();
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