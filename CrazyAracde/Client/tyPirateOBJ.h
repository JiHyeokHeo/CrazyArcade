#pragma once
#include "tyGameObject.h"

namespace ty
{
	class PirateOBJ : public GameObject
	{
	public:
		PirateOBJ();
		virtual ~PirateOBJ();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

		void SetPlayer(class Bazzi* player) { mPlayer = player; }

	private:
		class Collider* mCollider;
		class Image* mImage;
		class Bazzi* mPlayer;
		bool isGround;
		Vector2 mPlayerPos;
	};
}


