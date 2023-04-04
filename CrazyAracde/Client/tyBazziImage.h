#pragma once
#include"tyScene.h"

namespace ty
{
	class Image;
	class BazziImage : public GameObject
	{
	public:
		BazziImage();
		~BazziImage();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;


	private:
		Image* mImage;
	};
};


