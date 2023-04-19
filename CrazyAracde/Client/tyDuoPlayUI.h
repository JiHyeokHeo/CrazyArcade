#pragma once
#include"tyScene.h"

namespace ty
{
	class Image;
	class DuoPlayUI : public GameObject
	{
	public:
		DuoPlayUI();
		~DuoPlayUI();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;


	private:
		Image* mImage;
		DuoPlayUI* mBazziImage;
		bool isClicked;
	};
};


