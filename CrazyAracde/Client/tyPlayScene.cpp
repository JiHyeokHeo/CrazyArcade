#include "tyPlayScene.h"
#include "tyBazzi.h" // 전방 선언을 할 경우 cpp 파일에 헤더를 추가해야한다.
#include "tyInput.h"
#include "tySceneManager.h"


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
		//mPlayBG = new Play_BG();
		AddGameObject(mBazzi, eLayerType::Player);
		//AddGameObject(mPlayBG, eLayerType::BG);
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