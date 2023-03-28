#pragma once
#include "tyGameObject.h"


namespace ty
{
	class Animator;
	class BaseBomb : public GameObject
	{
	public:
		enum class eBombState
		{
			Idle,
			Bombed,
		};

		BaseBomb();
		~BaseBomb();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		
	private:
		void bombed();
		void idle();

	private:
		Vector2 BazziPos;;
		class BombEffect* mBombEffect;
		Animator* mAnimator;
		float mTime;
		int maxWaterWave;
		eBombState mState;
		bool isBomb;
	};
	
}
