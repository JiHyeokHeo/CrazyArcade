#pragma once
#include "tyGameObject.h"
#include "tyImage.h"
#include "tyBaseBomb.h"

namespace ty
{
	class Animator;
	class Dao : public GameObject
	{
	public:
		enum class eDaoState
		{
			Move,
			Shoot,
			Death,
			Bubble,
			BubbleMove,
			Revive,
			Idle,
			NoMove,
			Reset,
			BirdOn,
		};

		Dao();
		~Dao();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		//static std::vector<std::vector<int>>& GetMapIndex() { return mapIndex; }
		int& GetmClick() { return mClick; }
		float& GetmSpeed() { return mSpeed; }
		int& GetmWaterCourse() { return mWaterCourse; }
		INT& GetmBomb() { return mBomb; }
		int GetMaxWaterCourse() { return maxWaterCourse; }
		float GetMaxSpeed() { return maxSpeed; }
		int GetPlayerSpeed() { return mPlayerSpeed; }
		int GetPlayerHP() { return mHP; }
		Vector2 GetUpIdx() { return mUpIdx; }
		Vector2 GetRightIdx() { return mRightIdx; }
		Vector2 GetDownIdx() { return mDownIdx; }
		Vector2 GetLeftIdx() { return mLeftIdx; }
		bool GetIsPushPossible() { return isPushPossible; }
		void SetIsPushPossible(bool isPossible) { isPushPossible = isPossible; }
		bool& GetIsBirdOn() { return isBirdOn; }
		void Reset();

		bool GetIsShieldOn() { return isShieldOn; }
		eItemType GetItemState() { return mItemState; }
		void SetItemState(eItemType type) { mItemState = type; }
		void SeteBazziState(eDaoState type) { mState = type; }
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
		void dieCompleteEvent();
		void liveCompleteEvent();
		void hitComPleteEvent();
		void birdmove();
		void checkInVTime();
	private:
		int mBomb;
		int mHP;
		int mWaterCourse;
		float mSpeed;
		int maxHP;
		float maxSpeed;
		int maxBomb;
		int maxWaterCourse;
		int BombCnt;
		int maxItemCnt;
		int mItemCnt;

		int mClick;
		eDaoState mState;
		eItemType mItemState;
		Animator* mAnimator;
		float mTime;


		bool isColl;
		bool isReady;
		bool isLPressed;
		bool isRPressed;
		bool isUPressed;
		bool isDPressed;
		bool isPushPossible;
		bool isBirdOn;
		bool isShieldOn;

		int mRandomPosx;
		int mRandomPosy;
		float mInvincibility;

		//static std::vector<std::vector<int>> mapIndex;
		Vector2 IdxPos;
		int mPlayerSpeed;
		Collider* collider;
		Transform* tr;
		Vector2 mPos;

		Vector2 mUpIdx;
		Vector2 mRightIdx;
		Vector2 mDownIdx;
		Vector2 mLeftIdx;

	};
}


