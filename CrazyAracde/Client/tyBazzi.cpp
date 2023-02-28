#include "tyBazzi.h"
#include "tyTime.h"
#include "tySceneManager.h"
#include "tyinput.h"
#include "tyResources.h"
#include "tyTransform.h"
#include "tyAnimator.h"

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
		Image* mImage = Resources::Load<Image>(L"Bazzi", L"..\\Resources\\Bazzi.bmp");
		Animator* animator = AddComponent<Animator>();
		
		animator->CreateAnimation(L"up", mImage, Vector2::Zero, 8, 4, 8, Vector2::Zero, 0.1);
		animator->CreateAnimation(L"right", mImage, Vector2(0.0f, 150.0f), 8, 4, 6, Vector2::Zero, 0.1);
		animator->CreateAnimation(L"down", mImage, Vector2(0.0f, 150.0f * 2), 8, 4, 8, Vector2::Zero, 0.1);
		animator->CreateAnimation(L"left", mImage, Vector2(0.0f, 150.0f * 3), 8, 4, 6, Vector2::Zero, 0.1);

		animator->CreateAnimation(L"upIdle", mImage, Vector2::Zero, 8, 4, 1, Vector2::Zero, 0.1);
		animator->CreateAnimation(L"rightIdle", mImage, Vector2(0.0f, 150.0f), 8, 4, 1, Vector2::Zero, 0.1);
		animator->CreateAnimation(L"downIdle", mImage, Vector2(0.0f, 150.0f * 2), 8, 4, 1, Vector2::Zero, 0.1);
		animator->CreateAnimation(L"leftIdle", mImage, Vector2(0.0f, 150.0f * 3), 8, 4, 1, Vector2::Zero, 0.1);

		animator->Play(L"downIdle", false);
		GameObject::Initialize();

	}
	void Bazzi::Update()
	{
		GameObject::Update();

		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		Animator* animator = GetComponent<Animator>();
		if (Input::GetKeyState(eKeyCode::LEFT) == eKeyState::Pressed)
		{
			pos.x -= 200.0f * Time::DeltaTime();
			animator->Play(L"left", true);
		}

		if (Input::GetKeyState(eKeyCode::LEFT) == eKeyState::Down)
		{
			animator->Play(L"left", true);
		}
		
		if (Input::GetKeyState(eKeyCode::LEFT) == eKeyState::Up)
		{
			animator->Play(L"leftIdle", false);
		}

		if (Input::GetKeyState(eKeyCode::RIGHT) == eKeyState::Pressed)
		{
			pos.x += 200.0f * Time::DeltaTime();
			animator->Play(L"right", true);
		}

		if (Input::GetKeyState(eKeyCode::RIGHT) == eKeyState::Down)
		{
			animator->Play(L"right", true);
		}

		if (Input::GetKeyState(eKeyCode::RIGHT) == eKeyState::Up)
		{
			animator->Play(L"rightIdle", false);
		}

		//if (Input::GetKeyState(eKeyCode::SPACEBAR) == eKeyState::Down)
		//{
		//	  물풍선 사용 추후에 Sprite쪽이랑 연결하는걸까?
		//}

		//if (Input::GetKeyState(eKeyCode::CTRL) == eKeyState::Down)
		//{
		//    아이템 사용
		//}

		if (Input::GetKeyState(eKeyCode::UP) == eKeyState::Pressed)
		{
			pos.y -= 200.0f * Time::DeltaTime();
			animator->Play(L"up", true);
		}

		if (Input::GetKeyState(eKeyCode::UP) == eKeyState::Down)
		{
			animator->Play(L"up", true);
		}

		if (Input::GetKeyState(eKeyCode::UP) == eKeyState::Up)
		{
			animator->Play(L"upIdle", false);
		}

		if (Input::GetKeyState(eKeyCode::DOWN) == eKeyState::Pressed)
		{
			pos.y += 200.0f * Time::DeltaTime();
			animator->Play(L"down", true);
		}

		if (Input::GetKeyState(eKeyCode::DOWN) == eKeyState::Down)
		{
			animator->Play(L"down", true);
		}

		if (Input::GetKeyState(eKeyCode::DOWN) == eKeyState::Up)
		{
			animator->Play(L"downIdle", false);
		}
		tr->SetPos(pos);
	}
	void Bazzi::Render(HDC hdc)
	{
		GameObject::Render(hdc);
		
	}
	void Bazzi::Release()
	{
		GameObject::Release();
	}
}