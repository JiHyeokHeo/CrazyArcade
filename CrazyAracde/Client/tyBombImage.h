#pragma once
#include "tyGameObject.h"


namespace ty
{
	class Animator;
	class BombImage : public GameObject
	{
	public:
		BombImage();
		~BombImage();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;


		void SetBomb(class BaseBomb* bomb) { mBaseBomb = bomb; }
		void SetTime(float time) { mTime = time; }
	private:
		void idle();
		void bombed();

	private:
		Animator* mAnimator;
		float mTime;
		Vector2 mBaseBombPos;
		Vector2 EffectPos;
		class BaseBomb* mBaseBomb;
		bool isBlown;
		class Transform* tr;
		float mMovePos;
		bool isReached;
		float mDifference;
		Vector2 StartPos;
	};
}


