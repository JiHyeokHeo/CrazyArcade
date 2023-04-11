#include "tyTimer.h"
#include "tySceneManager.h"
#include "tyResources.h"
#include "tyImage.h"
#include "tyTime.h"
#include "tyAnimator.h"
#include "tyTransform.h"

namespace ty
{
	Timer::Timer()
	{
	}
	Timer::~Timer()
	{
	}
	void Timer::Initialize()
	{
	
		Transform* tr = GetComponent<Transform>();
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\UI\\Timer\\Zero", Vector2::Zero, 1.0f);
		mAnimator->CreateAnimations(L"..\\Resources\\UI\\Timer\\One", Vector2::Zero, 1.0f);
		mAnimator->CreateAnimations(L"..\\Resources\\UI\\Timer\\Two", Vector2::Zero, 1.0f);
		mAnimator->CreateAnimations(L"..\\Resources\\UI\\Timer\\Three", Vector2::Zero, 1.0f);
		mAnimator->CreateAnimations(L"..\\Resources\\UI\\Timer\\Four", Vector2::Zero, 1.0f);
		mAnimator->CreateAnimations(L"..\\Resources\\UI\\Timer\\Five", Vector2::Zero, 1.0f);
		mAnimator->CreateAnimations(L"..\\Resources\\UI\\Timer\\Six", Vector2::Zero, 1.0f);
		mAnimator->CreateAnimations(L"..\\Resources\\UI\\Timer\\Seven", Vector2::Zero, 1.0f);
		mAnimator->CreateAnimations(L"..\\Resources\\UI\\Timer\\Eight", Vector2::Zero, 1.0f);
		mAnimator->CreateAnimations(L"..\\Resources\\UI\\Timer\\Nine", Vector2::Zero, 1.0f);
		mAnimator->CreateAnimations(L"..\\Resources\\UI\\Timer\\Dot", Vector2::Zero, 1.0f);
		mAnimator->Play(L"TimerDot", false);

	/*	mAnimator->GetCompleteEvent(L"PirateBossDie") = std::bind(&PirateBoss::bubbleCompleteEvent, this);*/
		GameObject::Initialize();
	}
	void Timer::Update()
	{	
		mRealTime += Time::DeltaTime();

		if (isTimeOn == false)
		{
			mTime = SceneManager::GetTime();
			isTimeOn = true;
		}

		if (mRealTime >= 1.0f)
		{
			mTime -= 1;
			mRealTime = 0;
		}
		
		mMinutes = mTime / 60; // 분
		mSeconds = mTime % 10; // 초
		int mTenSeconds = mTime % 60;
		mTenSeconds = mTenSeconds / 10; // N 0초대

		if (mType == TimeType::TenMinutes)
		{
			mAnimator->Play(L"TimerZero", false);
		}
		if (mMinutes == 4 && mType == TimeType::Minutes)
		{
			mAnimator->Play(L"TimerFour", false);
		}
		if (mMinutes == 3 && mType == TimeType::Minutes)
		{
			mAnimator->Play(L"TimerThree", false);
		}
		if (mMinutes == 2 && mType == TimeType::Minutes)
		{
			mAnimator->Play(L"TimerTwo", false);
		}
		if (mMinutes == 1 && mType == TimeType::Minutes)
		{
			mAnimator->Play(L"TimerOne", false);
		}
		if (mMinutes == 0 && mType == TimeType::Minutes)
		{
			mAnimator->Play(L"TimerZero", false);
		}

		//-----------------------------------------------------
		if (mTenSeconds == 5 && mType == TimeType::TenSeconds)
		{
			mAnimator->Play(L"TimerFive", false);
		}
		if (mTenSeconds == 4 && mType == TimeType::TenSeconds)
		{
			mAnimator->Play(L"TimerFour", false);
		}
		if (mTenSeconds == 3 && mType == TimeType::TenSeconds)
		{
			mAnimator->Play(L"TimerThree", false);
		}
		if (mTenSeconds == 2 && mType == TimeType::TenSeconds)
		{
			mAnimator->Play(L"TimerTwo", false);
		}
		if (mTenSeconds == 1 && mType == TimeType::TenSeconds)
		{
			mAnimator->Play(L"TimerOne", false);
		}
		if (mTenSeconds == 0 && mType == TimeType::TenSeconds)
		{
			mAnimator->Play(L"TimerZero", false);
		}
		//-----------------------------------------------------
		if (mSeconds == 9 && mType == TimeType::Seconds)
		{
			mAnimator->Play(L"TimerNine", false);
		}
		if (mSeconds == 8 && mType == TimeType::Seconds)
		{
			mAnimator->Play(L"TimerEight", false);
		}
		if (mSeconds == 7 && mType == TimeType::Seconds)
		{
			mAnimator->Play(L"TimerSeven", false);
		}
		if (mSeconds == 6 && mType == TimeType::Seconds)
		{
			mAnimator->Play(L"TimerSix", false);
		}
		if (mSeconds == 5 && mType == TimeType::Seconds)
		{
			mAnimator->Play(L"TimerFive", false);
		}
		if (mSeconds == 4 && mType == TimeType::Seconds)
		{
			mAnimator->Play(L"TimerFour", false);
		}
		if (mSeconds == 3 && mType == TimeType::Seconds)
		{
			mAnimator->Play(L"TimerThree", false);
		}
		if (mSeconds == 2 && mType == TimeType::Seconds)
		{
			mAnimator->Play(L"TimerTwo", false);
		}
		if (mSeconds == 1 && mType == TimeType::Seconds)
		{
			mAnimator->Play(L"TimerOne", false);
		}
		if (mSeconds == 0 && mType == TimeType::Seconds)
		{
			mAnimator->Play(L"TimerZero", false);
		}


		SceneManager::SetmTime(mTime);

		GameObject::Update();
	}
	void Timer::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Timer::Release()
	{
	}
}