#include "tyDaoImage.h"
#include "tySceneManager.h"
#include "tyResources.h"
#include "tyTransform.h"
#include "tyImage.h"
#include "tyinput.h"
#include "tyObject.h"
#include "tyLobbyScene.h"
#include "tyDaoLobbyUI.h"

namespace ty
{
	DaoImage::DaoImage()
	{
	}
	DaoImage::~DaoImage()
	{
	}
	void DaoImage::Initialize()
	{
		mImage = Resources::Load<Image>(L"DaoUIImage", L"..\\Resources\\UI\\dao_image.bmp");
	}
	void DaoImage::Update()
	{
		Vector2 temp = Input::GetMousePos();
		if (temp.y <= 300 || temp.y >= 360 || temp.x <= 730 || temp.x >= 825)
		{
			if (isClicked == false)
			{
				object::Pause(this);
			}
		}


		if (Input::GetKeyDown(eKeyCode::LBUTTON) && temp.y >= 300 && temp.y <= 360 && temp.x >= 730 && temp.x <= 825)
		{
			if (LobbyScene::GetIsPicked() == false)
			{
				object::Instantiate<DaoLobbyUI>(eLayerType::UI);
			}
			isClicked = true;
		}

		if (Input::GetKeyDown(eKeyCode::LBUTTON) && temp.y >= 300 && temp.y <= 360 && temp.x >= 950 && temp.x <= 1040)
		{
			isClicked = true;
		}
		GameObject::Update();
	}
	void DaoImage::Render(HDC hdc)
	{
		StretchBlt(hdc, UPPERSELECT_X, UPPERSELECT_Y, mImage->GetWidth() * 1.5f, mImage->GetHeight() * 1.5f, mImage->GetHdc()
			, 0, 0, mImage->GetWidth(), mImage->GetHeight(), SRCCOPY);
		GameObject::Render(hdc);
	}
	void DaoImage::Release()
	{
	}
}