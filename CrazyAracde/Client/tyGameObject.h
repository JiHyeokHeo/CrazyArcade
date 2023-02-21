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
		std::vector<Component*> mComponents; // 스프라이트 렌더러, 중력 , 콜라이더 캐릭터
	};
}


