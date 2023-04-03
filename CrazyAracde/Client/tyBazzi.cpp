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
		
		Collider* collider = AddComponent<Collider>();
		collider->SetCenter(Vector2(13.0f, 25.0f));
		collider->SetSize(Vector2(49.0f, 49.0f));
	
		mState = eBazziState::Idle;

		//mAnimator->Play(L"downIlde", true);
		GameObject::Initialize();
	}
	void Bazzi::Update()
	{

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

		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		Vector2 idxpos = TileBomb::SetIndex(tr->GetPos());

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
	
		

		if (Input::GetKey(eKeyCode::LEFT) && isRPressed == false && isUPressed == false && isDPressed == false 
			)
		{
			pos.x -= mPlayerSpeed * mSpeed  * Time::DeltaTime();
		}
		if (Input::GetKey(eKeyCode::RIGHT) && isLPressed == false && isUPressed == false && isDPressed == false
			)
		{
			pos.x += mPlayerSpeed * mSpeed * Time::DeltaTime();
		}
		if (Input::GetKey(eKeyCode::UP) && isRPressed == false && isLPressed == false && isDPressed == false
			)
		{
			pos.y -= mPlayerSpeed * mSpeed * Time::DeltaTime();
		}
		if (Input::GetKey(eKeyCode::DOWN) && isRPressed == false && isLPressed == false && isUPressed == false
			)
		{
			pos.y += mPlayerSpeed * mSpeed * Time::DeltaTime();
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

		tr->SetPos(pos);
	}
	void Bazzi::shoot()
 	{
		Transform* tr = GetComponent<Transform>();
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
			mapIndex[IdxPos.y][IdxPos.x] = 1; // 13 15
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
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		if (pos.x <= 30.0f)
		{
			pos.x == 30.0f;
		}

		if (pos.x >= 900.0f)
		{
			pos.x == 900.0f;
		}

		if (pos.y <= 60.0f)
		{
			pos.y == 60.0f;
		}

		if (pos.y >= 780.0f)
		{
			pos.y == 780.0f;
		}


		if (Input::GetKey(eKeyCode::LEFT)
			/*&& pos.x >= 30.0f && pos.x <= 900.0f && pos.y >= 60.0f && pos.y <= 780.0f*/)
		{
			//isLPressed = true;
			pos.x -= 50.0f * Time::DeltaTime();
		}
		else if (Input::GetKey(eKeyCode::RIGHT)
			/*&& pos.x >= 30.0f && pos.x <= 900.0f && pos.y >= 60.0f && pos.y <= 780.0f*/)
		{
			//isRPressed = true;
			pos.x += 50.0f * Time::DeltaTime();
		}
		else if (Input::GetKey(eKeyCode::UP)
			/*&& pos.x >= 30.0f && pos.x <= 900.0f && pos.y >= 60.0f && pos.y <= 780.0f*/)
		{
			//isUPressed = true;
			pos.y -= 50.0f * Time::DeltaTime();
		}
		else if (Input::GetKey(eKeyCode::DOWN)
			/*&& pos.x >= 30.0f && pos.x <= 900.0f && pos.y >= 60.0f && pos.y <= 780.0f*/)
		{
			//isDPressed = true;
			pos.y += 50.0f * Time::DeltaTime();
		}

		tr->SetPos(pos);
	}
	void Bazzi::revive()
	{
		mRandomPosx = 40.0f;
		mRandomPosy = 60.0f;
		Transform* tr = GetComponent<Transform>();
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
}