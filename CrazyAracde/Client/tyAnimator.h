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
			//�Լ� ������
			//void(*name)(int, int);
			std::function<void()> mEvent;
		};

		struct Events // �ִϸ����͸��� �̰� ��� �־�� �ҵ� �ʹ�. �����ϳ� ���� ã�ƺ���
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

		// �̰� �ϳ��� �̹����� �� ����
		void CreateAnimation(const std::wstring& name
			, Image* sheet
			, Vector2 leftTop
			, UINT coulmn, UINT row, UINT spriteLength
			, Vector2 offset, float duration);
		
		// ���Ϻ��� �������� �� �Լ�
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
		Image* mSpriteSheet; // �� �̹������� �ϳ��ϳ� ������ �� ��������Ʈ��� �Ѵ�.
		bool mbLoop;
	};
}
