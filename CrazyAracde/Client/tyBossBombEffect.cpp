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
		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector2(1.5f, 1.5f));
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Bomb\\Centerflow", Vector2(11.76f, 22.84f), 0.16f);
		mAnimator->GetCompleteEvent(L"BombCenterflow") = std::bind(&BossBombEffect::BombComplete, this);
		mAnimator->Play(L"BombCenterflow", false);
		Collider* collider = AddComponent<Collider>();
		collider->SetCenter(Vector2(11.76f, 22.84f));
		collider->SetSize(Vector2(56.0f, 61.6f));
		GameObject::Initialize();
	}
	void BossBombEffect::Update()
	{
		GameObject::Update();
		mTime += Time::DeltaTime();

	}
	void BossBombEffect::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void BossBombEffect::Release()
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
		object::Destroy(this);
	}
}

