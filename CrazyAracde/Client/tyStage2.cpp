#include "tyStage2.h"
#include "tyBazzi.h" // ���� ������ �� ��� cpp ���Ͽ� ����� �߰��ؾ��Ѵ�.
#include "tyInput.h"
#include "tySceneManager.h"
#include "tyMonster.h"
#include "tyCollisionManager.h"
#include "tyTransform.h"
#include "tyCamera.h"
#include "tyObject.h"

namespace ty
{
	Stage2::Stage2()
	{
	}
	Stage2::~Stage2()
	{
	}
	void Stage2::Initialize()
	{
	}
	void Stage2::Update()
	{
		Scene::Update();
	}
	void Stage2::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
	void Stage2::Release()
	{
		Scene::Release();
	}
	void Stage2::OnEnter()
	{
	}
	void Stage2::OnExit()
	{
	}
}