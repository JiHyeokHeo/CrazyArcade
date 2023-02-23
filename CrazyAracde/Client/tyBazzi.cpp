#include "tyBazzi.h"
#include "tyTime.h"
#include "tySceneManager.h"
#include "tyinput.h"
#include "tyResources.h"
#include "tyTransform.h"
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

		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		if (Input::GetKeyState(eKeyCode::A) == eKeyState::Pressed)
		{
			pos.x -= 100.0f * Time::DeltaTime();
		}

		if (Input::GetKeyState(eKeyCode::D) == eKeyState::Pressed)
		{
			pos.x += 100.0f * Time::DeltaTime();
		}

		//if (Input::GetKeyState(eKeyCode::SPACEBAR) == eKeyState::Down)
		//{
		//	  물풍선 사용
		//}

		//if (Input::GetKeyState(eKeyCode::CTRL) == eKeyState::Down)
		//{
		//    아이템 사용
		//}

		if (Input::GetKeyState(eKeyCode::W) == eKeyState::Pressed)
		{
			pos.y -= 100.0f * Time::DeltaTime();
		}

		if (Input::GetKeyState(eKeyCode::S) == eKeyState::Pressed)
		{
			pos.y += 100.0f * Time::DeltaTime();
		}
		tr->SetPos(pos);
	}
	void Bazzi::Render(HDC hdc)
	{
		GameObject::Render(hdc);
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		BitBlt(hdc, pos.x, pos.y, mImage->GetWidth(), mImage->GetHeight(), mImage->GetHdc(), 0, 0, SRCCOPY);
	}
	void Bazzi::Release()
	{
		GameObject::Release();
	}
}