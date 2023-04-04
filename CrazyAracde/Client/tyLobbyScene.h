#pragma once
#include "tyScene.h"
#include "tyLobby_BG.h"

namespace ty
{
	class AlphaBlender;
	class LobbyScene : public Scene
	{
	public:
		LobbyScene();
		~LobbyScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;
	private:
		Lobby_BG* mLobbyBG;
		AlphaBlender* mBlender;
		IceMapSelect* mMapSelect;
		eSceneType mSceneType;
	};
}