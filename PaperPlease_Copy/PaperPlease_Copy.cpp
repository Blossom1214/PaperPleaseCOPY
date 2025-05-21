// PaperPlease_Copy.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "PaperPlease_Copy.h"
#include "DoubleBufferManager.h"
#include "FrameRateManager.h"
#include "StaticRenderCheckPoint.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "MainGameScene.h"
#define MAX_LOADSTRING 100
#include "Define.h"
#include "SoldierObj.h"
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
using namespace Gdiplus;
// Global Variables:

HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

ULONG_PTR gdiplusToken;
DoubleBufferManager backBuffer;//더블버퍼링(백버퍼)
HWND g_hWnd = nullptr;//핸들의 또다른이름이됨..
FrameRateManager frameManager;
// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{

    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    GdiplusStartupInput gdiInput;
    GdiplusStartup(&gdiplusToken, &gdiInput, nullptr);
    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_PAPERPLEASECOPY, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PAPERPLEASECOPY));
    //여기서 씬매니저 이니셜라이즈로 초기시작화면셋팅
    auto& SceneMgr = SceneManager::GetInstance();
    auto& renMgr = RenderManager::GetInstance();
    MSG msg;
    frameManager.Init(144);
    
    // Main message loop:
    while (true)
    {
        frameManager.BeginFrame();
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
                goto ExitLoop;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        backBuffer.Clear(Color(255,0,0,0));
        RECT clientRect;
        GetClientRect(g_hWnd, &clientRect);
        float sx = static_cast<float>(clientRect.right - clientRect.left) / RenderManager::BASE_WIDTH;
        float sy = static_cast<float>(clientRect.bottom - clientRect.top) / RenderManager::BASE_HEIGHT;
        SceneMgr.UpdateScene(frameManager.GetDeltaTime());
        SceneMgr.RenderScene();
        renMgr.RenderAll(backBuffer.GetGraphics(), sx, sy);
        renMgr.GetDynamicLayer().Clear();
        backBuffer.Present(g_hWnd);
        frameManager.EndFrame();
        
    }
ExitLoop:
    auto& resMgr = ResourceManager::GetInstance();
    resMgr.Clear();
    backBuffer.Release();
    GdiplusShutdown(gdiplusToken);
    return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW|CS_OWNDC;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(nullptr,IDI_APPLICATION);
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = nullptr;
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable
   RECT desiredClient = { 0, 0, 1280, 720 };
   AdjustWindowRect(&desiredClient, WS_OVERLAPPEDWINDOW, FALSE);

   int winWidth = desiredClient.right - desiredClient.left;
   int winHeight = desiredClient.bottom - desiredClient.top;
   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, winWidth, winHeight, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);
   g_hWnd = hWnd;
   backBuffer.Initialize(g_hWnd);
   auto& resMgr = ResourceManager::GetInstance();
   resMgr.InitImgJson();
   resMgr.PreloadingImageJson();
   SceneManager::GetInstance().RegisterScene(SceneType::MAINGAME, std::make_unique<MainGameScene>());
   SceneManager::GetInstance().ChangeScene(SceneType::MAINGAME);
   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    
    switch (message)
    {
    case WM_PAINT:
        {
              
            return DefWindowProc(hWnd, message, wParam, lParam);
            // TODO: Add any drawing code that uses hdc here...
            
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

