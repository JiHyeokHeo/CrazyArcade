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

	private:
		HWND mHwnd;
		HDC mHdc;

		// ����� ĳ���Ͱ� 100���� �Ǹ� DC�� 100���� �ʿ�!
		HBITMAP mBackBuffer;
		HDC mBackHDC;

		UINT mWidth;
		UINT mHeight;

		Vector2 mPos;
		//Scene mScene[256];
	};
}