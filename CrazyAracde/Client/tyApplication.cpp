#include "tyApplication.h"
#include "tySceneManager.h"
#include "tyTime.h"
#include "tyinput.h"
namespace ty
{
	Application::Application()
		: mHwnd(NULL)
		, mHdc(NULL)
	{
	}
	Application::~Application()
	{
	}

	void Application::Initialize(HWND hWnd)
	{
		mHwnd = hWnd;
		mHdc = GetDC(hWnd); 

		Time::Initialize();
		Input::Initialize();
;		SceneManager::Initialize();
	}

	void Application::Run()
	{
		Update();
		Render();
	}

	void Application::Update()
	{
		Time::Update();
		Input::Update();
		SceneManager::Update();
	}

	void Application::Render()
	{
		Time::Render(mHdc);
		Input::Render(mHdc);
		SceneManager::Render(mHdc);
	}
	
}



