#include "tyBaseBomb.h"
#include "tyTransform.h"
#include "tyTime.h"
#include "tyCollider.h"
#include "tyGameObject.h"
#include "tyAnimator.h"
#include "tyObject.h"
#include "tyBombEffect.h"
#include "tyinput.h"
#include "tyPlayScene.h"
#include "tyBazzi.h"
#include "tyTileBomb.h"

namespace ty
{
	
	BaseBomb::BaseBomb()
		: mTime(0.0f)
		, maxWaterWave(7)
		, pushcnt(0)
	{	
	
	}
	BaseBomb::~BaseBomb()
	{

	}
	void BaseBomb::Initialize()
	{
		SetName(L"BaseBomb");
		
    	Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector2(1.5f, 1.5f));
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Bomb\\Idle", Vector2::Zero, 0.16f);
		mAnimator->CreateAnimations(L"..\\Resources\\Bomb\\None", Vector2::Zero, 0.16f);
		mAnimator->Play(L"BombIdle", true);
		collider = AddComponent<Collider>();
		collider->SetCenter(Vector2::Zero);
		collider->SetSize(Vector2(58.0f, 58.0f));

		mBazzi = SceneManager::GetBazzi();

		mState = eBombState::Idle;
		GameObject::Initialize();
	}

	void BaseBomb::Update()
	{

		if (isBomb == true)
		{
			object::Destroy(this);
		}
		Transform* mPlayer = SceneManager::GetBazzi()->GetComponent<Transform>();
		Vector2 mPlayerPos = mPlayer->GetPos();
		Vector2 IDX = TileBomb::SetIndex(mPlayerPos);

		tr = GetComponent<Transform>();
		mBasePos = tr->GetPos();
		Vector2 ColPos = collider->GetPos();
		Vector2 ColMidPos = ColPos + Vector2(TILE_SIZE_X / 2, TILE_SIZE_Y / 2);
		Vector2 ColMidIdx = TileBomb::SetColIndex(ColMidPos);
		Vector2 ColRIdx = TileBomb::SetColIndex(ColMidPos + Vector2(32.0f, 0.0f));
		Vector2 ColLIdx = TileBomb::SetColIndex(ColMidPos + Vector2(-32.0f, 0.0f));
		Vector2 ColUIdx = TileBomb::SetColIndex(ColMidPos + Vector2(0.0f, -32.0f));
		Vector2 ColDIdx = TileBomb::SetColIndex(ColMidPos + Vector2(0.0f, +32.0f));
		//Vector2 mPos = TileBomb::SetIndex(tr->GetPos());

		if (Bazzi::GetMapIndex()[IDX.y][IDX.x] != Bazzi::GetMapIndex()[ColMidIdx.y][ColMidIdx.x])
		{
			Bazzi::GetMapIndex()[ColMidIdx.y][ColMidIdx.x] = 1;
		}

	


		mBazzi = SceneManager::GetBazzi();
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

		if (mBazzi->GetMapIndex()[mDownIdx.y][mDownIdx.x] == 1 
			&& mBazzi->GetIsPushPossible() == true && Input::GetKey(eKeyCode::DOWN))
		{
			mPushTime += Time::DeltaTime();
			if (mPushTime >= 0.3f)
			{
				pushcnt++;
				mdown = true;
			}
		}
		if (mBazzi->GetMapIndex()[mUpdx.y][mUpdx.x] == 1
			&& mBazzi->GetIsPushPossible() == true && Input::GetKey(eKeyCode::UP))
		{
			mPushTime += Time::DeltaTime();
			if (mPushTime >= 0.3f)
			{
				pushcnt++;
				mup = true;
			}
		}
		if (mBazzi->GetMapIndex()[mRightdx.y][mRightdx.x] == 1
			&& mBazzi->GetIsPushPossible() == true && Input::GetKey(eKeyCode::RIGHT))
		{
			mPushTime += Time::DeltaTime();
			if (mPushTime >= 0.3f)
			{
				pushcnt++;
				mright = true;
			}
		}
		if (mBazzi->GetMapIndex()[mLeftIdx.y][mLeftIdx.x] == 1
			&& mBazzi->GetIsPushPossible() == true && Input::GetKey(eKeyCode::LEFT))
		{
			mPushTime += Time::DeltaTime();
			if (mPushTime >= 0.3f)
			{
				pushcnt++;
				mleft = true;
			}
		}

		if (
			mBazzi->GetIsPushPossible() == true && mPushTime >= 0.3f && mleft == true && pushcnt ==1)
		{
			mBazzi->GetMapIndex()[ColMidIdx.y][ColMidIdx.x] = 0;
			left();
		}

		if (mBazzi->GetMapIndex()[ColRIdx.y][ColRIdx.x] != 2
			&& mBazzi->GetIsPushPossible() == true && mPushTime >= 0.3f && mright == true && pushcnt == 1)
		{
			mBazzi->GetMapIndex()[ColMidIdx.y][ColMidIdx.x] = 0;
			right();
		}

		if (mBazzi->GetMapIndex()[ColUIdx.y][ColUIdx.x] != 2
			&& mBazzi->GetIsPushPossible() == true && mPushTime >= 0.3f && mup == true && pushcnt == 1)
		{
			mBazzi->GetMapIndex()[ColMidIdx.y][ColMidIdx.x] = 0;
			up();
		}

		if (mBazzi->GetMapIndex()[ColDIdx.y][ColDIdx.x] != 2
			&& mBazzi->GetIsPushPossible() == true &&  mPushTime >= 0.3f && mdown == true && pushcnt == 1)
		{
			mBazzi->GetMapIndex()[ColMidIdx.y][ColMidIdx.x] = 0;
			down();
		}
		
		
		mTime += Time::DeltaTime();
			

		if (mTime >= 3.0f)
		{
			if (isShot == false)
			{
				isShot = true;
				Vector2 realPos = tr->GetPos();
				Vector2 mPos = TileBomb::SetIndex(tr->GetPos());
				Bazzi::GetMapIndex()[mPos.y][mPos.x] = 1;

				Vector2 BombPos = tr->GetPos();
				Vector2 BombIdx = TileBomb::SetIndex(BombPos);

				int WaterStatus = SceneManager::GetBazzi()->GetmWaterCourse();
				if (BombIdx.x < 15 || BombIdx.y < 13)
				{
					for (int i = 1; i < WaterStatus; i++)
					{
						if (BombIdx.x + i >= 15)
							break;
						mBombEffect.push_back(object::Instantiate<BombEffect>(BombPos + Vector2((float)(i * 60.0f), 0.0f), eLayerType::BombEffect)); // 우측
						if (Bazzi::GetMapIndex()[BombIdx.y][BombIdx.x + i] == 2)
							break;
					}
					for (int i = 1; i < WaterStatus; i++)
					{
						if (BombIdx.y + i >= 13)
							break;
						mBombEffect.push_back(object::Instantiate<BombEffect>(BombPos + Vector2(0.0f, float(i * 60.0f)), eLayerType::BombEffect)); // 하단
						if (Bazzi::GetMapIndex()[BombIdx.y + i][BombIdx.x] == 2)
							break;
					}
					for (int i = 1; i < WaterStatus; i++)
					{
						if (BombIdx.x - i <= -1)
							break;
						mBombEffect.push_back(object::Instantiate<BombEffect>(BombPos - Vector2((float)(i * 60.0f), 0.0f), eLayerType::BombEffect)); // 좌측
						if (Bazzi::GetMapIndex()[BombIdx.y][BombIdx.x - i] == 2)
							break;
					}
					for (int i = 1; i < WaterStatus; i++)
					{
						if (BombIdx.y - i <= -1)
							break;
						mBombEffect.push_back(object::Instantiate<BombEffect>(BombPos - Vector2(0.0f, (float)(i * 60.0f)), eLayerType::BombEffect)); // 상단
						if (Bazzi::GetMapIndex()[BombIdx.y - i][BombIdx.x] == 2)
							break;
					}
					mBombEffect.push_back(object::Instantiate<BombEffect>(BombPos, eLayerType::BombEffect));
				}
				for (int i = 0; i < mBombEffect.size(); i++)
				{
					mBombEffect[i]->SetBomb(this);
				}
			}

			mTime = 0;
			Vector2 mPos = TileBomb::SetIndex(tr->GetPos());
			Bazzi::GetMapIndex()[mPos.y][mPos.x] = 0;
			int Click = SceneManager::GetBazzi()->GetmClick()--;

			isBomb = true;
		}

		GameObject::Update();
    }
	
	void BaseBomb::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void BaseBomb::Release()
	{
		GameObject::Release();
	}
	void BaseBomb::OnCollisionEnter(Collider* other)
	{
		if (other->GetOwner()->GetName() == L"BombEffect")
		{
			for (int i = 0; i < mBombEffect.size(); i++)
			{
				mBombEffect[i]->SetTime(3.0f);
			}
			mTime = 3.0f;
		}
	}
	void BaseBomb::OnCollisionStay(Collider* other)
	{
	}
	void BaseBomb::OnCollisionExit(Collider* other)
	{
	}

	void BaseBomb::bombed()
	{
		//object::Destroy(this);
	}

	void BaseBomb::idle()
	{

		//if (mTime >= 3.0f)
		//{
		//	if (isShot == false)
		//	{
		//		isShot = true;
		//		Transform* tr = GetComponent<Transform>();
		//		Vector2 realPos = tr->GetPos();
		//		Vector2 mPos = TileBomb::SetIndex(tr->GetPos());
		//		Bazzi::GetMapIndex()[mPos.y][mPos.x] = 1;

		//		Vector2 BombPos = tr->GetPos();
		//		Vector2 BombIdx = TileBomb::SetIndex(BombPos);

		//		int WaterStatus = SceneManager::GetBazzi()->GetmWaterCourse();
		//		if (BombIdx.x < 15 || BombIdx.y < 13)
		//		{
		//			for (int i = 1; i < WaterStatus; i++)
		//			{
		//				if (BombIdx.x + i >= 15)
		//					break;
		//				mBombEffect.push_back(object::Instantiate<BombEffect>(BombPos + Vector2((float)(i * 60.0f), 0.0f), eLayerType::BombEffect)); // 우측
		//				if (Bazzi::GetMapIndex()[BombIdx.y][BombIdx.x + i] == 2)
		//					break;
		//			}
		//			for (int i = 1; i < WaterStatus; i++)
		//			{
		//				if (BombIdx.y + i >= 13)
		//					break;
		//				mBombEffect.push_back(object::Instantiate<BombEffect>(BombPos + Vector2(0.0f, float(i * 60.0f)), eLayerType::BombEffect)); // 하단
		//				if (Bazzi::GetMapIndex()[BombIdx.y + i][BombIdx.x] == 2)
		//					break;
		//			}
		//			for (int i = 1; i < WaterStatus; i++)
		//			{
		//				if (BombIdx.x - i <= -1)
		//					break;
		//				mBombEffect.push_back(object::Instantiate<BombEffect>(BombPos - Vector2((float)(i * 60.0f), 0.0f), eLayerType::BombEffect)); // 좌측
		//				if (Bazzi::GetMapIndex()[BombIdx.y][BombIdx.x - i] == 2)
		//					break;
		//			}
		//			for (int i = 1; i < WaterStatus; i++)
		//			{
		//				if (BombIdx.y - i <= -1)
		//					break;
		//				mBombEffect.push_back(object::Instantiate<BombEffect>(BombPos - Vector2(0.0f, (float)(i * 60.0f)), eLayerType::BombEffect)); // 상단
		//				if (Bazzi::GetMapIndex()[BombIdx.y - i][BombIdx.x] == 2)
		//					break;
		//			}
		//			mBombEffect.push_back(object::Instantiate<BombEffect>(BombPos, eLayerType::BombEffect));
		//		}
		//		for (int i = 0; i < mBombEffect.size(); i++)
		//		{
		//			mBombEffect[i]->SetBomb(this);
		//		}
		//	}
		//
		//	mTime = 0;
		//	Transform* tr = GetComponent<Transform>();
		//	Vector2 mPos = TileBomb::SetIndex(tr->GetPos());
		//	Bazzi::GetMapIndex()[mPos.y][mPos.x] = 0;
		//	int Click = SceneManager::GetBazzi()->GetmClick()--;
		//}
	}

	void BaseBomb::checked()
	{
	}

	void BaseBomb::up()
	{
		Vector2 realPos = tr->GetPos();
		Vector2 mPos = TileBomb::SetIndex(tr->GetPos());
		Vector2 ColPos = collider->GetPos();
		mTime = 0;
		realPos.y -= 740.0f * Time::DeltaTime();
		/*ColPos.y += 40.0f * Time::DeltaTime();*/

		Vector2 ColMidPos = ColPos + Vector2(TILE_SIZE_X / 2, TILE_SIZE_Y / 2);
		Vector2 ColRIdx = TileBomb::SetColIndex(ColMidPos + Vector2(32.0f, 0.0f));
		Vector2 ColLIdx = TileBomb::SetColIndex(ColMidPos + Vector2(-32.0f, 0.0f));
		Vector2 ColUIdx = TileBomb::SetColIndex(ColMidPos + Vector2(0.0f, -32.0f));
		Vector2 ColDIdx = TileBomb::SetColIndex(ColMidPos + Vector2(0.0f, +32.0f));
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


		if (SceneManager::GetBazzi()->GetMapIndex()[ColUIdx.y][ColUIdx.x] == 2)
		{
			tr->SetPos(TileBomb::SetIndex(realPos));
			Bazzi::GetMapIndex()[mPos.y][mPos.x] = 1;
		}
		tr->SetPos(realPos);
	}

	void BaseBomb::right()
	{
		Vector2 realPos = tr->GetPos();
		Vector2 mPos = TileBomb::SetIndex(tr->GetPos());
		Vector2 ColPos = collider->GetPos();
		mTime = 0;
		realPos.x += 740.0f * Time::DeltaTime();
		/*ColPos.y += 40.0f * Time::DeltaTime();*/

		Vector2 ColMidPos = ColPos + Vector2(TILE_SIZE_X / 2, TILE_SIZE_Y / 2);
		Vector2 ColRIdx = TileBomb::SetColIndex(ColMidPos + Vector2(32.0f, 0.0f));
		Vector2 ColLIdx = TileBomb::SetColIndex(ColMidPos + Vector2(-32.0f, 0.0f));
		Vector2 ColUIdx = TileBomb::SetColIndex(ColMidPos + Vector2(0.0f, -32.0f));
		Vector2 ColDIdx = TileBomb::SetColIndex(ColMidPos + Vector2(0.0f, +32.0f));
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

		tr->SetPos(realPos);

		if (SceneManager::GetBazzi()->GetMapIndex()[ColRIdx.y][ColRIdx.x] == 2)
		{
			tr->SetPos(TileBomb::SetPos(realPos));
			Bazzi::GetMapIndex()[mPos.y][mPos.x] = 1;
		}
	}

	void BaseBomb::down()
	{
		Vector2 realPos = tr->GetPos();
		Vector2 mPos = TileBomb::SetIndex(tr->GetPos());
		Vector2 ColPos = collider->GetPos();
		mTime = 0;
		realPos.y += 740.0f * Time::DeltaTime();
		/*ColPos.y += 40.0f * Time::DeltaTime();*/
		
		Vector2 ColMidPos = ColPos + Vector2(TILE_SIZE_X / 2, TILE_SIZE_Y / 2);
		Vector2 ColRIdx = TileBomb::SetColIndex(ColMidPos + Vector2(32.0f, 0.0f));
		Vector2 ColLIdx = TileBomb::SetColIndex(ColMidPos + Vector2(-32.0f, 0.0f));
		Vector2 ColUIdx = TileBomb::SetColIndex(ColMidPos + Vector2(0.0f, -32.0f));
		Vector2 ColDIdx = TileBomb::SetColIndex(ColMidPos + Vector2(0.0f, +32.0f));
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


		if (SceneManager::GetBazzi()->GetMapIndex()[ColDIdx.y][ColDIdx.x] == 2)
		{
			tr->SetPos(TileBomb::SetIndex(realPos));
			Bazzi::GetMapIndex()[mPos.y][mPos.x] = 1;
		}
		tr->SetPos(realPos);
	}

	void BaseBomb::left()
	{
		Vector2 realPos = tr->GetPos();
		Vector2 mPos = TileBomb::SetIndex(tr->GetPos());
		Vector2 ColPos = collider->GetPos();
		mTime = 0;
		realPos.x -= 740.0f * Time::DeltaTime();
		ColPos.x -= 740.0f * Time::DeltaTime();

		Vector2 ColMidPos = ColPos + Vector2(TILE_SIZE_X / 2, TILE_SIZE_Y / 2);
		Vector2 ColRIdx = TileBomb::SetColIndex(ColMidPos + Vector2(30.0f, 0.0f));
		Vector2 ColLIdx = TileBomb::SetColIndex(ColMidPos + Vector2(-30.0f, 0.0f));
		Vector2 ColUIdx = TileBomb::SetColIndex(ColMidPos + Vector2(0.0f, -30.0f));
		Vector2 ColDIdx = TileBomb::SetColIndex(ColMidPos + Vector2(0.0f, +30.0f));
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

		tr->SetPos(realPos);

		if (SceneManager::GetBazzi()->GetMapIndex()[ColLIdx.y][ColLIdx.x] == 2)
		{
			tr->SetPos(TileBomb::SetPos(Vector2(ColMidPos.x - TILE_SIZE_X/2, ColMidPos.y - TILE_SIZE_Y)));
			Bazzi::GetMapIndex()[mPos.y][mPos.x] = 1;
			mleft = false;
		}
	}

}