#include "tyTile.h"
#include "tyTransform.h"
#include "tyCamera.h"
#include "tyObject.h"
#include "tyCollider.h"
#include "tyBazzi.h"
#include "tyTileBomb.h"
#include "tyItem.h"
#include "tyPlayScene.h"
#include "tyBallon.h"
#include "tyTime.h"
#include "tyinput.h"

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
		if (index == 4)
		{
			mCollider = AddComponent<Collider>();
			mCollider -> SetPos(Vector2(30.0f + pos.x * TILE_SIZE_X, 60.0f + pos.y * TILE_SIZE_Y));
			mCollider ->SetSize(Vector2(58.0f, 58.0f));

		}
		mIndex = index;
		if (atlas == nullptr || index < 0)
			return;
		SetName(L"Tile");
		if (pos.y > 12 || pos.x > 14 || pos.y < 0 || pos.x < 0)
			return;
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
			object::Instantiate<Ballon>(tr->GetPos(), eLayerType::Item);
			Bazzi::GetMapIndex()[mPos.y][mPos.x] = 0;
			object::Destroy(this);
		}

		if (Input::GetKey(eKeyCode::RIGHT))
		{
			isRCol =true;
		}
		if (Input::GetKey(eKeyCode::LEFT))
		{
			isLCol = true;
		}
		if (Input::GetKey(eKeyCode::UP))
		{
			isUCol = true;
		}
		if (Input::GetKey(eKeyCode::DOWN))
		{
			isDCol = true;
		}
	}
	void Tile::OnCollisionStay(Collider* other)
	{
		mPlayer = PlayScene::GetBazzi();
		int mSpeed = mPlayer->GetmSpeed();
		Transform* mPlayerPos = mPlayer->GetComponent<Transform>();
		Vector2 mGameobjPos = mPlayerPos->GetPos();
		Vector2 mGameobjColPos = mPlayer->GetComponent<Collider>()->GetPos();
		Vector2 mColPos = mCollider->GetPos();
		Vector2 mPos = TileBomb::SetIndex(mGameobjPos);
		if (mGameobjColPos.y > mColPos.y && other->GetOwner()->GetName() == L"Bazzi" /*&& Bazzi::GetMapIndex()[mPos.y - 1][mPos.x] == 2 */
			&& isRCol == false && isLCol == false && isUCol == true && isDCol == false)
		{
			mGameobjPos.y += 50 * mSpeed * Time::DeltaTime();
			mPlayerPos->SetPos(mGameobjPos);
		}
		if (mGameobjColPos.y < mColPos.y && other->GetOwner()->GetName() == L"Bazzi"
			&& isRCol == false && isLCol == false && isUCol == false && isDCol == true/*&& Bazzi::GetMapIndex()[mPos.y + 1][mPos.x] == 2*/)
		{
			mGameobjPos.y -= 50.0f * mSpeed * Time::DeltaTime();
			mPlayerPos->SetPos(mGameobjPos);
		}
		if (mGameobjColPos.x > mColPos.x && other->GetOwner()->GetName() == L"Bazzi"
			&& isRCol == false && isLCol == true && isUCol == false && isDCol == false/*&& Bazzi::GetMapIndex()[mPos.y][mPos.x - 1] == 2*/)
		{
			mGameobjPos.x += 50.0f * mSpeed * Time::DeltaTime();
			mPlayerPos->SetPos(mGameobjPos);
		}
		if (mGameobjColPos.x < mColPos.x && other->GetOwner()->GetName() == L"Bazzi" 
			&& isRCol == true && isLCol == false && isUCol == false && isDCol == false/*&& Bazzi::GetMapIndex()[mPos.y][mPos.x + 1] == 2*/)
		{
			mGameobjPos.x -= 50.0f * mSpeed * Time::DeltaTime();
			mPlayerPos->SetPos(mGameobjPos);
		}

		//if (other->GetOwner()->GetName() == L"Bazzi" )
		//{
		//	Bazzi::GetMapIndex()[mPos.y][mPos.x] = 0;
		//	object::Destroy(this);
		//}
	}
	void Tile::OnCollisionExit(Collider* other)
	{
		isRCol = false;
		isLCol = false;
		isUCol = false;
		isDCol = false;
	}
}