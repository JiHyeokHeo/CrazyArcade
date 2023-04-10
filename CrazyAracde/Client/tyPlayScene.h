#pragma once
#include "tyScene.h"
#include "tyPlag_BG.h"


namespace ty
{
	class AlphaBlender;
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
		Play_BG* mPlayBG;
		AlphaBlender* mBlender;
		Image* mImage;
		int monstercnt;
		bool isLoad;
		int PlayIndex[13][15];
	};
};

