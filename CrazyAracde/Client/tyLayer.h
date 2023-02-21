#pragma once
#include "tyEntity.h"
#include "tyGameObject.h"


namespace ty
{
	class Layer : public Entity
	{
	public:
		Layer();
		virtual ~Layer();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		void AddGameObject(GameObject* gameObj);
	private:
		std::vector<GameObject*> mGameObjects;
	};
}

