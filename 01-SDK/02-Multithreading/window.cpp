//header files
#include<windows.h>
#include "Window.h"

//Global function declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
DWORD WINAPI ThreadProcOne(LPVOID);
DWORD WINAPI ThreadProcTwo(LPVOID);

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
	//local variable declarations
	HANDLE hThread1 = NULL;
	HANDLE hThread2 = NULL;

	//code
	switch (iMsg)
	{
	case WM_CREATE:
		hThread1 = CreateThread(
			NULL,                               //hya thread la kahi security attributes ahet ka(mala mahiti nahi OS che default vapar)
			0,			                               //tujhya thread chya runtime cha size kay ahe(process chya thread cha size)
			(LPTHREAD_START_ROUTINE)ThreadProcOne, //tumchya thread la associate kelelya function cha nav kay ahe
			(LPVOID)hwnd,                            //third parameter cha single parameter(apalela tya function la apala kuthla parameter pathvaycha asel tar)
			0,                                    //by default thread tayar zhalya zhalya palayla lagto
			NULL);

		hThread2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProcTwo, (LPVOID)hwnd, 0, NULL);
		break;

	case WM_LBUTTONDOWN:
		MessageBox(hwnd, TEXT("This is my message box"), TEXT("Message"), MB_OK);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		break;
	}

	return(DefWindowProc(hwnd, iMsg, wParam, lParam));

}

DWORD WINAPI ThreadProcOne(LPVOID param)
{
	//local variable declaration
	HDC hdc;
	TCHAR str[255];
	int i;

	//code
	hdc = GetDC((HWND)param);
	SetBkColor(hdc, RGB(0,0,0));
	SetTextColor(hdc, RGB(255, 255, 0));

	for (i = 0; i < 32767; i++)
	{
		wsprintf(str, TEXT("Number in incrementing order: %d"), i);
		TextOut(hdc, 5, 5, str, wcslen(str));
	}

	ReleaseDC((HWND)param, hdc);

	return 0;

}

DWORD WINAPI ThreadProcTwo(LPVOID param)
{
	//local variable declaration
	HDC hdc;
	TCHAR str[255];
	int i;

	//code
	hdc = GetDC((HWND)param);
	SetBkColor(hdc, RGB(0, 0, 0));
	SetTextColor(hdc, RGB(0, 255, 255));

	for (i = 32767; i > 0; i--)
	{
		wsprintf(str, TEXT("Number in decrementing order: %d"), i);
		TextOut(hdc, 5, 20, str, wcslen(str));
	}

	ReleaseDC((HWND)param, hdc);

	return 0;

}