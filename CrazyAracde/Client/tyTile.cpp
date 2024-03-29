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
#include "tyTilePalatte.h"

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
		if (pos.y > 12 || pos.x > 14 || pos.y < 0 || pos.x < 0)
			return;
		SetName(L"Tile");
		SceneManager::GetMapIndex()[pos.y][pos.x] = 2;
		
		if (index >= 5)
		{
			mCollider = AddComponent<Collider>();
			mCollider -> SetPos(Vector2(30.0f + pos.x * TILE_SIZE_X, 60.0f + pos.y * TILE_SIZE_Y));
			mCollider ->SetSize(Vector2(60.0f, 60.0f));
		}
		if (index == 28)
		{
			SceneManager::GetMapIndex()[pos.y][pos.x] = 4;
		}
		mIndex = index;
		if (atlas == nullptr || index < 0)
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
		rand_num = dist(gen);
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
		mTime = 0;
		GameObject* obj = this;
		if (obj->GetState() == eState::Active)
		{
			mTime += Time::DeltaTime();
			tr = GetComponent<Transform>();
			Vector2 mPos = TileBomb::SetIndex(tr->GetPos());

			if (other->GetOwner()->GetName() == L"BombEffect" && mIndex >= 24 )
			{
				if (rand_num < 0.15f)
				{
					object::Instantiate<Ballon>(tr->GetPos() + Vector2(0.0f, -2.0f), eLayerType::Item);
				}
				else if (rand_num < 0.3f)
				{
					object::Instantiate<Potion>(tr->GetPos() + Vector2(0.0f, -2.0f), eLayerType::Item);
				}
				else if (rand_num < 0.5f)
				{
					object::Instantiate<Skate>(tr->GetPos() + Vector2(0.0f, -2.0f), eLayerType::Item);
				}
				else if (rand_num < 0.55f)
				{
					object::Instantiate<PotionMax>(tr->GetPos() + Vector2(0.0f, -2.0f), eLayerType::Item);
				}

				SceneManager::GetMapIndex()[mPos.y][mPos.x] = 0;
				object::Instantiate<Steam>(tr->GetPos(), eLayerType::Effect);
				object::Pause(this);
			}
			else if(other->GetOwner()->GetName() == L"BossBombEffect" && mIndex >= 24 )
			{
				if (rand_num < 0.15f)
				{
					object::Instantiate<Ballon>(tr->GetPos() + Vector2(0.0f, -2.0f), eLayerType::Item);
				}
				else if (rand_num < 0.3f)
				{
					object::Instantiate<Potion>(tr->GetPos() + Vector2(0.0f, -2.0f), eLayerType::Item);
				}
				else if (rand_num < 0.5f)
				{
					object::Instantiate<Skate>(tr->GetPos() + Vector2(0.0f, -2.0f), eLayerType::Item);
				}
				else if (rand_num < 0.55f)
				{
					object::Instantiate<PotionMax>(tr->GetPos() + Vector2(0.0f, -2.0f), eLayerType::Item);
				}

				SceneManager::GetMapIndex()[mPos.y][mPos.x] = 0;
				object::Instantiate<Steam>(tr->GetPos(), eLayerType::Effect);
				object::Pause(this);
			}
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

	void Tile::checkTime()
	{
		mTime += Time::DeltaTime();
	}

}
