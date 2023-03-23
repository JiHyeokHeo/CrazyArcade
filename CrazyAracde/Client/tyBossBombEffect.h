#pragma once
#include "tyGameObject.h"


namespace ty
{
	class Animator;
	class BossBombEffect : public GameObject
	{
	public:
		enum class eBossBombEffectState
		{
			Idle,
			Bombed,
		};
		BossBombEffect();
		~BossBombEffect();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		void idle();
		void bombed();
		void BombComplete();

	private:
		Animator* mAnimator;
		float mTime;
		eBossBombEffectState mState;
	};
}


