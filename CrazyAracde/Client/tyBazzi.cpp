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

namespace ty
{
	Bazzi::Bazzi()
		: maxHP(1)
		
	{
	}
	Bazzi::~Bazzi()
	{
	}
	void Bazzi::Initialize()
	{
		Transform* tr = GetComponent<Transform>();
		tr->SetPos(Vector2(400.0f, 400.0f));
		tr->SetScale(Vector2(1.18f, 1.18f));
		
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
		mAnimator->CreateAnimation(L"Bazziready", mReadyImage, Vector2::Zero, 18, 1, 17, Vector2::Zero, 0.07); // 오프셋 조절해서 ready 모션 바꿈 x,y축 잘 확인하기

		mAnimator->CreateAnimation(L"Bazzidie", mDieImage, Vector2(352.0f,0.0f), 13, 1, 13, Vector2::Zero,  0.15);
		mAnimator->CreateAnimation(L"Bazzitrap", mTrapeImage, Vector2::Zero, 13, 1, 13, Vector2::Zero,  0.18);
		

		mAnimator->GetCompleteEvent(L"Bazzitrap") = std::bind(&Bazzi::trapCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"Bazzidie") = std::bind(&Bazzi::dieCompeleteEvent, this);
		mAnimator->Play(L"Bazziready", false);
		
		Collider* collider = AddComponent<Collider>();
		collider->SetCenter(Vector2(-23.0f, -55.0f));
		collider->SetSize(Vector2(50.0f, 43.6f));
		
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
		if (isColl == false)
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
		
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		
		if (Input::GetKey(eKeyCode::LEFT) && isRPressed == false && isUPressed == false && isDPressed == false)
		{
			//isLPressed = true;
			pos.x -= 250.0f  * Time::DeltaTime();
		}
		if (Input::GetKey(eKeyCode::RIGHT) && isLPressed == false && isUPressed == false && isDPressed == false)
		{
			//isRPressed = true;
			pos.x += 250.0f * Time::DeltaTime();
		}
		if (Input::GetKey(eKeyCode::UP) && isRPressed == false && isLPressed == false && isDPressed == false)
		{
			//isUPressed = true;
			pos.y -= 250.0f  * Time::DeltaTime();
		}
		if (Input::GetKey(eKeyCode::DOWN) && isRPressed == false && isLPressed == false && isUPressed == false)
		{
			//isDPressed = true;
			pos.y += 250.0f  * Time::DeltaTime();
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

		if (Input::GetKey(eKeyCode::SPACEBAR))
		{
			mState = eBazziState::Move;
			object::Instantiate<BaseBomb>(tr->GetPos() +Vector2(-10.0f, -20.0f), eLayerType::Bomb);
			
			for (int i = 0; i < 5; i++)
			{
				object::Instantiate<BombEffect>(tr->GetPos() + Vector2((i * 50), 0), eLayerType::BombEffect);
				object::Instantiate<BombEffect>(tr->GetPos() + Vector2(0, (i * 50)), eLayerType::BombEffect);
				object::Instantiate<BombEffect>(tr->GetPos() - Vector2((i * 50), 0), eLayerType::BombEffect);
				object::Instantiate<BombEffect>(tr->GetPos() - Vector2(0, (i * 50)), eLayerType::BombEffect);
			}
		}
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

		if (Input::GetKey(eKeyCode::LEFT))
		{
			//isLPressed = true;
			pos.x -= 50.0f * Time::DeltaTime();
		}
		else if (Input::GetKey(eKeyCode::RIGHT))
		{
			//isRPressed = true;
			pos.x += 50.0f * Time::DeltaTime();
		}
		else if (Input::GetKey(eKeyCode::UP))
		{
			//isUPressed = true;
			pos.y -= 50.0f * Time::DeltaTime();
		}
		else if (Input::GetKey(eKeyCode::DOWN))
		{
			//isDPressed = true;
			pos.y += 50.0f * Time::DeltaTime();
		}

		tr->SetPos(pos);
	}
	void Bazzi::revive()
	{
		mRandomPosx = rand() % 1000;
		mRandomPosx = rand() % 900;
		Transform* tr = GetComponent<Transform>();
		tr->SetPos(Vector2(mRandomPosx, mRandomPosx));
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