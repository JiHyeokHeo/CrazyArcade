#pragma once
#include "tyGameObject.h"
#include "tyImage.h"
#include "tyBaseBomb.h"

namespace ty
{
	class Animator;
	class Bazzi : public GameObject
	{
	public:
		enum class eBazziState
		{
			Move,
			Shoot,
			Death,
			Idle
		};

		Bazzi();
		~Bazzi();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;
		
		int GetBombCnt() { return maxBomb; }
		Vector2 GetBazziPos() { return BazziPos; }
	private:
		void move();
		void shoot();
		void death();
		void idle();

		void idleCompleteEvent();
	private:
		eBazziState mState;
		Animator* mAnimator;
		float mTime;
		int maxBomb;
		int BombCnt;
		bool isColl;
		int maxHP;
		Vector2 BazziPos;
		bool isLPressed;
		bool isRPressed;
		bool isUPressed;
		bool isDPressed;
	};
}
