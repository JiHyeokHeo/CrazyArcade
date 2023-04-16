#pragma once
#include"tyScene.h"
#include "tyImage.h"

namespace ty
{
	class PirateNormalTile : public GameObject
	{
	public:
		PirateNormalTile();
		~PirateNormalTile();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;


	private:
		Image* mImage;
	};
}
\


