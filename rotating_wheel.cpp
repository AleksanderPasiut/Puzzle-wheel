#include <Windows.h>
#include <stdexcept>

#include "master.h"

MASTER* Master = 0;

char ClassName[] = "RotatingWheelClass";

LRESULT CALLBACK WindowEventProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_LBUTTONDOWN:
	case WM_MOUSEMOVE:
	case WM_LBUTTONUP:
		Master->Mouse(uMsg, lParam);
		break;
	case WM_PAINT:
		BeginPaint(hwnd, 0);
		Master->Paint();
		EndPaint(hwnd, 0);
		break;
	case WM_SIZE:
		Master->Size(lParam);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WindowEventProc;
	wc.lpszClassName = ClassName;
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
	if (!RegisterClassEx(&wc))
		return 0;

	HWND hwnd = CreateWindowEx(0, ClassName, "RotatingWheel", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, hInstance, 0);

	if (!hwnd)
		return 0;

	try
	{	
		Master = new MASTER(hwnd);
	}
	catch(...)
	{
		return 0;
	}

	ShowWindow(hwnd, SW_SHOWNORMAL);

	MSG msg;
	while(GetMessage(&msg, 0, 0, 0))
	{	TranslateMessage(&msg);
		DispatchMessage(&msg);	}

	delete Master;

	return static_cast<int>(msg.wParam);
}