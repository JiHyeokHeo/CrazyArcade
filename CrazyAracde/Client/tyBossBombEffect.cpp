#include "tyBossBombEffect.h"
#include "tyTime.h"
#include "tySceneManager.h"
#include "tyinput.h"
#include "tyResources.h"
#include "tyTransform.h"
#include "tyAnimator.h"
#include "tyCollider.h"
#include "tyObject.h"


namespace ty
{
	BossBombEffect::BossBombEffect()
	{
	}
	BossBombEffect::~BossBombEffect()
	{
	}
	void BossBombEffect::Initialize()
	{
		SetName(L"BossBombEffect");
		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector2(1.5f, 1.5f));
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Bomb\\Centerflow", Vector2::Zero, 0.16f);
		mAnimator->GetCompleteEvent(L"BombCenterflow") = std::bind(&BossBombEffect::BombComplete, this);
		mAnimator->Play(L"BombCenterflow", false);
		Collider* collider = AddComponent<Collider>();
		collider->SetCenter(Vector2(15.00f, 15.00f));
		collider->SetSize(Vector2(30.0f, 30.0f));
		GameObject::Initialize();
	}
	void BossBombEffect::Update()
	{
		GameObject::Update();
	}
	void BossBombEffect::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void BossBombEffect::Release()
	{
	
	}
	void BossBombEffect::OnCollisionEnter(Collider* other)
	{
		if (other->GetOwner()->GetName() == L"Ground")
			object::Destroy(this);
	}
	void BossBombEffect::OnCollisionStay(Collider* other)
	{
		if (other->GetOwner()->GetName() == L"Ground")
			object::Destroy(this);
	}
	void BossBombEffect::OnCollisionExit(Collider* other)
	{
	}
	void BossBombEffect::idle()
	{
	}
	void BossBombEffect::bombed()
	{
	}
	void BossBombEffect::BombComplete()
	{
		if (mAnimator->isComplete() == true)
			object::Destroy(this);
	}
}

