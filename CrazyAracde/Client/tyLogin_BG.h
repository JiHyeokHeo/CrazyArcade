#pragma once
#include"tyScene.h"
#include "tyImage.h"

namespace ty
{
	class Login_BG : public GameObject
	{
	public:
		Login_BG();
		~Login_BG();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;


	private:
		Image* mImage;
	};
}

