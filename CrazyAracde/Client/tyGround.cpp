#include "tyGround.h"
#include "tyCollider.h"
#include "tyBazzi.h"
#include "tyRigidbody.h"
#include "tyTransform.h"
#include "tyResources.h"
#include "tyImage.h"


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
		mCollider->SetSize(Vector2(1600.0f, 50.0f));


		//mImage = Resources::Load<Image>(L"Ground", L"..\\Resources\\GroundPixel.bmp"); vlr

		GameObject::Initialize();
	}

	void Ground::Update()
	{
		GameObject::Update();

		Transform* playerTr = mPlayer->GetComponent<Transform>();

		COLORREF color = mImage->GetPixel(playerTr->GetPos().x, playerTr->GetPos().y);

		//Rigidbody* rb = mPlayer->GetComponent<Rigidbody>();
		if (color == RGB(255, 0, 255))
		{
			//rb->SetGround(true);

			Vector2 pos = playerTr->GetPos();
			pos.y -= 1;
			playerTr->SetPos(pos);
		}
		else
		{
			//rb->SetGround(false);
		}
	}

	void Ground::Render(HDC hdc)
	{
		GameObject::Render(hdc);

		Transform* tr = GetComponent<Transform>();

		TransparentBlt(hdc, tr->GetPos().x, tr->GetPos().y
			, mImage->GetWidth(), mImage->GetHeight()
			, mImage->GetHdc()
			, 0, 0
			, mImage->GetWidth(), mImage->GetHeight()
			, RGB(255, 255, 255));


		//TransparentBlt(hdc, tr->GetPos().x, tr->GetPos().y
		//	, mImage->GetWidth(), mImage->GetHeight()
		//	, mImage->GetHdc()
		//	, 0, 0
		//	, mImage->GetWidth(), mImage->GetHeight()
		//	, RGB(255, 255, 255));
	}

	void Ground::Release()
	{
	}

	void Ground::OnCollisionEnter(Collider* other)
	{
		GameObject* gameobj = dynamic_cast<GameObject*>(other->GetOwner());
		if (gameobj == nullptr)
			return;

		//Rigidbody* rb = gameobj->GetComponent<Rigidbody>();
		//rb->SetGround(true);

		Collider* gameobjCol = gameobj->GetComponent<Collider>();
		Vector2 gameobjPos = gameobjCol->GetPos();

		Collider* groundCol = this->GetComponent<Collider>();
		Vector2 groundPos = groundCol->GetPos();

		float fLen = fabs(gameobjPos.y - groundPos.y);
		float fSize = (gameobjCol->GetSize().y / 2.0f) + (groundCol->GetSize().y / 2.0f);

		if (fLen < fSize)
		{
			Transform* gameobjTr = gameobj->GetComponent<Transform>();
			Transform* grTr = this->GetComponent<Transform>();

			Vector2 gameobjPos = gameobjTr->GetPos();
			Vector2 grPos = grTr->GetPos();

			gameobjPos -= (fSize - fLen) - 1.0f;
			gameobjTr->SetPos(gameobjPos);
		}
	}

	void Ground::OnCollisionStay(Collider* other)
	{
	}

	void Ground::OnCollisionExit(Collider* other)
	{
	}

}
