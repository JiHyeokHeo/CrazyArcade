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
			Bomb,
		};

		BaseBomb();
		~BaseBomb();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;


	private:
		Animator* mAnimator;
	};
	
}
