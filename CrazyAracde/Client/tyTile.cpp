#include "tyTile.h"
#include "tyTransform.h"
#include "tyCamera.h"
#include "tyObject.h"
#include "tyCollider.h"
#include "tyBazzi.h"
#include "tyTileBomb.h"

namespace ty
{
	Tile::Tile()
		: mAtlas(nullptr)
		, mIndex(-1)
		, mX(-1)
		, mY(-1)
	{
	}
	Tile::Tile(Vector2 pos)
		: mAtlas(nullptr)
		, mIndex(-1)
		, mX(-1)
		, mY(-1)
	{
		
		GetComponent<Transform>()->SetPos(pos);
	}
	Tile::~Tile()
	{
	}
	void Tile::InitializeTile(Image* atlas, int index, Vector2 pos)
	{
		mIndex = index;
		if (atlas == nullptr || index < 0)
			return;
		SetName(L"Tile");
		Bazzi::GetMapIndex()[pos.y][pos.x] = 2;
		mAtlas = atlas;
		SetIndex(index);

	}
	void Tile::SetIndex(int index)
	{
		int maxCol = mAtlas->GetWidth() / TILE_SIZE_X;
		int maxRow = mAtlas->GetHeight() / TILE_SIZE_Y;

		mY = index / maxCol; // 이걸 활용해서 콜라이더 관련된걸 건드릴수 있다. 예를 들면 충돌쪽 또는 내 폭탄이랑도 관련되서 응용할수 있을꺼라고 유추해본다.
		mX = index % maxCol;
	}
	void Tile::Update()
	{
		
		GameObject::Update();
	}
	void Tile::Render(HDC hdc)
	{
		if (mAtlas == nullptr || mIndex < 0)
			return;

		Transform* tr = GetComponent<Transform>();

		Vector2 renderPos = tr->GetPos();

		TransparentBlt(hdc
			, renderPos.x, renderPos.y
			, TILE_SIZE_X, TILE_SIZE_Y
			, mAtlas->GetHdc()
			, TILE_SIZE_X * mX, TILE_SIZE_Y * mY
			, TILE_SIZE_X, TILE_SIZE_X
			, RGB(255, 0, 255));
		GameObject::Render(hdc);
	}
	void Tile::OnCollisionEnter(Collider* other)
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 mPos = TileBomb::SetIndex(tr->GetPos());
		if (other->GetOwner()->GetName() == L"BombEffect")
		{
			Bazzi::GetMapIndex()[mPos.y - 1][mPos.x] = 0;
			object::Destroy(this);
		}
	}
	void Tile::OnCollisionStay(Collider* other)
	{
	}
	void Tile::OnCollisionExit(Collider* other)
	{
	}
}