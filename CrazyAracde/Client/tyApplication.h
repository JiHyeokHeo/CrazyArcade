#pragma once
#include "ToryEngine.h"

namespace ty
{
	class Application
	{
	public:
		Application();
		~Application();

		void Initialize(HWND hWnd);
		void Run();
		void Update();
		void Render();
		
		//void Release();

		HWND GetHwnd() { return mHwnd; }
		HDC GetHdc() { return mHdc; }


	private:
		void clear();
		

	private:
		HWND mHwnd;
		HDC mHdc;

		// 백버퍼 캐릭터가 100개가 되면 DC도 100개가 필요!
		HBITMAP mBackBuffer;
		HDC mBackHDC;

		UINT mWidth;
		UINT mHeight;

		Vector2 mPos;
		//Scene mScene[256];
	};
}