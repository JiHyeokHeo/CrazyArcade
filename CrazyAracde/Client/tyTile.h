#pragma once
#include "tyGameObject.h"
#include "tyImage.h"

namespace ty
{

	class Tile : public GameObject
	{
	public:
		Tile();
		Tile(Vector2 pos);
		~Tile();

		void InitializeTile(Image* atlas, int index, Vector2 pos);
		void SetIndex(int index);
		void Clear();

		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		UINT Y() { return mY; }
		UINT X() { return mX; }
		UINT Index() { return mIndex; }
		
	private:
		Image* mAtlas;
		UINT mIndex;
		UINT mX;
		UINT mY;
		class Bazzi* mPlayer;
		Collider* mCollider;
		int colcnt = 0;
		bool isRCol;
		bool isLCol;
		bool isUCol;
		bool isDCol;
		float mTime;
		float movePos;
		bool isRMove;
		Transform* tr;
		Vector2 resultPos;
		bool tilesAreMoving;
		float rand_num;
	};
}

