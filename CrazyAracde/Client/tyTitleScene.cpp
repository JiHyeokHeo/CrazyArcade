#include "tyTitleScene.h"
#include "tyInput.h"
#include "tySceneManager.h"

namespace ty
{
	TitleScene::TitleScene()
	{
	}
	TitleScene::~TitleScene()
	{
	}
	void TitleScene::Initialize()
	{
	}
	void TitleScene::Update()
	{
		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			SceneManager::LoadScene(eSceneType::Play);
		}

	}
	void TitleScene::Render(HDC hdc)
	{
	}
	void TitleScene::Release()
	{
	}
	void TitleScene::OnEnter()
	{
	}
	void TitleScene::OnExit()
	{
	}
}