#include "tyBossMonster.h"
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
	BossMonster::BossMonster()
	{
	}
	BossMonster::~BossMonster()
	{
	}
	void BossMonster::Initialize()
	{
		Transform* tr = GetComponent<Transform>();
		tr->SetPos(Vector2(300.0f, 500.0f));
		tr->SetScale(Vector2(1.18f, 1.18f));

		
		Image* mAttackImage = Resources::Load<Image>(L"SealAtt", L"..\\Resources\\Monster\\Seal\\Seal_attack.bmp");
		Image* mLeftImage = Resources::Load<Image>(L"SealL", L"..\\Resources\\Monster\\Seal\\Seal_left.bmp");
		Image* mRightImage = Resources::Load<Image>(L"SealR", L"..\\Resources\\Monster\\Seal\\Seal_right.bmp");
		Image* mRollImage = Resources::Load<Image>(L"SealRoll", L"..\\Resources\\Monster\\Seal\\Seal_roll.bmp");
		Image* mReadyImage = Resources::Load<Image>(L"SealIdle", L"..\\Resources\\Monster\\Seal\\Seal_ideal.bmp");
		//Image* mDieImage = Resources::Load<Image>(L"BazziDie", L"..\\Resources\\Bazzi\\die.bmp");
		//Image* mTrapeImage = Resources::Load<Image>(L"BazziTrap", L"..\\Resources\\Bazzi\\trap.bmp");
		mAnimator = AddComponent<Animator>();

		mAnimator->CreateAnimation(L"SealIdle", mReadyImage, Vector2::Zero, 9, 1, 2, Vector2::Zero, 0.1);
		mAnimator->CreateAnimation(L"SealRoll", mRollImage, Vector2::Zero, 7, 1, 4, Vector2::Zero, 0.1);

		mAnimator->Play(L"SealRoll", true);

		Collider* collider = AddComponent<Collider>();
		collider->SetCenter(Vector2::Zero);
		collider->SetSize(Vector2(44.0f, 44.0f));
		mState = eMonsterState::Idle;
	}
	void BossMonster::Update()
	{
		GameObject::Update();
	}
	void BossMonster::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void BossMonster::Release()
	{
		GameObject::Release();
	}
	void BossMonster::OnCollisionEnter(Collider* other)
	{
	}
	void BossMonster::OnCollisionStay(Collider* other)
	{
	}
	void BossMonster::OnCollisionExit(Collider* other)
	{
	}
}