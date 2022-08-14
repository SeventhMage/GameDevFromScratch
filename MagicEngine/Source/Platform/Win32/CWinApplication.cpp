#ifdef _WIN32
#define UNICODE
#include "Application/CApplication.h"
#include "Foundation/System/CMain.h"
#include "Foundation/Memory/Memory.h"
#include "SWinRenderContext.h"
#include "Graphic/Rendering/Renderer/SoftRenderer/CSoftRenderer.h"

#include <Windows.h>

namespace Magic
{
    LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        switch (uMsg)
        {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        default:
            break;
        }
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    CApplication::CApplication()
        :Renderer(nullptr), _FPS(60), _MaxFPS(120), _WindowWidth(1280), _WindowHeight(960)
    {
        Renderer = NEW CSoftRenderer(_WindowWidth, _WindowHeight);
    }

    CApplication::~CApplication()
    {
    }

    void CApplication::StartMain()
    {
        const wchar_t *title = L"WinApp";

        const wchar_t CLASS_NAME[] = L"Window";

        HINSTANCE hInstance = GetModuleHandle(NULL);
        WNDCLASSEX wcex;
        wcex.cbSize = sizeof(WNDCLASSEX);
        wcex.style = CS_HREDRAW | CS_VREDRAW;
        wcex.lpfnWndProc = WindowProc;
        wcex.cbClsExtra = 0;
        wcex.cbWndExtra = 0;
        wcex.hInstance = hInstance;
        wcex.hIcon = LoadCursor(NULL, IDC_ICON);
        wcex.hCursor = LoadCursor(NULL, IDI_APPLICATION);
        wcex.hbrBackground = NULL;
        wcex.lpszMenuName = 0;
        wcex.lpszClassName = CLASS_NAME;
        wcex.hIconSm = 0;

        RegisterClassEx(&wcex);

        DWORD style = WS_SYSMENU | WS_BORDER | WS_CAPTION | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;

        RECT clientSize;
        clientSize.top = 0;
        clientSize.left = 0;
        clientSize.right = _WindowWidth;
        clientSize.bottom = _WindowHeight;

        AdjustWindowRect(&clientSize, style, FALSE);

        int realWidth = clientSize.right - clientSize.left;
        int realHeight = clientSize.bottom - clientSize.top;

        int windowLeft = (GetSystemMetrics(SM_CXSCREEN) - realWidth) / 2;
        int windowTop = (GetSystemMetrics(SM_CYSCREEN) - realHeight) / 2;

        HWND hWnd = CreateWindowEx(
            0,           
            CLASS_NAME,  
            title, 
            style, 
            windowLeft, windowTop, realWidth, realHeight,
            NULL,
            NULL,
            hInstance,
            NULL
        );

        if (hWnd == NULL)
        {
            return;
        }
        ShowWindow(hWnd, SW_SHOWNORMAL);
        UpdateWindow(hWnd);
        MoveWindow(hWnd, windowLeft, windowTop, realWidth, realHeight, TRUE);

        ShowCursor(TRUE);

        SWinRenderContext context;
        context.hWnd = hWnd;
        Renderer->InitDriver(&context);

        const int SKIP_TICKS = 1000 / _FPS;
        unsigned long long nextGameTick = GetTickCount();

        bool isRunning = true;
        MSG msg = {};
        while (isRunning)
        {
            if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);

                if (msg.message == WM_QUIT)
                    isRunning = false;
            }

            unsigned long long curTick = ::GetTickCount();

            long long sleepTime = nextGameTick - curTick;
            if (sleepTime <= 0)
            {
                nextGameTick = curTick + SKIP_TICKS;
                Update();
            }
            else
            {
                Sleep(sleepTime);
            }
        }

        Renderer->CleanDriver();
    }


}

int main(int argc, char *argv[])
{
    using namespace Magic;
    CMain::Initialize();
    CApplication::Run();
    CMain::Terminate();
}

#endif