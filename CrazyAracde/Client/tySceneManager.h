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

		// 배찌 씬 매니저에 등록
		static void SetBazzi(Bazzi* bazzi) { mBazzi = bazzi; }
		static void DeleteBazzi() { mBazzi = nullptr; }

		static void SetDao(Dao* dao) { mDao = dao; }
		static void DeleteDao() { mDao = nullptr; }

		// 다른 클래스에서 사용하기 위해 만듬
		static Bazzi* GetBazzi() { return mBazzi; }
		static Dao* GetDao() { return mDao; }
		// 시간 설정 및 가져오기
		static void SetmTime(int time) { mRealPlayTime = time; }
		static int GetTime() { return mRealPlayTime; }

		// 몬스터 갯수 정하기
		static void SetMonsterCnt(int cnt) { monstercnt = cnt; }
		static int GetMonsterCnt() { return monstercnt; }

		// 보스 몬스터 갯수 정하기
		static void SetBossCnt(int cnt) { mBossCnt = cnt; }
		static int GetBossCnt() { return mBossCnt; }
		
		// 맵 정보 가져오기
		static std::vector<std::vector<int>>& GetMapIndex() { return mapIndex; }

		// 1인플레이 또는 2인 플레이 구분하기
		static void SetIsDuo(bool check) { isDuo = check; }
		static bool GetIsFirstPlayer() { return isFirstPlayer; }
		static bool GetIsDuo() { return isDuo; }

		// 캐릭터 선택
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