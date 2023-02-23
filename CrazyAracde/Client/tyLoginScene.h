#pragma once
#include "tyScene.h"
#include "tyLogin_BG.h"

namespace ty
{
	class LoginScene : public Scene
	{
	public:
		LoginScene();
		~LoginScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;
	private:
		Login_BG* mLoginBG;
	};
}
