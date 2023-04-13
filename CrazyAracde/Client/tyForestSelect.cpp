#include "tyForestSelect.h"
#include "tyMapSelect.h"
#include "tySceneManager.h"
#include "tyResources.h"
#include "tyTransform.h"
#include "tyImage.h"
#include "tyinput.h"
#include "tyObject.h"


namespace ty
{
	ForestSelect::ForestSelect()
	{
	}
	ForestSelect::~ForestSelect()
	{
	}
	void ForestSelect::Initialize()
	{
		mImage = Resources::Load<Image>(L"ForestRandom", L"..\\Resources\\UI\\ForestRandom.bmp");
	}
	void ForestSelect::Update()
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
	void ForestSelect::Render(HDC hdc)
	{
		StretchBlt(hdc, 280, 214, mImage->GetWidth(), mImage->GetHeight(), mImage->GetHdc()
			, 0, 0, mImage->GetWidth(), mImage->GetHeight(), SRCCOPY);
		GameObject::Render(hdc);
	}
	void ForestSelect::Release()
	{
	}
}