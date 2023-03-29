#pragma once
#include "tyGameObject.h"
#include "tyImage.h"
#include "tyBaseBomb.h"

namespace ty
{
	class Animator;
	class Shadow : public GameObject
	{
	public:
		Shadow();
		~Shadow();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;



	private:

	};
}

