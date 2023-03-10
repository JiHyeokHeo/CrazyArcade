#pragma once
#include "tyGameObject.h"
#include "tyImage.h"

namespace ty
{
	class Animator;
	class Monster : public GameObject
	{
	public:
		enum class eMonsterState
		{
			Idle,
			Left,
			Right,
			Up,
			Down,
		};
		Monster();
		~Monster();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

	private:
		void idle();
		void left();
		void right();
		void up();
		void down();

		void animationCtr();

	private:
		Animator* mAnimator;
		eMonsterState mState;
		float mTime;
		Vector2 mPos;
	};
}
