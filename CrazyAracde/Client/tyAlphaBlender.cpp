#include "tyAlphaBlender.h"
#include "tySceneManager.h"
#include "tyResources.h"
#include "tyTime.h"

namespace ty
{
	AlphaBlender::AlphaBlender()
	{
	}
	AlphaBlender::~AlphaBlender()
	{
	}
	void AlphaBlender::Initialize()
	{
		mImage = Resources::Load<Image>(L"Play_BG", L"..\\Resources\\Bg\\play.bmp");
	}

	void AlphaBlender::Update()
	{
		mTime += Time::DeltaTime();
	}
	void AlphaBlender::Render(HDC hdc)
	{
		AlphaBlend(hdc, 0, 0
			, mImage->GetWidth()
			, mImage->GetHeight()
			, mImage->GetHdc()
			, mImage->GetWidth()
			, mImage->GetHeight()
			, RGB(255, 0, 255));
		// 이쪽을 집가서 수정을 할 것
		
	}
	void AlphaBlender::Release()
	{
	}
}