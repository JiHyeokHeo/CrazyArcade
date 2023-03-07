#pragma once
#include "tyScene.h"
#include "tyPlag_BG.h"


namespace ty
{
	class Bazzi; // �̰��� ���漱��
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

	private:
		Bazzi* mBazzi;
		Play_BG* mPlayBG;
	};
};

