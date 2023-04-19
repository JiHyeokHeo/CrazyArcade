#include "tySinglePlayUI.h"
#include "tySceneManager.h"
#include "tyResources.h"
#include "tyTransform.h"
#include "tyImage.h"
#include "tyinput.h"
#include "tyObject.h"

namespace ty
{
	SinglePlayUI::SinglePlayUI()
	{
	}
	SinglePlayUI::~SinglePlayUI()
	{
	}
	void SinglePlayUI::Initialize()
	{
		mImage = Resources::Load<Image>(L"SingleUIImage", L"..\\Resources\\UI\\SingleUI.bmp");
	}
	void SinglePlayUI::Update()
	{
		GameObject::Update();
	}
	void SinglePlayUI::Render(HDC hdc)
	{
		TransparentBlt(hdc, 350, 120, mImage->GetWidth() * 1.5f, mImage->GetHeight() * 1.5f, mImage->GetHdc()
			, 0, 0, mImage->GetWidth(), mImage->GetHeight(), RGB(255, 0, 255));
		GameObject::Render(hdc);
	}
	void SinglePlayUI::Release()
	{
	}
}