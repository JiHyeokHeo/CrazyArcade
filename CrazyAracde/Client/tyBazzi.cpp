#include "tyBazzi.h"
#include "tyTime.h"
#include "tySceneManager.h"
#include "tyinput.h"
#include "tyResources.h"
#include "tyImage.h"

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
		mImage = Resources::Load<Image>(L"Bazzi", L"..\\Resources\\Idle.bmp");
		
		GameObject::Initialize();
	}
	void Bazzi::Update()
	{
		GameObject::Update();
		if (Input::GetKeyState(eKeyCode::LEFT) == eKeyState::Pressed)
		{
			mPos.x -= 100.0f * Time::DeltaTime();
		}

		if (Input::GetKeyState(eKeyCode::RIGHT) == eKeyState::Pressed)
		{
			mPos.x += 100.0f * Time::DeltaTime();
		}

		//if (Input::GetKeyState(eKeyCode::SPACEBAR) == eKeyState::Down)
		//{
		//	  물풍선 사용
		//}

		//if (Input::GetKeyState(eKeyCode::CTRL) == eKeyState::Down)
		//{
		//    아이템 사용
		//}

		if (Input::GetKeyState(eKeyCode::UP) == eKeyState::Pressed)
		{
			mPos.y -= 100.0f * Time::DeltaTime();
		}

		if (Input::GetKeyState(eKeyCode::DOWN) == eKeyState::Pressed)
		{
			mPos.y += 100.0f * Time::DeltaTime();
		}
	}
	void Bazzi::Render(HDC hdc)
	{
		GameObject::Render(hdc);

		BitBlt(hdc, mPos.x, mPos.y, mImage->GetWidth(), mImage->GetHeight(), mImage->GetHdc(), 0, 0, SRCCOPY);
	}
	void Bazzi::Release()
	{
		GameObject::Release();
	}
}