#include "tyGround.h"
#include "tyCollider.h"
#include "tyBazzi.h"
#include "tyRigidbody.h"
#include "tyTransform.h"
#include "tyResources.h"
#include "tyImage.h"
#include "tyPlayScene.h"
#include "tyColliderPosControl.h"

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
		mCollider = AddComponent<Collider>();
		mCollider->SetSize(Vector2(900.0f, 10.0f));

	
		//mImage = Resources::Load<Image>(L"Ground", L"..\\Resources\\Ground\\Ground.bmp"); 
		mPlayer = PlayScene::GetBazzi();
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
		Transform* mPlayerPos = mPlayer->GetComponent<Transform>();
		Vector2 mGamObjPos = mPlayerPos->GetPos();
		Vector2 mColPos = mCollider->GetPos();
		if (mGamObjPos.y < mColPos.y )
		{
			mGamObjPos.y = 40.0f;
			mPlayerPos->SetPos(mGamObjPos);
		}
		
		//colposctr::ColPosControl(other, this);
	}

	void Ground::OnCollisionExit(Collider* other)
	{
		isGround = false;
	}

}
