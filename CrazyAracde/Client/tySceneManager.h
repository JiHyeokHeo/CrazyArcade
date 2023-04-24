#pragma once
#include "tyScene.h"

namespace ty
{
	class Bazzi;
	class Dao;
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

		static void SetDao(Dao* dao) { mDao = dao; }
		static void DeleteDao() { mDao = nullptr; }

		// �ٸ� Ŭ�������� ����ϱ� ���� ����
		static Bazzi* GetBazzi() { return mBazzi; }
		static Dao* GetDao() { return mDao; }
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
		static bool GetIsFirstPlayer() { return isFirstPlayer; }
		static bool GetIsDuo() { return isDuo; }

		// ĳ���� ����
		static void SetFirstCharactorPick(eCharactorPick pick) { mFirstPick = pick; }
		static eCharactorPick GetFirstCharactorPick() { return mFirstPick; }

		static void SetSecondCharactorPick(eCharactorPick pick) { mSecondPick = pick; }
		static eCharactorPick GetSecondCharactorPick() { return mSecondPick; }

	private:
		static std::vector<Scene*> mScenes;
		static Scene* mActiveScene;
		static Bazzi* mBazzi;
		static Dao* mDao;
		static eCharactorPick mFirstPick;
		static eCharactorPick mSecondPick;

		static int mRealPlayTime;
		static int monstercnt;
		static int mBossCnt;
		static std::vector<std::vector<int>> mapIndex;
		static bool isDuo;
		static bool isFirstPlayer;
	};
}