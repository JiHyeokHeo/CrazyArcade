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
		: mTime(0.0f)
		, mIdx(0)
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
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();


		mTime += Time::DeltaTime();

		if (mIdx >= 16)
		{
			mIdx = 0;
		}

		if (mTime > 0.1f)
		{
			mIdx++;
			mTime = 0.0f;
		}

		// 시작 지점 103, 113 그리고 103 x좌표는 midx만큼 계속 곱해진다
		TransparentBlt(hdc, pos.x, pos.y, mImage->GetWidth(), mImage->GetHeight(), mImage->GetHdc(),
			0, 0, mImage->GetWidth(), mImage->GetHeight(), RGB(255, 0, 255));

		//BitBlt(hdc, pos.x, pos.y, mImage->GetWidth(), mImage->GetHeight(), mImage->GetHdc(), 0, 0, SRCCOPY);
		
	}
	void Bazzi::Release()
	{
		GameObject::Release();
	}
}