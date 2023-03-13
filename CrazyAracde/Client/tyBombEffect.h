#pragma once
#include "tyGameObject.h"


namespace ty
{
	class Animator;
	class BombEffect : public GameObject
	{
	public:
		BombEffect();
		~BombEffect();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;


	private:
		Animator* mAnimator;
		float mTime;
	};
}

