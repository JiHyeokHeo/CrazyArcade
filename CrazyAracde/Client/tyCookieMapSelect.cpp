#include "tyCookieMapSelect.h"
#include "tyMapSelect.h"
#include "tySceneManager.h"
#include "tyResources.h"
#include "tyTransform.h"
#include "tyImage.h"
#include "tyinput.h"
#include "tyObject.h"


namespace ty
{
	CookieMapSelect::CookieMapSelect()
	{
	}
	CookieMapSelect::~CookieMapSelect()
	{
	}
	void CookieMapSelect::Initialize()
	{
		mImage = Resources::Load<Image>(L"CookieMapSelect", L"..\\Resources\\UI\\CookieMapSelect.bmp");
	}
	void CookieMapSelect::Update()
	{
	}
	void CookieMapSelect::Render(HDC hdc)
	{
		StretchBlt(hdc, 725, 517, mImage->GetWidth(), mImage->GetHeight(), mImage->GetHdc()
			, 0, 0, mImage->GetWidth(), mImage->GetHeight(), SRCCOPY);
	}
	void CookieMapSelect::Release()
	{
	}
}