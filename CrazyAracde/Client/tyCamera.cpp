#include "tyCamera.h"
#include "tyApplication.h"
#include "tyGameObject.h"
#include "tyTransform.h"
#include "tyinput.h"
#include "tyTime.h"
#include "tyImage.h"

extern ty::Application application; // 이거 구글링 찾아보자

namespace ty
{
	Vector2 Camera::mResolution = Vector2::Zero;
	Vector2 Camera::mLookPosition = Vector2::Zero;
	Vector2 Camera::mDistance = Vector2::Zero;
	GameObject* Camera::mTarget = nullptr;

	Camera::eCameraEffectType Camera::mType = Camera::eCameraEffectType::None;
	class Image* Camera::mCutton = nullptr;
	float Camera::mCuttonAlpha = 1.0f;
	float Camera::mAlphaTime = 0.0f;
	float Camera::mEndTime = 5.0f;

	void Camera::Initialize()
	{
		mResolution.x = application.GetWidth();
		mResolution.y = application.GetHeight();
		mLookPosition = (mResolution / 2.0f);

		mType = eCameraEffectType::FadeIn;
		mCutton = Image::Create(L"Cutton", mResolution.x, mResolution.y, RGB(0, 0, 0));
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
	

		if (mAlphaTime < mEndTime)
		{
			//255 에서 1로 변환 시켜준것이다.
			mAlphaTime += Time::DeltaTime();
			float ratio = (mAlphaTime / mEndTime);
			if (mType == eCameraEffectType::FadeIn)
			{
				mCuttonAlpha = 1.0f - ratio;
			}
			else if (mType == eCameraEffectType::FadeOut)
			{
				mCuttonAlpha = ratio;
			}
			else
			{

			}
		}
	

		mDistance = mLookPosition - (mResolution / 2.0f); 
	}

	void Camera::Render(HDC hdc)
	{
		if (mAlphaTime < mEndTime
			&& mType == eCameraEffectType::FadeIn)
		{
			BLENDFUNCTION func = {};
			func.BlendOp = AC_SRC_OVER;
			func.BlendFlags = 0;
			func.AlphaFormat = 0;
			func.SourceConstantAlpha = (BYTE)(255.0f * mCuttonAlpha);

			AlphaBlend(hdc, 0, 0
				, mResolution.x, mResolution.y
				, mCutton->GetHdc()
				, 0, 0
				, mCutton->GetWidth(), mCutton->GetHeight()
				, func);
		}
	}

	void Camera::Clear()
	{
		mResolution.x = application.GetWidth();
		mResolution.y = application.GetHeight();
		mLookPosition = (mResolution / 2.0f);
		mDistance = Vector2::Zero;
	}

}