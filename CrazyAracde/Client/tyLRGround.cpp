#include "tyLRGround.h"
#include "tyCollider.h"
#include "tyBazzi.h"
#include "tyRigidbody.h"
#include "tyTransform.h"
#include "tyResources.h"
#include "tyImage.h"
#include "tyPlayScene.h"
#include "tyColliderPosControl.h"
#include "tyTime.h"

namespace ty
{
	LRGround::LRGround()
	{
	}

	LRGround::~LRGround()
	{
	}

	void LRGround::Initialize()
	{
		SetName(L"Ground");
		mCollider = AddComponent<Collider>();
		mCollider->SetSize(Vector2(900.0f, 780.0f));


		//mImage = Resources::Load<Image>(L"Ground", L"..\\Resources\\Ground\\Ground.bmp"); 
		mPlayer = PlayScene::GetBazzi();
		GameObject::Initialize();
	}

	void LRGround::Update()
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
	void LRGround::Render(HDC hdc)
	{
		GameObject::Render(hdc);

	}

	void LRGround::Release()
	{
	}

	void LRGround::OnCollisionEnter(Collider* other)
	{
		isGround = true;
	}

	void LRGround::OnCollisionStay(Collider* other)
	{
		Transform* mPlayerPos = mPlayer->GetComponent<Transform>();
		Vector2 mGameobjPos = mPlayerPos->GetPos();
		Vector2 mGameobjColPos = mPlayer->GetComponent<Collider>()->GetPos();
		Vector2 mColPos = mCollider->GetPos();
		if (mGameobjColPos.x > mColPos.x  && other->GetOwner()->GetName() == L"Bazzi")
		{
			mGameobjPos.x += 250.0f * Time::DeltaTime();
			mPlayerPos->SetPos(mGameobjPos);
		}
		if (mGameobjColPos.x < mColPos.x  && other->GetOwner()->GetName() == L"Bazzi")
		{
			mGameobjPos.x -= 250.0f * Time::DeltaTime();
			mPlayerPos->SetPos(mGameobjPos);
		}


		//colposctr::ColPosControl(other, this);
	}

	void LRGround::OnCollisionExit(Collider* other)
	{
		isGround = false;
	}

}
