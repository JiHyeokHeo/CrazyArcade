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

namespace ty
{
	Bazzi::Bazzi()
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
		mAnimator = AddComponent<Animator>();
		
		mAnimator->CreateAnimation(L"up", mUpImage, Vector2::Zero, 8, 1, 8, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"down", mDownImage, Vector2::Zero, 8, 1, 8, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"left", mLeftImage, Vector2::Zero, 6, 1, 6, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"right", mRightImage, Vector2::Zero, 6, 1, 6, Vector2::Zero, 0.1);

		mAnimator->CreateAnimation(L"upIdle", mUpImage, Vector2::Zero, 8, 1, 1, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"downIdle", mDownImage, Vector2::Zero, 8, 1, 1, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"leftIdle", mLeftImage, Vector2::Zero, 6, 1, 1, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"rightIdle", mRightImage, Vector2::Zero, 6, 1, 1, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"ready", mReadyImage, Vector2::Zero, 18, 1, 17, Vector2(0.0f, -10.0f), 0.07); // 오프셋 조절해서 ready 모션 바꿈 x,y축 잘 확인하기


		mAnimator->Play(L"ready", false);
		
		Collider* collider = AddComponent<Collider>();
		collider->SetCenter(Vector2(0.0f, 0.0f));
		collider->SetSize(Vector2(75.52f,89.68f));
		
		mState = eBazziState::Idle;

		//mAnimator->GetStartEvent(L"downIdle") = std::bind(&Bazzi::idleCompleteEvent, this);
		

		//mAnimator->Play(L"downIlde", true);
		GameObject::Initialize();

	}
	void Bazzi::Update()
	{
		GameObject::Update();

		//if()
		//if (mbombtime == 3)
		//{
		//	delete [] bomb;
		//}

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
	void Bazzi::Render(HDC hdc)
	{
		GameObject::Render(hdc);
		
	}
	void Bazzi::Release()
	{
		GameObject::Release();
	}
	void Bazzi::move()
	{
		if (Input::GetKeyUp(eKeyCode::LEFT))
		{
			mAnimator->Play(L"leftIdle", true);
		}
		else if (Input::GetKeyUp(eKeyCode::RIGHT))
		{
			mAnimator->Play(L"rightIdle", true);
		}
		else if (Input::GetKeyUp(eKeyCode::UP))
		{
			mAnimator->Play(L"upIdle", true);
		}
		else if (Input::GetKeyUp(eKeyCode::DOWN))
		{
			mAnimator->Play(L"downIdle", true);
		}
			
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		if (Input::GetKey(eKeyCode::LEFT))
		{
			mAnimator->Play(L"left", true); 
			pos.x -= 200.0f * Time::DeltaTime();
		}
		else if (Input::GetKey(eKeyCode::RIGHT))
		{
			mAnimator->Play(L"right", true);
			pos.x += 200.0f * Time::DeltaTime();
		}
		else if (Input::GetKey(eKeyCode::UP))
		{
			mAnimator->Play(L"up", true);
			pos.y -= 200.0f * Time::DeltaTime();
		}
		else if (Input::GetKey(eKeyCode::DOWN))
		{
			mAnimator->Play(L"down", true);
			pos.y += 200.0f * Time::DeltaTime();
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
 			Scene* curScene = SceneManager::GetActiveScene();
			BaseBomb* mBomb = new BaseBomb();
			mBomb->GetComponent<Transform>()->SetPos(tr->GetPos());
			curScene->AddGameObject(mBomb, eLayerType::Bomb);
			mState = eBazziState::Move;
		}
	}
	void Bazzi::death()
	{
	}
	void Bazzi::idle()
	{
		if (Input::GetKeyDown(eKeyCode::LEFT)
			|| Input::GetKeyDown(eKeyCode::RIGHT)
			|| Input::GetKeyDown(eKeyCode::UP)
			|| Input::GetKeyDown(eKeyCode::DOWN))
		{
			mState = eBazziState::Move;
			//mAnimator->Play(L"down", true);
		}
	}
	void Bazzi::idleCompleteEvent(/*const Cuphead* this*/)
	{
		int a = 0;
		//mState =
		//Transform* tr = GetComponent<Transform>();
		//Scene* curScene = SceneManager::GetActiveScene();
		//BaseBullet* bullet = new BaseBullet();
		//bullet->GetComponent<Transform>()->SetPos(tr->GetPos());
		//curScene->AddGameObeject(bullet, eLayerType::Bullet);
	}
}