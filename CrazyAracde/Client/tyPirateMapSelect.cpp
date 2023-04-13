#include "tyPirateMapSelect.h"
#include "tyMapSelect.h"
#include "tySceneManager.h"
#include "tyResources.h"
#include "tyTransform.h"
#include "tyImage.h"
#include "tyinput.h"
#include "tyObject.h"

namespace ty
{
	PirateMapSelect::PirateMapSelect()
	{
	}
	PirateMapSelect::~PirateMapSelect()
	{
	}
	void PirateMapSelect::Initialize()
	{
		mImage = Resources::Load<Image>(L"PirateMapSelect", L"..\\Resources\\UI\\PirateMapSelect.bmp");
	}
	void PirateMapSelect::Update()
	{
	}
	void PirateMapSelect::Render(HDC hdc)
	{
		StretchBlt(hdc, 725, 517, mImage->GetWidth(), mImage->GetHeight(), mImage->GetHdc()
			, 0, 0, mImage->GetWidth(), mImage->GetHeight(), SRCCOPY);
	}
	void PirateMapSelect::Release()
	{
	}
}