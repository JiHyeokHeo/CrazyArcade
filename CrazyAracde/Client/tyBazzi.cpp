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
		Image* mImage = Resources::Load<Image>(L"Bazzi", L"..\\Resources\\right.bmp");
		Animator* animator = AddComponent<Animator>();
		animator->CreateAnimation(L"right", mImage, Vector2::Zero, 6, 1, 6, Vector2::Zero, 0.1);

		animator->Play(L"right", false);
		GameObject::Initialize();

	}
	void Bazzi::Update()
	{
		GameObject::Update();

		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		if (Input::GetKeyState(eKeyCode::LEFT) == eKeyState::Pressed)
		{
			pos.x -= 100.0f * Time::DeltaTime();
		}

		if (Input::GetKeyState(eKeyCode::RIGHT) == eKeyState::Pressed)
		{
			pos.x += 100.0f * Time::DeltaTime();
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
			pos.y -= 100.0f * Time::DeltaTime();
		}

		if (Input::GetKeyState(eKeyCode::DOWN) == eKeyState::Pressed)
		{
			pos.y += 100.0f * Time::DeltaTime();
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