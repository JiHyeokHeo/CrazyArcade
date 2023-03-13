#pragma once
#include"tyScene.h"
#include"tyImage.h"

namespace ty
{
	class AlphaBlender : public GameObject
	{
	public:
		AlphaBlender();
		~AlphaBlender();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;


	private:
		Image* mImage;
		float mTime;
	};
}
