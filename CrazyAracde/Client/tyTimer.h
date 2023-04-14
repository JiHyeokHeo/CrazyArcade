#pragma once
#include"tyScene.h"
#include "tyImage.h"

namespace ty
{
	class Timer : public GameObject
	{
	public:
		enum class TimeType
		{
			TenMinutes,
			Minutes,
			TenSeconds,
			Seconds,
			None,
		};

		Timer();
		~Timer();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;


		int GetPlayTime() { return mTime; }
		void SetTimeType(TimeType type) { mType = type; }
		void ResetIsTimeOn() { isTimeOn = false; }
	private:
		Image* mImage;
		int mTime;
		int mSeconds;
		int mMinutes;
		int mTenSeconds;
		Animator* mAnimator;
		TimeType mType;
		bool isTimeOn;
		float mRealTime;
	};
}

