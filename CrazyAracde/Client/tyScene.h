#pragma once
#include "tyEntity.h"
#include "tyLayer.h"

namespace ty
{
	class Scene : public Entity
	{
	public:
		Scene();
		virtual ~Scene();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		void AddGameObject(GameObject* obj, eLayerType layer);
	private:
		std::vector<Layer> mLayers; // 배경 많아봐야 10개 내외 * 메모리 아껴쓸려고 Scene은 많으니깐 포인터를 쓴거고?
	};
}