#pragma once
#include "tyGameObject.h"
#include "tyImage.h"

namespace ty
{
	class Animator;
	class ForestMonster : public GameObject
	{
	public:
		enum class eMonsterState
		{
			Idle,
			Left,
			Right,
			Up,
			Down,
			Die,
		};
		ForestMonster();
		~ForestMonster();

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
		void die();
		void animationCtr();

	private:
		Animator* mAnimator;
		eMonsterState mState;
		float mTime;
		Vector2 mPos;
		Collider* collider;
		int colcnt;
		bool isStateChosen;
		Transform* tr;
		Vector2 ColRIdx;
		Vector2 ColLIdx;
		Vector2 ColUIdx;
		Vector2 ColDIdx;
		float mPlayTime;
	};
}


