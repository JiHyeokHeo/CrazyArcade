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

namespace ty
{
	Bazzi::Bazzi()
		: maxHP(1)
		
	{
	}
	Bazzi::~Bazzi()
	{
	}
	void Bazzi::Initialize()
	{
		Transform* tr = GetComponent<Transform>();
		tr->SetPos(Vector2(400.0f, 400.0f));
		tr->SetScale(Vector2(1.18f, 1.18f));
		
		Image* mUpImage = Resources::Load<Image>(L"BazziU", L"..\\Resources\\Bazzi\\up.bmp");
		Image* mLeftImage = Resources::Load<Image>(L"BazziL", L"..\\Resources\\Bazzi\\left.bmp");
		Image* mRightImage = Resources::Load<Image>(L"BazziR", L"..\\Resources\\Bazzi\\right.bmp");
		Image* mDownImage = Resources::Load<Image>(L"BazziD", L"..\\Resources\\Bazzi\\down.bmp");
		Image* mReadyImage = Resources::Load<Image>(L"BazziReady", L"..\\Resources\\Bazzi\\ready.bmp");
		Image* mDieImage = Resources::Load<Image>(L"BazziDie", L"..\\Resources\\Bazzi\\die.bmp");
		Image* mTrapeImage = Resources::Load<Image>(L"BazziTrap", L"..\\Resources\\Bazzi\\trap.bmp");
		mAnimator = AddComponent<Animator>();
		
		mAnimator->CreateAnimation(L"up", mUpImage, Vector2::Zero, 8, 1, 8, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"down", mDownImage, Vector2::Zero, 8, 1, 8, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"left", mLeftImage, Vector2::Zero, 6, 1, 6, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"right", mRightImage, Vector2::Zero, 6, 1, 6, Vector2::Zero, 0.1);

		mAnimator->CreateAnimation(L"upIdle", mUpImage, Vector2::Zero, 8, 1, 1, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"downIdle", mDownImage, Vector2::Zero, 8, 1, 1, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"leftIdle", mLeftImage, Vector2::Zero, 6, 1, 1, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"rightIdle", mRightImage, Vector2::Zero, 6, 1, 1, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"ready", mReadyImage, Vector2::Zero, 18, 1, 17, Vector2::Zero, 0.07); // 오프셋 조절해서 ready 모션 바꿈 x,y축 잘 확인하기

		mAnimator->CreateAnimation(L"die", mDieImage, Vector2(352.0f,0.0f), 13, 1, 13, Vector2(-12.0f, -50.0f), 0.15);
		mAnimator->CreateAnimation(L"trap", mTrapeImage, Vector2::Zero, 13, 1, 13, Vector2(-12.0f, -50.0f), 0.1);
		

		//mAnimator->GetStartEvent(L"ready") = std::bind(&Bazzi::idleCompleteEvent, this);
		mAnimator->Play(L"ready", false);
		
		Collider* collider = AddComponent<Collider>();
		collider->SetCenter(Vector2(-23.0f, -55.0f));
		collider->SetSize(Vector2(50.0f, 43.6f));
		
		mState = eBazziState::Idle;

		//mAnimator->Play(L"downIlde", true);
		GameObject::Initialize();

	}
	void Bazzi::Update()
	{
		GameObject::Update();

		mTime += Time::DeltaTime();

		//delete mBomb;
		if (mTime >= 1.2)
		{
			switch (mState)
			{
			case ty::Bazzi::eBazziState::Move:
				move();
				break;
			case ty::Bazzi::eBazziState::Shoot:
				shoot();
				break;
			case ty::Bazzi::eBazziState::Death:
				death();
				break;
			case ty::Bazzi::eBazziState::Idle:
				idle();
				break;
			default:
				break;
			}
		}

	}
	void Bazzi::Render(HDC hdc)
	{
		GameObject::Render(hdc);
		
	}
	void Bazzi::Release()
	{
		GameObject::Release();
	}
	void Bazzi::OnCollisionEnter(Collider* other)
	{ 
		int a = 0;
		//mState = eBazziState::Death;
	}
	void Bazzi::OnCollisionStay(Collider* other)
	{
		//mState = eBazziState::Death;
	}
	void Bazzi::OnCollisionExit(Collider* other)
	{
	}
	void Bazzi::move()
	{
		if (Input::GetKeyUp(eKeyCode::LEFT))
		{
			mAnimator->Play(L"leftIdle", false);
			mState = eBazziState::Idle;
		}
		if (Input::GetKeyUp(eKeyCode::RIGHT))
		{
			mAnimator->Play(L"rightIdle", false);
			mState = eBazziState::Idle;
		}
		if (Input::GetKeyUp(eKeyCode::UP))
		{
			mAnimator->Play(L"upIdle", false);
			mState = eBazziState::Idle;
		}
		if (Input::GetKeyUp(eKeyCode::DOWN))
		{	
			mAnimator->Play(L"downIdle", false);
			mState = eBazziState::Idle;
		}
		
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		if (Input::GetKey(eKeyCode::LEFT) && isRPressed == false && isUPressed == false && isDPressed == false)
		{
			//isLPressed = true;
			pos.x -= 250.0f  * Time::DeltaTime();
		}
		if (Input::GetKey(eKeyCode::RIGHT) && isLPressed == false && isUPressed == false && isDPressed == false)
		{
			//isRPressed = true;
			pos.x += 250.0f * Time::DeltaTime();
		}
		if (Input::GetKey(eKeyCode::UP) && isRPressed == false && isLPressed == false && isDPressed == false)
		{
			//isUPressed = true;
			pos.y -= 250.0f  * Time::DeltaTime();
		}
		if (Input::GetKey(eKeyCode::DOWN) && isRPressed == false && isLPressed == false && isUPressed == false)
		{
			//isDPressed = true;
			pos.y += 250.0f  * Time::DeltaTime();
		}

		if (Input::GetKeyDown(eKeyCode::SPACEBAR))
		{
			mState = eBazziState::Shoot;
			//mAnimator->Play(L"downIdle", true);
		}

		tr->SetPos(pos);
	}
	void Bazzi::shoot()
 	{
		Transform* tr = GetComponent<Transform>();
		

		if (Input::GetKey(eKeyCode::SPACEBAR))
		{
			mState = eBazziState::Idle;
			object::Instantiate<BaseBomb>(tr->GetPos() +Vector2(-10.0f, -20.0f), eLayerType::Bomb);
		}
	}
	void Bazzi::death()
	{
		mAnimator->Play(L"die", false);
	}
	void Bazzi::idle()
	{
		isLPressed = false;
		isRPressed = false;
		isUPressed = false;
		isDPressed = false;
		if (Input::GetKey(eKeyCode::LEFT))
		{
			isLPressed = true;
			mAnimator->Play(L"left", true);
			mState = eBazziState::Move;
		}
		if (Input::GetKey(eKeyCode::RIGHT))
		{
			isRPressed = true;
			mAnimator->Play(L"right", true);
			mState = eBazziState::Move;
		}
		if (Input::GetKey(eKeyCode::UP))
		{
			isUPressed = true;
			mAnimator->Play(L"up", true);
			mState = eBazziState::Move;
		}
		if(Input::GetKey(eKeyCode::DOWN))
		{
			isDPressed = true;
			mAnimator->Play(L"down", true);
			mState = eBazziState::Move;
		}
		if (Input::GetKeyDown(eKeyCode::SPACEBAR))
		{
			mState = eBazziState::Shoot;
			//mAnimator->Play(L"downIdle", true);
		}

	}
	void Bazzi::idleCompleteEvent(/*const Cuphead* this*/) // 애니메이션 동작이 끝나면 실행되도록 할 수 있다.
	{
		int a = 0;
		//mState =
		//Transform* tr = GetComponent<Transform>();
		//Scene* curScene = SceneManager::GetActiveScene();
		////mBomb = new BaseBomb();
		////mBomb->Initialize(); /*가독성을 위해서 basebomb 생성자쪽에 이니셜 라이즈 붙임*/
		////mBomb->GetComponent<Transform>()->SetPos(tr->GetPos());
		////curScene->AddGameObject(mBomb, eLayerType::Bomb);
		//mState = eBazziState::Move;
	}
}