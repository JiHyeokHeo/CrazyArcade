#include "tyMapSelect.h"
#include "tySceneManager.h"
#include "tyResources.h"
#include "tyTransform.h"
#include "tyImage.h"
#include "tyinput.h"
#include "tyObject.h"
#include "tyIceSelect.h"

namespace ty
{
	MapSelect::MapSelect()
	{
	}
	MapSelect::~MapSelect()
	{
	}
	void MapSelect::Initialize()
	{
		mImage = Resources::Load<Image>(L"MapSelect", L"..\\Resources\\UI\\MapSelect.bmp");
	}
	void MapSelect::Update()
	{
		Vector2 temp = Input::GetMousePos();
		if (Input::GetKeyDown(eKeyCode::LBUTTON) && temp.y >= 680 && temp.y <= 715 && temp.x >= 460 && temp.x <= 590)
		{
			object::Destroy(this);
		}

		if (Input::GetKeyDown(eKeyCode::LBUTTON) && temp.y >= 680 && temp.y <= 715 && temp.x >= 612 && temp.x <= 739)
		{
			object::Destroy(this);
		}
		GameObject::Update();
	}
	void MapSelect::Render(HDC hdc)
	{
		StretchBlt(hdc, 250, 100, mImage->GetWidth(), mImage->GetHeight(), mImage->GetHdc()
			, 0, 0, mImage->GetWidth(), mImage->GetHeight(), SRCCOPY);
		GameObject::Render(hdc);
	}
	void MapSelect::Release()
	{
	}
}