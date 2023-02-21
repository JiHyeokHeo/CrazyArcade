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

		Vector2 mPos;
		//Scene mScene[256];
	};
}