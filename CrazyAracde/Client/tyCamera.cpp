#include "tyCamera.h"
#include "tyApplication.h"
#include "tyGameObject.h"
#include "tyTransform.h"
#include "tyinput.h"
#include "tyTime.h"

extern ty::Application application; // 이거 구글링 찾아보자

namespace ty
{
	Vector2 Camera::mResolution = Vector2::Zero;
	Vector2 Camera::mLookPosition = Vector2::Zero;
	Vector2 Camera::mDistance = Vector2::Zero;
	GameObject* Camera::mTarget = nullptr;

	void Camera::Initialize()
	{
		mResolution.x = application.GetWidth();
		mResolution.y = application.GetHeight();
		mLookPosition = (mResolution / 2.0f);
	}

	void Camera::Update()
	{
		if (Input::GetKey(eKeyCode::A))
		{
			mLookPosition.x -= 200.0f * Time::DeltaTime();
		}
		if (Input::GetKey(eKeyCode::D))
		{
			mLookPosition.x += 200.0f * Time::DeltaTime();
		}
		if (Input::GetKey(eKeyCode::S))
		{
			mLookPosition.y -= 200.0f * Time::DeltaTime();
		}
		if (Input::GetKey(eKeyCode::W))
		{
			mLookPosition.y += 200.0f * Time::DeltaTime();
		}

		if (mTarget != nullptr)
		{ 
			mLookPosition
				= mTarget->GetComponent<Transform>()->GetPos();
		}
	
		mDistance = mLookPosition - (mResolution / 2.0f); 
	}

	void Camera::Clear()
	{
		mResolution.x = application.GetWidth();
		mResolution.y = application.GetHeight();
		mLookPosition = (mResolution / 2.0f);
		mDistance = Vector2::Zero;
	}

}