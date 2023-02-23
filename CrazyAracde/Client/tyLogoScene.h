#pragma once
#include "tyScene.h"
#include "tyLogo_BG.h"

namespace ty
{
	class LogoScene : public Scene
	{
	public:
		LogoScene();
		~LogoScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;
	private:
		Logo_BG* mLogoBG;
	};
};

