#pragma once
#include "tyGameObject.h"
#include "tyImage.h"

namespace ty
{
	class Animator;
	class Item : public GameObject
	{
	public:
		enum class ItemType
		{
			Ballon,
			Potion,
			PotionMax,
			Skate
		};
		Item();
		Item(ItemType type);
		~Item();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

	private:
		Animator* mAnimator;
		std::vector<Item*>items;
		ItemType mItemType;
	};
}



