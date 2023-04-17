#pragma once
#include "tyGameObject.h"
#include "tyImage.h"

namespace ty
{
	class Animator;
	class SealBoss : public GameObject
	{
	public:
		enum class eSealMonsterState
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
		void attack();
		void bubble();
		void die();
		void animationCtr();
		void bubbleCompleteEvent();
	private:
		Animator* mAnimator;
		eSealMonsterState mState;
		float mTime;
		Vector2 mPos;
		bool isColl;
		int Hp;
		float mInvincibility;
		bool isAttack;
		Transform* tr;
		Vector2 ColLIdx;
		Vector2 ColUIdx;
		Vector2 ColDIdx;
		Vector2 ColRIdx;
		Vector2 midmPos;
		float TimeSpend;
	};
}


