#include "tyPlayScene.h"
#include "tyBazzi.h"


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
		Bazzi* bazzi = new Bazzi();
		AddGameObject(bazzi, eLayerType::PLAYER);

		Scene::Initialize();
	}
	void PlayScene::Update()
	{
	
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
}