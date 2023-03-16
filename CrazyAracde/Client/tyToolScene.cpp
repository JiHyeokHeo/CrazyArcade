#include "tyToolScene.h"
#include "tyApplication.h"
#include "tyImage.h"
#include "tyResources.h"
#include "tyTile.h"
#include "tyObject.h"
#include "tyInput.h"
#include "tyPlag_BG.h"
extern ty::Application application;

namespace ty
{
	ToolScene::ToolScene()
	{
	}
	ToolScene::~ToolScene()
	{
	}
	void ToolScene::Initialize()
	{
		Scene::Initialize();
		
		Image* tile = Resources::Find<Image>(L"TileAtlas");
        Tile* test = object::Instantiate<Tile>(eLayerType::Tile);
        test->InitializeTile(tile, 0);
       // object::Instantiate<Play_BG>(eLayerType::BG);

	}
	void ToolScene::Update()
	{
        Scene::Update();

        Vector2 temp = Input::GetMousePos();

	}
	void ToolScene::Render(HDC hdc)
	{
        HPEN redPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
        HPEN oldPen = (HPEN)SelectObject(hdc, redPen);

        int maxRow = 723 / TILE_SIZE_Y + 1;
        for (size_t y = 0; y < maxRow; y++)
        {
            MoveToEx(hdc, 30, 60 + TILE_SIZE_Y * y, NULL);
            LineTo(hdc, 900, 60 + TILE_SIZE_Y * y);
        }
        int maxColumn = 870 / TILE_SIZE_X + 1;
        for (size_t x = 0; x < maxColumn; x++)
        {
            MoveToEx(hdc, 30 + TILE_SIZE_X * x, 60, NULL);
            LineTo(hdc, 30 + TILE_SIZE_X * x, 756);
        }
        (HPEN)SelectObject(hdc, oldPen);
        DeleteObject(redPen);


        Scene::Render(hdc);
    }
	void ToolScene::Release()
	{
        Scene::Release();
	}
	void ToolScene::OnEnter()
	{
	}
	void ToolScene::OnExit()
	{
	}
}


#include "Resource.h"

LRESULT CALLBACK AtlasWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {
        //512 384
        //HMENU mMenubar = LoadMenu(nullptr, MAKEINTRESOURCE(IDC_CLIENT));
        //SetMenu(hWnd, mMenubar);
        ty::Image* tile = ty::Resources::Load< ty::Image>(L"TileAtlas", L"..\\Resources\\Tile.bmp");
        RECT rect = { 0, 0, tile->GetWidth(), tile->GetHeight() };
        AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

        // 윈도우 크기 변경및 출력 설정
        SetWindowPos(hWnd
            , nullptr, 1200, 0
            , rect.right - rect.left
            , rect.bottom - rect.top
            , 0);
        ShowWindow(hWnd, true);
    }

    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // 메뉴 선택을 구문 분석합니다:
        switch (wmId)
        {
            //case IDM_ABOUT:
            //    DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            //    break;
            //case IDM_EXIT:
            //    DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        ty::Image* tile = ty::Resources::Find<ty::Image>(L"TileAtlas");
        BitBlt(hdc, 0, 0, tile->GetWidth(), tile->GetHeight(), tile->GetHdc(), 0, 0, SRCCOPY);

        //HPEN redPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
        //HPEN oldPen = (HPEN)SelectObject(hdc, redPen);

        //Ellipse(hdc, 0, 0, 100, 100);
        ////RoundRect(hdc, 200, 200, 300, 300, 500, 500);
        //(HPEN)SelectObject(hdc, oldPen);
        //DeleteObject(redPen);
        // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

