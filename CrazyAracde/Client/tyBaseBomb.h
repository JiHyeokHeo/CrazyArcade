#pragma once
#include "tyGameObject.h"


namespace ty
{

	class BaseBomb : public GameObject
	{
	public:
		BaseBomb();
		~BaseBomb();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;


	private:
	};
	
}
