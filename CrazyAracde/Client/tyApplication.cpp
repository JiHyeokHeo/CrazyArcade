#include "Resource.h"
#include "tyApplication.h"
#include "tySceneManager.h"
#include "tyTime.h"
#include "tyinput.h"
#include "tyCollisionManager.h"
#include "tyCamera.h"
#include "tySoundManager.h"

namespace ty
{
	Application::Application()
		: mHwnd(NULL)
		, mHdc(NULL)
	{
	}
	Application::~Application()
	{
		//SceneManager::Release();
		//Time::Release();
	}

	void Application::Initialize(HWND hWnd)
	{
		mHwnd = hWnd;
		mHdc = GetDC(hWnd); 
		mWidth = 1200;
		mHeight = 900;

		//비트맵 해상도를 설정하기 위한 실제 윈도우 크기를 계산해준다.
		RECT rect = { 0,0, mWidth, mHeight };
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

		//GetClientRect(mHwnd, &rect);
		// 윈도우 크기 변경및 출력 설정
		SetWindowPos(mHwnd
			, nullptr, 0, 0
			, rect.right - rect.left
			, rect.bottom - rect.top
			, 0);
		ShowWindow(hWnd, true);

		mBackBuffer = CreateCompatibleBitmap(mHdc, mWidth, mHeight);
		mBackHDC = CreateCompatibleDC(mHdc);
		mMenubar = LoadMenu(nullptr, MAKEINTRESOURCE(IDI_CLIENT));

		HBITMAP defaultBitmap = (HBITMAP)SelectObject(mBackHDC, mBackBuffer);
		DeleteObject(defaultBitmap);

		Time::Initialize();
		Input::Initialize();
		SoundManager::Initialize();
		SceneManager::Initialize();
		/*Camera::Initialize();*/

		SetMenuBar(false);
	}

	void Application::Run()
	{
		Update();
		Render();
		SceneManager::Destroy();
		

	}

	void Application::Update()
	{
		Time::Update();
		Input::Update();
		/*Camera::Update();*/

		SceneManager::Update();
		CollisionManager::Update();
	}

	void Application::Render()
	{
		clear();

		Time::Render(mBackHDC);
		Input::Render(mBackHDC);
		SceneManager::Render(mBackHDC);
		//Camera::Render(mBackHDC);
		

		// 백버퍼에 있는 그림을 원본 버퍼에 그려야 한다. // 원본을 가져다가 복사
		BitBlt(mHdc, 0, 0, mWidth, mHeight, mBackHDC, 0, 0, SRCCOPY);

	}

	void Application::SetMenuBar(bool power)
	{
		SetMenu(mHwnd, mMenubar);

		RECT rect = { 0,0, mWidth, mHeight };
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, power);

		// 윈도우 크기 변경및 출력 설정
		SetWindowPos(mHwnd
			, nullptr, 0, 0
			, rect.right - rect.left
			, rect.bottom - rect.top
			, 0);
		ShowWindow(mHwnd, true);
	}

	void Application::clear()
	{
		// Clear
		HBRUSH whiteBrush = CreateSolidBrush(RGB(255, 255, 255));
		HBRUSH oldBrush = (HBRUSH)SelectObject(mBackHDC, whiteBrush);
		Rectangle(mBackHDC, -1, -1, 1602, 902);
		SelectObject(mBackHDC, oldBrush);
		DeleteObject(whiteBrush);
	}
	
}



