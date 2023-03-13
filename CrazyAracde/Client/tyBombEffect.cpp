#include "tyBombEffect.h"
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
	BombEffect::BombEffect()
	{
	}
	BombEffect::~BombEffect()
	{
	}
	void BombEffect::Initialize()
	{
		Transform* tr = GetComponent<Transform>();
		//tr->SetPos(Vector2(400.0f, 400.0f));
		tr->SetScale(Vector2(1.1f, 1.1f));


		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\Bomb\\Downflow", Vector2(11.76f, 22.84f), 0.16f);
		mAnimator->CreateAnimations(L"..\\Resources\\Bomb\\Upflow", Vector2(11.76f, 22.84f), 0.16f);

		mAnimator->Play(L"BombDownflow", false);
		//mAnimator->Play(L"BombUpflow", false);

		Collider* collider = AddComponent<Collider>();
		collider->SetCenter(Vector2(11.76f, 22.84f));
		collider->SetSize(Vector2(56.0f, 61.6f));

	}
	void BombEffect::Update()
	{
		if (mAnimator->isComplete() == true)
		{
			object::Destroy(this);
		}
			
		GameObject::Update();
	}
	void BombEffect::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void BombEffect::Release()
	{
		GameObject::Release();
	}
}