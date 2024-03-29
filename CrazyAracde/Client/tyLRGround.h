#pragma once
#include "tyGameObject.h"

namespace ty
{
	class LRGround : public GameObject
	{
	public:
		LRGround();
		virtual ~LRGround();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);


	private:
		class Collider* mCollider;
		class Image* mImage;
		class Bazzi* mBazzi;
		class Dao* mDao;
		bool isGround;
		Vector2 mPlayerPos;
	};
}

