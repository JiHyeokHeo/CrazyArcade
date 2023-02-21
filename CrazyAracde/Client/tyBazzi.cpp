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
		// stock ������Ʈ
		HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);
		//Rectangle(mHdc, -1, -1, 1601, 901);

		HPEN pen = CreatePen(PS_SOLID, 2, RGB(255, 0, 255)); // �갡 ����Ÿ.
		HPEN oldpen = (HPEN)SelectObject(hdc, pen); // ���� ��� �ִ� ���� ��ȯ�Ѵ�. �� �������� oldpen�� ��ȯ

		Rectangle(hdc, mPos.x, mPos.y, mPos.x + 100, mPos.y + 100);

		SelectObject(hdc, oldpen); // �ٽ� �õ����� �������ش�.
		DeleteObject(pen); // ������ ���� �����ϱ� ���� ���� ���� �����ش�. ���� �޸𸮸� ���������� �޸� ����ȭ�� �߻��Ѵ�.
		SelectObject(hdc, oldBrush);
		DeleteObject(brush);
	}
	void Bazzi::Release()
	{
		GameObject::Release();
	}
}