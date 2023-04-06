#pragma once
#include "tyGameObject.h"


namespace ty
{
	class BombEffect;
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
		void checked();
		void up();
		void right();
		void down();
		void left();
	private:
		std::vector<BombEffect*> mBombEffect;
		Collider* collider;
		Transform* tr;
		class Bazzi* mBazzi;
		Vector2 BazziPos;;
		Vector2 mBasePos;
		Vector2 realPos;
		Animator* mAnimator;
		int maxWaterWave;
		float mTime;
		eBombState mState;
		bool isBomb;
		bool isShot;
		bool isPush;
		float mPushTime;
		
		bool mleft;
		bool mright;
		bool mup;
		bool mdown;
		int pushcnt;
	};
	
	
}
