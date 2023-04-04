#include "tyIceSelect.h"
#include "tyMapSelect.h"
#include "tySceneManager.h"
#include "tyResources.h"
#include "tyTransform.h"
#include "tyImage.h"
#include "tyinput.h"
#include "tyObject.h"

namespace ty
{
	IceSelect::IceSelect()
	{
	}
	IceSelect::~IceSelect()
	{
	}
	void IceSelect::Initialize()
	{
		mImage = Resources::Load<Image>(L"IceRandom", L"..\\Resources\\UI\\IceRandom.bmp");
	}
	void IceSelect::Update()
	{
		Vector2 temp = Input::GetMousePos();
		if (Input::GetKeyDown(eKeyCode::LBUTTON) && temp.y >= 680 && temp.y <= 715 && temp.x >= 460 && temp.x <= 590)
		{
			object::Destroy(this);
		}
		GameObject::Update();
	}
	void IceSelect::Render(HDC hdc)
	{
		StretchBlt(hdc, 324, 243, mImage->GetWidth(), mImage->GetHeight() ,  mImage->GetHdc()
			, 0, 0, mImage->GetWidth(), mImage->GetHeight(), SRCCOPY);
		GameObject::Render(hdc);
	}
	void IceSelect::Release()
	{
	}
}