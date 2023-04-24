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

		static bool GetIsPicked() { return isPicked; }
		static void SetIsPicked(bool ispicked) { isPicked = ispicked; }
		bool GetisMapClicked() { return isMapClicked; }
		void SetIsMapClicked(bool check) { isMapClicked = check; }
	private:
		static bool isPicked;

		Lobby_BG* mLobbyBG;
		AlphaBlender* mBlender;
		class IceMapSelect* mMapSelect;
		eSceneType mSceneType;
		class BazziImage* mBazziUIImage;
		class DaoImage* mDaoUIImage;
		bool isBazziVisited;
		bool isDaoVisited;
		bool isMapClicked;
		
	};
}