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
		mImage = Resources::Load<Image>(L"Play_BG", L"..\\Resources\\AlphaBlend\\AlphaBlender.bmp");
	}
	void AlphaBlender::Update()
	{
		mTime += Time::DeltaTime();
	}
	void AlphaBlender::Render(HDC hdc)
	{
		func.BlendOp = AC_SRC_OVER;
		func.BlendFlags = 0;
		func.AlphaFormat = 0; // �̰� �� Ư���ϳ׿�
		func.SourceConstantAlpha = mAlpha;

		AlphaBlend(hdc, 0, 0
			, mImage->GetWidth()
			, mImage->GetHeight()
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