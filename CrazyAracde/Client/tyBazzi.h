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
		BaseBomb* mBomb;
	};
}
