#pragma once
#include "tyGameObject.h"

namespace ty
{
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

	};
}
