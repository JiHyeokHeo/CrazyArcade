#pragma once
#include "tyScene.h"
#include "tyLobby_BG.h"
#include "tySound.h"

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
		// 1p 확인
		static bool GetFirstPicked() { return isFirstPicked; }
		static void SetisFirstPicked(bool ispicked) { isFirstPicked = ispicked; }

		// 2p 확인
		static bool GetSecondPicked() { return isSecondPicked; }
		static void SetisSecondPicked(bool ispicked) { isSecondPicked = ispicked; }



		bool GetisMapClicked() { return isMapClicked; }
		void SetIsMapClicked(bool check) { isMapClicked = check; }
	private:
		static bool isFirstPicked;
		static bool isSecondPicked;


		Lobby_BG* mLobbyBG;
		AlphaBlender* mBlender;
		class IceMapSelect* mMapSelect;
		eSceneType mSceneType;
		class BazziImage* mBazziUIImage;
		class DaoImage* mDaoUIImage;
		bool isBazziVisited;
		bool isDaoVisited;
		bool isMapClicked;
		

		Sound* Lobby;
		Sound* Click;
		Sound* mouseMove;
	};
}