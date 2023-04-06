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

namespace ty
{
	std::vector<std::vector<int>> Bazzi:: mapIndex;
	Bazzi::Bazzi()
		: mHP(1) // 체력 
		, mBomb(3) // 폭탄
		, mWaterCourse(3) // 물줄기
		, mSpeed(5.0f) // 속도
		, maxSpeed(9.0f)
		, maxBomb(6)
		, maxWaterCourse(7)
		, mPlayerSpeed(50)
		
	{
		int row = 15;
		int col = 13;
		mapIndex.assign(col, std::vector<int>(row, 0));
	}
	Bazzi::~Bazzi()
	{
	}
	void Bazzi::Initialize()
	{
		isPushPossible = true;
		Transform* tr = GetComponent<Transform>();
		tr->SetPos(Vector2(20,40));
		tr->SetScale(Vector2(1.18f, 1.18f));
		SetName(L"Bazzi");
		Image* mUpImage = Resources::Load<Image>(L"BazziU", L"..\\Resources\\Bazzi\\up.bmp");
		Image* mLeftImage = Resources::Load<Image>(L"BazziL", L"..\\Resources\\Bazzi\\left.bmp");
		Image* mRightImage = Resources::Load<Image>(L"BazziR", L"..\\Resources\\Bazzi\\right.bmp");
		Image* mDownImage = Resources::Load<Image>(L"BazziD", L"..\\Resources\\Bazzi\\down.bmp");
		Image* mReadyImage = Resources::Load<Image>(L"BazziReady", L"..\\Resources\\Bazzi\\ready.bmp");
		Image* mDieImage = Resources::Load<Image>(L"BazziDie", L"..\\Resources\\Bazzi\\die.bmp");
		Image* mTrapeImage = Resources::Load<Image>(L"BazziTrap", L"..\\Resources\\Bazzi\\trap.bmp");
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
		

		mAnimator->GetCompleteEvent(L"Bazzitrap") = std::bind(&Bazzi::trapCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"Bazzidie") = std::bind(&Bazzi::dieCompeleteEvent, this);
		mAnimator->Play(L"Bazziready", false);
		
		collider = AddComponent<Collider>();
		collider->SetCenter(Vector2(12.0f, 25.0f));
		collider->SetSize(Vector2(55.0f, 55.0f));
	
		mState = eBazziState::Idle;

		//mAnimator->Play(L"downIlde", true);
		GameObject::Initialize();
	}
	void Bazzi::Update()
	{
		tr = GetComponent<Transform>();
		mPos = tr->GetPos();
		IdxPos = TileBomb::SetIndex(tr->GetPos());
		mTime += Time::DeltaTime();

		//delete mBomb;
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
			case ty::Bazzi::eBazziState::Revive:
				revive();
				break;
			case ty::Bazzi::eBazziState::NoMove:
				nomove();
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

		if (Input::GetKeyDown(eKeyCode::X))
		{
			mBomb = 1; // 폭탄
			mWaterCourse = 2; // 물줄기
			mSpeed = 5.0f; // 속도
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
		if (isColl == false && other->GetOwner()->GetName() ==L"BossBombEffect" )
		{
			mAnimator->Play(L"Bazzitrap", false);
			mState = eBazziState::BubbleMove;
			isColl = true;
		}
		else if (isColl == false && other->GetOwner()->GetName() == L"BombEffect")
		{
			mAnimator->Play(L"Bazzitrap", false);
			mState = eBazziState::BubbleMove;
			isColl = true;
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

		if (Input::GetKeyUp(eKeyCode::LEFT))
		{
			mAnimator->Play(L"BazzileftIdle", false);
			mState = eBazziState::Idle;
		}
		if (Input::GetKeyUp(eKeyCode::RIGHT))
		{
			mAnimator->Play(L"BazzirightIdle", false);
			mState = eBazziState::Idle;
		}
		if (Input::GetKeyUp(eKeyCode::UP))
		{
			mAnimator->Play(L"BazziupIdle", false);
			mState = eBazziState::Idle;
		}
		if (Input::GetKeyUp(eKeyCode::DOWN))
		{	
			mAnimator->Play(L"BazzidownIdle", false);
			mState = eBazziState::Idle;
		}
	
		Vector2 ColPos = collider->GetPos();
		Vector2 ColMidPos = ColPos + Vector2(TILE_SIZE_X / 2, TILE_SIZE_Y / 2);
		Vector2 ColRIdx = TileBomb::SetColIndex(ColMidPos + Vector2(30.0f,0.0f));
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


		if (Input::GetKey(eKeyCode::LEFT) && isRPressed == false && isUPressed == false && isDPressed == false 
			&& mapIndex[ColLIdx.y][ColLIdx.x] != 2 && mapIndex[ColLIdx.y][ColLIdx.x] != 1 )
		{
			mLeftIdx = TileBomb::SetColIndex(Vector2(ColMidPos.x - TILE_SIZE_X, ColMidPos.y));
			mPos.x -= mPlayerSpeed * mSpeed  * Time::DeltaTime();
		}
		if (Input::GetKey(eKeyCode::RIGHT) && isLPressed == false && isUPressed == false && isDPressed == false
			&& mapIndex[ColRIdx.y][ColRIdx.x] != 2 && mapIndex[ColRIdx.y][ColRIdx.x] != 1)
		{
			mRightIdx = TileBomb::SetColIndex(Vector2(ColMidPos.x + TILE_SIZE_X, ColMidPos.y));
			mPos.x += mPlayerSpeed * mSpeed * Time::DeltaTime();
		}
		if (Input::GetKey(eKeyCode::UP) && isRPressed == false && isLPressed == false && isDPressed == false
			&& mapIndex[ColUIdx.y][ColUIdx.x] != 2 && mapIndex[ColUIdx.y][ColUIdx.x] != 1)
		{
			mUpIdx = TileBomb::SetColIndex(Vector2(ColMidPos.x, ColMidPos.y - TILE_SIZE_Y));
			mPos.y -= mPlayerSpeed * mSpeed * Time::DeltaTime();
		}
		if (Input::GetKey(eKeyCode::DOWN) && isRPressed == false && isLPressed == false && isUPressed == false
			&& mapIndex[ColDIdx.y][ColDIdx.x] != 2 && mapIndex[ColDIdx.y][ColDIdx.x] != 1 )
		{
			mDownIdx = TileBomb::SetColIndex(Vector2(ColMidPos.x , ColMidPos.y  +TILE_SIZE_Y));
			mPos.y += mPlayerSpeed * mSpeed * Time::DeltaTime();
		}

		if (Input::GetKeyDown(eKeyCode::SPACEBAR))
		{
			mState = eBazziState::Shoot;
			//mAnimator->Play(L"downIdle", true);
		}

		if (Input::GetKeyDown(eKeyCode::LEFT) && isRPressed == false && isUPressed == false && isDPressed == false)
		{
			mAnimator->Play(L"Bazzileft", true);
		}
		if (Input::GetKeyDown(eKeyCode::RIGHT) && isLPressed == false && isUPressed == false && isDPressed == false)
		{
			mAnimator->Play(L"Bazziright", true);
		}
		if (Input::GetKeyDown(eKeyCode::UP) && isRPressed == false && isLPressed == false && isDPressed == false)
		{
			mAnimator->Play(L"Bazziup", true);
		}
		if (Input::GetKeyDown(eKeyCode::DOWN) && isRPressed == false && isLPressed == false && isUPressed == false)
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
		if (Input::GetKey(eKeyCode::SPACEBAR) && mapIndex[IdxPos.y][IdxPos.x] == 0 && mBomb <= maxBomb && mClick < mBomb)
		{
			mClick++;
			object::Instantiate<BaseBomb>(TileBomb::SetPos(tr->GetPos()), eLayerType::Bomb);
			IdxPos = TileBomb::SetIndex(tr->GetPos());
			mapIndex[IdxPos.y][IdxPos.x] = 3; // 13 15
		}
			mState = eBazziState::Move;
	}
	void Bazzi::death()
	{
		if (isColl == true)
		{
			mAnimator->Play(L"Bazzitrap", false);
		}

	}
	void Bazzi::idle()
	{
		isLPressed = false;
		isRPressed = false;
		isUPressed = false;
		isDPressed = false;
		if (Input::GetKey(eKeyCode::LEFT))
		{
			isLPressed = true;
			mAnimator->Play(L"Bazzileft", true);
			mState = eBazziState::Move;
		}
		if (Input::GetKey(eKeyCode::RIGHT))
		{
			isRPressed = true;
			mAnimator->Play(L"Bazziright", true);
			mState = eBazziState::Move;
		}
		if (Input::GetKey(eKeyCode::UP))
		{
			isUPressed = true;
			mAnimator->Play(L"Bazziup", true);
			mState = eBazziState::Move;
		}
		if(Input::GetKey(eKeyCode::DOWN))
		{
			isDPressed = true;
			mAnimator->Play(L"Bazzidown", true);
			mState = eBazziState::Move;
		}
		if (Input::GetKeyDown(eKeyCode::SPACEBAR))
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

		tr->SetPos(mPos);
	}
	void Bazzi::revive()
	{
		mRandomPosx = 80.0f;
		mRandomPosy = 100.0f;
		tr->SetPos(Vector2(mRandomPosx, mRandomPosy));
		mState = eBazziState::Idle;
		mAnimator->Play(L"Bazziready", false);
		mTime = 0;
		isColl = false;
	}
	void Bazzi::nomove()
	{
		
	}
	void Bazzi::trapCompleteEvent(/*const Cuphead* this*/) // 애니메이션 동작이 끝나면 실행되도록 할 수 있다.
	{
		mState = eBazziState::NoMove;
		mAnimator->Play(L"Bazzidie", false);
		
	}
	void Bazzi::dieCompeleteEvent()
	{
		mState = eBazziState::Revive;
		
	}
	void Bazzi::Reset()
	{
		mHP = 1; // 체력 
		mBomb = 3; // 폭탄
		mWaterCourse = 3; // 물줄기
		mSpeed = 5.0f; // 속도
		maxSpeed = 9.0f;
		maxBomb = 6;
		maxWaterCourse = 7;
		mPlayerSpeed = 50;
	}
}