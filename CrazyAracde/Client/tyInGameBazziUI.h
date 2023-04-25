#pragma once
#include"tyScene.h"

namespace ty
{
	class Image;
	class InGameBazziUI : public GameObject
	{
	public:
		InGameBazziUI();
		~InGameBazziUI();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;


	private:
		Image* mImage;
		InGameBazziUI* mBazziImage;
		bool isClicked;
	};
};



