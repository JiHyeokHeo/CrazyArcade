#pragma once
#include "tyComponent.h"
#include "tyAnimation.h"
#include "tyImage.h"

namespace ty
{
	class Animator : public Component
	{
	public:
		struct Event
		{
			void operator=(std::function<void()> func)
			{
				mEvent = std::move(func);
			}
			void operator()()
			{
				if (mEvent)
					mEvent();
			}
			//함수 포인터
			//void(*name)(int, int);
			std::function<void()> mEvent;
		};

		struct Events // 애니메이터마다 이걸 들고 있어야 할듯 싶다. 월요일날 이유 찾아보기
		{
			Event mStartEvent;
			Event mCompleteEvent;
			Event mEndEvent;


			//mStartEvent();
			//mStartEvent = test;
		};
		
		Animator();
		~Animator();

		virtual void Initialize() override;
		virtual void Update()override;
		virtual void Render(HDC hdc)override;
		virtual void Release()override;

		// 이건 하나의 이미지에 다 돌때
		void CreateAnimation(const std::wstring& name
			, Image* sheet
			, Vector2 leftTop
			, UINT coulmn, UINT row, UINT spriteLength
			, Vector2 offset, float duration);
		
		// 파일별로 돌릴때는 이 함수
		void CreateAnimations(const std::wstring& path, Vector2 offset, float duration);

		Animation* FindAnimation(const std::wstring& name);
		void Play(const std::wstring& name, bool loop);

		Events* FindEvents(const std::wstring& name);
		std::function<void()>& GetStartEvent(const std::wstring& name);
		std::function<void()>& GetCompleteEvent(const std::wstring& name);
		std::function<void()>& GetEndEvent(const std::wstring& name);

	private:
		std::map<std::wstring, Animation*> mAnimations;
		std::map<std::wstring, Events*> mEvents;
		Animation* mActiveAnimation;
		Image* mSpriteSheet; // 한 이미지에서 하나하나 장면들을 다 스프라이트라고 한다.
		bool mbLoop;
	};
}
