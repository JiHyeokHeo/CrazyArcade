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
#include "tyDao.h"
#include "tySound.h"
#include "tyResources.h"

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
		bomb_set = Resources::Load<Sound>(L"bomb_set", L"..\\Resources\\Sound\\bomb_set.wav");
		bomb_set->Play(false);
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

		/*mState = eBombState::Idle;*/
		GameObject::Initialize();
	}

	void BaseBomb::Update()
	{


		BaseBomb* bomb = this;
		Vector2 ColPos = collider->GetPos();
		Vector2 ColMidPos = ColPos + Vector2(TILE_SIZE_X / 2, TILE_SIZE_Y / 2);
		Vector2 ColMidIdx = TileBomb::SetColIndex(ColMidPos);
		Vector2 ColRIdx = TileBomb::SetColIndex(ColMidPos + Vector2(31.0f, 0.0f));
		Vector2 ColLIdx = TileBomb::SetColIndex(ColMidPos + Vector2(-31.0f, 0.0f));
		Vector2 ColUIdx = TileBomb::SetColIndex(ColMidPos + Vector2(0.0f, -31.0f));
		Vector2 ColDIdx = TileBomb::SetColIndex(ColMidPos + Vector2(0.0f, +31.0f));
		tr = bomb->GetComponent<Transform>();

		if (isBomb == true)
		{
			SceneManager::GetMapIndex()[ColMidIdx.y][ColMidIdx.x] = 0;
			object::Destroy(this);
		}



		if (SceneManager::GetIsDuo() == false)
		{
			if(SceneManager::GetFirstCharactorPick() == eCharactorPick::Bazzi)
			{
				BazziBombChecking();
			}
			else if (SceneManager::GetFirstCharactorPick() == eCharactorPick::Dao)
			{
				DaoBombChecking();
			}
		}
		else if (SceneManager::GetIsDuo() == true)
		{
			if (SceneManager::GetBazzi()->GetState() == eState::Active && SceneManager::GetBombIndex()[ColMidIdx.y][ColMidIdx.x] == 1)
			{
				BazziBombChecking();
			}
			else if (SceneManager::GetDao()->GetState() == eState::Active && SceneManager::GetBombIndex()[ColMidIdx.y][ColMidIdx.x] == 2)
			{
				DaoBombChecking();
			}
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
		if (other->GetOwner()->GetName() == L"BombEffect" || other->GetOwner()->GetName() == L"BossBombEffect")
		{
			for (int i = 0; i < mBombEffect.size(); i++)
			{
				mBombEffect[i]->SetTime(3.5f);
			}
			mTime = 4.5f;
		}

		if (other->GetOwner()->GetName() == L"Boss")
		{
			mTime = 4.5f;
			isBossCol = true;
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
		bomb_set->Stop(true);
		object::Destroy(this);
	}

	void BaseBomb::idle()
	{
		//mTime += Time::DeltaTime();
		//Vector2 ColPos = collider->GetPos();
		//Vector2 ColMidPos = ColPos + Vector2(TILE_SIZE_X / 2, TILE_SIZE_Y / 2);
		//Vector2 ColMidIdx = TileBomb::SetColIndex(ColMidPos);
		//if (mTime >= 3.0f)
		//{
		//	if (isShot == false)
		//	{
		//		isShot = true;
		//		Transform* tr = GetComponent<Transform>();
		//		Vector2 realPos = tr->GetPos();
		//		Vector2 mPos = TileBomb::SetIndex(tr->GetPos());
		//		Vector2 ColPos = collider->GetPos();
		//		Vector2 ColMidPos = ColPos + Vector2(TILE_SIZE_X / 2, TILE_SIZE_Y / 2);
		//		Vector2 ColMidIdx = TileBomb::SetColIndex(ColMidPos);
		//		SceneManager::GetMapIndex()[mPos.y][mPos.x] = 1;

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
		//				if (SceneManager::GetMapIndex()[BombIdx.y][BombIdx.x + i] >= 2)
		//					break;
		//			}
		//			for (int i = 1; i < WaterStatus; i++)
		//			{
		//				if (BombIdx.y + i >= 13)
		//					break;
		//				mBombEffect.push_back(object::Instantiate<BombEffect>(BombPos + Vector2(0.0f, float(i * 60.0f)), eLayerType::BombEffect)); // 하단
		//				if (SceneManager::GetMapIndex()[BombIdx.y + i][BombIdx.x] >= 2)
		//					break;
		//			}
		//			for (int i = 1; i < WaterStatus; i++)
		//			{
		//				if (BombIdx.x - i <= -1)
		//					break;
		//				mBombEffect.push_back(object::Instantiate<BombEffect>(BombPos - Vector2((float)(i * 60.0f), 0.0f), eLayerType::BombEffect)); // 좌측
		//				if (SceneManager::GetMapIndex()[BombIdx.y][BombIdx.x - i] >= 2)
		//					break;
		//			}
		//			for (int i = 1; i < WaterStatus; i++)
		//			{
		//				if (BombIdx.y - i <= -1)
		//					break;
		//				mBombEffect.push_back(object::Instantiate<BombEffect>(BombPos - Vector2(0.0f, (float)(i * 60.0f)), eLayerType::BombEffect)); // 상단
		//				if (SceneManager::GetMapIndex()[BombIdx.y - i][BombIdx.x] >= 2)
		//					break;
		//			}
		//			mBombEffect.push_back(object::Instantiate<BombEffect>(BombPos, eLayerType::BombEffect));
		//		}
		//		for (int i = 0; i < mBombEffect.size(); i++)
		//		{
		//			mBombEffect[i]->SetBomb(this);
		//		}

		//		if (isBossCol == true)
		//		{
		//			for (int i = 0; i < mBombEffect.size(); i++)
		//			{
		//				mBombEffect[i]->SetTime(3.5f);
		//			}
		//		}
		//		
		//	}
		//
		//	mTime = 0;
		//	Transform* tr = GetComponent<Transform>();
		//	Vector2 mPos = TileBomb::SetIndex(tr->GetPos());
		//	SceneManager::GetMapIndex()[ColMidIdx.y][ColMidIdx.x] = 0;
		//	int Click = SceneManager::GetBazzi()->GetmClick()--;
		//	isBomb = true;
		//}
	}

	void BaseBomb::checked()
	{
	}

	void BaseBomb::up()
	{
		if (isBossCol == true)
		{
			return;
		}
		
		Vector2 realPos = tr->GetPos();
		Vector2 mPos = TileBomb::SetIndex(tr->GetPos());
		Vector2 ColPos = collider->GetPos();
		mTime = 0;
		realPos.y -= 740.0f * Time::DeltaTime();
		ColPos.y -= 740.0f * Time::DeltaTime();

		Vector2 ColMidPos = ColPos + Vector2(TILE_SIZE_X / 2, TILE_SIZE_Y / 2);
		Vector2 ColMidIdx = TileBomb::SetColIndex(ColMidPos);
		Vector2 ColRIdx = TileBomb::SetColIndex(ColMidPos + Vector2(31.0f, 0.0f));
		Vector2 ColLIdx = TileBomb::SetColIndex(ColMidPos + Vector2(-31.0f, 0.0f));
		Vector2 ColUIdx = TileBomb::SetColIndex(ColMidPos + Vector2(0.0f, -31.0f));
		Vector2 ColDIdx = TileBomb::SetColIndex(ColMidPos + Vector2(0.0f, +31.0f));
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

		if (realPos.x <= 30.0f)
		{
			realPos.x = 30.0f;
			SceneManager::GetMapIndex()[ColMidIdx.y][ColMidIdx.x] = 1;
			mleft = false;
			hasBeenPushed = true;
		}

		if (realPos.x >= 840.0f)
		{
			realPos.x = 840.0f;
			SceneManager::GetMapIndex()[ColMidIdx.y][ColMidIdx.x] = 1;
			mright = false;
			hasBeenPushed = true;
		}

		if (realPos.y <= 60.0f)
		{
			realPos.y = 60.0f;
			SceneManager::GetMapIndex()[ColMidIdx.y][ColMidIdx.x] = 1;
			mup = false;
			hasBeenPushed = true;
		}

		if (realPos.y >= 780.0f)
		{
			realPos.y = 780.0f;
			SceneManager::GetMapIndex()[ColMidIdx.y][ColMidIdx.x] = 1;
			mdown = false;
			hasBeenPushed = true;
		}

		tr->SetPos(realPos);

		if (SceneManager::GetMapIndex()[ColUIdx.y][ColUIdx.x] >=2 || SceneManager::GetMapIndex()[ColUIdx.y][ColUIdx.x] == 1)
		{
			tr->SetPos(TileBomb::SetPos(Vector2(ColMidPos.x - TILE_SIZE_X, ColMidPos.y - TILE_SIZE_Y / 2)));
			SceneManager::GetMapIndex()[ColMidIdx.y][ColMidIdx.x] = 1;
			pushcnt = 0;
			hasBeenPushed = true;
		}
	}

	void BaseBomb::right()
	{
		if (isBossCol == true)
		{
			return;
		}
		Vector2 realPos = tr->GetPos();
		Vector2 mPos = TileBomb::SetIndex(tr->GetPos());
		Vector2 ColPos = collider->GetPos();
		realPos.x += 740.0f * Time::DeltaTime();
		ColPos.x += 740.0f * Time::DeltaTime();
		mTime = 0;
		Vector2 ColMidPos = ColPos + Vector2(TILE_SIZE_X / 2, TILE_SIZE_Y / 2);
		Vector2 ColMidIdx = TileBomb::SetColIndex(ColMidPos);
		Vector2 ColRIdx = TileBomb::SetColIndex(ColMidPos + Vector2(31.0f, 0.0f));
		Vector2 ColLIdx = TileBomb::SetColIndex(ColMidPos + Vector2(-31.0f, 0.0f));
		Vector2 ColUIdx = TileBomb::SetColIndex(ColMidPos + Vector2(0.0f, -31.0f));
		Vector2 ColDIdx = TileBomb::SetColIndex(ColMidPos + Vector2(0.0f, +31.0f));
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

		if (realPos.x <= 30.0f)
		{
			realPos.x = 30.0f;
			SceneManager::GetMapIndex()[ColMidIdx.y][ColMidIdx.x] = 1;
			mleft = false;
			hasBeenPushed = true;
		}

		if (realPos.x >= 870.0f)
		{
			realPos.x = 890.0f;
			SceneManager::GetMapIndex()[ColMidIdx.y][ColMidIdx.x] = 1;
			mright = false;
			hasBeenPushed = true;
		}

		if (realPos.y <= 60.0f)
		{
			realPos.y = 60.0f;
			SceneManager::GetMapIndex()[ColMidIdx.y][ColMidIdx.x] = 1;
			mup = false;
			hasBeenPushed = true;
		}

		if (realPos.y >= 780.0f)
		{
			realPos.y = 780.0f;
			SceneManager::GetMapIndex()[ColMidIdx.y][ColMidIdx.x] = 1;
			mdown = false;
			hasBeenPushed = true;
		}

		tr->SetPos(realPos);

		if (SceneManager::GetMapIndex()[ColRIdx.y][ColRIdx.x] >= 2 || SceneManager::GetMapIndex()[ColRIdx.y][ColRIdx.x] == 1)
		{
			tr->SetPos(TileBomb::SetPos(Vector2(ColMidPos.x- TILE_SIZE_X, ColMidPos.y - TILE_SIZE_Y)));
			SceneManager::GetMapIndex()[ColMidIdx.y][ColMidIdx.x] = 1;
			pushcnt = 0;
			mTime = 0;
			hasBeenPushed = true;
		}
	}

	void BaseBomb::down()
	{
		if (isBossCol == true)
		{
			return;
		}
		Vector2 realPos = tr->GetPos();
		Vector2 mPos = TileBomb::SetIndex(tr->GetPos());
		Vector2 ColPos = collider->GetPos();
		mTime = 0;
		realPos.y += 740.0f * Time::DeltaTime();
		ColPos.y += 740.0f * Time::DeltaTime();

		Vector2 ColMidPos = ColPos + Vector2(TILE_SIZE_X / 2, TILE_SIZE_Y / 2);
		Vector2 ColMidIdx = TileBomb::SetColIndex(ColMidPos);
		Vector2 ColRIdx = TileBomb::SetColIndex(ColMidPos + Vector2(31.0f, 0.0f));
		Vector2 ColLIdx = TileBomb::SetColIndex(ColMidPos + Vector2(-31.0f, 0.0f));
		Vector2 ColUIdx = TileBomb::SetColIndex(ColMidPos + Vector2(0.0f, -31.0f));
		Vector2 ColDIdx = TileBomb::SetColIndex(ColMidPos + Vector2(0.0f, +31.0f));
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

		if (realPos.x <= 30.0f)
		{
			realPos.x = 30.0f;
			SceneManager::GetMapIndex()[ColMidIdx.y][ColMidIdx.x] = 1;
			mdown = false;
			hasBeenPushed = true;
		}

		if (realPos.x >= 840.0f)
		{
			realPos.x = 840.0f;
			SceneManager::GetMapIndex()[ColMidIdx.y][ColMidIdx.x] = 1;
			mright = false;
			hasBeenPushed = true;
		}

		if (realPos.y <= 60.0f)
		{
			realPos.y = 60.0f;
			SceneManager::GetMapIndex()[ColMidIdx.y][ColMidIdx.x] = 1;
			mup = false;
			hasBeenPushed = true;
		}

		if (realPos.y >= 780.0f)
		{
			realPos.y = 780.0f;
			SceneManager::GetMapIndex()[ColMidIdx.y][ColMidIdx.x] = 1;
			mdown = false;
			hasBeenPushed = true;
		}

		tr->SetPos(realPos);

		if (SceneManager::GetMapIndex()[ColDIdx.y][ColDIdx.x] >= 2 || SceneManager::GetMapIndex()[ColDIdx.y][ColDIdx.x] == 1)
		{
			tr->SetPos(TileBomb::SetPos(Vector2(ColMidPos.x - TILE_SIZE_X, ColMidPos.y - TILE_SIZE_Y * 1.5 )));;
			SceneManager::GetMapIndex()[ColMidIdx.y][ColMidIdx.x] = 1;
			pushcnt = 0;
			mTime = 0;
			hasBeenPushed = true;
		}
	}

	void BaseBomb::left()
	{
		if (isBossCol == true)
		{
			return;
		}
		Vector2 realPos = tr->GetPos();
		Vector2 mPos = TileBomb::SetIndex(tr->GetPos());
		Vector2 ColPos = collider->GetPos();
		realPos.x -= 740.0f * Time::DeltaTime();
		ColPos.x -= 740.0f * Time::DeltaTime();
		mTime = 0;
		Vector2 ColMidPos = ColPos + Vector2(TILE_SIZE_X / 2, TILE_SIZE_Y / 2);
		Vector2 ColMidIdx = TileBomb::SetColIndex(ColMidPos);
		Vector2 ColRIdx = TileBomb::SetColIndex(ColMidPos + Vector2(31.0f, 0.0f));
		Vector2 ColLIdx = TileBomb::SetColIndex(ColMidPos + Vector2(-31.0f, 0.0f));
		Vector2 ColUIdx = TileBomb::SetColIndex(ColMidPos + Vector2(0.0f, -31.0f));
		Vector2 ColDIdx = TileBomb::SetColIndex(ColMidPos + Vector2(0.0f, +31.0f));
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

		if (realPos.x <= 30.0f)
		{
			realPos.x = 30.0f;
			SceneManager::GetMapIndex()[ColMidIdx.y][ColMidIdx.x] = 1;
			mleft = false;
			hasBeenPushed = true;
		}

		if (realPos.x >= 840.0f)
		{
			realPos.x = 840.0f;
			SceneManager::GetMapIndex()[ColMidIdx.y][ColMidIdx.x] = 1;
			mright = false;
			hasBeenPushed = true;
		}

		if (realPos.y <= 60.0f)
		{
			realPos.y = 60.0f;
			SceneManager::GetMapIndex()[ColMidIdx.y][ColMidIdx.x] = 1;
			mup = false;
			hasBeenPushed = true;
		}

		if (realPos.y >= 780.0f)
		{
			realPos.y = 780.0f;
			SceneManager::GetMapIndex()[ColMidIdx.y][ColMidIdx.x] = 1;
			mdown = false;
			hasBeenPushed = true;
		}
		tr->SetPos(realPos);

		if (SceneManager::GetMapIndex()[ColLIdx.y][ColLIdx.x] >= 2 || SceneManager::GetMapIndex()[ColLIdx.y][ColLIdx.x] == 1)
		{
			tr->SetPos(TileBomb::SetPos(Vector2(ColMidPos.x - TILE_SIZE_X / 2, ColMidPos.y - TILE_SIZE_Y)));
			SceneManager::GetMapIndex()[ColMidIdx.y][ColMidIdx.x] = 1;
			pushcnt = 0;
			mTime = 0;
			hasBeenPushed = true;
		}
	}

	void BaseBomb::BazziBombChecking()
	{	//BaseBomb* bomb = this;
		Transform* mPlayer = SceneManager::GetBazzi()->GetComponent<Transform>();
		Collider* mPlayerCollider = SceneManager::GetBazzi()->GetComponent<Collider>();
		Vector2 mPlayerColPos = mPlayerCollider->GetPos();
		mPlayerColPos = mPlayerColPos + Vector2(30.0f, 30.0f);
		Vector2 mPlayerPos = mPlayer->GetPos();
		Vector2 IDX = TileBomb::SetColIndex(mPlayerColPos);

		//tr = bomb->GetComponent<Transform>();
		//mBasePos = tr->GetPos();
		Vector2 ColPos = collider->GetPos();
		Vector2 ColMidPos = ColPos + Vector2(TILE_SIZE_X / 2, TILE_SIZE_Y / 2);
		Vector2 ColMidIdx = TileBomb::SetColIndex(ColMidPos);
		Vector2 ColRIdx = TileBomb::SetColIndex(ColMidPos + Vector2(31.0f, 0.0f));
		Vector2 ColLIdx = TileBomb::SetColIndex(ColMidPos + Vector2(-31.0f, 0.0f));
		Vector2 ColUIdx = TileBomb::SetColIndex(ColMidPos + Vector2(0.0f, -31.0f));
		Vector2 ColDIdx = TileBomb::SetColIndex(ColMidPos + Vector2(0.0f, +31.0f));
		//Vector2 mPos = TileBomb::SetIndex(tr->GetPos());

		if (SceneManager::GetMapIndex()[IDX.y][IDX.x] != SceneManager::GetMapIndex()[ColMidIdx.y][ColMidIdx.x])
		{
			SceneManager::GetMapIndex()[ColMidIdx.y][ColMidIdx.x] = 1;
		}


		//if (isBomb == true)
		//{
		//	SceneManager::GetMapIndex()[ColMidIdx.y][ColMidIdx.x] = 0;
		//	object::Destroy(this);
		//}


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



		if (SceneManager::GetMapIndex()[mDownIdx.y][mDownIdx.x] == 1
			&& mBazzi->GetIsPushPossible() == true && Input::GetKey(eKeyCode::DOWN) && mBazzi->GetIsBirdOn() == false)
		{
			mPushTime += Time::DeltaTime();
			if (mPushTime >= 0.1f)
			{
				pushcnt++;
				mPushTime = 0;
				mdown = true;
				this->SetTarget();
			}
		}
		if (SceneManager::GetMapIndex()[mUpdx.y][mUpdx.x] == 1
			&& mBazzi->GetIsPushPossible() == true && Input::GetKey(eKeyCode::UP) && mBazzi->GetIsBirdOn() == false)
		{
			mPushTime += Time::DeltaTime();
			if (mPushTime >= 0.1f)
			{
				pushcnt++;
				mPushTime = 0;
				mup = true;
				this->SetTarget();
			}
		}
		if (SceneManager::GetMapIndex()[mRightdx.y][mRightdx.x] == 1
			&& mBazzi->GetIsPushPossible() == true && Input::GetKey(eKeyCode::RIGHT) && mBazzi->GetIsBirdOn() == false)
		{
			mPushTime += Time::DeltaTime();
			if (mPushTime >= 0.1f)
			{
				pushcnt++;
				mPushTime = 0;
				mright = true;
				this->SetTarget();
			}
		}
		if (SceneManager::GetMapIndex()[mLeftIdx.y][mLeftIdx.x] == 1
			&& mBazzi->GetIsPushPossible() == true && Input::GetKey(eKeyCode::LEFT) && mBazzi->GetIsBirdOn() == false)
		{
			mPushTime += Time::DeltaTime();
			if (mPushTime >= 0.1f)
			{
				pushcnt++;
				mPushTime = 0;
				mleft = true;
				this->SetTarget();
			}
		}

		if (isTarget == true /*&& mBazzi->GetMapIndex()[mLeftIdx.y][mLeftIdx.x] == 1*/
			&& mBazzi->GetIsPushPossible() == true
			&& mleft == true && mright == false && mup == false && mdown == false
			&& pushcnt == 1 && hasBeenPushed == false)
		{
			SceneManager::GetMapIndex()[ColMidIdx.y][ColMidIdx.x] = 0;
			left();
		}
		else if (isTarget == true /*&& mBazzi->GetMapIndex()[mRightdx.y][mRightdx.x] == 1*/
			&& mBazzi->GetIsPushPossible() == true
			&& mright == true && mleft == false && mup == false && mdown == false
			&& pushcnt == 1 && hasBeenPushed == false)
		{
			SceneManager::GetMapIndex()[ColMidIdx.y][ColMidIdx.x] = 0;
			right();
		}
		else if (isTarget == true /*&& mBazzi->GetMapIndex()[mUpdx.y][mUpdx.x] == 1*/
			&& mBazzi->GetIsPushPossible() == true
			&& mup == true && mright == false && mleft == false && mdown == false
			&& pushcnt == 1 && hasBeenPushed == false)
		{
			SceneManager::GetMapIndex()[ColMidIdx.y][ColMidIdx.x] = 0;
			up();
		}
		else if (isTarget == true /*&& mBazzi->GetMapIndex()[mDownIdx.y][mDownIdx.x] == 1*/
			&& mBazzi->GetIsPushPossible() == true
			&& mup == false && mright == false && mleft == false && mdown == true
			&& pushcnt == 1 && hasBeenPushed == false)
		{
			SceneManager::GetMapIndex()[ColMidIdx.y][ColMidIdx.x] = 0;
			down();
		}



		switch (mState)
		{
		case ty::BaseBomb::eBombState::Idle:
			idle();
			break;
		}

		mTime += Time::DeltaTime();

		if (mTime >= 2.5f)
		{
			if (isShot == false)
			{
				isShot = true;
				Transform* tr = GetComponent<Transform>();
				Vector2 realPos = tr->GetPos();
				Vector2 mPos = TileBomb::SetIndex(tr->GetPos());
				Vector2 ColPos = collider->GetPos();
				Vector2 ColMidPos = ColPos + Vector2(TILE_SIZE_X / 2, TILE_SIZE_Y / 2);
				Vector2 ColMidIdx = TileBomb::SetColIndex(ColMidPos);
				SceneManager::GetMapIndex()[mPos.y][mPos.x] = 1;

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
						if (SceneManager::GetMapIndex()[BombIdx.y][BombIdx.x + i] >= 2)
							break;
					}
					for (int i = 1; i < WaterStatus; i++)
					{
						if (BombIdx.y + i >= 13)
							break;
						mBombEffect.push_back(object::Instantiate<BombEffect>(BombPos + Vector2(0.0f, float(i * 60.0f)), eLayerType::BombEffect)); // 하단
						if (SceneManager::GetMapIndex()[BombIdx.y + i][BombIdx.x] >= 2)
							break;
					}
					for (int i = 1; i < WaterStatus; i++)
					{
						if (BombIdx.x - i <= -1)
							break;
						mBombEffect.push_back(object::Instantiate<BombEffect>(BombPos - Vector2((float)(i * 60.0f), 0.0f), eLayerType::BombEffect)); // 좌측
						if (SceneManager::GetMapIndex()[BombIdx.y][BombIdx.x - i] >= 2)
							break;
					}
					for (int i = 1; i < WaterStatus; i++)
					{
						if (BombIdx.y - i <= -1)
							break;
						mBombEffect.push_back(object::Instantiate<BombEffect>(BombPos - Vector2(0.0f, (float)(i * 60.0f)), eLayerType::BombEffect)); // 상단
						if (SceneManager::GetMapIndex()[BombIdx.y - i][BombIdx.x] >= 2)
							break;
					}
					mBombEffect.push_back(object::Instantiate<BombEffect>(BombPos, eLayerType::BombEffect));
				}
				for (int i = 0; i < mBombEffect.size(); i++)
				{
					mBombEffect[i]->SetBomb(this);
				}

				if (isBossCol == true)
				{
					for (int i = 0; i < mBombEffect.size(); i++)
					{
						mBombEffect[i]->SetTime(3.5f);
					}
				}

			}

			mTime = 0;
			Transform* tr = GetComponent<Transform>();
			Vector2 mPos = TileBomb::SetIndex(tr->GetPos());
			SceneManager::GetMapIndex()[ColMidIdx.y][ColMidIdx.x] = 0;
			int Click = SceneManager::GetBazzi()->GetmClick()--;
			isBomb = true;
		}
	}

	void BaseBomb::DaoBombChecking()
	{
		Transform* mPlayer = SceneManager::GetDao()->GetComponent<Transform>();
		Collider* mPlayerCollider = SceneManager::GetDao()->GetComponent<Collider>();
		Vector2 mPlayerColPos = mPlayerCollider->GetPos();
		mPlayerColPos = mPlayerColPos + Vector2(30.0f, 30.0f);
		Vector2 mPlayerPos = mPlayer->GetPos();
		Vector2 IDX = TileBomb::SetColIndex(mPlayerColPos);

		//tr = bomb->GetComponent<Transform>();
		//mBasePos = tr->GetPos();
		Vector2 ColPos = collider->GetPos();
		Vector2 ColMidPos = ColPos + Vector2(TILE_SIZE_X / 2, TILE_SIZE_Y / 2);
		Vector2 ColMidIdx = TileBomb::SetColIndex(ColMidPos);
		Vector2 ColRIdx = TileBomb::SetColIndex(ColMidPos + Vector2(31.0f, 0.0f));
		Vector2 ColLIdx = TileBomb::SetColIndex(ColMidPos + Vector2(-31.0f, 0.0f));
		Vector2 ColUIdx = TileBomb::SetColIndex(ColMidPos + Vector2(0.0f, -31.0f));
		Vector2 ColDIdx = TileBomb::SetColIndex(ColMidPos + Vector2(0.0f, +31.0f));
		//Vector2 mPos = TileBomb::SetIndex(tr->GetPos());

		if (SceneManager::GetMapIndex()[IDX.y][IDX.x] != SceneManager::GetMapIndex()[ColMidIdx.y][ColMidIdx.x])
		{
			SceneManager::GetMapIndex()[ColMidIdx.y][ColMidIdx.x] = 1;
		}


		//if (isBomb == true)
		//{
		//	SceneManager::GetMapIndex()[ColMidIdx.y][ColMidIdx.x] = 0;
		//	object::Destroy(this);
		//}


		mDao = SceneManager::GetDao();
		Vector2 mDownIdx = mDao->GetDownIdx();
		Vector2 mUpdx = mDao->GetUpIdx();
		Vector2 mRightdx = mDao->GetRightIdx();
		Vector2 mLeftIdx = mDao->GetLeftIdx();


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



		if (SceneManager::GetMapIndex()[mDownIdx.y][mDownIdx.x] == 1
			&& mDao->GetIsPushPossible() == true && Input::GetKey(eKeyCode::DOWN) && mDao->GetIsBirdOn() == false)
		{
			mPushTime += Time::DeltaTime();
			if (mPushTime >= 0.1f)
			{
				pushcnt++;
				mPushTime = 0;
				mdown = true;
				this->SetTarget();
			}
		}
		if (SceneManager::GetMapIndex()[mUpdx.y][mUpdx.x] == 1
			&& mDao->GetIsPushPossible() == true && Input::GetKey(eKeyCode::UP) && mDao->GetIsBirdOn() == false)
		{
			mPushTime += Time::DeltaTime();
			if (mPushTime >= 0.1f)
			{
				pushcnt++;
				mPushTime = 0;
				mup = true;
				this->SetTarget();
			}
		}
		if (SceneManager::GetMapIndex()[mRightdx.y][mRightdx.x] == 1
			&& mDao->GetIsPushPossible() == true && Input::GetKey(eKeyCode::RIGHT) && mDao->GetIsBirdOn() == false)
		{
			mPushTime += Time::DeltaTime();
			if (mPushTime >= 0.1f)
			{
				pushcnt++;
				mPushTime = 0;
				mright = true;
				this->SetTarget();
			}
		}
		if (SceneManager::GetMapIndex()[mLeftIdx.y][mLeftIdx.x] == 1
			&& mDao->GetIsPushPossible() == true && Input::GetKey(eKeyCode::LEFT) && mDao->GetIsBirdOn() == false)
		{
			mPushTime += Time::DeltaTime();
			if (mPushTime >= 0.1f)
			{
				pushcnt++;
				mPushTime = 0;
				mleft = true;
				this->SetTarget();
			}
		}

		if (isTarget == true /*&& mBazzi->GetMapIndex()[mLeftIdx.y][mLeftIdx.x] == 1*/
			&& mDao->GetIsPushPossible() == true
			&& mleft == true && mright == false && mup == false && mdown == false
			&& pushcnt == 1 && hasBeenPushed == false)
		{
			SceneManager::GetMapIndex()[ColMidIdx.y][ColMidIdx.x] = 0;
			left();
		}
		else if (isTarget == true /*&& mBazzi->GetMapIndex()[mRightdx.y][mRightdx.x] == 1*/
			&& mDao->GetIsPushPossible() == true
			&& mright == true && mleft == false && mup == false && mdown == false
			&& pushcnt == 1 && hasBeenPushed == false)
		{
			SceneManager::GetMapIndex()[ColMidIdx.y][ColMidIdx.x] = 0;
			right();
		}
		else if (isTarget == true /*&& mBazzi->GetMapIndex()[mUpdx.y][mUpdx.x] == 1*/
			&& mDao->GetIsPushPossible() == true
			&& mup == true && mright == false && mleft == false && mdown == false
			&& pushcnt == 1 && hasBeenPushed == false)
		{
			SceneManager::GetMapIndex()[ColMidIdx.y][ColMidIdx.x] = 0;
			up();
		}
		else if (isTarget == true /*&& mBazzi->GetMapIndex()[mDownIdx.y][mDownIdx.x] == 1*/
			&& mDao->GetIsPushPossible() == true
			&& mup == false && mright == false && mleft == false && mdown == true
			&& pushcnt == 1 && hasBeenPushed == false)
		{
			SceneManager::GetMapIndex()[ColMidIdx.y][ColMidIdx.x] = 0;
			down();
		}



		switch (mState)
		{
		case ty::BaseBomb::eBombState::Idle:
			idle();
			break;
		}

		mTime += Time::DeltaTime();

		if (mTime >= 2.5f)
		{
			if (isShot == false)
			{
				isShot = true;
				Transform* tr = GetComponent<Transform>();
				Vector2 realPos = tr->GetPos();
				Vector2 mPos = TileBomb::SetIndex(tr->GetPos());
				Vector2 ColPos = collider->GetPos();
				Vector2 ColMidPos = ColPos + Vector2(TILE_SIZE_X / 2, TILE_SIZE_Y / 2);
				Vector2 ColMidIdx = TileBomb::SetColIndex(ColMidPos);
				SceneManager::GetMapIndex()[mPos.y][mPos.x] = 1;

				Vector2 BombPos = tr->GetPos();
				Vector2 BombIdx = TileBomb::SetIndex(BombPos);

				int WaterStatus = SceneManager::GetDao()->GetmWaterCourse();
				if (BombIdx.x < 15 || BombIdx.y < 13)
				{
					for (int i = 1; i < WaterStatus; i++)
					{
						if (BombIdx.x + i >= 15)
							break;
						mBombEffect.push_back(object::Instantiate<BombEffect>(BombPos + Vector2((float)(i * 60.0f), 0.0f), eLayerType::BombEffect)); // 우측
						if (SceneManager::GetMapIndex()[BombIdx.y][BombIdx.x + i] >= 2)
							break;
					}
					for (int i = 1; i < WaterStatus; i++)
					{
						if (BombIdx.y + i >= 13)
							break;
						mBombEffect.push_back(object::Instantiate<BombEffect>(BombPos + Vector2(0.0f, float(i * 60.0f)), eLayerType::BombEffect)); // 하단
						if (SceneManager::GetMapIndex()[BombIdx.y + i][BombIdx.x] >= 2)
							break;
					}
					for (int i = 1; i < WaterStatus; i++)
					{
						if (BombIdx.x - i <= -1)
							break;
						mBombEffect.push_back(object::Instantiate<BombEffect>(BombPos - Vector2((float)(i * 60.0f), 0.0f), eLayerType::BombEffect)); // 좌측
						if (SceneManager::GetMapIndex()[BombIdx.y][BombIdx.x - i] >= 2)
							break;
					}
					for (int i = 1; i < WaterStatus; i++)
					{
						if (BombIdx.y - i <= -1)
							break;
						mBombEffect.push_back(object::Instantiate<BombEffect>(BombPos - Vector2(0.0f, (float)(i * 60.0f)), eLayerType::BombEffect)); // 상단
						if (SceneManager::GetMapIndex()[BombIdx.y - i][BombIdx.x] >= 2)
							break;
					}
					mBombEffect.push_back(object::Instantiate<BombEffect>(BombPos, eLayerType::BombEffect));
				}
				for (int i = 0; i < mBombEffect.size(); i++)
				{
					mBombEffect[i]->SetBomb(this);
				}

				if (isBossCol == true)
				{
					for (int i = 0; i < mBombEffect.size(); i++)
					{
						mBombEffect[i]->SetTime(3.5f);
					}
				}

			}

			mTime = 0;
			Transform* tr = GetComponent<Transform>();
			Vector2 mPos = TileBomb::SetIndex(tr->GetPos());
			SceneManager::GetMapIndex()[ColMidIdx.y][ColMidIdx.x] = 0;
			int Click = mDao->GetmClick()--;
			isBomb = true;
		}
	}

}