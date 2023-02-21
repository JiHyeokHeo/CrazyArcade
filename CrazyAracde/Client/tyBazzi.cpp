#include "tyBazzi.h"
#include "tyTime.h"
#include "tySceneManager.h"
#include "tyinput.h"

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
		GameObject::Initialize();
	}
	void Bazzi::Update()
	{
		GameObject::Update();
		if (Input::GetKeyState(eKeyCode::A) == eKeyState::Pressed)
		{
			mPos.x -= 100.0f * Time::DeltaTime();
		}

		if (Input::GetKeyState(eKeyCode::D) == eKeyState::Pressed)
		{
			mPos.x += 100.0f * Time::DeltaTime();
		}

		//if (Input::GetKeyState(eKeyCode::D) == eKeyState::Up)
		//{
		//	mPos.x = 0.0f;
		//	mPos.y = 0.0f;
		//}

		if (Input::GetKeyState(eKeyCode::W) == eKeyState::Pressed)
		{
			mPos.y -= 100.0f * Time::DeltaTime();
		}

		if (Input::GetKeyState(eKeyCode::S) == eKeyState::Pressed)
		{
			mPos.y += 100.0f * Time::DeltaTime();
		}
	}
	void Bazzi::Render(HDC hdc)
	{
		GameObject::Render(hdc);
		// stock 오브젝트
		HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);
		//Rectangle(mHdc, -1, -1, 1601, 901);

		HPEN pen = CreatePen(PS_SOLID, 2, RGB(255, 0, 255)); // 얘가 마젠타.
		HPEN oldpen = (HPEN)SelectObject(hdc, pen); // 원래 들고 있던 팬을 반환한다. 즉 검은색을 oldpen에 반환

		Rectangle(hdc, mPos.x, mPos.y, mPos.x + 100, mPos.y + 100);

		SelectObject(hdc, oldpen); // 다시 올드펜을 샐렉해준다.
		DeleteObject(pen); // 데이터 릭을 방지하기 위해 만든 펜을 지워준다. 스톡 메모리를 지워버리면 메모리 단편화가 발생한다.
		SelectObject(hdc, oldBrush);
		DeleteObject(brush);
	}
	void Bazzi::Release()
	{
		GameObject::Release();
	}
}