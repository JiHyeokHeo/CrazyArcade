#pragma once
#include"tyScene.h"
#include "tyImage.h"

namespace ty
{
	class IceTile : public GameObject
	{
	public:
		IceTile();
		~IceTile();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;


	private:
		Image* mImage;
	};
}
\

