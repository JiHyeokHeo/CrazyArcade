#include "tyStage2.h"
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