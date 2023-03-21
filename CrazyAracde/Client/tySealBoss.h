#pragma once
#include "tyGameObject.h"
#include "tyImage.h"

namespace ty
{
	class Animator;
	class SealBoss : public GameObject
	{
	public:
		enum class eSealBossState
		{
			Idle,
			Left,
			Right,
			Up,
			Down,
			Hit,
			Die,
		};
		SealBoss();
		~SealBoss();

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
		void hit();
		void die();
		void animationCtr();

	private:
		Animator* mmAnimator;
		eSealBossState mState;
		float mTime;
		Vector2 mPos;
		bool isColl;
		int Hp;
		float mInvincibility;
	};
}


