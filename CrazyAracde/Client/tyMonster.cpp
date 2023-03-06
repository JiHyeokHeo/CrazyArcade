#include "tyMonster.h"
#include "tyTime.h"
#include "tySceneManager.h"
#include "tyinput.h"
#include "tyResources.h"
#include "tyTransform.h"
#include "tyAnimator.h"
#include "tyCollider.h"
#include "tyBaseBomb.h"
#include "tyScene.h"

namespace ty
{
	Monster::Monster()
	{
	}
	Monster::~Monster()
	{
	}
	void Monster::Initialize()
	{
		Transform* tr = GetComponent<Transform>();
		tr->SetPos(Vector2(700.0f, 700.0f));
		tr->SetScale(Vector2(1.2f, 1.2f));

		mAnimator = AddComponent<Animator>();
		Image* mImage = Resources::Load<Image>(L"Croco", L"..\\Resources\\Monster\\Croco.bmp");

		mAnimator->CreateAnimation(L"Idle", mImage, Vector2::Zero, 6, 1, 6, Vector2::Zero, 0.1f);


		mAnimator->Play(L"Idle", true);
		
		Collider* collider = AddComponent<Collider>();
		collider->SetCenter(Vector2(0.0f, 0.0f));

		mState = eMonsterState::Idle;
		GameObject::Initialize();
	}
	void Monster::Update()
	{
		GameObject::Update();
	}
	void Monster::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Monster::Release()
	{
		GameObject::Release();
	}
}