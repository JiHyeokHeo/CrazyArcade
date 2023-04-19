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

		// ���� �� �Ŵ����� ���
		static void SetBazzi(Bazzi* bazzi) { mBazzi = bazzi; }
		static void DeleteBazzi() { mBazzi = nullptr; }

		// �ٸ� Ŭ�������� ����ϱ� ���� ����
		static Bazzi* GetBazzi() { return mBazzi; }

		// �ð� ���� �� ��������
		static void SetmTime(int time) { mRealPlayTime = time; }
		static int GetTime() { return mRealPlayTime; }

		// ���� ���� ���ϱ�
		static void SetMonsterCnt(int cnt) { monstercnt = cnt; }
		static int GetMonsterCnt() { return monstercnt; }

		// ���� ���� ���� ���ϱ�
		static void SetBossCnt(int cnt) { mBossCnt = cnt; }
		static int GetBossCnt() { return mBossCnt; }
		
		// �� ���� ��������
		static std::vector<std::vector<int>>& GetMapIndex() { return mapIndex; }

		// 1���÷��� �Ǵ� 2�� �÷��� �����ϱ�
		static void SetIsDuo(bool check) { isDuo = check; }


	private:
		static std::vector<Scene*> mScenes;
		static Scene* mActiveScene;
		static Bazzi* mBazzi;
		static int mRealPlayTime;
		static int monstercnt;
		static int mBossCnt;
		static std::vector<std::vector<int>> mapIndex;
		static bool isDuo;
	};
}