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
		mAlpha = 255;
		mImage = Resources::Load<Image>(L"AlphaBlend", L"..\\Resources\\AlphaBlend\\AlphaBlender.bmp");
	}
	void AlphaBlender::Update()
	{
		mTime += Time::DeltaTime();
	
		mAlpha = mAlpha - mTime * 40;
		
	}
	void AlphaBlender::Render(HDC hdc)
	{
		BLENDFUNCTION func = {};
		func.BlendOp = AC_SRC_OVER;
		func.BlendFlags = 0;
		func.AlphaFormat = 0;
		if (mAlpha >= 255)
		{
			func.SourceConstantAlpha = 255;
		}
		else if (mAlpha < 255 && mAlpha >= 0)
		{
			func.SourceConstantAlpha = mAlpha;
		}
		else if (mAlpha <= 0)
		{
			func.SourceConstantAlpha = 0;
		}

		AlphaBlend(hdc, 0, 0
			, mImage->GetWidth() * 1.43f
			, mImage->GetHeight() * 1.43f
			, mImage->GetHdc()
			, 0, 0
			, mImage->GetWidth()
			, mImage->GetHeight()
			, func);

	}
	void AlphaBlender::Release()
	{
	}
}