#include "tyGameStartUI.h"
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
#include "tyPlayScene.h"
#include "tyinput.h"


namespace ty
{
	GameStartUI::GameStartUI()
	{
	}
	GameStartUI::~GameStartUI()
	{
	}
	void GameStartUI::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Game_Start\\Game", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\Game_Start\\Start", Vector2::Zero, 0.1f);
		mAnimator->Play(L"Game_StartGame", false);
	}
	void GameStartUI::Update()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 mPos = tr->GetPos();
		
		if (mPos.x <= 300.0f)
		{
			if (isPlayed == false)
			{
				mAnimator->Play(L"Game_StartGame", false);
				isPlayed = true;
			}
			mPos.y += 750.0f * Time::DeltaTime();
		}
		else if (mPos.x >= 350.0f)
		{
			if (isPlayed == false)
			{
				mAnimator->Play(L"Game_StartStart", false);
				isPlayed = true;
			}
			mPos.y -= 750.0f * Time::DeltaTime();
		}
		
		if (isDone == false)
		{
			tr->SetPos(mPos);
		}
		
		if (mPos.y >= 400.0f && mPos.x <= 300.0f)
		{
			isDone = true;
		}
		else if (mPos.y <=400.0f && mPos.x >=350.0f)
		{
			isDone = true;
		}
		
		mTime += Time::DeltaTime();
		if (mTime >= 1.5f)
		{
			object::Destroy(this);
		}
		GameObject::Update();
	}
	void GameStartUI::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void GameStartUI::Release()
	{
	}
	void GameStartUI::OnCollisionEnter(Collider* other)
	{
	}
	void GameStartUI::OnCollisionStay(Collider* other)
	{
	}
	void GameStartUI::OnCollisionExit(Collider* other)
	{
	}
}