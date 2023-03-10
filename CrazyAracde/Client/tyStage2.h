#pragma once
#include "tyScene.h"
#include "tyPlag_BG.h"


namespace ty
{
	class Bazzi; // 이것이 전방선언
	class Stage2 : public Scene
	{
	public:
		Stage2();
		~Stage2();

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

