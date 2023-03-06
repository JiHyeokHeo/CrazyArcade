#include "tyPlayScene.h"
#include "tyBazzi.h" // 전방 선언을 할 경우 cpp 파일에 헤더를 추가해야한다.
#include "tyInput.h"
#include "tySceneManager.h"
#include "tyMonster.h"
#include "tyCollisionManager.h"

namespace ty
{
	PlayScene::PlayScene()
	{
	}
	PlayScene::~PlayScene()
	{
	}
	void PlayScene::Initialize()
	{
		mBazzi = new Bazzi();
		AddGameObject(mBazzi, eLayerType::Player);

		mPlayBG = new Play_BG();
		AddGameObject(mPlayBG, eLayerType::BG);

		Monster* monster = new Monster();
		AddGameObject(monster, eLayerType::Monster);
		
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster, true); // 이것이 콜라이더 설정하는 값이다.

		Scene::Initialize();
	}
	void PlayScene::Update()
	{
		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			SceneManager::LoadScene(eSceneType::Lobby);
		}
		Scene::Update();
	}
	void PlayScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
	void PlayScene::Release()
	{
		Scene::Release();
	}
	void PlayScene::OnEnter()
	{
	}
	void PlayScene::OnExit()
	{
		//mbazzi->SetPos(Vector2{ 0.0f, 0.0f });
	}
}