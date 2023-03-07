#include "tyBombEffect.h"
#include "tyTime.h"
#include "tySceneManager.h"
#include "tyinput.h"
#include "tyResources.h"
#include "tyTransform.h"
#include "tyAnimator.h"
#include "tyCollider.h"
#include "tyScene.h"

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
		tr->SetPos(Vector2(400.0f, 400.0f));
		tr->SetScale(Vector2(1.4f, 1.4f));


		Image* BombImage = Resources::Load<Image>(L"Bomb", L"..\\Resources\\Bomb\\bomb.bmp");
		mAnimator = AddComponent<Animator>();

		mAnimator->CreateAnimation(L"bomb", BombImage, Vector2::Zero, 2, 1, 2, Vector2(11.76f, 22.84f), 0.16);
		mAnimator->Play(L"bomb", true);

		Collider* collider = AddComponent<Collider>();
		collider->SetCenter(Vector2(11.76f, 22.84f));
		collider->SetSize(Vector2(56.0f, 61.6f));

	}
	void BombEffect::Update()
	{
	}
	void BombEffect::Render(HDC hdc)
	{
	}
	void BombEffect::Release()
	{
	}
}