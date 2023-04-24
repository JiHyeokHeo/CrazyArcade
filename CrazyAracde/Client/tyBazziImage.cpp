#include "tyBazziImage.h"
#include "tySceneManager.h"
#include "tyResources.h"
#include "tyTransform.h"
#include "tyImage.h"
#include "tyinput.h"
#include "tyObject.h"
#include "tyBazziLobbyUI.h"
#include "tyLobbyScene.h"
namespace ty
{
	BazziImage::BazziImage()
	{
	}
	BazziImage::~BazziImage()
	{
	}
	void BazziImage::Initialize()
	{
		mImage = Resources::Load<Image>(L"BazziUIImage", L"..\\Resources\\UI\\bazzi_image.bmp");
	}
	void BazziImage::Update()
	{
		Vector2 temp = Input::GetMousePos();
		//if (temp.y <= 300 || temp.y >= 360 || temp.x <= 950 || temp.x >= 1040)
		//{
		//	if (isClicked == false)
		//	{
		//		object::Pause(this);
		//	}
		//}
		
		
		//if (Input::GetKeyDown(eKeyCode::LBUTTON) && temp.y >= 300 && temp.y <= 360 && temp.x >= 950 && temp.x <= 1040)
		//{
		//	if (LobbyScene::GetIsPicked() == false)
		//	{
		//		object::Instantiate<BazziLobbyUI>(eLayerType::UI);
		//	}
		//	isClicked = true;
		//}

		//if (Input::GetKeyDown(eKeyCode::LBUTTON) && temp.y >= 300 && temp.y <= 360 && temp.x >= 950 && temp.x <= 1040)
		//{
		//	isClicked = true;
		//}
		GameObject::Update();
	}
	void BazziImage::Render(HDC hdc)
	{
		if (LobbyScene::GetFirstPicked() == true && LobbyScene::GetSecondPicked() == true && SceneManager::GetSecondCharactorPick() == eCharactorPick::Bazzi && SceneManager::GetFirstCharactorPick() == eCharactorPick::Bazzi)
		{
			 StretchBlt(hdc, LOWERSELECT_X, LOWERSELECT_Y, mImage->GetWidth() * 1.5f, mImage->GetHeight() * 1.5f, mImage->GetHdc()
				 , 0, 0, mImage->GetWidth(), mImage->GetHeight(), SRCCOPY);
		}
		if (LobbyScene::GetFirstPicked() == true && SceneManager::GetFirstCharactorPick() == eCharactorPick::Bazzi)
		{
			StretchBlt(hdc, UPPERSELECT_X, UPPERSELECT_Y, mImage->GetWidth()* 1.5f, mImage->GetHeight()* 1.5f, mImage->GetHdc()
				, 0, 0, mImage->GetWidth(), mImage->GetHeight(), SRCCOPY);
		}
		else if (LobbyScene::GetSecondPicked() == true && SceneManager::GetSecondCharactorPick() == eCharactorPick::Bazzi)
		{
			StretchBlt(hdc, LOWERSELECT_X, LOWERSELECT_Y, mImage->GetWidth() * 1.5f, mImage->GetHeight() * 1.5f, mImage->GetHdc()
				, 0, 0, mImage->GetWidth(), mImage->GetHeight(), SRCCOPY);
		}
	
		GameObject::Render(hdc);
	}
	void BazziImage::Release()
	{
	}
}