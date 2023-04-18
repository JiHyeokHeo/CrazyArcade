#pragma once
#include "tyScene.h"
#include "tyPlag_BG.h"

namespace ty
{
	class Bazzi; // 이것이 전방선언
	class ForestStage2 : public Scene
	{
	public:
		ForestStage2();
		~ForestStage2();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;


		virtual void OnEnter() override;
		virtual void OnExit() override;

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
		class ForestMonster* monster[10];
		class Monster2* monster2[10];
		bool isPlayed;
	};
};


