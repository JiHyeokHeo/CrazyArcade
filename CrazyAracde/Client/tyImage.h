#pragma once
#include "tyResource.h"


namespace ty
{
	class Image : public Resource
	{
	public:
		static Image* Create(const std::wstring& name, UINT width, UINT height, COLORREF rgb = RGB(0,0,0));

		Image();
		~Image();

		virtual HRESULT Load(const std::wstring& path) override;

		COLORREF GetPixel(int x, int y);
		void SetPixel(int x, int y, COLORREF color);
		
		HDC GetHdc() { return mHdc; }
		HBITMAP GetBitmap() { return mBitmap; }
		UINT GetWidth() {return mWidth; }
		UINT GetHeight() { return mHeight; }
	private:
		HBITMAP mBitmap;
		HDC mHdc;
		UINT mWidth;
		UINT mHeight;
	};
}
