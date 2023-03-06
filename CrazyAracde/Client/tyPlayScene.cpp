#include "tyPlayScene.h"
#include "tyBazzi.h" // ���� ������ �� ��� cpp ���Ͽ� ����� �߰��ؾ��Ѵ�.
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
		
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster, true); // �̰��� �ݶ��̴� �����ϴ� ���̴�.

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