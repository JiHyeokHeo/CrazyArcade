#pragma once
#include "tyScene.h"


namespace ty
{
	class Bazzi; 
	class BG;
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
		BG* mBG;
	};
};

