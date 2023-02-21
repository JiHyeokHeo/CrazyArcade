#include "tyTime.h"
#include "tyApplication.h"

extern ty::Application application;

namespace ty
{
	double Time :: mDeltaTime = 0.0l;
	double Time::mSecond = 0.0f;
	LARGE_INTEGER Time::mCpuFrequency = {};
	LARGE_INTEGER Time::mPrevFrequency = {};
	LARGE_INTEGER Time::mCurFrequency = {};

	void Time::Initialize()
	{
		// CPU ���� ������ ��������
		QueryPerformanceFrequency(&mCpuFrequency);

		// ���α׷��� ó�� �����Ҷ� ������
		QueryPerformanceCounter(&mPrevFrequency);

	}
	void Time::Update()
	{
		QueryPerformanceCounter(&mCurFrequency); 

		double differenceFrequency = mCurFrequency.QuadPart - mPrevFrequency.QuadPart;

		mDeltaTime = differenceFrequency / mCpuFrequency.QuadPart;

		mPrevFrequency.QuadPart = mCurFrequency.QuadPart;

	}
	void Time::Render(HDC hdc)
	{
		mSecond += DeltaTime();

		if (mSecond > 1.0f)
		{
			HWND hwnd = application.GetHwnd();

			wchar_t szFloat[50] = {};
			float FPS = 1.0f / mDeltaTime;
			swprintf_s(szFloat, 50, L"FPS : %d", (UINT)FPS);
			int iLen = wcsnlen_s(szFloat, 50);

			SetWindowText(hwnd, szFloat);

			mSecond = 0.0f;
		}
	}
}