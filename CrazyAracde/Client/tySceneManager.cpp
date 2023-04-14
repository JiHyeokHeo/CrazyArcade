#include "tySceneManager.h"
#include "tyPlayScene.h"
#include "tyLoginScene.h"
#include "tyLobbyScene.h"
#include "tyLogoScene.h"
#include "tyCollisionManager.h"
#include "tyCamera.h"
#include "tyToolScene.h"
#include "tyStage2.h"
#include "tyBazzi.h"
#include "tyPlaySceneStage2.h"
#include "tyPlaySceneStage3.h"

namespace ty
{
	std::vector<Scene*> SceneManager::mScenes = {};
	Scene* SceneManager::mActiveScene = nullptr;
	Bazzi* SceneManager::mBazzi;
	int SceneManager::mRealPlayTime = {};
	int SceneManager::monstercnt = {};
	void SceneManager::Initialize()
	{
		mScenes.resize((UINT)eSceneType::End); 

		mScenes[(UINT)eSceneType::Logo] = new LogoScene();
		mScenes[(UINT)eSceneType::Login] = new LoginScene();
		mScenes[(UINT)eSceneType::Lobby] = new LobbyScene();
		mScenes[(UINT)eSceneType::Play] = new PlayScene(); 
		mScenes[(UINT)eSceneType::PlayStage2 ] = new PlaySceneStage2();
		mScenes[(UINT)eSceneType::PlayStage3] = new PlaySceneStage3();
		mScenes[(UINT)eSceneType::Stage2] = new Stage2();
		mScenes[(UINT)eSceneType::Tool] = new ToolScene();
		
		//mScenes[(UINT)eSceneType::PLAY]->SetName(L"PLAYER");

		for (Scene* scene : mScenes)
		{
			if (scene == nullptr)
				continue;
			
 			scene->Initialize();
		}
		mActiveScene = mScenes[(UINT)eSceneType::Login];
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
		/*Camera::Clear();*/
		// ÇöÀç¾À
		mActiveScene->OnExit();

		CollisionManager::Clear();
		// ´ÙÀ½¾À
		mActiveScene = mScenes[(UINT)type];
		mActiveScene->OnEnter();

	}
}
