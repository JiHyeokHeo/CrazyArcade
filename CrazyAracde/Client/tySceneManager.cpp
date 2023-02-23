#include "tySceneManager.h"
#include "tyPlayScene.h"
#include "tyTitleScene.h"


namespace ty
{
	std::vector<Scene*> SceneManager::mScenes = {};
	Scene* SceneManager::mActiveScene = nullptr;

	void SceneManager::Initialize()
	{
		mScenes.resize((UINT)eSceneType::End); 

		mScenes[(UINT)eSceneType::Title] = new TitleScene();
		mScenes[(UINT)eSceneType::Play] = new PlayScene(); 
		

		//mScenes[(UINT)eSceneType::PLAY]->SetName(L"PLAYER");

		mActiveScene = mScenes[(UINT)eSceneType::Play];


		for (Scene* scene : mScenes)
		{
			if (scene == nullptr)
				continue;

			scene->Initialize();
		}
	}

	void SceneManager::Update()
	{
		mActiveScene->Update();
	}

	void SceneManager::Render(HDC hdc)
	{
		for (Scene* scene : mScenes)
		{
			if (scene == nullptr)
				continue;

			mActiveScene->Render(hdc);
		}
	}

	void SceneManager::Release()
	{
		for (Scene* scene : mScenes)
		{
			if (scene == nullptr)
				continue;

			delete scene;
			scene = nullptr;
		}
	}
	void SceneManager::LoadScene(eSceneType type)
	{
		// ÇöÀç¾À
		mActiveScene->OnExit();

		// ´ÙÀ½¾À
		mActiveScene = mScenes[(UINT)type];
		mActiveScene->OnEnter();

	}
}
