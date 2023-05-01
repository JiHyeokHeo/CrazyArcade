#pragma once
#include "tyScene.h"
#include "tyPlag_BG.h"


namespace ty
{
	class AlphaBlender;
	class Dao;
	class Bazzi; // 이것이 전방선언
	class PlayScene : public Scene
	{
	public:
		PlayScene();
		~PlayScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;


		virtual void OnEnter() override;
		virtual void OnExit() override;

		/*static Bazzi* GetBazzi() { return mBazzi; }*/

	private:
		Bazzi* mBazzi;
		Dao* mDao;
		class InGameBazziUI* mBazziUI;
		class InGameDaoUI* mDaoUI;
		Play_BG* mPlayBG;
		AlphaBlender* mBlender;
		Image* mImage;
		int monstercnt;
		bool isLoad;
		int PlayIndex[13][15];
		class Timer* time[5];
		float mTime;
		class Monster* monster[10];
		class Monster2* monster2[10];
		bool isPlayed;
		
		class Sound* iceStage;
	};
};

