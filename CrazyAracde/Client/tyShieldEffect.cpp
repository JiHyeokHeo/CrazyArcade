#include "tyShieldEffect.h"
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
#include "tySceneManager.h"

namespace ty
{
	ShieldEffect::ShieldEffect()
	{
	}
	ShieldEffect::~ShieldEffect()
	{
	}
	void ShieldEffect::Initialize()
	{
		tr = GetComponent<Transform>();
		Image* mShieldEffect = Resources::Load<Image>(L"ShieldEffect", L"..\\Resources\\Effect\\ShieldEffects.bmp");
		mAnimator = AddComponent<Animator>();

		mAnimator->CreateAnimation(L"mShiledEffect", mShieldEffect, Vector2::Zero, 4, 1, 4, Vector2::Zero, 0.1);
		mAnimator->Play(L"mShiledEffect", true);
	}
	void ShieldEffect::Update()
	{
		Vector2 mPlayerPos = SceneManager::GetBazzi()->GetComponent<Transform>()->GetPos();
		tr->SetPos(mPlayerPos);

		mTime += Time::DeltaTime();
		if (mTime>=1.9f)
		{
			object::Destroy(this);
		}
		GameObject::Update();
	}
	void ShieldEffect::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void ShieldEffect::Release()
	{
	}
}