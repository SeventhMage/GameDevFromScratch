#define UNICODE
#include <Windows.h>
#include <WinBase.h>
#include <stdio.h>
#include <math.h>
#include <float.h>

#include "Math/Triangle.hpp"
#include "Math/Vector3.hpp"
#include "Math/Matrix4x4.hpp"

using namespace Magic;

const int FRAMES_PER_SECOND = 120;
const int SKIP_TICKS = 1000 / FRAMES_PER_SECOND;
const int WIDTH = 800;
const int HEIGHT = 600;

unsigned long long nextGameTick = GetTickCount();

HWND hWnd;
BITMAPINFO bmpInfo;
unsigned int buffer[WIDTH * HEIGHT];
float depth[WIDTH * HEIGHT];
Rayf rays[WIDTH][HEIGHT];

Trianglef triangle(Vector3f(-1.f, -1.f, 0.f), Vector3f(1.f, -1.f, 0.f), Vector3f(0.f, 1.f, 0.f));
Trianglef triangleToRender = triangle;
Matrix4x4f triToWoldMatrix;

Spheref sphere(Vector3f(0.f, 0.f, -8.f), 1.0f);

void Update(int delta);
void ClearBuffer();
void Render();
void DrawBuffer(unsigned char *buffer);
void Initalize();


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
        L"Triangle",    // Window text
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
	bmpInfo.bmiHeader.biHeight = HEIGHT;
	bmpInfo.bmiHeader.biPlanes = 1;
	bmpInfo.bmiHeader.biBitCount = 32;
	bmpInfo.bmiHeader.biCompression = BI_RGB;

    Initalize();
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

        unsigned long long curTick = ::GetTickCount();
        
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

    return 0;
}

void Update(int delta)
{
    for (int i = 0; i < 3; ++i)
    {
        triangle[i].RotateByY(0.05f);
        triangle[i].RotateByZ(0.05f);
    }

    static float change = 0.2;
    sphere.Center().z += change;
    if (sphere.Center().z > -3.f || sphere.Center().z < -10.f)
        change = -change;
}

void ClearBuffer()
{
    memset(buffer, 0, sizeof(buffer));
    for (int i = 0; i < WIDTH * HEIGHT; ++i)
        depth[i] = -FLT_MAX;
}

void Render()
{
    ClearBuffer();

    for (int i = 0; i < 3; ++i)
    {
        triangleToRender[i] = triToWoldMatrix.Transform(triangle[i]);
    }


    Vector3f intersectPoint;
    for (int i = 0; i < WIDTH; ++i)
    {
        for (int j = 0; j < HEIGHT; ++j)
        {
            int index = j * WIDTH + i;
            if (triangleToRender.Intersect(rays[i][j], nullptr, &intersectPoint))
            {
                buffer[index] = 0x00ff0000;
                depth[index] = intersectPoint.z;
            }

            if (sphere.Intersect(rays[i][j], nullptr, &intersectPoint) && depth[index] < intersectPoint.z)
            {
                auto sphereNormal = intersectPoint - sphere.Center();
                sphereNormal.Normalize();
                float dot = sphereNormal.DotProduct(-rays[i][j].Direction());
                buffer[index] = 0x000000ff * dot;
                depth[index] = intersectPoint.z;
            }
        }
    }
    DrawBuffer((unsigned char *)buffer);
}

void DrawBuffer(unsigned char * buffer)
{
    HDC hdc = GetDC(hWnd);

    StretchDIBits(hdc, 0, 0, WIDTH, HEIGHT, 0, HEIGHT, WIDTH, -HEIGHT, buffer, &bmpInfo, DIB_RGB_COLORS, SRCCOPY);

    ReleaseDC(hWnd, hdc);
}


void Initalize()
{
    float width_div_2 = 1.0;
    float height_div_2 = width_div_2 * HEIGHT / WIDTH;
    float deltaP = width_div_2 * 2.f / WIDTH;


    for (int i = 0; i < WIDTH; ++i)
    {
        for (int j = 0; j < HEIGHT; ++j)
        {
            Vector3f dir(-width_div_2 + deltaP * i, height_div_2 - deltaP * j, -1.f);
            dir.Normalize();
            rays[i][j] = Rayf(Vector3f(0, 0, 0), dir);
        }
    }

    triToWoldMatrix.MakeTransition(Vector3f(0, 0, -5.f));
}