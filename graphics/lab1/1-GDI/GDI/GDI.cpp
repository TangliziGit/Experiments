// GDI.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "GDI.h"

#include <windows.h>
#include <time.h>
#include <stdio.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void Draw(HWND hwnd);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR lpCmdLine, int nCmdShow) {
    MSG  msg;
    WNDCLASSW wc = {0};

    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpszClassName = L"Lab1-1";
    wc.hInstance     = hInstance;
    wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
    wc.lpfnWndProc   = WndProc;
    wc.hCursor       = LoadCursor(0, IDC_ARROW);

    RegisterClassW(&wc);
    CreateWindowW(wc.lpszClassName, L"Lab1-1",
                WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                100, 100, 400, 350, NULL, NULL, hInstance, NULL);

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
            Draw(hwnd);
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }

    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

void DrawPoints(HDC hdc, int ox, int oy, int unitX, int unitY){
	for (int i=0; i<1000; i++) {
        int x = rand() % unitX;
        int y = rand() % unitY;
        SetPixel(hdc, ox+x, oy+y, RGB(255, 0, 0));
    }
}

void DrawEllipse(HDC hdc, int ox, int oy, int sizeX, int sizeY){
	HGDIOBJ brush = CreateSolidBrush(RGB(152,123,213));
	HGDIOBJ old = SelectObject(hdc, brush);
	Ellipse(hdc, ox, oy, ox+sizeX, oy+sizeY);
	SelectObject(hdc, old);
}

void DrawLines(HDC hdc, int ox, int oy, int ex, int ey, int rate = 3){
	HGDIOBJ pens[4];
	pens[0]=GetStockObject(BLACK_PEN);
	pens[1]=CreatePen(PS_SOLID, 1, RGB(255,0,0));
	pens[2]=CreatePen(PS_SOLID, 1, RGB(0,255,0));
	pens[3]=CreatePen(PS_SOLID, 1, RGB(0,0,255));
	
	for (int i=0; oy+rate*i<ey; i++){
		int y=i*rate+oy;
		SelectObject(hdc, pens[i%4]);
		MoveToEx(hdc, ox, y, NULL);
		LineTo(hdc, ex, y);
	}SelectObject(hdc, pens[0]);
}

void DrawRect(HDC hdc, int ox, int oy, int sizeX, int sizeY){
	HGDIOBJ brush = CreateSolidBrush(RGB(123,213,152));
	HGDIOBJ old = SelectObject(hdc, brush);
	Rectangle(hdc, ox, oy, sizeX+ox, sizeY+oy);
	SelectObject(hdc, old);
}

void DrawPolygon(HDC hdc, int ox, int oy, int sX, int sY){
	POINT points[5];
	points[0].x = 0+ox; points[0].y = 0+oy;
	points[1].x = sX/4+ox; points[1].y = sY+oy;
	points[2].x = 6*sX/8+ox; points[2].y = sY/2+oy;
	points[3].x = sX/3+ox; points[3].y = sY/3+oy;
	points[4].x = 3*sX/8+ox; points[4].y = 5*sY/9+oy;

	HGDIOBJ brush = CreateSolidBrush(RGB(213,152,123));
	HGDIOBJ old = SelectObject(hdc, brush);
	Polygon(hdc, points, 4);
	SelectObject(hdc, old);
}

void DrawArc(HDC hdc, int ox, int oy, int r){
	HGDIOBJ pens[4];
	pens[0]=GetStockObject(BLACK_PEN);
	pens[1]=CreatePen(PS_SOLID, 1, RGB(255,0,0));
	pens[2]=CreatePen(PS_SOLID, 1, RGB(0,255,0));
	pens[3]=CreatePen(PS_SOLID, 1, RGB(0,0,255));

	MoveToEx(hdc, ox, oy-r, NULL);
	SelectObject(hdc, pens[0]);
	AngleArc(hdc, ox, oy, r, 90, 90);
	MoveToEx(hdc, ox-r, oy, NULL);
	SelectObject(hdc, pens[1]);
	AngleArc(hdc, ox, oy, r, 180, 90);
	MoveToEx(hdc, ox, oy+r, NULL);
	SelectObject(hdc, pens[2]);
	AngleArc(hdc, ox, oy, r, 270, 90);
	MoveToEx(hdc, ox+r, oy, NULL);
	SelectObject(hdc, pens[3]);
	AngleArc(hdc, ox, oy, r, 360, 90);
	SelectObject(hdc, pens[0]);
}

void Draw(HWND hwnd) {
    PAINTSTRUCT ps;
    RECT r;

    GetClientRect(hwnd, &r);
    if (r.bottom == 0) return;

	long margin=5;
	long unitX=r.right/3-margin*2, unitY=r.bottom/2-margin*2;

    HDC hdc = BeginPaint(hwnd, &ps);

	DrawPoints(hdc, margin, margin, unitX, unitY);
	DrawEllipse(hdc, unitX+3*margin, margin, unitX, unitY);
	DrawRect(hdc, 2*unitX+5*margin, margin, unitX, unitY);
	DrawLines(hdc, margin, unitY+3*margin, unitX+margin, 2*unitY+3*margin);
	DrawPolygon(hdc, unitX+3*margin, unitY+3*margin, unitX, unitY);
	DrawArc(hdc, (5*unitX)/2+3*margin, (3*unitY)/2+3*margin, 2*unitY/6);

    EndPaint(hwnd, &ps);
}
