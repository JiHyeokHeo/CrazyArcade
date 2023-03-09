#include "tyPlayScene.h"
#include "tyBazzi.h" // 전방 선언을 할 경우 cpp 파일에 헤더를 추가해야한다.
#include "tyInput.h"
#include "tySceneManager.h"
#include "tyMonster.h"
#include "tyCollisionManager.h"
#include "tyTransform.h"
#include "tyCamera.h"
#include "tyObject.h"

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
		Scene::Initialize();
		object::Instantiate<Bazzi>(Vector2(400.0f, 400.0f), eLayerType::Player);
		//Camera::SetTarget(mBazzi);

		object::Instantiate<Play_BG>(eLayerType::BG);
		object::Instantiate<Monster>(Vector2(500.0f, 400.0f), eLayerType::Monster);
		object::Instantiate<Monster>(Vector2(800.0f, 400.0f), eLayerType::Monster);


		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster, true); // 이것이 콜라이더 설정하는 값이다.
		//CollisionManager::SetLayer(eLayerType::Player, eLayerType::Bomb, true);
		//CollisionManager::SetLayer(eLayerType::Monster, eLayerType::Bomb, true);
		//CollisionManager::SetLayer(eLayerType::Bomb, eLayerType::Bomb, true);

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
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster, true);
	}
	void PlayScene::OnExit()
	{
		//mBazzi->GetComponent<Transform>()->SetPos(Vector2(300.0f, 300.0f)); // 화면 전환시 기능 추가
	}
}