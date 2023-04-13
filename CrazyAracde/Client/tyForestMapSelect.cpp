#include "tyForestMapSelect.h"
#include "tyMapSelect.h"
#include "tySceneManager.h"
#include "tyResources.h"
#include "tyTransform.h"
#include "tyImage.h"
#include "tyinput.h"
#include "tyObject.h"


namespace ty
{
	ForestMapSelect::ForestMapSelect()
	{
	}
	ForestMapSelect::~ForestMapSelect()
	{
	}
	void ForestMapSelect::Initialize()
	{
		mImage = Resources::Load<Image>(L"ForestMapSelect", L"..\\Resources\\UI\\ForestMapSelect.bmp");
	}
	void ForestMapSelect::Update()
	{
	}
	void ForestMapSelect::Render(HDC hdc)
	{
		StretchBlt(hdc, 725, 517, mImage->GetWidth(), mImage->GetHeight(), mImage->GetHdc()
			, 0, 0, mImage->GetWidth(), mImage->GetHeight(), SRCCOPY);
	}
	void ForestMapSelect::Release()
	{
	}
}