#pragma once
#include "tyGameObject.h"
#include "tyImage.h"

namespace ty
{
	class Animator;
	class PirateBoss : public GameObject
	{
	public:
		enum class ePirateMonsterState
		{
			Idle,
			Attack,
			Left,
			Right,
			Up,
			Down,
			Hit,
			Bubble,
			Die,
		};
		PirateBoss();
		~PirateBoss();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

	private:
		void idle();
		void attack();
		void left();
		void right();
		void up();
		void down();
		void hit();
		void bubble();
		void die();
		void animationCtr();
		void bubbleCompleteEvent();
	private:
		Animator* mAnimator;
		ePirateMonsterState mState;
		float mTime;
		Vector2 mPos;
		Transform* tr;
		bool isColl;
		int Hp;
		float mInvincibility;
		bool isAttack;
		Vector2 ColLIdx;
		Vector2 ColUIdx;
		Vector2 ColDIdx;
		Vector2 ColRIdx;
		Vector2 midmPos;
	};
}


