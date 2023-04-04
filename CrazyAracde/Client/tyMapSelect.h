#pragma once
#include"tyScene.h"

namespace ty
{
	class Image;
	class MapSelect : public GameObject
	{
	public:
		MapSelect();
		~MapSelect();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;


	private:
		Image* mImage;
	};
};
