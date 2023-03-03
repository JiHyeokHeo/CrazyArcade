#include "tyBaseBomb.h"
#include "tyTransform.h"
#include "tyTime.h"

namespace ty
{
	BaseBomb::BaseBomb()
	{
	}
	BaseBomb::~BaseBomb()
	{
	}
	void BaseBomb::Initialize()
	{
	}
	void BaseBomb::Update()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos(); // 이쪽에서 뭔가 물풍선 밀거나 하는 조건을 걸 수 있을듯함
		pos.x += 100.0f * Time::DeltaTime();
		tr->SetPos(pos);
	}
	void BaseBomb::Render(HDC hdc)
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		HPEN pen = CreatePen(BS_SOLID, 2, RGB(0, 255, 0));

		HPEN oldPen = (HPEN)SelectObject(hdc, pen);
		HBRUSH brush = (HBRUSH)GetStockObject(NULL_BRUSH);
		HBRUSH oldbrush = (HBRUSH)SelectObject(hdc, brush);

		Ellipse(hdc, pos.x, pos.y, pos.x + 50, pos.y + 50);


		(HPEN)SelectObject(hdc, oldPen);
		(HBRUSH)SelectObject(hdc, oldbrush);
		DeleteObject(pen);
		

	}
	void BaseBomb::Release()
	{
	}
}