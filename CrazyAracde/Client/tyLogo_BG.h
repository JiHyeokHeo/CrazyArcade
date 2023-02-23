#pragma once
#include"tyScene.h"

namespace ty
{
	class Image;
	class Logo_BG : public GameObject
	{
	public:
		Logo_BG();
		~Logo_BG();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;


	private:
		Image* mImage;
	};
};

