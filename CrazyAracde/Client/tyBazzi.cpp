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
		//배율 tr->SetScale(Vector2(2.0f, 2.0f));

		Image* mDownImage = Resources::Load<Image>(L"Bazzi", L"..\\Resources\\Bazzi\\down.bmp");
		Image* mUpImage = Resources::Load<Image>(L"Bazzi", L"..\\Resources\\Bazzi\\up.bmp");
		Image* mRightImage = Resources::Load<Image>(L"Bazzi", L"..\\Resources\\Bazzi\\right.bmp");
		Image* mLeftImage = Resources::Load<Image>(L"Bazzi", L"..\\Resources\\Bazzi\\left.bmp");
		mAnimator = AddComponent<Animator>();
		
		mAnimator->CreateAnimation(L"up", mUpImage, Vector2::Zero, 8, 1, 8, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"right", mRightImage, Vector2::Zero, 6, 1, 6, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"down", mDownImage, Vector2::Zero, 8, 1, 8, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"left", mLeftImage, Vector2::Zero, 6, 1, 6, Vector2::Zero, 0.1);

		mAnimator->CreateAnimation(L"upIdle", mUpImage, Vector2::Zero, 8, 1, 1, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"rightIdle", mRightImage, Vector2::Zero, 6, 1, 1, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"downIdle", mDownImage, Vector2::Zero, 8, 1, 1, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"leftIdle", mLeftImage, Vector2::Zero, 6, 1, 1, Vector2::Zero, 0.1);

		mAnimator->Play(L"downIdle", true);

		Collider* collider = AddComponent<Collider>();
		collider->SetCenter(Vector2(0.0f, 0.0f));

		mState = eBazziState::Idle;

		GameObject::Initialize();

	}
	void Bazzi::Update()
	{
		GameObject::Update();

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

		//Transform* tr = GetComponent<Transform>();
		//Vector2 pos = tr->GetPos();

		//Animator* animator = GetComponent<Animator>();
		//if (Input::GetKeyState(eKeyCode::LEFT) == eKeyState::Pressed)
		//{
		//	pos.x -= 200.0f * Time::DeltaTime();
		//	animator->Play(L"left", true);
		//}

		//if (Input::GetKeyState(eKeyCode::LEFT) == eKeyState::Down)
		//{
		//	animator->Play(L"left", true);
		//}
		//
		//if (Input::GetKeyState(eKeyCode::LEFT) == eKeyState::Up)
		//{
		//	animator->Play(L"leftIdle", false);
		//}

		//if (Input::GetKeyState(eKeyCode::RIGHT) == eKeyState::Pressed)
		//{
		//	pos.x += 200.0f * Time::DeltaTime();
		//	animator->Play(L"right", true);
		//}

		//if (Input::GetKeyState(eKeyCode::RIGHT) == eKeyState::Down)
		//{
		//	animator->Play(L"right", true);
		//}

		//if (Input::GetKeyState(eKeyCode::RIGHT) == eKeyState::Up)
		//{
		//	animator->Play(L"rightIdle", false);
		//}

		////if (Input::GetKeyState(eKeyCode::SPACEBAR) == eKeyState::Down)
		////{
		////	  물풍선 사용 추후에 Sprite쪽이랑 연결하는걸까?
		////}

		////if (Input::GetKeyState(eKeyCode::CTRL) == eKeyState::Down)
		////{
		////    아이템 사용
		////}

		//if (Input::GetKeyState(eKeyCode::UP) == eKeyState::Pressed)
		//{
		//	pos.y -= 200.0f * Time::DeltaTime();
		//	animator->Play(L"up", true);
		//}

		//if (Input::GetKeyState(eKeyCode::UP) == eKeyState::Down)
		//{
		//	animator->Play(L"up", true);
		//}

		//if (Input::GetKeyState(eKeyCode::UP) == eKeyState::Up)
		//{
		//	animator->Play(L"upIdle", false);
		//}

		//if (Input::GetKeyState(eKeyCode::DOWN) == eKeyState::Pressed)
		//{
		//	pos.y += 200.0f * Time::DeltaTime();
		//	animator->Play(L"down", true);
		//}

		//if (Input::GetKeyState(eKeyCode::DOWN) == eKeyState::Down)
		//{
		//	animator->Play(L"down", true);
		//}

		//if (Input::GetKeyState(eKeyCode::DOWN) == eKeyState::Up)
		//{
		//	animator->Play(L"downIdle", false);
		//}
		//tr->SetPos(pos);
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
		if (Input::GetKeyUp(eKeyCode::LEFT)
			|| Input::GetKeyUp(eKeyCode::RIGHT)
			|| Input::GetKeyUp(eKeyCode::UP)
			|| Input::GetKeyUp(eKeyCode::DOWN))
		{
			mState = eBazziState::Idle;
			mAnimator->Play(L"downIdle", true);
		}
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		if (Input::GetKey(eKeyCode::LEFT))
		{
			pos.x -= 200.0f * Time::DeltaTime();
			mAnimator->Play(L"right", true); // 이따가 봐야할것 
		}
		else if (Input::GetKey(eKeyCode::RIGHT))
			pos.x += 200.0f * Time::DeltaTime();
		else if (Input::GetKey(eKeyCode::UP))
			pos.y -= 200.0f * Time::DeltaTime();
		else if (Input::GetKey(eKeyCode::DOWN))
			pos.y += 200.0f * Time::DeltaTime();

		tr->SetPos(pos);
	}
	void Bazzi::shoot()
	{
		Transform* tr = GetComponent<Transform>();
		if (Input::GetKey(eKeyCode::SPACEBAR))
		{
			Scene* curScene = SceneManager::GetActiveScene();
			BaseBomb* bomb = new BaseBomb();
			bomb->GetComponent<Transform>()->SetPos(tr->GetPos());
			curScene->AddGameObject(bomb, eLayerType::Bomb);
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
			mAnimator->Play(L"down", true);
		}

		if (Input::GetKeyDown(eKeyCode::SPACEBAR))
		{
			mState = eBazziState::Shoot;
			mAnimator->Play(L"downIdle", true);
		}
	}
}