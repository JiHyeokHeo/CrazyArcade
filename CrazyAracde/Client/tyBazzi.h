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
			Bubble,
			BubbleMove,
			Revive,
			Idle,
			NoMove,
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
		
		static std::vector<std::vector<int>>& GetMapIndex() { return mapIndex; }
		int& GetmClick() { return mClick; }
		int& GetmSpeed() { return mSpeed; }
		int& GetmWaterCourse() { return mWaterCourse; }
	private:
		void move();
		void shoot();
		void death();
		void idle();
		void bubble();
		void bubblemove();
		void revive();
		void nomove();
		void trapCompleteEvent();
		void dieCompeleteEvent();
		
	private:
		int mBomb;
		int mHP;
		int mWaterCourse;
		int mSpeed;
		int maxHP;
		int maxSpeed;
		int maxBomb;
		int maxWaterCourse;
		int mClick;
		eBazziState mState;
		Animator* mAnimator;
		float mTime;
		int BombCnt;
		bool isColl;
		bool isReady;
		bool isLPressed;
		bool isRPressed;
		bool isUPressed;
		bool isDPressed;
		int mRandomPosx;
		int mRandomPosy;
		static std::vector<std::vector<int>> mapIndex;
		Vector2 IdxPos;
		
	};
}
