//header files
#include<windows.h>
#include "Window.h"

//Global function declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//Global variable declarations


//Entry point function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	//Local variable declarations
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("WINDEV");

	//code
	//WNDCLASSEX initialization
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));


	//Registration of WNDCLASSEX
	RegisterClassEx(&wndclass);


	//Creating the window
	hwnd = CreateWindow(
		szAppName,
		TEXT("KUK:Window"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	//Show the window
	ShowWindow(hwnd, iCmdShow);

	//update the window
	UpdateWindow(hwnd);

	//message loop
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return((int)msg.wParam);
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	//variable declarations
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rc;
	HBRUSH hbrush;
	static int iPaintFlag = 0;

	//code
	switch (iMsg)
	{
	case WM_LBUTTONDOWN:
		iPaintFlag++;
		if (iPaintFlag > 8)
		{
			iPaintFlag = 0;
		}
		InvalidateRect(hwnd, NULL, TRUE);
		break;

	case WM_PAINT:
		GetClientRect(hwnd, &rc);
		hdc = BeginPaint(hwnd, &ps);
		if (iPaintFlag == 1)
		{
			hbrush = CreateSolidBrush(RGB(255, 0, 0));
		}
		else if (iPaintFlag == 2)
		{
			hbrush = CreateSolidBrush(RGB(0, 255, 0));
		}
		else if (iPaintFlag == 3)
		{
			hbrush = CreateSolidBrush(RGB(0, 0, 255));
		}
		else if (iPaintFlag == 4)
		{
			hbrush = CreateSolidBrush(RGB(0, 255, 255));
		}
		else if (iPaintFlag == 5)
		{
			hbrush = CreateSolidBrush(RGB(255, 0, 255));
		}
		else if (iPaintFlag == 6)
		{
			hbrush = CreateSolidBrush(RGB(255, 255, 0));
		}
		else if (iPaintFlag == 7)
		{
			hbrush = CreateSolidBrush(RGB(0, 0, 0));
		}
		else if (iPaintFlag == 8)
		{
			hbrush = CreateSolidBrush(RGB(255, 255, 255));
		}
		else
		{
			hbrush = CreateSolidBrush(RGB(128, 128, 128)); // Medium Gray
		}
		FillRect(hdc, &rc, hbrush);
		DeleteObject(hbrush);
		EndPaint(hwnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		break;
	}

	return(DefWindowProc(hwnd, iMsg, wParam, lParam));

}