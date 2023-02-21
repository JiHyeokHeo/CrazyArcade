#include "tySceneManager.h"
#include "tyPlayScene.h"

namespace ty
{
	std::vector<Scene*> SceneManager::mScenes = {};
	void SceneManager::Initialize()
	{
		mScenes.resize((UINT)eSceneType::MAX); 

		mScenes[(UINT)eSceneType::Play] = new PlayScene(); 
		
		for (Scene* scene : mScenes)
		{
			if (scene == nullptr)
				continue;

			scene->Initialize();
		}
	}
	void SceneManager::Update()
	{
		//mScenes[(UINT)eSceneType::Play]->SetName(L"PLAYER");
		//for (size_t i = 0; i < (UINT)eSceneType::MAX; i++)
		//{
		//	if (mScenes[i] == nullptr)
		//		continue;

		//	mScenes[i]->Initialize();
		//}

		//read only 
		for (Scene* scene : mScenes)
		{
			if (scene == nullptr)
				continue;

			scene->Update();
		}
	}
	void SceneManager::Render(HDC hdc)
	{
		for (Scene* scene : mScenes)
		{
			if (scene == nullptr)
				continue;

			scene->Render(hdc);
		}
	}
	void SceneManager::Release()
	{
		for (Scene* scene : mScenes)
		{
			if (scene == nullptr)
				continue;

			scene->Release();
		}
	}
}
