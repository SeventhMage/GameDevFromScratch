#define UNICODE
#include <Windows.h>
#include <stdio.h>
#include <math.h>
#include <stdio.h>

const int FRAMES_PER_SECOND = 120;
const int SKIP_TICKS = 1000 / FRAMES_PER_SECOND;
const int WIDTH = 800;
const int HEIGHT = 600;

unsigned long long nextGameTick = GetTickCount();

HWND hWnd;
HDC hMemoryDC;
HDC hWindowDC;
HBITMAP hBitmap;
BITMAPINFO bmpInfo;
unsigned int* buffer = nullptr;

typedef struct
{
    int x;
    int y;
}Vector2;

typedef struct
{
    Vector2 position[3];
}Triangle;

Triangle triangle;

void Update(int delta);
void Render();
void DrawBuffer(unsigned char *buffer);


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

int main(int argc, char *argv[])
{
    // Register the window class.
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
    clientSize.right = WIDTH;
    clientSize.bottom = HEIGHT;

    AdjustWindowRect(&clientSize, style, FALSE);

    int realWidth = clientSize.right - clientSize.left;
    int realHeight = clientSize.bottom - clientSize.top;

    int windowLeft = (GetSystemMetrics(SM_CXSCREEN) - realWidth) / 2;
    int windowTop = (GetSystemMetrics(SM_CYSCREEN) - realHeight) / 2;

    // Create the window.
    hWnd = CreateWindowEx(
        0,                              // Optional window styles.
        CLASS_NAME,                     // Window class
        L"Hello Triangle",    // Window text
        style,            // Window style

        // Size and position
        windowLeft, windowTop, realWidth, realHeight,

        NULL,       // Parent window    
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
    );

    if (hWnd == NULL)
    {
        return 0;
    }
    ShowWindow(hWnd, SW_SHOWNORMAL);
    UpdateWindow(hWnd);
    MoveWindow(hWnd, windowLeft, windowTop, realWidth, realHeight, TRUE);

    ShowCursor(TRUE);


	memset(&bmpInfo, 0, sizeof(BITMAPINFO));
	bmpInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmpInfo.bmiHeader.biWidth = WIDTH;
	bmpInfo.bmiHeader.biHeight = -HEIGHT;
	bmpInfo.bmiHeader.biPlanes = 1;
	bmpInfo.bmiHeader.biBitCount = 32;
	bmpInfo.bmiHeader.biCompression = BI_RGB;

    hWindowDC = GetDC(hWnd);
    hMemoryDC = CreateCompatibleDC(hWindowDC);

    hBitmap = CreateDIBSection(hMemoryDC, &bmpInfo, DIB_RGB_COLORS,(void**)&buffer, 0, 0);

    SelectObject(hMemoryDC, hBitmap);

    // Run the message loop.
    bool isRunning = true;
    MSG msg = { };
    while (isRunning)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);

            if (msg.message == WM_QUIT)
                isRunning = false;
        }

        unsigned long long curTick = GetTickCount();
        
        long long sleepTime = nextGameTick - curTick;
        if (sleepTime <= 0)
        {
            nextGameTick = curTick + SKIP_TICKS;
            Update(SKIP_TICKS - (int)sleepTime);
            Render();
        }
        else
        {
            Sleep(sleepTime);
        }
    }

    DeleteObject(hBitmap);
    DeleteDC(hMemoryDC);
    ReleaseDC(hWnd, hWindowDC);

    free(buffer);
    return 0;
}

void Update(int delta)
{
    Vector2 initValue[3] = { {400, 100}, {100, 500}, {700, 500} };
    static float rot = 0.f;
    rot += 0.05f;
    if (rot > 3.14 * 2)
        rot = 0;
    float c = cos(rot);
    float s = sin(rot);
    for (int i = 0; i < 3; ++i)
    {
        initValue[i].x -= WIDTH * 0.5f;
        initValue[i].y -= HEIGHT * 0.5f;
        triangle.position[i].x = initValue[i].x * c - initValue[i].y * s;
        triangle.position[i].y = initValue[i].x * s + initValue[i].y * c;
        triangle.position[i].x += WIDTH * 0.5f;
        triangle.position[i].y += HEIGHT * 0.5f;
        initValue[i].x += WIDTH * 0.5f;
        initValue[i].y += HEIGHT * 0.5f;
    }
}

void Render()
{
    for (int i = 0; i < WIDTH; ++i)
    {
        for (int j = 0; j < HEIGHT; ++j)
        {
            Vector2 triEdge0 = { triangle.position[1].x - triangle.position[0].x, triangle.position[1].y - triangle.position[0].y };
            Vector2 triEdge1 = { triangle.position[2].x - triangle.position[1].x, triangle.position[2].y - triangle.position[1].y };
            Vector2 triEdge2 = { triangle.position[0].x - triangle.position[2].x, triangle.position[0].y - triangle.position[2].y };
            Vector2 pTo0 = { i - triangle.position[0].x, j - triangle.position[0].y };
            Vector2 pTo1 = { i - triangle.position[1].x, j - triangle.position[1].y };
            Vector2 pTo2 = { i - triangle.position[2].x, j - triangle.position[2].y };

            if (pTo0.x * triEdge0.y - triEdge0.x * pTo0.y > 0
                && pTo1.x * triEdge1.y - triEdge1.x * pTo1.y > 0
                && pTo2.x * triEdge2.y - triEdge2.x * pTo2.y > 0)
                buffer[j * WIDTH + i] = 0xffff0000;
            else
                buffer[j * WIDTH + i] = 0x00000000;
        }
    }

    DrawBuffer((unsigned char *)buffer);
}

void DrawBuffer(unsigned char * buffer)
{
    //StretchDIBits(hWindowDC, 0, 0, WIDTH, HEIGHT, 0, HEIGHT, WIDTH, -HEIGHT, buffer, &bmpInfo, DIB_RGB_COLORS, SRCCOPY);

    BitBlt(hWindowDC, 0, 0, WIDTH, HEIGHT, hMemoryDC, 0, 0, SRCCOPY);
}
