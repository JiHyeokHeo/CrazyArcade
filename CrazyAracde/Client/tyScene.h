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
		std::vector<Layer> mLayers; // ��� ���ƺ��� 10�� ���� * �޸� �Ʋ������� Scene�� �����ϱ� �����͸� ���Ű�?
	};
}