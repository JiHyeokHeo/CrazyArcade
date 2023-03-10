#include "tySceneManager.h"
#include "tyPlayScene.h"
#include "tyLoginScene.h"
#include "tyLobbyScene.h"
#include "tyLogoScene.h"
#include "tyCollisionManager.h"
#include "tyCamera.h"

namespace ty
{
	std::vector<Scene*> SceneManager::mScenes = {};
	Scene* SceneManager::mActiveScene = nullptr;

	void SceneManager::Initialize()
	{
		mScenes.resize((UINT)eSceneType::End); 

		mScenes[(UINT)eSceneType::Logo] = new LogoScene();
		mScenes[(UINT)eSceneType::Login] = new LoginScene();
		mScenes[(UINT)eSceneType::Lobby] = new LobbyScene();
		mScenes[(UINT)eSceneType::Play] = new PlayScene(); 
		
		
		//mScenes[(UINT)eSceneType::PLAY]->SetName(L"PLAYER");
		
		

		for (Scene* scene : mScenes)
		{
			if (scene == nullptr)
				continue;
			
 			scene->Initialize();
		}
		mActiveScene = mScenes[(UINT)eSceneType::Play];
	}

	void SceneManager::Update()
	{
		mActiveScene->Update();
	}

	void SceneManager::Render(HDC hdc)
	{
	
		mActiveScene->Render(hdc);
		
	}

	void SceneManager::Destroy()
	{
		mActiveScene->Destroy();
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
		Camera::Clear();
		// ÇöÀç¾À
		mActiveScene->OnExit();

		CollisionManager::Clear();
		// ´ÙÀ½¾À
		mActiveScene = mScenes[(UINT)type];
		mActiveScene->OnEnter();

	}
}
