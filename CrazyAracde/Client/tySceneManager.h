#pragma once
#include "tyScene.h"

namespace ty
{
	class Bazzi;
	class SceneManager
	{
	public:
		static void Initialize();
		static void Update();
		static void Render(HDC hdc);
		static void Destroy();
		static void Release();

		static void LoadScene(eSceneType type);
		static Scene* GetActiveScene() { return mActiveScene; }
		static void SetActiveScene(Scene* scene) { mActiveScene = scene; }

		static void SetBazzi(Bazzi* bazzi) { mBazzi = bazzi; }
		static void DeleteBazzi() { mBazzi = nullptr; }
		static Bazzi* GetBazzi() { return mBazzi; }
		static void SetmTime(int time) { mTime = time; }
		static int GetTime() { return mTime; }
		
	private:
		static std::vector<Scene*> mScenes;
		static Scene* mActiveScene;
		static Bazzi* mBazzi;
		static int mTime;

	};
}