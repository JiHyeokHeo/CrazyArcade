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
		
		void SetMenuBar(bool power);

		//void Release();

		HWND GetHwnd() { return mHwnd; }
		HWND GetToolHwnd() { return mToolHwnd; }
		HDC GetHdc() { return mHdc; }
		UINT GetWidth() { return mWidth; }
		UINT GetHeight() { return mHeight; }

		void SetToolHwnd(HWND hwnd) { mToolHwnd = hwnd; }

	private:
		void clear();
		

	private:
		// main
		HWND mHwnd;
		HDC mHdc;
		HMENU mMenubar;

		// tool
		HWND mToolHwnd;

		// ����� ĳ���Ͱ� 100���� �Ǹ� DC�� 100���� �ʿ�!
		HBITMAP mBackBuffer;
		HDC mBackHDC;

		UINT mWidth;
		UINT mHeight;

		Vector2 mPos;
		//Scene mScene[256];
	};
}