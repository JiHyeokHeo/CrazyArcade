#include "tyLogo_BG.h"
#include "tySceneManager.h"
#include "tyResources.h"
#include "tyImage.h"
#include "tyTime.h"

namespace ty
{
	Logo_BG::Logo_BG()
	{
	}
	Logo_BG::~Logo_BG()
	{
	}
	void Logo_BG::Initialize()
	{
		mImage = Resources::Load<Image>(L"Logo_BG", L"..\\Resources\\Bg\\Logo.bmp");

		//GameObject::Initialize();
	}
	void Logo_BG::Update()
	{
		mTime += Time::DeltaTime();
		
		if (mAlpha > 255 && isTransparent == false)
		{
			isTransparent = true;
			mTime = 0;
		}

		if (mAlpha <= 255 && isTransparent == false)
		{
			mAlpha = mTime * 90;
		}
		else if (isTransparent == true)
		{
			mAlpha = 255 - mTime * 90;
		}

		
		GameObject::Update();
	}
	void Logo_BG::Render(HDC hdc)
	{
		BLENDFUNCTION func = {};
		func.BlendOp = AC_SRC_OVER;
		func.BlendFlags = 0;
		func.AlphaFormat = 0; 
		
		if (mAlpha >= 255)
		{
			func.SourceConstantAlpha = 255;
		}
		else if (mAlpha < 255 && mAlpha >=0)
		{
			func.SourceConstantAlpha = mAlpha;
		}
		else if (mAlpha <= 0)
		{
			func.SourceConstantAlpha = 0;
		}

		//if(mAlpha  0)
		//{
		//	func.SourceConstantAlpha = -(mAlpha);
		//}

		


		AlphaBlend(hdc, 0, 0
			, mImage->GetWidth() * 1.43f
			, mImage->GetHeight() * 1.43f
			, mImage->GetHdc()
			, 0, 0
			, mImage->GetWidth()
			, mImage->GetHeight()
			, func);

		/*StretchBlt(hdc, 0, 0, mImage->GetWidth()*1.43f, mImage->GetHeight()*1.43f
			, mImage->GetHdc(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), SRCCOPY);*/
	}
	void Logo_BG::Release()
	{

	}
}