#include "tyCollider.h"
#include "tyTransform.h"
#include "tyGameObject.h"

namespace ty
{
	Collider::Collider()
		:Component(eComponentType::Collider)
		, mCenter(Vector2::Zero)
		, mScale(Vector2::One)
		, mPos(Vector2::Zero)
		, mSize(100.0f, 100.0f)
	{
	}
	Collider::~Collider()
	{
	}
	void Collider::Initialize()
	{
	}
	void Collider::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		mPos = tr->GetPos() + mCenter;
	}
	void Collider::Render(HDC hdc)
	{
		HPEN pen = CreatePen(BS_SOLID, 2, RGB(0, 255, 0));
		HPEN oldPen = (HPEN)SelectObject(hdc, pen);
		HBRUSH brush = (HBRUSH)GetStockObject(NULL_BRUSH);
		HBRUSH oldbrush = (HBRUSH)SelectObject(hdc,brush);

		Rectangle(hdc, mPos.x, mPos.y, mPos.x + mSize.x, mPos.y + mSize.y);
		(HPEN)SelectObject(hdc, oldPen);
		(HBRUSH)SelectObject(hdc, oldbrush);
		DeleteObject(pen);
		
	}
	void Collider::Release()
	{
	}
}