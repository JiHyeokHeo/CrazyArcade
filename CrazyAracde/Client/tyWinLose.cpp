#include "tyWinLose.h"
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
#include "tyinput.h"
#include "tyDao.h"

namespace ty
{
	WinLose::WinLose()
	{
	}
	WinLose::~WinLose()
	{
	}
	void WinLose::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\UI\\Win", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\UI\\Lose", Vector2::Zero, 0.1f);
		//mAnimator->Play(L"UIWin", false);
	}
	void WinLose::Update()
	{
		if (SceneManager::GetIsDuo() == false)
		{
			if (SceneManager::GetBazzi() != NULL)
			{
				if (SceneManager::GetBazzi()->GetPlayerHP() == -1 && isPlayed == false)
				{
					isPlayed = true;
					mAnimator->Play(L"UILose", false);
				}
			}
			else if (SceneManager::GetDao() != NULL)
			{

				if (SceneManager::GetDao()->GetPlayerHP() == -1 && isPlayed == false)
				{
					isPlayed = true;
					mAnimator->Play(L"UILose", false);
				}
			}
			if (SceneManager::GetActiveScene()->GetName() == L"Lobby")
			{
				object::Destroy(this);
			}
			if (SceneManager::GetMonsterCnt() == 0 && isPlayed == false)
			{
				isPlayed = true;
				mAnimator->Play(L"UIWin", false);
			}
			else if (SceneManager::GetTime() == 0 && isPlayed == false)
			{
				isPlayed = true;
				mAnimator->Play(L"UILose", false);
			}
			mTime += Time::DeltaTime();

			if (mTime >= 3.0f)
			{
				object::Destroy(this);
				mTime = 0;
			}

		}
		


		GameObject::Update();
	}
	void WinLose::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void WinLose::Release()
	{
	}
	void WinLose::OnCollisionEnter(Collider* other)
	{
	}
	void WinLose::OnCollisionStay(Collider* other)
	{
	}
	void WinLose::OnCollisionExit(Collider* other)
	{
	}
}