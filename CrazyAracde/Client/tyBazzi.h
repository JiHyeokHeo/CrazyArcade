#pragma once
#include "tyGameObject.h"


namespace ty
{
	class Image;
	class Bazzi : public GameObject
	{
	public:
		Bazzi();
		~Bazzi();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;


	private:
		Image* mImage;
		float mTime;
		int mIdx;
	};
}
