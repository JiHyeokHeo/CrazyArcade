#pragma once
#include"tyScene.h"

namespace ty
{
	class Image;
	class ForestSelect : public GameObject
	{
	public:
		ForestSelect();
		~ForestSelect();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;


	private:
		Image* mImage;
	};
};
