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
#include "tySkate.h"
#include "tyPotionMax.h"
#include "tyPotion.h"
#include "tySteam.h"

namespace ty
{
	Tile::Tile()
		: mAtlas(nullptr)
		, mIndex(-1)
		, mX(-1)
		, mY(-1)
		, mTime(0.0f)
		, movePos(30.0f)
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
		SetName(L"Tile");
		SceneManager::GetBazzi()->GetMapIndex()[pos.y][pos.x] = 2;
		if (index >= 5)
		{
			mCollider = AddComponent<Collider>();
			mCollider -> SetPos(Vector2(30.0f + pos.x * TILE_SIZE_X, 60.0f + pos.y * TILE_SIZE_Y));
			mCollider ->SetSize(Vector2(60.0f, 60.0f));
		}
		if (index == 28)
		{
			SceneManager::GetBazzi()->GetMapIndex()[pos.y][pos.x] = 4;
		}
		mIndex = index;
		if (atlas == nullptr || index < 0)
			return;
		if (pos.y > 12 || pos.x > 14 || pos.y < 0 || pos.x < 0)
			return;
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
		/*mBazzi = SceneManager::GetBazzi();
		Vector2 mDownIdx = mBazzi->GetDownIdx();
		Vector2 mUpdx = mBazzi->GetUpIdx();
		Vector2 mRightdx = mBazzi->GetRightIdx();
		Vector2 mLeftIdx = mBazzi->GetLeftIdx();


		if (ColRIdx.x > 14)
			ColRIdx.x = 14;
		if (ColLIdx.x > 14)
			ColLIdx.x = 14;
		if (ColUIdx.x > 14)
			ColUIdx.x = 14;
		if (ColDIdx.x > 14)
			ColDIdx.x = 14;

		if (ColRIdx.y > 12)
			ColRIdx.y = 12;
		if (ColLIdx.y > 12)
			ColLIdx.y = 12;
		if (ColUIdx.y > 12)
			ColUIdx.y = 12;
		if (ColDIdx.y > 12)
			ColDIdx.y = 12;


		if (mDownIdx.x > 14)
			mDownIdx.x = 14;
		if (mUpdx.x > 14)
			mUpdx.x = 14;
		if (mRightdx.x > 14)
			mRightdx.x = 14;
		if (mLeftIdx.x > 14)
			mLeftIdx.x = 14;

		if (mDownIdx.y > 12)
			mDownIdx.y = 12;
		if (mUpdx.y > 12)
			mUpdx.y = 12;
		if (mRightdx.y > 12)
			mRightdx.y = 12;
		if (mLeftIdx.y > 12)
			mLeftIdx.y = 12;

		Vector2 StartIdx;
		if (mBazzi->GetMapIndex()[mDownIdx.y][mDownIdx.x] == 1
			&& mBazzi->GetIsPushPossible() == true && Input::GetKey(eKeyCode::DOWN) && mBazzi->GetIsBirdOn() == false)
		{
			mPushTime += Time::DeltaTime();
			if (mPushTime >= 0.1f)
			{
				pushcnt++;
				mPushTime = 0;
				mdown = true;
			}
		}
		if (mBazzi->GetMapIndex()[mUpdx.y][mUpdx.x] == 1
			&& mBazzi->GetIsPushPossible() == true && Input::GetKey(eKeyCode::UP) && mBazzi->GetIsBirdOn() == false)
		{
			mPushTime += Time::DeltaTime();
			if (mPushTime >= 0.1f)
			{
				pushcnt++;
				mPushTime = 0;
				mup = true;
			}
		}
		if (mBazzi->GetMapIndex()[mRightdx.y][mRightdx.x] == 1
			&& mBazzi->GetIsPushPossible() == true && Input::GetKey(eKeyCode::RIGHT) && mBazzi->GetIsBirdOn() == false)
		{
			mPushTime += Time::DeltaTime();
			if (mPushTime >= 0.1f)
			{
				pushcnt++;
				mPushTime = 0;
				mright = true;
			}
		}
		if (mBazzi->GetMapIndex()[mLeftIdx.y][mLeftIdx.x] == 1
			&& mBazzi->GetIsPushPossible() == true && Input::GetKey(eKeyCode::LEFT) && mBazzi->GetIsBirdOn() == false)
		{
			mPushTime += Time::DeltaTime();
			if (mPushTime >= 0.1f)
			{
				pushcnt++;
				mPushTime = 0;
				mleft = true;
			}
		}

		if (
			mBazzi->GetIsPushPossible() == true
			&& mleft == true && mright == false && mup == false && mdown == false
			&& pushcnt == 1 && hasBeenPushed == false)
		{
			mBazzi->GetMapIndex()[ColMidIdx.y][ColMidIdx.x] = 0;
			left();
		}
		if (
			mBazzi->GetIsPushPossible() == true
			&& mright == true && mleft == false && mup == false && mdown == false
			&& pushcnt == 1 && hasBeenPushed == false)
		{
			mBazzi->GetMapIndex()[ColMidIdx.y][ColMidIdx.x] = 0;
			right();
		}
		if (
			mBazzi->GetIsPushPossible() == true
			&& mup == true && mright == false && mleft == false && mdown == false
			&& pushcnt == 1 && hasBeenPushed == false)
		{
			mBazzi->GetMapIndex()[ColMidIdx.y][ColMidIdx.x] = 0;
			up();
		}
		if (
			mBazzi->GetIsPushPossible() == true
			&& mup == false && mright == false && mleft == false && mdown == true
			&& pushcnt == 1 && hasBeenPushed == false)
		{
			mBazzi->GetMapIndex()[ColMidIdx.y][ColMidIdx.x] = 0;
			down();
		}*/
		rand_num = (float)rand() / RAND_MAX; // 0 또는 1
		GameObject::Update();
	}
	void Tile::Render(HDC hdc)
	{
		if (mAtlas == nullptr || mIndex < 0)
			return;
		tr = GetComponent<Transform>();
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
		mTime += Time::DeltaTime();
		tr = GetComponent<Transform>();
		Vector2 mPos = TileBomb::SetIndex(tr->GetPos());
		if (other->GetOwner()->GetName() == L"BombEffect" && mIndex >= 24)
		{
			if (rand_num < 0.15f)
			{
				object::Instantiate<Ballon>(tr->GetPos() + Vector2(0.0f, -10.0f), eLayerType::Item);
			}
			else if (rand_num < 0.3f)
			{
				object::Instantiate<Potion>(tr->GetPos() + Vector2(0.0f, -10.0f), eLayerType::Item);
			}
			else if (rand_num < 0.5f)
			{
				object::Instantiate<Skate>(tr->GetPos() + Vector2(0.0f, -10.0f), eLayerType::Item);
			}
			else if (rand_num < 0.55f)
			{
				object::Instantiate<PotionMax>(tr->GetPos() + Vector2(0.0f, -10.0f), eLayerType::Item);
			}
		
			SceneManager::GetBazzi()->GetMapIndex()[mPos.y][mPos.x] = 0;
			object::Instantiate<Steam>(tr->GetPos(), eLayerType::Effect);
			object::Pause(this);
		}
	}
	void Tile::OnCollisionStay(Collider* other)
	{
		
	}
	void Tile::OnCollisionExit(Collider* other)
	{
		isRCol = false;
		isLCol = false;
		isUCol = false;
		isDCol = false;
	}

	
}
