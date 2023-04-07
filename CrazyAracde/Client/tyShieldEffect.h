#pragma once
#include"tyScene.h"


namespace ty
{
	class Image;
	class ShieldEffect : public GameObject
	{
	public:
		ShieldEffect();
		~ShieldEffect();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		void MakeItem() {};
	private:
		Image* mImage;
		class Animator* mAnimator;
		float mTime;
		Transform* tr;
	};
};
