#include "tyPlayerNum.h"
#include "tyBazzi.h"
#include "tyTime.h"
#include "tySceneManager.h"
#include "tyinput.h"
#include "tyResources.h"
#include "tyTransform.h"
#include "tyAnimator.h"
#include "tyCollider.h"
#include "tyBaseBomb.h"
#include "tyScene.h"
#include "tyObject.h"
#include "tyBombEffect.h"
#include "tyTile.h"
#include "tyTileBomb.h"
#include "tyPlayScene.h"
#include"tyinput.h"

namespace ty
{
	PlayerNum::PlayerNum()
		:mTime(0)
	{
	}
	PlayerNum::~PlayerNum()
	{
	}
	void PlayerNum::Initialize()
	{
		Image* mPlayerNum = Resources::Load<Image>(L"PlayerNum", L"..\\Resources\\Bazzi\\player1.bmp");
		Animator* mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"PLNum", mPlayerNum, Vector2::Zero, 1, 1, 1, Vector2::Zero, 0.1);
		mAnimator->Play(L"PLNum", true);
	}
	void PlayerNum::Update()
	{
		mTime += Time::DeltaTime();

		if (mTime >= 1.5f)
		{
			object::Destroy(this);
		}
		GameObject::Update();
	}
	void PlayerNum::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void PlayerNum::Release()
	{
	}
	void PlayerNum::OnCollisionEnter(Collider* other)
	{
	}
	void PlayerNum::OnCollisionStay(Collider* other)
	{
	}
	void PlayerNum::OnCollisionExit(Collider* other)
	{
	}
}