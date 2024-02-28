//header files
#include<windows.h>

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
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);


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
	TCHAR str[255];

	//code
	switch (iMsg)
	{
	case WM_CREATE:
		wsprintf(str, TEXT("WM_CREATE message is received"));
		MessageBox(hwnd, str, TEXT("Message"), MB_OK);
		break;

	case WM_KEYDOWN:
		wsprintf(str, TEXT("WM_KEYDOWN message is received"));
		MessageBox(hwnd, str, TEXT("Message"), MB_OK);
		break;

	case WM_LBUTTONDOWN:
		wsprintf(str, TEXT("WM_LBUTTONDOWN message is received"));
		MessageBox(hwnd, str, TEXT("Message"), MB_OK);
		break;

	case WM_RBUTTONDOWN:
		wsprintf(str, TEXT("WM_RBUTTONDOWN message is received"));
		MessageBox(hwnd, str, TEXT("Message"), MB_OK);
		break;

	case WM_DESTROY:
		wsprintf(str, TEXT("WM_DESTROY message is received"));
		MessageBox(hwnd, str, TEXT("Message"), MB_OK);
		PostQuitMessage(0);
		break;

	default:
		break;
	}

	return(DefWindowProc(hwnd, iMsg, wParam, lParam));

}