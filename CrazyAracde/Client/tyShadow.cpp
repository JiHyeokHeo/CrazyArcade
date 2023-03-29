#include "tyShadow.h"
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

namespace ty
{
	Shadow::Shadow()
	{
	}
	Shadow::~Shadow()
	{
	}
	void Shadow::Initialize()
	{
		Image* mShadowImage = Resources::Load<Image>(L"Shadow", L"..\\Resources\\Bazzi\\shadow.bmp");
		Animator* mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(L"BazziShadow", mShadowImage, Vector2::Zero, 1, 1, 1, Vector2(18.0f, 70.0f), 0.1);
		mAnimator->Play(L"BazziShadow", true);
		
	}
	void Shadow::Update()
	{
		Bazzi* mPlayer = PlayScene::GetBazzi();
		GetComponent<Transform>()->SetPos(mPlayer->GetComponent<Transform>()->GetPos());
;		GameObject::Update();
	}
	void Shadow::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Shadow::Release()
	{
	}
	void Shadow::OnCollisionEnter(Collider* other)
	{

	}
	void Shadow::OnCollisionStay(Collider* other)
	{
	}
	void Shadow::OnCollisionExit(Collider* other)
	{
	}
}