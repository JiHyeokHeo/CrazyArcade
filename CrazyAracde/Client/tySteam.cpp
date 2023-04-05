#include "tySteam.h"
#include "tyCollider.h"
#include "tyBazzi.h"
#include "tyRigidbody.h"
#include "tyTransform.h"
#include "tyResources.h"
#include "tyImage.h"
#include "tyPlayScene.h"
#include "tyColliderPosControl.h"
#include "tyTime.h"
#include "tyPlayScene.h"
#include "tyAnimator.h"
#include "tyObject.h"

namespace ty
{
	Steam::Steam()
	{
	}
	Steam::~Steam()
	{
	}
	void Steam::Initialize()
	{
		mAnimator = AddComponent<Animator>();

		mAnimator->CreateAnimations(L"..\\Resources\\Effect\\Crashed", Vector2(Vector2(10.0f, 5.0f)), 0.1f);
		mAnimator->Play(L"EffectCrashed", false);
	}
	void Steam::Update()
	{
		if (mAnimator->isComplete() == true)
		{
			object::Destroy(this);
		}
		GameObject::Update();
	}
	void Steam::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Steam::Release()
	{
	}
}