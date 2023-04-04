#include "tyIceMapSelect.h"
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
	IceMapSelect::IceMapSelect()
	{
	}
	IceMapSelect::~IceMapSelect()
	{
	}
	void IceMapSelect::Initialize()
	{
		mImage = Resources::Load<Image>(L"IceMapSelect", L"..\\Resources\\UI\\IceMapSelect.bmp");
	}
	void IceMapSelect::Update()
	{
	}
	void IceMapSelect::Render(HDC hdc)
	{
		StretchBlt(hdc, 723, 513, mImage->GetWidth(), mImage->GetHeight(), mImage->GetHdc()
			, 0, 0, mImage->GetWidth(), mImage->GetHeight(), SRCCOPY);
	}
	void IceMapSelect::Release()
	{
	}
}