#pragma once
#include "tyEntity.h" 

//
namespace ty
{
	class Component : public Entity
	{
	public:
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

	private:
	};
}


