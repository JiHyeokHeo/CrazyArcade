#pragma once
#include "tyGameObject.h"
#include "tyImage.h"

namespace ty
{
	class Animator;
	class Monster : public GameObject
	{
	public:
		enum class eMonsterState
		{
			Idle,
			Damaged,
		};
		Monster();
		~Monster();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;


	private:
		Animator* mAnimator;
		eMonsterState mState;
	};
}
