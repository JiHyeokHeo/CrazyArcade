#pragma once
#include "tyScene.h"
#include "tyPlag_BG.h"


namespace ty
{
	class AlphaBlender;
	class Bazzi; // �̰��� ���漱��
	class PlaySceneStage3 : public Scene
	{
	public:
		PlaySceneStage3();
		~PlaySceneStage3();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;


		virtual void OnEnter() override;
		virtual void OnExit() override;

		/*static Bazzi* GetBazzi() { return mBazzi; }*/
	private:
		Bazzi* mBazzi;
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
		int mBossCnt;
		class PirateBoss* Bossmonster[3];
		bool isPlayed;

	};
};
