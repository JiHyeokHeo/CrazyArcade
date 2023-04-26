#include "tyDao.h"
#include "tyTime.h"
#include "tySceneManager.h"
#include "tyinput.h"
#include "tyResources.h"
#include "tyTransform.h"
#include "tyAnimator.h"
#include "tyCollider.h"
#include "tyBaseBomb.h"
#include "tyScene.h"
#include "tyObject.h"
#include "tyBombEffect.h"
#include "tyTile.h"
#include "tyTileBomb.h"
#include "tyBallon.h"
#include "tyPotion.h"
#include "tyPotionMax.h"
#include "tySkate.h"
#include  "tySteam.h"
#include "tyShieldEffect.h"
#include "tyShield.h"
#include "tyNeedle.h"
#include "tyDevil.h"

namespace ty
{
	Dao::Dao()
		: mHP(1) // 체력 
		, mItemState(eItemType::None)
		, mBomb(1) // 폭탄
		, mWaterCourse(2) // 물줄기
		, mSpeed(4.5f) // 속도
		, maxSpeed(8.5f)
		, maxBomb(6)
		, maxWaterCourse(7)
		, mPlayerSpeed(50)
		, mInvincibility(1.5f)
		, mItemCnt(0)
		, maxItemCnt(1) // 최대 아이템 보유 갯수
		, isColl(true)
	{
	}
	Dao::~Dao()
	{
	}
	void Dao::Initialize()
	{	/*	isBirdOn = true;*/
		//isPushPossible = true;
		Transform* tr = GetComponent<Transform>();

		tr->SetScale(Vector2(1.5f, 1.5f));
		SetName(L"Dao");
	

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Dao\\Up", Vector2(-15.0f, -5.0f), 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Dao\\Right", Vector2(-15.0f, -5.0f), 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Dao\\Up", Vector2(-15.0f, -5.0f), 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Dao\\Left", Vector2(-15.0f, -5.0f), 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Dao\\Down", Vector2(-15.0f, -5.0f), 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Dao\\UpIdle", Vector2(-15.0f, -5.0f), 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Dao\\RightIdle", Vector2(-15.0f, -5.0f), 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Dao\\UpIdle", Vector2(-15.0f, -5.0f), 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Dao\\LeftIdle", Vector2(-15.0f, -5.0f), 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Dao\\DownIdle", Vector2(-15.0f, -5.0f), 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Dao\\Die", Vector2(-15.0f, -5.0f), 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Dao\\Bubble", Vector2(-15.0f, -5.0f), 0.5f);
		mAnimator->CreateAnimations(L"..\\Resources\\Dao\\Live", Vector2(-15.0f, -5.0f), 0.1f);


		mAnimator->GetCompleteEvent(L"DaoBubble") = std::bind(&Dao::trapCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"DaoDie") = std::bind(&Dao::dieCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"DaoLive") = std::bind(&Dao::liveCompleteEvent, this);
		mAnimator->Play(L"DaoDownIdle", false);

		collider = AddComponent<Collider>();
		collider->SetCenter(Vector2(12.0f, 25.0f));
		collider->SetSize(Vector2(55.0f, 55.0f));

		mState = eDaoState::Idle;

