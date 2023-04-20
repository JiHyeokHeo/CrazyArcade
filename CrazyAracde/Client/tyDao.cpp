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
		: mHP(1) // ü�� 
		, mItemState(eItemType::None)
		, mBomb(1) // ��ź
		, mWaterCourse(2) // ���ٱ�
		, mSpeed(4.5f) // �ӵ�
		, maxSpeed(8.5f)
		, maxBomb(6)
		, maxWaterCourse(7)
		, mPlayerSpeed(50)
		, mInvincibility(1.5f)
		, mItemCnt(0)
		, maxItemCnt(1) // �ִ� ������ ���� ����
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

		tr->SetScale(Vector2(1.18f, 1.18f));
		SetName(L"Dao");
	

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Dao\\Up", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Dao\\Right", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Dao\\Up", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Dao\\Left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Dao\\Down", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Dao\\UpIdle", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Dao\\RightIdle", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Dao\\UpIdle", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Dao\\LeftIdle", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Dao\\DownIdle", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Dao\\Die", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Dao\\Bubble", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Dao\\Live", Vector2::Zero, 0.1f);


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
		checkInVTime(); // �����ð� üũ

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
			mBomb = 1; // ��ź
			mWaterCourse = 2; // ���ٱ�
			mSpeed = 5.0f; // �ӵ�
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

		if (Input::GetKeyDown(eKeyCode::CTRL) && mItemState == eItemType::Shield)
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

		tr->SetPos(mPos);
	}
	void Dao::shoot()
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

		if (Input::GetKeyDown(eKeyCode::CTRL) && mItemState == eItemType::Shield)
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
		mHP = 1; // ü�� 
		mBomb = 1; // ��ź
		mWaterCourse = 2; // ���ٱ�
		mSpeed = 5.0f; // �ӵ�
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