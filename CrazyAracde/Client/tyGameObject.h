#pragma once
#include "tyEntity.h"
#include "tyComponent.h"

namespace ty
{
	class GameObject : public Entity
	{
	public:
		GameObject();
		virtual ~GameObject();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();


	protected:
		Vector2 mPos;

	private:
		std::vector<Component*> mComponents; // ��������Ʈ ������, �߷� , �ݶ��̴� ĳ����
	};
}


