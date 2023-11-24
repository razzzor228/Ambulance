#include"windowApplication.h"
#include<Windows.h>
#include<vector>
#include<string>
#include <locale>
#include <tchar.h>

struct leaks
{
    ~leaks()
    {
        _CrtDumpMemoryLeaks();
    }
} leaks;

static TCHAR szWindowClass[] = _T("DesktopApp");

static TCHAR szTitle[] = _T("База данных больницы");
HINSTANCE hInst;
Window app(hInst);

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR     lpCmdLine,
    _In_ int       nCmdShow
)
{
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(wcex.hInstance, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = reinterpret_cast<HBRUSH>(WHITE_BRUSH);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

    if (!RegisterClassEx(&wcex))
    {
        MessageBox(NULL,
            _T("Call to RegisterClassEx failed!"),
            _T("База данных больницы"),
            NULL);

        return 1;
    }

    hInst = hInstance;

    HWND hWnd = app.createWindow(0, 0, 1500, 1000, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX);


    if (!hWnd)
    {
        MessageBox(NULL,
            _T("Call to CreateWindow failed!"),
            _T("База данных больницы"),
            NULL);

        return 1;
    }

    ShowWindow(hWnd,
        nCmdShow);
    UpdateWindow(hWnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    setlocale(LC_ALL, "Russian");
    return app.getCommand(hwnd, uMsg, wParam, lParam);
}