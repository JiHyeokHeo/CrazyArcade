#pragma once
#include "tyApplication.h"
#include "tySceneManager.h"
#include "tyObject.h"
#include "tyWinLose.h"
#include "tyTime.h"
#include "tyBazzi.h"
#include "tyDao.h"
#include "tyScene.h"
#include "tyPlayScene.h"

namespace ty::CheckCharactor
{
	float mTime;
	bool isPlayed = false;
	void Check(eSceneType type)
	{
		if (SceneManager::GetIsDuo() == false)
		{
			if (SceneManager::GetBazzi() != NULL) // ¹èÂî
			{
				if (SceneManager::GetMonsterCnt() == 0)
				{
					if (isPlayed == false)
					{
						object::Instantiate<WinLose>(Vector2(350.0f, 400.0f), eLayerType::UI);
						isPlayed = true;
					}
					mTime += Time::DeltaTime();
					if (mTime >= 6.0f)
					{
						isPlayed = false;
						SceneManager::LoadScene(type);
						mTime = 0;
					}
				}
				else if (SceneManager::GetBazzi()->GetPlayerHP() == -1)
				{
					if (isPlayed == false)
					{
						object::Instantiate<WinLose>(Vector2(350.0f, 400.0f), eLayerType::UI);
						isPlayed = true;
					}
					mTime += Time::DeltaTime();
					if (mTime >= 3.0f)
					{
						SceneManager::LoadScene(eSceneType::Lobby);
						mTime = 0;
					}
				}
			}
			else if (SceneManager::GetDao() != NULL) // ´Ù¿À
			{
				if (SceneManager::GetMonsterCnt() == 0)
				{
					if (isPlayed == false)
					{
						object::Instantiate<WinLose>(Vector2(350.0f, 400.0f), eLayerType::UI);
						isPlayed = true;
					}
					mTime += Time::DeltaTime();
					if (mTime >= 3.0f)
					{
						isPlayed = false;
						SceneManager::LoadScene(type);
						mTime = 0;
					}
				}
				else if (SceneManager::GetDao()->GetPlayerHP() == -1)
				{
					if (isPlayed == false)
					{
						object::Instantiate<WinLose>(Vector2(350.0f, 400.0f), eLayerType::UI);
						isPlayed = true;
					}
					mTime += Time::DeltaTime();
					if (mTime >= 3.0f)
					{
						SceneManager::LoadScene(eSceneType::Lobby);
						mTime = 0;
					}
				}
			}
		}
		else if (SceneManager::GetIsDuo() == true)
		{
			if (SceneManager::GetMonsterCnt() == 0)
			{
				if (isPlayed == false)
				{
					object::Instantiate<WinLose>(Vector2(350.0f, 400.0f), eLayerType::UI);
					isPlayed = true;
				}
				mTime += Time::DeltaTime();
				if (mTime >= 3.0f)
				{
					isPlayed = false;
					SceneManager::LoadScene(type);
					mTime = 0;
				}
			}

			if (SceneManager::GetDao() != NULL && SceneManager::GetBazzi() != NULL)
			{
				if (SceneManager::GetDao()->GetPlayerHP() == -1 && SceneManager::GetBazzi()->GetPlayerHP() == -1)
				{
					if (isPlayed == false)
					{
						object::Instantiate<WinLose>(Vector2(350.0f, 400.0f), eLayerType::UI);
						isPlayed = true;
					}
					mTime += Time::DeltaTime();
					if (mTime >= 3.0f)
					{
						SceneManager::LoadScene(eSceneType::Lobby);
						mTime = 0;
					}
				}
			}
		}
	};

}

