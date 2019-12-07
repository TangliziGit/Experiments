
#include "stdafx.h"

#include <windows.h>
#include <windowsx.h>
#include <time.h>
#include <stdio.h>
#include "resource.h"

#define WINDOW_WIDTH 400
#define WINDOW_HEIGHT 300

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void Paint(HWND hwnd);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR lpCmdLine, int nCmdShow) {
    MSG  msg;
    WNDCLASSW wc = {0};

    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpszClassName = L"Lab1-2";
    wc.hInstance     = hInstance;
    wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
    wc.lpfnWndProc   = WndProc;
    wc.hCursor       = LoadCursor(0, IDC_ARROW);

    RegisterClassW(&wc);
    CreateWindowW(wc.lpszClassName, L"Lab1-2",
                WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                100, 100, 800, 400, NULL, NULL, hInstance, NULL);

    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    srand(time(NULL));

    return (int) msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {

    switch(msg) {
        case WM_PAINT:
            Paint(hwnd);
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }

    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

void Paint(HWND hwnd)
{
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd,&ps);;
    HDC mdc;
    HBITMAP hbmp; 
	int error;

  HINSTANCE hInstance = GetWindowInstance(hwnd);
  HBITMAP hbm = LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_BITMAP1));

  error = GetLastError();


  HDC hdcMem = CreateCompatibleDC(NULL);
  HBITMAP hbmT = SelectBitmap(hdcMem,hbm);
  
  error = GetLastError();
  BITMAP bm;
  GetObject(hbm,sizeof(bm),&bm);
  
  error = GetLastError();
  BitBlt(hdc,0,0,bm.bmWidth,bm.bmHeight,hdcMem,0,0,SRCCOPY);
  
  error = GetLastError();
  SelectBitmap(hdcMem,hbmT);
  DeleteDC(hdcMem);
  error = GetLastError();


	int errorCode = GetLastError();
 
    EndPaint(hwnd, &ps);
}