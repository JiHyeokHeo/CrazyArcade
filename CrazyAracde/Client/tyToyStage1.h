#pragma once
#include "tyScene.h"
#include "tyPlag_BG.h"


namespace ty
{
	class AlphaBlender;
	class Bazzi; // �̰��� ���漱��
	class ToyStage1 : public Scene
	{
	public:
		ToyStage1();
		~ToyStage1();

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
		class ToyMonster* monster[10];
		class Monster2* monster2[10];
		bool isPlayed;
	};
};