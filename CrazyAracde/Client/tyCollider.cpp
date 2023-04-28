#include "tyCollider.h"
#include "tyTransform.h"
#include "tyGameObject.h"
#include "tyCamera.h"

namespace ty
{
	UINT Collider::ColliderNumber = 0;
	bool Collider::isCollider = false;
	Collider::Collider()
		:Component(eComponentType::Collider)
		, mCenter(Vector2::Zero)
		, mPos(Vector2::Zero)
		, mSize(100.0f, 100.0f)
		, mID(ColliderNumber++)
		, mCollisionCount(0)
	{
		
	}
	Collider::~Collider()
	{
	}
	void Collider::Initialize()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		mPos = tr->GetPos() + mCenter;
		
	}
	void Collider::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		mPos = tr->GetPos() + mCenter;
	}
	void Collider::Render(HDC hdc)
	{
		if (isCollider == true)
		{
			HPEN pen = NULL;
			if (mCollisionCount <= 0)
				pen = CreatePen(BS_SOLID, 2, RGB(0, 255, 0));
			else
				pen = CreatePen(BS_SOLID, 2, RGB(255, 0, 0));
		
			HPEN oldPen = (HPEN)SelectObject(hdc, pen);
			HBRUSH brush = (HBRUSH)GetStockObject(NULL_BRUSH);
			HBRUSH oldbrush = (HBRUSH)SelectObject(hdc,brush);

		
			Rectangle(hdc, mPos.x, mPos.y, mPos.x + mSize.x, mPos.y + mSize.y);
			(HPEN)SelectObject(hdc, oldPen);
			(HBRUSH)SelectObject(hdc, oldbrush);
			DeleteObject(pen);
		}
		mCollisionCount = 0;
	}
	void Collider::Release()
	{
	}
	void Collider::OnCollisionEnter(Collider* other)
	{
		GetOwner()->OnCollisionEnter(other);
	}
	void Collider::OnCollisionStay(Collider* other)
	{
		mCollisionCount = 1;
		GetOwner()->OnCollisionStay(other);
	}
	void Collider::OnCollisionExit(Collider* other)
	{
		GetOwner()->OnCollisionExit(other);
	}
}