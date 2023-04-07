#pragma once
#include "tyItem.h"

namespace ty
{
	class Devil : public Item
	{
	public:
		Devil();
		Devil(ItemType type);
		~Devil();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

	private:
		Animator* mAnimator;
		int isHit;
	};

}