#pragma once
#include "tyGameObject.h"


namespace ty
{
	class Animator;
	class BombEffect : public GameObject
	{
	public:
		enum class eBombEffectState
		{
			Idle,
			Bombed,
		};
		BombEffect();
		~BombEffect();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;
		//void SetPlayer(class Bazzi* player) { mPlayer = player; }
	private:
		void idle();
		void bombed();

	private:
		Animator* mAnimator;
		float mTime;
		eBombEffectState mState;
		Vector2 BazziPos;
		Vector2 EffectPos;
		Vector2 BazziStartPos;
		bool isBlown;
	};
}

