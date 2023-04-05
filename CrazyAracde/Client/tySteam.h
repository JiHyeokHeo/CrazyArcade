#pragma once
#include"tyScene.h"


namespace ty
{
	class Image;
	class Steam : public GameObject
	{
	public:
		Steam();
		~Steam();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		void MakeItem() {};
	private:
		Image* mImage;
		Animator* mAnimator;
	};
};
