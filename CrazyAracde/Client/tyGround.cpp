#include "tyGround.h"
#include "tyCollider.h"
#include "tyBazzi.h"
#include "tyRigidbody.h"
#include "tyTransform.h"
#include "tyResources.h"
#include "tyImage.h"
#include "tyPlayScene.h"
#include "tyColliderPosControl.h"
#include "tyTime.h"
#include "tyPlayScene.h"
#include "tySceneManager.h"
#include "tyDao.h"

namespace ty
{
	Ground::Ground()
	{
	}

	Ground::~Ground()
	{
	}

	void Ground::Initialize()
	{
		SetName(L"Ground");
		mCollider = AddComponent<Collider>();
		mCollider->SetSize(Vector2(900.0f, 780.0f));

	
		//mImage = Resources::Load<Image>(L"Ground", L"..\\Resources\\Ground\\Ground.bmp"); 
		GameObject::Initialize();
	}

	void Ground::Update()
	{
		GameObject::Update();
		

		//COLORREF color = mImage->GetPixel(playerTr.x, playerTr.y);

		//if (color == RGB(0, 255, 255))
		//{
		//	playerTr.y -= 1;
		//	
		//}
		//else if
		//{

		//}

			
	}
	void Ground::Render(HDC hdc)
	{
		GameObject::Render(hdc);

	}

	void Ground::Release()
	{
	}

	void Ground::OnCollisionEnter(Collider* other)
	{
		isGround = true;
	}

	void Ground::OnCollisionStay(Collider* other)
	{
		if (SceneManager::GetBazzi() != NULL || SceneManager::GetDao() != NULL)
		{
			if (other->GetOwner()->GetName() == L"Bazzi" && SceneManager::GetBazzi() != NULL )
			{
				int mSpeed = SceneManager::GetBazzi()->GetmSpeed();
				mBazzi = SceneManager::GetBazzi();
				Transform* mPlayerPos = mBazzi->GetComponent<Transform>();
				Vector2 mGameobjPos = mPlayerPos->GetPos();
				Vector2 mGameobjColPos = mBazzi->GetComponent<Collider>()->GetPos();
				Vector2 mColPos = mCollider->GetPos();
				if (mGameobjColPos.y > mColPos.y && other->GetOwner()->GetName() == L"Bazzi")
				{
					mGameobjPos.y += mBazzi->GetPlayerSpeed() * mSpeed * Time::DeltaTime();
					mPlayerPos->SetPos(mGameobjPos);
				}
				if(mGameobjColPos.y < mColPos.y && other->GetOwner()->GetName() == L"Bazzi")
				{
					mGameobjPos.y -= mBazzi->GetPlayerSpeed() * mSpeed * Time::DeltaTime();
					mPlayerPos->SetPos(mGameobjPos);
				}
			}
			if(other->GetOwner()->GetName() == L"Dao" && SceneManager::GetDao() != NULL)
			{
				int mSpeed = SceneManager::GetDao()->GetmSpeed();
				mDao = SceneManager::GetDao();
				Transform* mPlayerPos = mDao->GetComponent<Transform>();
				Vector2 mGameobjPos = mPlayerPos->GetPos();
				Vector2 mGameobjColPos = mDao->GetComponent<Collider>()->GetPos();
				Vector2 mColPos = mCollider->GetPos();
				if (mGameobjColPos.y > mColPos.y && other->GetOwner()->GetName() == L"Dao")
				{
					mGameobjPos.y += mDao->GetPlayerSpeed() * mSpeed * Time::DeltaTime();
					mPlayerPos->SetPos(mGameobjPos);
				}
				if (mGameobjColPos.y < mColPos.y && other->GetOwner()->GetName() == L"Dao")
				{
					mGameobjPos.y -= mDao->GetPlayerSpeed() * mSpeed * Time::DeltaTime();
					mPlayerPos->SetPos(mGameobjPos);
				}

			}
		}

		//colposctr::ColPosControl(other, this);
	}

	void Ground::OnCollisionExit(Collider* other)
	{
		isGround = false;
	}

	void Ground::ColCheck()
	{
		
	}

}
