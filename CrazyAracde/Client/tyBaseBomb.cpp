#include "tyBaseBomb.h"
#include "tyTransform.h"
#include "tyTime.h"
#include "tyCollider.h"
#include "tyGameObject.h"
#include "tyAnimator.h"
#include "tyObject.h"

namespace ty
{
	BaseBomb::BaseBomb()
		: mTime(0.0f)
	{	
	
	}
	BaseBomb::~BaseBomb()
	{

	}
	void BaseBomb::Initialize()
	{
		
    	//Transform* tr = GetComponent<Transform>();
		//tr->SetPos(Vector2(400.0f, 400.0f));
		//tr->SetScale(Vector2(1.4f, 1.4f));
		//
		//Image* BombImage = Resources::Load<Image>(L"Bomb", L"..\\Resources\\Bomb\\bomb.bmp");
		mAnimator = AddComponent<Animator>();

		//mAnimator->CreateAnimation(L"bomb", BombImage, Vector2::Zero, 2, 1, 2, Vector2(11.76f, 22.84f), 0.16);
		//mAnimator->Play(L"bomb", true);
		mAnimator->CreateAnimations(L"..\\Resources\\Bomb\\Idle", Vector2(11.76f, 22.84f), 0.16f);
		mAnimator->Play(L"BombIdle", true);

		Collider* collider = AddComponent<Collider>();
		collider->SetCenter(Vector2(12.76f, 22.84f));
		collider->SetSize(Vector2(56.0f, 61.6f));

		//GameObject::Initialize();
	}

	void BaseBomb::Update()
	{
		/*Transform* tr = GetComponent<Transform>();*/
		//Vector2 pos = tr->GetPos(); //+ Vector2::Vector2(6.0f, 10.0f); // 이쪽에서 뭔가 물풍선 밀거나 하는 조건을 걸 수 있을듯함
		////pos.x += 100.0f * Time::DeltaTime();
		//tr->SetPos(pos);
		//
		Transform* tr = GetComponent<Transform>();

		Vector2 dir = Vector2(500.0f, 500.0f);// - tr->GetPos();
		dir.Normalize();
		///*float x = cosf(-PI / 4.0f);
		//float y = sinf(-PI / 4.0f);*/
		////float x = dir.x * cosf(PI / 5.0f) - dir.y * sinf(PI / 5.0f);
		////float y = dir.x * sinf(PI / 5.0f) + dir.y * cosf(PI / 5.0f);


		Vector2 pos = tr->GetPos();
		pos.x += 100.0f * dir.x * Time::DeltaTime();
		pos.y += 100.0f * dir.y * Time::DeltaTime();

		mTime += Time::DeltaTime();

		if (mTime >= 3)
		{
 			object::Destroy(this); // 자기 스스로를 없애는거기 때문에 this 사용
		}
		GameObject::Update();
    }
	
	void BaseBomb::Render(HDC hdc)
	{
		//Transform* tr = GetComponent<Transform>();
		//Vector2 pos = tr->GetPos() + Vector2::Vector2(6.0f, 10.0f);;
		//HPEN pen = CreatePen(BS_SOLID, 2, RGB(0, 255, 0));

		//HPEN oldPen = (HPEN)SelectObject(hdc, pen);
		//HBRUSH brush = (HBRUSH)GetStockObject(NULL_BRUSH);
		//HBRUSH oldbrush = (HBRUSH)SelectObject(hdc, brush);

		//Ellipse(hdc, pos.x, pos.y, pos.x + 50, pos.y + 50);


		//(HPEN)SelectObject(hdc, oldPen);
		//(HBRUSH)SelectObject(hdc, oldbrush);
		//DeleteObject(pen);


		GameObject::Render(hdc);
	}
	void BaseBomb::Release()
	{
		GameObject::Release();
	}
}