		//mAnimator->Play(L"downIlde", true);^
		GameObject::Initialize();
	}
	void Dao::Update()
	{
		tr = GetComponent<Transform>();
		mPos = tr->GetPos();
		IdxPos = TileBomb::SetIndex(tr->GetPos());
		mTime += Time::DeltaTime();

		Vector2 temp = Input::GetMousePos();
		checkInVTime(); // 무적시간 체크

		if (mTime >= 1.5f)
		{
			switch (mState)
			{
			case ty::Dao::eDaoState::Move:
				move();
				break;
			case ty::Dao::eDaoState::Shoot:
				shoot();
				break;
			case ty::Dao::eDaoState::Death:
				death();
				break;
			case ty::Dao::eDaoState::Idle:
				idle();
				break;
			case ty::Dao::eDaoState::Bubble:
				bubble();
				break;
			case ty::Dao::eDaoState::BubbleMove:
				bubblemove();
				break;
				//case ty::Bazzi::eBazziState::Revive:
				//	revive();
				//	break;
			case ty::Dao::eDaoState::NoMove:
				nomove();
				break;
			case ty::Dao::eDaoState::BirdOn:
				birdmove();
				break;
			default:
				break;
			}
		}

		if (Input::GetKeyDown(eKeyCode::Z))
		{
			object::Instantiate<Ballon>(TileBomb::SetPos(Vector2(tr->GetPos().x + TILE_SIZE_X, tr->GetPos().y)), eLayerType::Item);
			object::Instantiate<Skate>(TileBomb::SetPos(Vector2(tr->GetPos().x - TILE_SIZE_X, tr->GetPos().y)), eLayerType::Item);
			object::Instantiate<Potion>(TileBomb::SetPos(Vector2(tr->GetPos().x, tr->GetPos().y + TILE_SIZE_Y)), eLayerType::Item);
		}

		if (Input::GetKeyDown(eKeyCode::B))
		{
			object::Instantiate<Needle>(TileBomb::SetPos(Vector2(tr->GetPos().x + TILE_SIZE_X, tr->GetPos().y)), eLayerType::Item);
			object::Instantiate<Shield>(TileBomb::SetPos(Vector2(tr->GetPos().x - TILE_SIZE_X, tr->GetPos().y)), eLayerType::Item);
			object::Instantiate<Devil>(TileBomb::SetPos(Vector2(tr->GetPos().x, tr->GetPos().y + TILE_SIZE_Y)), eLayerType::Item);
		}

		if (Input::GetKeyDown(eKeyCode::X))
		{
			mBomb = 1; // 폭탄
			mWaterCourse = 2; // 물줄기
			mSpeed = 5.0f; // 속도
			isPushPossible = false;
		}


		if (Input::GetKeyDown(eKeyCode::C))
		{
			mInvincibility = 1000;
		}

		if (Input::GetKeyDown(eKeyCode::V))
		{
			mInvincibility = -1;
		}
		GameObject::Update();
	}
	void Dao::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Dao::Release()
	{
	}
	void Dao::OnCollisionEnter(Collider* other)
	{
		if (isColl == false && other->GetOwner()->GetName() == L"Monster" && mInvincibility <= 0.0f && other->GetOwner()->GetState() == eState::Active)
		{
			mInvincibility = 3.0f;
			mAnimator->Play(L"DaoDie", false);
			mState = eDaoState::Death;
			isColl = true;
		}
		if (isColl == false && other->GetOwner()->GetName() == L"Boss" && mInvincibility <= 0.0f)
		{
			mAnimator->Play(L"DaoDie", false);
			mState = eDaoState::Death;
			isColl = true;
		}
		if (isColl == false && other->GetOwner()->GetName() == L"BossBombEffect" && isBirdOn == false && mInvincibility <= 0.0f)
		{
			mAnimator->Play(L"DaoBubble", false);
			mState = eDaoState::BubbleMove;
			isColl = true;
		}
		if (isColl == false && other->GetOwner()->GetName() == L"BombEffect" && isBirdOn == false && mInvincibility <= 0.0f)
		{
			mAnimator->Play(L"DaoBubble", false);
			mState = eDaoState::BubbleMove;
			isColl = true;
		}
		//if (other->GetOwner()->GetName() == L"Bird" );
		//{
		//	mHP++;
		//	isBirdOn = true;
		//	mState = eBazziState::Idle;
		//	mAnimator->Play(L"BirdDown", true);
		//}
		if (other->GetOwner()->GetName() == L"BossBombEffect" && isBirdOn == true)
		{
			mHP--;
			object::Instantiate<Steam>(mPos, eLayerType::Effect);
			mAnimator->Play(L"DaoDownIdle", false);
			mState = eDaoState::Idle;
			isColl = true;
			isBirdOn = false;
			mInvincibility = 1.0f;
		}
		/*f (other->GetOwner()->GetName() == L"BombEffect" && isBirdOn == true)
		{
			mHP--;
			object::Instantiate<Steam>(mPos, eLayerType::Effect);
			mAnimator->Play(L"Bazziflash", false);
			mState = eDaoState::Idle;
			isColl = true;
			isBirdOn = false;
			mInvincibility = 1.0f;
		}*/
	}
	void Dao::OnCollisionStay(Collider* other)
	{
	}
	void Dao::OnCollisionExit(Collider* other)
	{
	}

	void Dao::move()
	{
		Vector2 idxpos = TileBomb::SetIndex(mPos);

		if (mSpeed >= maxSpeed)
		{
			mSpeed = maxSpeed;
		}

		if (SceneManager::GetIsDuo() == false)                                  ///////// 솔로플레이
		{
			if (Input::GetKeyUp(eKeyCode::LEFT) && isBirdOn == false)
			{
				mAnimator->Play(L"DaoLeftIdle", false);
				mState = eDaoState::Idle;
			}
			if (Input::GetKeyUp(eKeyCode::RIGHT) && isBirdOn == false)
			{
				mAnimator->Play(L"DaoRightIdle", false);
				mState = eDaoState::Idle;
			}
			if (Input::GetKeyUp(eKeyCode::UP) && isBirdOn == false)
			{
				mAnimator->Play(L"DaoUpIdle", false);
				mState = eDaoState::Idle;
			}
			if (Input::GetKeyUp(eKeyCode::DOWN) && isBirdOn == false)
			{
				mAnimator->Play(L"DaoDownIdle", false);
				mState = eDaoState::Idle;
			}

			Vector2 ColPos = collider->GetPos();
			Vector2 ColMidPos = ColPos + Vector2(TILE_SIZE_X / 2, TILE_SIZE_Y / 2);
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


			if (Input::GetKey(eKeyCode::LEFT) && isRPressed == false && isUPressed == false && isDPressed == false
				&& SceneManager::GetMapIndex()[ColLIdx.y][ColLIdx.x] != 4 && SceneManager::GetMapIndex()[ColLIdx.y][ColLIdx.x] != 2 && SceneManager::GetMapIndex()[ColLIdx.y][ColLIdx.x] != 1)
			{
				mLeftIdx = TileBomb::SetColIndex(Vector2(ColMidPos.x - TILE_SIZE_X, ColMidPos.y));
				mPos.x -= mPlayerSpeed * mSpeed * Time::DeltaTime();
			}
			if (Input::GetKey(eKeyCode::RIGHT) && isLPressed == false && isUPressed == false && isDPressed == false
				&& SceneManager::GetMapIndex()[ColRIdx.y][ColRIdx.x] != 4 && SceneManager::GetMapIndex()[ColRIdx.y][ColRIdx.x] != 2 && SceneManager::GetMapIndex()[ColRIdx.y][ColRIdx.x] != 1)
			{
				mRightIdx = TileBomb::SetColIndex(Vector2(ColMidPos.x + TILE_SIZE_X, ColMidPos.y));
				mPos.x += mPlayerSpeed * mSpeed * Time::DeltaTime();
			}
			if (Input::GetKey(eKeyCode::UP) && isRPressed == false && isLPressed == false && isDPressed == false
				&& SceneManager::GetMapIndex()[ColUIdx.y][ColUIdx.x] != 4 && SceneManager::GetMapIndex()[ColUIdx.y][ColUIdx.x] != 2 && SceneManager::GetMapIndex()[ColUIdx.y][ColUIdx.x] != 1)
			{
				mUpIdx = TileBomb::SetColIndex(Vector2(ColMidPos.x, ColMidPos.y - TILE_SIZE_Y));
				mPos.y -= mPlayerSpeed * mSpeed * Time::DeltaTime();
			}
			if (Input::GetKey(eKeyCode::DOWN) && isRPressed == false && isLPressed == false && isUPressed == false
				&& SceneManager::GetMapIndex()[ColDIdx.y][ColDIdx.x] != 4 && SceneManager::GetMapIndex()[ColDIdx.y][ColDIdx.x] != 2 && SceneManager::GetMapIndex()[ColDIdx.y][ColDIdx.x] != 1)
			{
				mDownIdx = TileBomb::SetColIndex(Vector2(ColMidPos.x, ColMidPos.y + TILE_SIZE_Y));
				mPos.y += mPlayerSpeed * mSpeed * Time::DeltaTime();
			}

			if (Input::GetKeyDown(eKeyCode::SPACEBAR))
			{
				mState = eDaoState::Shoot;
				//mAnimator->Play(L"downIdle", true);
			}

			if (Input::GetKeyDown(eKeyCode::LCTRL) && mItemState == eItemType::Shield)
			{
				isShieldOn = true;
				mInvincibility = 2;
				object::Instantiate<ShieldEffect>(mPos, eLayerType::Effect);
				mItemState = eItemType::None;
			}

			if (Input::GetKeyDown(eKeyCode::LEFT) && isRPressed == false && isUPressed == false && isDPressed == false && isBirdOn == false)
			{
				mAnimator->Play(L"DaoLeft", true);
			}
			if (Input::GetKeyDown(eKeyCode::RIGHT) && isLPressed == false && isUPressed == false && isDPressed == false && isBirdOn == false)
			{
				mAnimator->Play(L"DaoRight", true);
			}
			if (Input::GetKeyDown(eKeyCode::UP) && isRPressed == false && isLPressed == false && isDPressed == false && isBirdOn == false)
			{
				mAnimator->Play(L"DaoUp", true);
			}
			if (Input::GetKeyDown(eKeyCode::DOWN) && isRPressed == false && isLPressed == false && isUPressed == false && isBirdOn == false)
			{
				mAnimator->Play(L"DaoDown", true);
			}
		} // 솔로플레이   
		else if (SceneManager::GetIsDuo() == true && is1P == true)            ///////// 1P플레이
		{
			if (Input::GetKeyUp(eKeyCode::F) && isBirdOn == false)
			{
				mAnimator->Play(L"DaoLeftIdle", false);
				mState = eDaoState::Idle;
			}
			if (Input::GetKeyUp(eKeyCode::H) && isBirdOn == false)
			{
				mAnimator->Play(L"DaoRightIdle", false);
				mState = eDaoState::Idle;
			}
			if (Input::GetKeyUp(eKeyCode::T) && isBirdOn == false)
			{
				mAnimator->Play(L"DaoUpIdle", false);
				mState = eDaoState::Idle;
			}
			if (Input::GetKeyUp(eKeyCode::G) && isBirdOn == false)
			{
				mAnimator->Play(L"DaoDownIdle", false);
				mState = eDaoState::Idle;
			}

			Vector2 ColPos = collider->GetPos();
			Vector2 ColMidPos = ColPos + Vector2(TILE_SIZE_X / 2, TILE_SIZE_Y / 2);
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


			if (Input::GetKey(eKeyCode::F) && isRPressed == false && isUPressed == false && isDPressed == false
				&& SceneManager::GetMapIndex()[ColLIdx.y][ColLIdx.x] != 4 && SceneManager::GetMapIndex()[ColLIdx.y][ColLIdx.x] != 2 && SceneManager::GetMapIndex()[ColLIdx.y][ColLIdx.x] != 1)
			{
				mLeftIdx = TileBomb::SetColIndex(Vector2(ColMidPos.x - TILE_SIZE_X, ColMidPos.y));
				mPos.x -= mPlayerSpeed * mSpeed * Time::DeltaTime();
			}
			if (Input::GetKey(eKeyCode::H) && isLPressed == false && isUPressed == false && isDPressed == false
				&& SceneManager::GetMapIndex()[ColRIdx.y][ColRIdx.x] != 4 && SceneManager::GetMapIndex()[ColRIdx.y][ColRIdx.x] != 2 && SceneManager::GetMapIndex()[ColRIdx.y][ColRIdx.x] != 1)
			{
				mRightIdx = TileBomb::SetColIndex(Vector2(ColMidPos.x + TILE_SIZE_X, ColMidPos.y));
				mPos.x += mPlayerSpeed * mSpeed * Time::DeltaTime();
			}
			if (Input::GetKey(eKeyCode::T) && isRPressed == false && isLPressed == false && isDPressed == false
				&& SceneManager::GetMapIndex()[ColUIdx.y][ColUIdx.x] != 4 && SceneManager::GetMapIndex()[ColUIdx.y][ColUIdx.x] != 2 && SceneManager::GetMapIndex()[ColUIdx.y][ColUIdx.x] != 1)
			{
				mUpIdx = TileBomb::SetColIndex(Vector2(ColMidPos.x, ColMidPos.y - TILE_SIZE_Y));
				mPos.y -= mPlayerSpeed * mSpeed * Time::DeltaTime();
			}
			if (Input::GetKey(eKeyCode::G) && isRPressed == false && isLPressed == false && isUPressed == false
				&& SceneManager::GetMapIndex()[ColDIdx.y][ColDIdx.x] != 4 && SceneManager::GetMapIndex()[ColDIdx.y][ColDIdx.x] != 2 && SceneManager::GetMapIndex()[ColDIdx.y][ColDIdx.x] != 1)
			{
				mDownIdx = TileBomb::SetColIndex(Vector2(ColMidPos.x, ColMidPos.y + TILE_SIZE_Y));
				mPos.y += mPlayerSpeed * mSpeed * Time::DeltaTime();
			}

			if (Input::GetKeyDown(eKeyCode::LSHIFT))
			{
				mState = eDaoState::Shoot;
				//mAnimator->Play(L"downIdle", true);
			}

			if (Input::GetKeyDown(eKeyCode::LCTRL) && mItemState == eItemType::Shield)
			{
				isShieldOn = true;
				mInvincibility = 2;
				object::Instantiate<ShieldEffect>(mPos, eLayerType::Effect);
				mItemState = eItemType::None;
			}

			if (Input::GetKeyDown(eKeyCode::F) && isRPressed == false && isUPressed == false && isDPressed == false && isBirdOn == false)
			{
				mAnimator->Play(L"DaoLeft", true);
			}
			if (Input::GetKeyDown(eKeyCode::H) && isLPressed == false && isUPressed == false && isDPressed == false && isBirdOn == false)
			{
				mAnimator->Play(L"DaoRight", true);
			}
			if (Input::GetKeyDown(eKeyCode::T) && isRPressed == false && isLPressed == false && isDPressed == false && isBirdOn == false)
			{
				mAnimator->Play(L"DaoUp", true);
			}
			if (Input::GetKeyDown(eKeyCode::G) && isRPressed == false && isLPressed == false && isUPressed == false && isBirdOn == false)
			{
				mAnimator->Play(L"DaoDown", true);
			}
		} // 1인 플레이 // 1P플레이
		else if (SceneManager::GetIsDuo() == true && is1P == false)                   // 2p플레이
		{

			if (Input::GetKeyUp(eKeyCode::LEFT) && isBirdOn == false)
			{
				mAnimator->Play(L"DaoLeftIdle", false);
				mState = eDaoState::Idle;
			}
			if (Input::GetKeyUp(eKeyCode::RIGHT) && isBirdOn == false)
			{
				mAnimator->Play(L"DaoRightIdle", false);
				mState = eDaoState::Idle;
			}
			if (Input::GetKeyUp(eKeyCode::UP) && isBirdOn == false)
			{
				mAnimator->Play(L"DaoUpIdle", false);
				mState = eDaoState::Idle;
			}
			if (Input::GetKeyUp(eKeyCode::DOWN) && isBirdOn == false)
			{
				mAnimator->Play(L"DaoDownIdle", false);
				mState = eDaoState::Idle;
			}

			Vector2 ColPos = collider->GetPos();
			Vector2 ColMidPos = ColPos + Vector2(TILE_SIZE_X / 2, TILE_SIZE_Y / 2);
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


			if (Input::GetKey(eKeyCode::LEFT) && isRPressed == false && isUPressed == false && isDPressed == false
				&& SceneManager::GetMapIndex()[ColLIdx.y][ColLIdx.x] != 4 && SceneManager::GetMapIndex()[ColLIdx.y][ColLIdx.x] != 2 && SceneManager::GetMapIndex()[ColLIdx.y][ColLIdx.x] != 1)
			{
				mLeftIdx = TileBomb::SetColIndex(Vector2(ColMidPos.x - TILE_SIZE_X, ColMidPos.y));
				mPos.x -= mPlayerSpeed * mSpeed * Time::DeltaTime();
			}
			if (Input::GetKey(eKeyCode::RIGHT) && isLPressed == false && isUPressed == false && isDPressed == false
				&& SceneManager::GetMapIndex()[ColRIdx.y][ColRIdx.x] != 4 && SceneManager::GetMapIndex()[ColRIdx.y][ColRIdx.x] != 2 && SceneManager::GetMapIndex()[ColRIdx.y][ColRIdx.x] != 1)
			{
				mRightIdx = TileBomb::SetColIndex(Vector2(ColMidPos.x + TILE_SIZE_X, ColMidPos.y));
				mPos.x += mPlayerSpeed * mSpeed * Time::DeltaTime();
			}
			if (Input::GetKey(eKeyCode::UP) && isRPressed == false && isLPressed == false && isDPressed == false
				&& SceneManager::GetMapIndex()[ColUIdx.y][ColUIdx.x] != 4 && SceneManager::GetMapIndex()[ColUIdx.y][ColUIdx.x] != 2 && SceneManager::GetMapIndex()[ColUIdx.y][ColUIdx.x] != 1)
			{
				mUpIdx = TileBomb::SetColIndex(Vector2(ColMidPos.x, ColMidPos.y - TILE_SIZE_Y));
				mPos.y -= mPlayerSpeed * mSpeed * Time::DeltaTime();
			}
			if (Input::GetKey(eKeyCode::DOWN) && isRPressed == false && isLPressed == false && isUPressed == false
				&& SceneManager::GetMapIndex()[ColDIdx.y][ColDIdx.x] != 4 && SceneManager::GetMapIndex()[ColDIdx.y][ColDIdx.x] != 2 && SceneManager::GetMapIndex()[ColDIdx.y][ColDIdx.x] != 1)
			{
				mDownIdx = TileBomb::SetColIndex(Vector2(ColMidPos.x, ColMidPos.y + TILE_SIZE_Y));
				mPos.y += mPlayerSpeed * mSpeed * Time::DeltaTime();
			}

			if (Input::GetKeyDown(eKeyCode::RSHIFT))
			{
				mState = eDaoState::Shoot;
				//mAnimator->Play(L"downIdle", true);
			}

			if (Input::GetKeyDown(eKeyCode::RCTRL) && mItemState == eItemType::Shield)
			{
				isShieldOn = true;
				mInvincibility = 2;
				object::Instantiate<ShieldEffect>(mPos, eLayerType::Effect);
				mItemState = eItemType::None;
			}

			if (Input::GetKeyDown(eKeyCode::F) && isRPressed == false && isUPressed == false && isDPressed == false && isBirdOn == false)
			{
				mAnimator->Play(L"DaoLeft", true);
			}
			if (Input::GetKeyDown(eKeyCode::H) && isLPressed == false && isUPressed == false && isDPressed == false && isBirdOn == false)
			{
				mAnimator->Play(L"DaoRight", true);
			}
			if (Input::GetKeyDown(eKeyCode::T) && isRPressed == false && isLPressed == false && isDPressed == false && isBirdOn == false)
			{
				mAnimator->Play(L"DaoUp", true);
			}
			if (Input::GetKeyDown(eKeyCode::G) && isRPressed == false && isLPressed == false && isUPressed == false && isBirdOn == false)
			{
				mAnimator->Play(L"DaoDown", true);
			}
		} // 2인 플레이 //    // 2P플레이

		tr->SetPos(mPos);
	}
	void Dao::shoot()
	{
		IdxPos = TileBomb::SetIndex(tr->GetPos());
		if (mBomb > maxBomb)
		{
			mBomb = maxBomb;
		}
		if (SceneManager::GetIsDuo() == false)
		{

			if (Input::GetKey(eKeyCode::SPACEBAR) && SceneManager::GetMapIndex()[IdxPos.y][IdxPos.x] == 0 && mBomb <= maxBomb && mClick < mBomb)
			{
				mClick++;
				object::Instantiate<BaseBomb>(TileBomb::SetPos(tr->GetPos()), eLayerType::Bomb);
				IdxPos = TileBomb::SetIndex(tr->GetPos());
				SceneManager::GetMapIndex()[IdxPos.y][IdxPos.x] = 3; // 13 15
				SceneManager::GetBombIndex()[IdxPos.y][IdxPos.x] = 2; // 폭탄 벨류는 2
			}
		}
		else if (SceneManager::GetIsDuo() == true && is1P == true)
		{
			if (Input::GetKey(eKeyCode::LSHIFT) && SceneManager::GetMapIndex()[IdxPos.y][IdxPos.x] == 0 && mBomb <= maxBomb && mClick < mBomb)
			{
				mClick++;
				object::Instantiate<BaseBomb>(TileBomb::SetPos(tr->GetPos()), eLayerType::Bomb);
				IdxPos = TileBomb::SetIndex(tr->GetPos());
				SceneManager::GetMapIndex()[IdxPos.y][IdxPos.x] = 3; // 13 15
				SceneManager::GetBombIndex()[IdxPos.y][IdxPos.x] = 2; // 폭탄 벨류는 2
			}
		}
		else if (SceneManager::GetIsDuo() == true && is1P == false)
		{
			if (Input::GetKey(eKeyCode::RSHIFT) && SceneManager::GetMapIndex()[IdxPos.y][IdxPos.x] == 0 && mBomb <= maxBomb && mClick < mBomb)
			{
				mClick++;
				object::Instantiate<BaseBomb>(TileBomb::SetPos(tr->GetPos()), eLayerType::Bomb);
				IdxPos = TileBomb::SetIndex(tr->GetPos());
				SceneManager::GetMapIndex()[IdxPos.y][IdxPos.x] = 3; // 13 15
				SceneManager::GetBombIndex()[IdxPos.y][IdxPos.x] = 2; // 폭탄 벨류는 2
			}
		}
		if (isBirdOn == false)
		{
			mState = eDaoState::Move;
		}
		else if (isBirdOn == true)
		{
			mState = eDaoState::BirdOn;
		}
	}
	void Dao::death()
	{
	}
	void Dao::idle()
	{
		isLPressed = false;
		isRPressed = false;
		isUPressed = false;
		isDPressed = false;
		if (SceneManager::GetIsDuo() == false)
		{
			if (Input::GetKey(eKeyCode::LEFT) && isBirdOn == false)
			{
				isLPressed = true;
				mAnimator->Play(L"DaoLeft", true);
				mState = eDaoState::Move;
			}
			if (Input::GetKey(eKeyCode::RIGHT) && isBirdOn == false)
			{
				isRPressed = true;
				mAnimator->Play(L"DaoRight", true);
				mState = eDaoState::Move;
			}
			if (Input::GetKey(eKeyCode::UP) && isBirdOn == false)
			{
				isUPressed = true;
				mAnimator->Play(L"DaoUp", true);
				mState = eDaoState::Move;
			}
			if (Input::GetKey(eKeyCode::DOWN) && isBirdOn == false)
			{
				isDPressed = true;
				mAnimator->Play(L"DaoDown", true);
				mState = eDaoState::Move;
			}

			//if (Input::GetKey(eKeyCode::LEFT) && isBirdOn == true)
			//{
			//	isLPressed = true;
			//	mAnimator->Play(L"BirdLeft", true);
			//	mState = eDaoState::BirdOn;
			//}
			//if (Input::GetKey(eKeyCode::RIGHT) && isBirdOn == true)
			//{
			//	isRPressed = true;
			//	mAnimator->Play(L"BirdRight", true);
			//	mState = eDaoState::BirdOn;
			//}
			//if (Input::GetKey(eKeyCode::UP) && isBirdOn == true)
			//{
			//	isUPressed = true;
			//	mAnimator->Play(L"BirdUp", true);
			//	mState = eDaoState::BirdOn;
			//}
			//if (Input::GetKey(eKeyCode::DOWN) && isBirdOn == true)
			//{
			//	isDPressed = true;
			//	mAnimator->Play(L"BirdDown", true);
			//	mState = eDaoState::BirdOn;
			//}

			if (Input::GetKeyDown(eKeyCode::LCTRL) && mItemState == eItemType::Shield)
			{
				isShieldOn = true;
				mInvincibility = 2;
				mItemState = eItemType::None;
				object::Instantiate<ShieldEffect>(mPos, eLayerType::Effect);
			}

			if (Input::GetKey(eKeyCode::SPACEBAR))
			{
				mState = eDaoState::Shoot;
				//mAnimator->Play(L"downIdle", true);
			}
		}
		else if (SceneManager::GetIsDuo() == true && is1P == true)
		{
			if (Input::GetKey(eKeyCode::F) && isBirdOn == false)
			{
				isLPressed = true;
				mAnimator->Play(L"DaoLeft", true);
				mState = eDaoState::Move;
			}
			if (Input::GetKey(eKeyCode::H) && isBirdOn == false)
			{
				isRPressed = true;
				mAnimator->Play(L"DaoRight", true);
				mState = eDaoState::Move;
			}
			if (Input::GetKey(eKeyCode::T) && isBirdOn == false)
			{
				isUPressed = true;
				mAnimator->Play(L"DaoUp", true);
				mState = eDaoState::Move;
			}
			if (Input::GetKey(eKeyCode::G) && isBirdOn == false)
			{
				isDPressed = true;
				mAnimator->Play(L"DaoDown", true);
				mState = eDaoState::Move;
			}

			//if (Input::GetKey(eKeyCode::F) && isBirdOn == true)
			//{
			//	isLPressed = true;
			//	mAnimator->Play(L"BirdLeft", true);
			//	mState = eDaoState::BirdOn;
			//}
			//if (Input::GetKey(eKeyCode::H) && isBirdOn == true)
			//{
			//	isRPressed = true;
			//	mAnimator->Play(L"BirdRight", true);
			//	mState = eDaoState::BirdOn;
			//}
			//if (Input::GetKey(eKeyCode::T) && isBirdOn == true)
			//{
			//	isUPressed = true;
			//	mAnimator->Play(L"BirdUp", true);
			//	mState = eDaoState::BirdOn;
			//}
			//if (Input::GetKey(eKeyCode::G) && isBirdOn == true)
			//{
			//	isDPressed = true;
			//	mAnimator->Play(L"BirdDown", true);
			//	mState = eDaoState::BirdOn;
			//}

			if (Input::GetKeyDown(eKeyCode::LCTRL) && mItemState == eItemType::Shield)
			{
				isShieldOn = true;
				mInvincibility = 2;
				mItemState = eItemType::None;
				object::Instantiate<ShieldEffect>(mPos, eLayerType::Effect);
			}

			if (Input::GetKey(eKeyCode::LSHIFT))
			{
				mState = eDaoState::Shoot;
				//mAnimator->Play(L"downIdle", true);
			}
		}
		else if (SceneManager::GetIsDuo() == true && is1P == false)
		{
			if (Input::GetKey(eKeyCode::LEFT) && isBirdOn == false)
			{
				isLPressed = true;
				mAnimator->Play(L"DaoLeft", true);
				mState = eDaoState::Move;
			}
			if (Input::GetKey(eKeyCode::RIGHT) && isBirdOn == false)
			{
				isRPressed = true;
				mAnimator->Play(L"DaoRight", true);
				mState = eDaoState::Move;
			}
			if (Input::GetKey(eKeyCode::UP) && isBirdOn == false)
			{
				isUPressed = true;
				mAnimator->Play(L"DaoUp", true);
				mState = eDaoState::Move;
			}
			if (Input::GetKey(eKeyCode::DOWN) && isBirdOn == false)
			{
				isDPressed = true;
				mAnimator->Play(L"DaoDown", true);
				mState = eDaoState::Move;
			}

			//if (Input::GetKey(eKeyCode::LEFT) && isBirdOn == true)
			//{
			//	isLPressed = true;
			//	mAnimator->Play(L"BirdLeft", true);
			//	mState = eDaoState::BirdOn;
			//}
			//if (Input::GetKey(eKeyCode::RIGHT) && isBirdOn == true)
			//{
			//	isRPressed = true;
			//	mAnimator->Play(L"BirdRight", true);
			//	mState = eDaoState::BirdOn;
			//}
			//if (Input::GetKey(eKeyCode::UP) && isBirdOn == true)
			//{
			//	isUPressed = true;
			//	mAnimator->Play(L"BirdUp", true);
			//	mState = eDaoState::BirdOn;
			//}
			//if (Input::GetKey(eKeyCode::DOWN) && isBirdOn == true)
			//{
			//	isDPressed = true;
			//	mAnimator->Play(L"BirdDown", true);
			//	mState = eDaoState::BirdOn;
			//}

			if (Input::GetKeyDown(eKeyCode::RCTRL) && mItemState == eItemType::Shield)
			{
				isShieldOn = true;
				mInvincibility = 2;
				mItemState = eItemType::None;
				object::Instantiate<ShieldEffect>(mPos, eLayerType::Effect);
			}

			if (Input::GetKey(eKeyCode::RSHIFT))
			{
				mState = eDaoState::Shoot;
				//mAnimator->Play(L"downIdle", true);
			}
		}


	}
	void Dao::bubble()
	{
	}
	void Dao::bubblemove()
	{
		mInvincibility = 2;
		mPos = tr->GetPos();

		if (mPos.x <= 30.0f)
		{
			mPos.x == 30.0f;
		}

		if (mPos.x >= 900.0f)
		{
			mPos.x == 900.0f;
		}

		if (mPos.y <= 60.0f)
		{
			mPos.y == 60.0f;
		}

		if (mPos.y >= 780.0f)
		{
			mPos.y == 780.0f;
		}

		if (SceneManager::GetIsDuo() == false)
		{
			if (Input::GetKey(eKeyCode::LEFT)
				/*&& pos.x >= 30.0f && pos.x <= 900.0f && pos.y >= 60.0f && pos.y <= 780.0f*/)
			{
				//isLPressed = true;
				mPos.x -= 50.0f * Time::DeltaTime();
			}
			else if (Input::GetKey(eKeyCode::RIGHT)
				/*&& pos.x >= 30.0f && pos.x <= 900.0f && pos.y >= 60.0f && pos.y <= 780.0f*/)
			{
				//isRPressed = true;
				mPos.x += 50.0f * Time::DeltaTime();
			}
			else if (Input::GetKey(eKeyCode::UP)
				/*&& pos.x >= 30.0f && pos.x <= 900.0f && pos.y >= 60.0f && pos.y <= 780.0f*/)
			{
				//isUPressed = true;
				mPos.y -= 50.0f * Time::DeltaTime();
			}
			else if (Input::GetKey(eKeyCode::DOWN)
				/*&& pos.x >= 30.0f && pos.x <= 900.0f && pos.y >= 60.0f && pos.y <= 780.0f*/)
			{
				//isDPressed = true;
				mPos.y += 50.0f * Time::DeltaTime();
			}

			if (Input::GetKey(eKeyCode::LCTRL) && mItemState == eItemType::Needle
				/*&& pos.x >= 30.0f && pos.x <= 900.0f && pos.y >= 60.0f && pos.y <= 780.0f*/)
			{
				isColl = true;
				mItemState = eItemType::None;
				mAnimator->Play(L"DaoLive", false);
			}
		}
		else if (SceneManager::GetIsDuo() == true && is1P == true)
		{
			if (Input::GetKey(eKeyCode::F)
				/*&& pos.x >= 30.0f && pos.x <= 900.0f && pos.y >= 60.0f && pos.y <= 780.0f*/)
			{
				//isLPressed = true;
				mPos.x -= 50.0f * Time::DeltaTime();
			}
			else if (Input::GetKey(eKeyCode::H)
				/*&& pos.x >= 30.0f && pos.x <= 900.0f && pos.y >= 60.0f && pos.y <= 780.0f*/)
			{
				//isRPressed = true;
				mPos.x += 50.0f * Time::DeltaTime();
			}
			else if (Input::GetKey(eKeyCode::T)
				/*&& pos.x >= 30.0f && pos.x <= 900.0f && pos.y >= 60.0f && pos.y <= 780.0f*/)
			{
				//isUPressed = true;
				mPos.y -= 50.0f * Time::DeltaTime();
			}
			else if (Input::GetKey(eKeyCode::G)
				/*&& pos.x >= 30.0f && pos.x <= 900.0f && pos.y >= 60.0f && pos.y <= 780.0f*/)
			{
				//isDPressed = true;
				mPos.y += 50.0f * Time::DeltaTime();
			}

			if (Input::GetKey(eKeyCode::LCTRL) && mItemState == eItemType::Needle
				/*&& pos.x >= 30.0f && pos.x <= 900.0f && pos.y >= 60.0f && pos.y <= 780.0f*/)
			{
				isColl = true;
				mItemState = eItemType::None;
				mAnimator->Play(L"DaoLive", false);
			}
		}
		else if (SceneManager::GetIsDuo() == true && is1P == false)
		{

			if (Input::GetKey(eKeyCode::LEFT)
				/*&& pos.x >= 30.0f && pos.x <= 900.0f && pos.y >= 60.0f && pos.y <= 780.0f*/)
			{
				//isLPressed = true;
				mPos.x -= 50.0f * Time::DeltaTime();
			}
			else if (Input::GetKey(eKeyCode::RIGHT)
				/*&& pos.x >= 30.0f && pos.x <= 900.0f && pos.y >= 60.0f && pos.y <= 780.0f*/)
			{
				//isRPressed = true;
				mPos.x += 50.0f * Time::DeltaTime();
			}
			else if (Input::GetKey(eKeyCode::UP)
				/*&& pos.x >= 30.0f && pos.x <= 900.0f && pos.y >= 60.0f && pos.y <= 780.0f*/)
			{
				//isUPressed = true;
				mPos.y -= 50.0f * Time::DeltaTime();
			}
			else if (Input::GetKey(eKeyCode::DOWN)
				/*&& pos.x >= 30.0f && pos.x <= 900.0f && pos.y >= 60.0f && pos.y <= 780.0f*/)
			{
				//isDPressed = true;
				mPos.y += 50.0f * Time::DeltaTime();
			}

			if (Input::GetKey(eKeyCode::RCTRL) && mItemState == eItemType::Needle
				/*&& pos.x >= 30.0f && pos.x <= 900.0f && pos.y >= 60.0f && pos.y <= 780.0f*/)
			{
				isColl = true;
				mItemState = eItemType::None;
				mAnimator->Play(L"DaoLive", false);
			}
		}
	}
	void Dao::revive()
	{
	}
	void Dao::nomove()
	{
		mInvincibility = 3.0f;
	}
	void Dao::trapCompleteEvent()
	{
		mState = eDaoState::NoMove;
		mAnimator->Play(L"DaoDie", false);
	}
	void Dao::dieCompleteEvent()
	{
		mInvincibility = 3.0f;
		mHP = -1;
	}
	void Dao::liveCompleteEvent()
	{
		mHP = 1;
		mState = eDaoState::Move;
		mAnimator->Play(L"DaoDownIdle", false);
	}
	void Dao::hitComPleteEvent()
	{
		mAnimator->Play(L"DaoDownIdle", false);
	}
	void Dao::birdmove()
	{
	}
	void Dao::checkInVTime()
	{
		if (isColl == true)
		{
			mInvincibility -= Time::DeltaTime();

			if (mInvincibility < 0.0f)
			{
				isColl = false;
			}
		}

		if (isShieldOn == true)
		{
			mInvincibility -= Time::DeltaTime();


			if (mInvincibility < 0.0f)
			{
				isShieldOn = false;
			}
		}
	}

	void Dao::Reset()
	{
		mState = eDaoState::Idle;
		mAnimator->Play(L"DaoDownIdle", false);
		mHP = 1; // 체력 
		mBomb = 1; // 폭탄
		mWaterCourse = 2; // 물줄기
		mSpeed = 5.0f; // 속도
		maxSpeed = 9.0f;
		maxBomb = 6;
		maxWaterCourse = 7;
		mTime = 0;
		mPlayerSpeed = 50;
		mItemCnt = 0;
		mInvincibility = 1.5f;
		mItemState = eItemType::None;
		isPushPossible = false;
		isColl = true;
		mClick = 0;
	}
}