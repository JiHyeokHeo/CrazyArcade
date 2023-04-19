#include "tyDuoPlayUI.h"
#include "tySceneManager.h"
#include "tyResources.h"
#include "tyTransform.h"
#include "tyImage.h"
#include "tyinput.h"
#include "tyObject.h"

namespace ty
{
	DuoPlayUI::DuoPlayUI()
	{
	}
	DuoPlayUI::~DuoPlayUI()
	{
	}
	void DuoPlayUI::Initialize()
	{
		mImage = Resources::Load<Image>(L"DuoUIImage", L"..\\Resources\\UI\\DuoUI.bmp");
	}
	void DuoPlayUI::Update()
	{
		GameObject::Update();
	}
	void DuoPlayUI::Render(HDC hdc)
	{
		TransparentBlt(hdc, 720, 120, mImage->GetWidth() * 1.5f, mImage->GetHeight() * 1.5f, mImage->GetHdc()
			, 0, 0, mImage->GetWidth(), mImage->GetHeight(), RGB(255, 0, 255));
		GameObject::Render(hdc);
	}
	void DuoPlayUI::Release()
	{
	}
}