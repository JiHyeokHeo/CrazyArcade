#pragma once
#include "tyGameObject.h"

namespace ty
{
	class Image;
	class BGInstance : public GameObject
	{
	public:
		BGInstance(eBGType type = eBGType::None);
		~BGInstance();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

	private:
		Image* mImage;
		eBGType mBGType;
	};

}
