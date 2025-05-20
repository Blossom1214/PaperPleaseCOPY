// PaperPlease_Copy.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "PaperPlease_Copy.h"
#include "DoubleBufferManager.h"
#include "FrameRateManager.h"
#include "StaticRenderCheckPoint.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#define MAX_LOADSTRING 100
#include "SoldierObj.h"
using namespace Gdiplus;
// Global Variables:

HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

ULONG_PTR gdiplusToken;
DoubleBufferManager backBuffer;//더블버퍼링(백버퍼)
HWND g_hWnd = nullptr;//핸들의 또다른이름이됨..
FrameRateManager frameManager;
std::vector<std::unique_ptr<SoldierObj>> testNpcs;
void SpawnTestSoldier();//test
// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{

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

    MSG msg;
    frameManager.Init(144);
    
    // Main message loop:
    while (true)
    {
        frameManager.BeginFrame();
        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
                goto ExitLoop;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
       //이위치에서 업데이트를 받아야하는가?!(맞는거같긴한데... 어음...음..으?)
        backBuffer.Clear(Color(255,0,0,0));
        RECT clientRect;
        GetClientRect(g_hWnd, &clientRect);
        float sx = static_cast<float>(clientRect.right - clientRect.left) / RenderManager::BASE_WIDTH;
        float sy = static_cast<float>(clientRect.bottom - clientRect.top) / RenderManager::BASE_HEIGHT;
        for (auto& npc : testNpcs)
        {
            npc->Update(frameManager.GetDeltaTime());
            npc->Render(backBuffer.GetGraphics());
        }
        RenderManager::GetInstance().RenderAll(backBuffer.GetGraphics(), sx, sy);
        RenderManager::GetInstance().GetDynamicLayer().Clear();
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
   InitStaticRenderLayer(resMgr.GetImageResource(L"CheckpointBack"));
   InitStaticRenderLayer(resMgr.GetImageResource(L"BoothWall"));
   InitStaticRenderLayer(resMgr.GetImageResource(L"Desk"));
   SpawnTestSoldier();//test
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
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
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

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);


    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
//test
void SpawnTestSoldier()
{
    const AnimationSequence* seq = AnimationManager::GetInstance().Get(L"soldier", L"walk");
    auto soldier = std::make_unique<SoldierObj>(L"soldier");
    soldier->GetAnimator()->SetSequence(seq);
    soldier->SetPosition({ 100.0f, 300.0f });
    soldier->StartWalkingTo({ 600.0f, 100.0f });
    testNpcs.emplace_back(std::move(soldier));
}