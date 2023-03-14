#include "tyPlayScene.h"
#include "tyBazzi.h" // ���� ������ �� ��� cpp ���Ͽ� ����� �߰��ؾ��Ѵ�.
#include "tyInput.h"
#include "tySceneManager.h"
#include "tyMonster.h"
#include "tyCollisionManager.h"
#include "tyTransform.h"
#include "tyCamera.h"
#include "tyObject.h"
#include "tyBossMonster.h"
#include "tyAlphaBlender.h"

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
		mBazzi = object::Instantiate<Bazzi>(Vector2(400.0f, 400.0f), eLayerType::Player);
		//Camera::SetTarget(mBazzi);
		object::Instantiate<Play_BG>(eLayerType::BG);
		object::Instantiate<BossMonster>(Vector2(110.0f, 300.0f), eLayerType::Player);
		object::Instantiate<Monster>(Vector2(300.0f, 400.0f), eLayerType::Player);
		object::Instantiate<Monster>(Vector2(600.0f, 400.0f), eLayerType::Player);


		//CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster, true); // �̰��� �ݶ��̴� �����ϴ� ���̴�.
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
		//mBlender = object::Instantiate<AlphaBlender>(eLayerType::AlphaBlender);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Player, true);
		
	}
	void PlayScene::OnExit()
	{
		mBazzi->GetComponent<Transform>()->SetPos(Vector2(300.0f, 300.0f)); // ȭ�� ��ȯ�� ��� �߰�
		mBazzi->SetState(GameObject::eState::Active);
		//object::Destroy(mBlender);
	}
}