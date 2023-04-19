#include "tyBazzi.h"
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
	//std::vector<std::vector<int>> Bazzi:: mapIndex;
	Bazzi::Bazzi()
		: mHP(1) // 체력 
		, mItemState(eItemType::None)
		, mBomb(1) // 폭탄
		, mWaterCourse(2) // 물줄기
		, mSpeed(5.0f) // 속도
		, maxSpeed(9.0f)
		, maxBomb(6)
		, maxWaterCourse(7)
		, mPlayerSpeed(50)
		, mInvincibility(1.5f)
		, mItemCnt(0)
		, maxItemCnt(1) // 최대 아이템 보유 갯수
		, isColl(true)
		
	{
		
	}
	Bazzi::~Bazzi()
	{
	}
	void Bazzi::Initialize()
	{
	/*	isBirdOn = true;*/
		//isPushPossible = true;
		Transform* tr = GetComponent<Transform>();
	
		tr->SetScale(Vector2(1.18f, 1.18f));
		SetName(L"Bazzi");
		Image* mUpImage = Resources::Load<Image>(L"BazziU", L"..\\Resources\\Bazzi\\up.bmp");
		Image* mLeftImage = Resources::Load<Image>(L"BazziL", L"..\\Resources\\Bazzi\\left.bmp");
		Image* mRightImage = Resources::Load<Image>(L"BazziR", L"..\\Resources\\Bazzi\\right.bmp");
		Image* mDownImage = Resources::Load<Image>(L"BazziD", L"..\\Resources\\Bazzi\\down.bmp");
		Image* mReadyImage = Resources::Load<Image>(L"BazziReady", L"..\\Resources\\Bazzi\\ready.bmp");
		Image* mDieImage = Resources::Load<Image>(L"BazziDie", L"..\\Resources\\Bazzi\\die.bmp");
		Image* mTrapeImage = Resources::Load<Image>(L"BazziTrap", L"..\\Resources\\Bazzi\\trap.bmp");
		Image* mLiveImage = Resources::Load<Image>(L"BazziLive", L"..\\Resources\\Bazzi\\live.bmp");
		Image* mFlashImage = Resources::Load<Image>(L"BazziFlash", L"..\\Resources\\Bazzi\\flash.bmp");
		mAnimator = AddComponent<Animator>();
		
		mAnimator->CreateAnimation(L"Bazziup", mUpImage, Vector2::Zero, 8, 1, 8, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"Bazzidown", mDownImage, Vector2::Zero, 8, 1, 8, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"Bazzileft", mLeftImage, Vector2::Zero, 6, 1, 6, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"Bazziright", mRightImage, Vector2::Zero, 6, 1, 6, Vector2::Zero, 0.1);

		mAnimator->CreateAnimation(L"BazziupIdle", mUpImage, Vector2::Zero, 8, 1, 1, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"BazzidownIdle", mDownImage, Vector2::Zero, 8, 1, 1, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"BazzileftIdle", mLeftImage, Vector2::Zero, 6, 1, 1, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"BazzirightIdle", mRightImage, Vector2::Zero, 6, 1, 1, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"Bazziready", mReadyImage, Vector2::Zero, 18, 1, 17, Vector2(0.0f, -10.0f), 0.07); // 오프셋 조절해서 ready 모션 바꿈 x,y축 잘 확인하기

		mAnimator->CreateAnimation(L"Bazzidie", mDieImage, Vector2::Zero, 13, 1, 13, Vector2(-15.0f, -30.0f), 0.15);
		mAnimator->CreateAnimation(L"Bazzitrap", mTrapeImage, Vector2::Zero, 13, 1, 13, Vector2(-15.0f, - 30.0f), 0.18);
		mAnimator->CreateAnimation(L"Bazzilive", mLiveImage, Vector2::Zero, 5, 1, 5, Vector2(-15.0f, -30.0f), 0.1);
		mAnimator->CreateAnimation(L"Bazziflash", mFlashImage, Vector2::Zero, 4, 1, 1, Vector2::Zero, 0.1);

		mAnimator->CreateAnimations(L"..\\Resources\\Bazzi\\Bird\\Down", Vector2(0.0f, -30.0f), 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Bazzi\\Bird\\DownIdle", Vector2(0.0f, -30.0f), 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Bazzi\\Bird\\Right", Vector2(0.0f, -30.0f), 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Bazzi\\Bird\\RightIdle", Vector2(0.0f, -30.0f), 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Bazzi\\Bird\\Left", Vector2(0.0f, -30.0f), 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Bazzi\\Bird\\LeftIdle", Vector2(0.0f, -30.0f), 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Bazzi\\Bird\\Up", Vector2(0.0f, -30.0f), 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Bazzi\\Bird\\UpIdle", Vector2(0.0f, -30.0f), 0.1f);


		mAnimator->GetCompleteEvent(L"Bazzitrap") = std::bind(&Bazzi::trapCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"Bazzidie") = std::bind(&Bazzi::dieCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"Bazzilive") = std::bind(&Bazzi::liveCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"Bazziflash") = std::bind(&Bazzi::hitComPleteEvent, this);
		mAnimator->Play(L"Bazziready", false);
		
		collider = AddComponent<Collider>();
		collider->SetCenter(Vector2(12.0f, 25.0f));
		collider->SetSize(Vector2(55.0f, 55.0f));
	
		mState = eBazziState::Idle;

		//mAnimator->Play(L"downIlde", true);^
		GameObject::Initialize();
	}
	void Bazzi::Update()
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
			case ty::Bazzi::eBazziState::Move:
				move();
				break;
			case ty::Bazzi::eBazziState::Shoot:
				shoot();
				break;
			case ty::Bazzi::eBazziState::Death:
				death();
				break;
			case ty::Bazzi::eBazziState::Idle:
				idle();
				break;
			case ty::Bazzi::eBazziState::Bubble:
				bubble();
				break;
			case ty::Bazzi::eBazziState::BubbleMove:
				bubblemove();
				break;
			//case ty::Bazzi::eBazziState::Revive:
			//	revive();
			//	break;
			case ty::Bazzi::eBazziState::NoMove:
				nomove();
				break;
			case ty::Bazzi::eBazziState::BirdOn:
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
			object::Instantiate<Potion>(TileBomb::SetPos(Vector2(tr->GetPos().x , tr->GetPos().y + TILE_SIZE_Y)), eLayerType::Item);
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
	void Bazzi::Render(HDC hdc)
	{
		GameObject::Render(hdc);
		
	}
	void Bazzi::Release()
	{
		GameObject::Release();
	}
	void Bazzi::OnCollisionEnter(Collider* other)
	{
		if (isColl == false && other->GetOwner()->GetName() == L"Monster"  && mInvincibility <= 0.0f && other->GetOwner()->GetState() == eState::Active )
		{
			mInvincibility = 3.0f;
			mAnimator->Play(L"Bazzidie", false);
			mState = eBazziState::Death;
			isColl = true;
		}
		if (isColl == false && other->GetOwner()->GetName() == L"Boss" && mInvincibility <= 0.0f)
		{
			mAnimator->Play(L"Bazzidie", false);
			mState = eBazziState::Death;
			isColl = true;
		}
		if (isColl == false && other->GetOwner()->GetName() ==L"BossBombEffect" && isBirdOn == false && mInvincibility <= 0.0f)
		{
			mAnimator->Play(L"Bazzitrap", false);
			mState = eBazziState::BubbleMove;
			isColl = true;
		}
		if (isColl == false && other->GetOwner()->GetName() == L"BombEffect" && isBirdOn == false && mInvincibility <= 0.0f)
		{
			mAnimator->Play(L"Bazzitrap", false);
			mState = eBazziState::BubbleMove;
			isColl = true;
		}
		//if (other->GetOwner()->GetName() == L"Bird" );
		//{
		//	mHP++;
		//	isBirdOn = true;
		//	mState = eBazziState::Idle;
		//	mAnimator->Play(L"BirdDown", true);
		//}
		if(other->GetOwner()->GetName() == L"BossBombEffect" && isBirdOn == true)
		{
			mHP--;
			object::Instantiate<Steam>(mPos, eLayerType::Effect);
			mAnimator->Play(L"BazzidownIdle", false);
			mState = eBazziState::Idle;
			isColl = true;
			isBirdOn = false;
			mInvincibility = 1.0f;
		}
		if (other->GetOwner()->GetName() == L"BombEffect" && isBirdOn == true)
		{
			mHP--;
			object::Instantiate<Steam>(mPos, eLayerType::Effect);
			mAnimator->Play(L"Bazziflash", false);
			mState = eBazziState::Idle;
			isColl = true;
			isBirdOn = false;
			mInvincibility = 1.0f;
		}
	}
	void Bazzi::OnCollisionStay(Collider* other)
	{
		//isDead = true;
		//mState = eBazziState::Death;
	}
	void Bazzi::OnCollisionExit(Collider* other)
	{
		/*maxHP
		mState = eBazziState::Idle;*/
	}
	void Bazzi::move()
	{
		Vector2 idxpos = TileBomb::SetIndex(mPos);

		if (mSpeed >= maxSpeed)
		{
			mSpeed = maxSpeed;
		}

		if (Input::GetKeyUp(eKeyCode::LEFT) && isBirdOn == false)
		{
			mAnimator->Play(L"BazzileftIdle", false);
			mState = eBazziState::Idle;
		}
		if (Input::GetKeyUp(eKeyCode::RIGHT) && isBirdOn == false)
		{
			mAnimator->Play(L"BazzirightIdle", false);
			mState = eBazziState::Idle;
		}
		if (Input::GetKeyUp(eKeyCode::UP) && isBirdOn == false)
		{
			mAnimator->Play(L"BazziupIdle", false);
			mState = eBazziState::Idle;
		}
		if (Input::GetKeyUp(eKeyCode::DOWN) && isBirdOn == false)
		{	
			mAnimator->Play(L"BazzidownIdle", false);
			mState = eBazziState::Idle;
		}
	
		Vector2 ColPos = collider->GetPos();
		Vector2 ColMidPos = ColPos + Vector2(TILE_SIZE_X / 2, TILE_SIZE_Y / 2);
		Vector2 ColRIdx = TileBomb::SetColIndex(ColMidPos + Vector2(31.0f,0.0f));
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
			&& SceneManager::GetMapIndex()[ColLIdx.y][ColLIdx.x] != 4 && SceneManager::GetMapIndex()[ColLIdx.y][ColLIdx.x] != 2 && SceneManager::GetMapIndex()[ColLIdx.y][ColLIdx.x] != 1 )
		{
			mLeftIdx = TileBomb::SetColIndex(Vector2(ColMidPos.x - TILE_SIZE_X, ColMidPos.y));
			mPos.x -= mPlayerSpeed * mSpeed  * Time::DeltaTime();
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
			&& SceneManager::GetMapIndex()[ColDIdx.y][ColDIdx.x] != 4 && SceneManager::GetMapIndex()[ColDIdx.y][ColDIdx.x] != 2 && SceneManager::GetMapIndex()[ColDIdx.y][ColDIdx.x] != 1 )
		{
			mDownIdx = TileBomb::SetColIndex(Vector2(ColMidPos.x , ColMidPos.y  +TILE_SIZE_Y));
			mPos.y += mPlayerSpeed * mSpeed * Time::DeltaTime();
		}

		if (Input::GetKeyDown(eKeyCode::SPACEBAR))
		{
			mState = eBazziState::Shoot;
			//mAnimator->Play(L"downIdle", true);
		}

		if (Input::GetKeyDown(eKeyCode::CTRL) && mItemState == eItemType::Shield)
		{
			isShieldOn = true;
			mInvincibility = 2;
			object::Instantiate<ShieldEffect>(mPos, eLayerType::Effect);
			mItemState = eItemType::None;
		}

		if (Input::GetKeyDown(eKeyCode::LEFT) && isRPressed == false && isUPressed == false && isDPressed == false && isBirdOn == false)
		{
			mAnimator->Play(L"Bazzileft", true);
		}
		if (Input::GetKeyDown(eKeyCode::RIGHT) && isLPressed == false && isUPressed == false && isDPressed == false && isBirdOn == false)
		{
			mAnimator->Play(L"Bazziright", true);
		}
		if (Input::GetKeyDown(eKeyCode::UP) && isRPressed == false && isLPressed == false && isDPressed == false && isBirdOn == false)
		{
			mAnimator->Play(L"Bazziup", true);
		}
		if (Input::GetKeyDown(eKeyCode::DOWN) && isRPressed == false && isLPressed == false && isUPressed == false && isBirdOn == false)
		{
			mAnimator->Play(L"Bazzidown", true);
		}

		tr->SetPos(mPos);
	}
	void Bazzi::shoot()
 	{
		IdxPos = TileBomb::SetIndex(tr->GetPos());
		if (mBomb > maxBomb)
		{
			mBomb = maxBomb;
		}
		if (Input::GetKey(eKeyCode::SPACEBAR) && SceneManager::GetMapIndex()[IdxPos.y][IdxPos.x] == 0 && mBomb <= maxBomb && mClick < mBomb)
		{
			mClick++;
			object::Instantiate<BaseBomb>(TileBomb::SetPos(tr->GetPos()), eLayerType::Bomb);
			IdxPos = TileBomb::SetIndex(tr->GetPos());
			SceneManager::GetMapIndex()[IdxPos.y][IdxPos.x] = 3; // 13 15
		}
		if (isBirdOn == false)
		{
			mState = eBazziState::Move;
		}
		else if (isBirdOn == true)
		{
			mState = eBazziState::BirdOn;
		}
	}
	void Bazzi::death()
	{
	

	}
	void Bazzi::idle()
	{
		isLPressed = false;
		isRPressed = false;
		isUPressed = false;
		isDPressed = false;
		if (Input::GetKey(eKeyCode::LEFT) && isBirdOn == false)
		{
			isLPressed = true;
			mAnimator->Play(L"Bazzileft", true);
			mState = eBazziState::Move;
		}
		if (Input::GetKey(eKeyCode::RIGHT) && isBirdOn == false)
		{
			isRPressed = true;
			mAnimator->Play(L"Bazziright", true);
			mState = eBazziState::Move;
		}
		if (Input::GetKey(eKeyCode::UP) && isBirdOn == false)
		{
			isUPressed = true;
			mAnimator->Play(L"Bazziup", true);
			mState = eBazziState::Move;
		}
		if(Input::GetKey(eKeyCode::DOWN) && isBirdOn == false)
		{
			isDPressed = true;
			mAnimator->Play(L"Bazzidown", true);
			mState = eBazziState::Move;
		}

		if (Input::GetKey(eKeyCode::LEFT) && isBirdOn == true)
		{
			isLPressed = true;
			mAnimator->Play(L"BirdLeft", true);
			mState = eBazziState::BirdOn;
		}
		if (Input::GetKey(eKeyCode::RIGHT) && isBirdOn == true)
		{
			isRPressed = true;
			mAnimator->Play(L"BirdRight", true);
			mState = eBazziState::BirdOn;
		}
		if (Input::GetKey(eKeyCode::UP) && isBirdOn == true)
		{
			isUPressed = true;
			mAnimator->Play(L"BirdUp", true);
			mState = eBazziState::BirdOn;
		}
		if (Input::GetKey(eKeyCode::DOWN) && isBirdOn == true)
		{
			isDPressed = true;
			mAnimator->Play(L"BirdDown", true);
			mState = eBazziState::BirdOn;
		}

		if (Input::GetKeyDown(eKeyCode::CTRL) && mItemState == eItemType::Shield)
		{
			isShieldOn = true;
			mInvincibility = 2;
			mItemState = eItemType::None;
			object::Instantiate<ShieldEffect>(mPos, eLayerType::Effect);
		}

		if (Input::GetKey(eKeyCode::SPACEBAR))
		{
			mState = eBazziState::Shoot;
			//mAnimator->Play(L"downIdle", true);
		}

	}
	void Bazzi::bubble()
	{
		//mAnimator->Play(L"Bazzidie", false);
	}
	void Bazzi::bubblemove()
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

		if (Input::GetKey(eKeyCode::CTRL) && mItemState == eItemType::Needle
			/*&& pos.x >= 30.0f && pos.x <= 900.0f && pos.y >= 60.0f && pos.y <= 780.0f*/)
		{
			isColl = true;
			mItemState = eItemType::None;
			mAnimator->Play(L"Bazzilive", false);
		}

		tr->SetPos(mPos);
	}
	void Bazzi::revive()
	{
		mRandomPosx = 80.0f;
		mHP = 1;
		mRandomPosy = 100.0f;
		tr->SetPos(Vector2(mRandomPosx, mRandomPosy));
		mState = eBazziState::Idle;
		mAnimator->Play(L"Bazziready", false);
		mTime = 0;
		
	}
	void Bazzi::nomove()
	{
		mInvincibility = 3.0f;
	}
	
	void Bazzi::trapCompleteEvent(/*const Cuphead* this*/) // 애니메이션 동작이 끝나면 실행되도록 할 수 있다.
	{
		mState = eBazziState::NoMove;
		mAnimator->Play(L"Bazzidie", false);
		
	}
	void Bazzi::dieCompleteEvent()
	{
		mInvincibility = 3.0f;
		mHP = -1;
	}
	void Bazzi::liveCompleteEvent()
	{
		mHP = 1;
		mState = eBazziState::Move;
		mAnimator->Play(L"BazzidownIdle", false);
	}
	void Bazzi::hitComPleteEvent()
	{
		
		mAnimator->Play(L"BazzidownIdle", false);
	}
	void Bazzi::birdmove()
	{
		Vector2 idxpos = TileBomb::SetIndex(mPos);

		if (mSpeed >= maxSpeed)
		{
			mSpeed = maxSpeed;
		}

		if (Input::GetKeyUp(eKeyCode::LEFT) && isBirdOn == true)
		{
			mAnimator->Play(L"BirdLeftIdle", false);
			mState = eBazziState::Idle;
		}
		if (Input::GetKeyUp(eKeyCode::RIGHT) && isBirdOn == true)
		{
			mAnimator->Play(L"BirdRightIdle", false);
			mState = eBazziState::Idle;
		}
		if (Input::GetKeyUp(eKeyCode::UP) && isBirdOn == true)
		{
			mAnimator->Play(L"BirdUpIdle", false);
			mState = eBazziState::Idle;
		}
		if (Input::GetKeyUp(eKeyCode::DOWN) && isBirdOn == true)
		{
			mAnimator->Play(L"BirdDownIdle", false);
			mState = eBazziState::Idle;
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
			&& SceneManager::GetMapIndex()[ColLIdx.y][ColLIdx.x] != 2 && SceneManager::GetMapIndex()[ColLIdx.y][ColLIdx.x] != 1)
		{
			mLeftIdx = TileBomb::SetColIndex(Vector2(ColMidPos.x - TILE_SIZE_X, ColMidPos.y));
			mPos.x -= 250.0f * Time::DeltaTime();
		}
		if (Input::GetKey(eKeyCode::RIGHT) && isLPressed == false && isUPressed == false && isDPressed == false
			&& SceneManager::GetMapIndex()[ColRIdx.y][ColRIdx.x] != 2 && SceneManager::GetMapIndex()[ColRIdx.y][ColRIdx.x] != 1)
		{
			mRightIdx = TileBomb::SetColIndex(Vector2(ColMidPos.x + TILE_SIZE_X, ColMidPos.y));
			mPos.x += 250.0f * Time::DeltaTime();
		}
		if (Input::GetKey(eKeyCode::UP) && isRPressed == false && isLPressed == false && isDPressed == false
			&& SceneManager::GetMapIndex()[ColUIdx.y][ColUIdx.x] != 2 && SceneManager::GetMapIndex()[ColUIdx.y][ColUIdx.x] != 1)
		{
			mUpIdx = TileBomb::SetColIndex(Vector2(ColMidPos.x, ColMidPos.y - TILE_SIZE_Y));
			mPos.y -= 250.0f * Time::DeltaTime();
		}
		if (Input::GetKey(eKeyCode::DOWN) && isRPressed == false && isLPressed == false && isUPressed == false
			&& SceneManager::GetMapIndex()[ColDIdx.y][ColDIdx.x] != 2 && SceneManager::GetMapIndex()[ColDIdx.y][ColDIdx.x] != 1)
		{
			mDownIdx = TileBomb::SetColIndex(Vector2(ColMidPos.x, ColMidPos.y + TILE_SIZE_Y));
			mPos.y += 250.0f * Time::DeltaTime();
		}

		if (Input::GetKeyDown(eKeyCode::SPACEBAR))
		{
			mState = eBazziState::Shoot;
			//mAnimator->Play(L"downIdle", true);
		}

		if (Input::GetKeyDown(eKeyCode::LEFT) && isRPressed == false && isUPressed == false && isDPressed == false && isBirdOn == false)
		{
			mAnimator->Play(L"BirdLeft", true);
		}
		if (Input::GetKeyDown(eKeyCode::RIGHT) && isLPressed == false && isUPressed == false && isDPressed == false && isBirdOn == false)
		{
			mAnimator->Play(L"BirdRight", true);
		}
		if (Input::GetKeyDown(eKeyCode::UP) && isRPressed == false && isLPressed == false && isDPressed == false && isBirdOn == false)
		{
			mAnimator->Play(L"BirdUp", true);
		}
		if (Input::GetKeyDown(eKeyCode::DOWN) && isRPressed == false && isLPressed == false && isUPressed == false && isBirdOn == false)
		{
			mAnimator->Play(L"BirdDown", true);
		}

		tr->SetPos(mPos);
	}

	void Bazzi::checkInVTime()
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
	
	void Bazzi::Reset()
	{
		mState = eBazziState::Idle;
		mAnimator->Play(L"Bazziready", false);
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
	}
}