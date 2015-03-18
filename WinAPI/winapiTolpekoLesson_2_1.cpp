#include <windows.h>
#include <tchar.h>
#include <time.h>

int NUM = 0;

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

TCHAR szClassWindow[] = TEXT("Каркасное приложение");	

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nCmdShow)
{
	HWND hWnd;
	MSG lpMsg;
	WNDCLASSEX wcl;
	wcl.cbSize = sizeof(wcl);	
	wcl.style = CS_HREDRAW | CS_VREDRAW;	
	wcl.lpfnWndProc = WindowProc;	
	wcl.cbClsExtra = 0;	
	wcl.cbWndExtra = 0; 	
	wcl.hInstance = hInst;	
	wcl.hIcon = LoadIcon(NULL, IDI_APPLICATION);	
	wcl.hCursor = LoadCursor(NULL, IDC_ARROW);	
	wcl.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH); 
	wcl.lpszMenuName = NULL;	
	wcl.lpszClassName = szClassWindow;	
	wcl.hIconSm = NULL;	
	if (!RegisterClassEx(&wcl))
		return 0;
	hWnd = CreateWindowEx(0, szClassWindow, TEXT("Передвижение окна калькулятора"), WS_OVERLAPPEDWINDOW,	
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInst, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	MessageBox(
		0,
		TEXT("Нажмите Enter для передвижения калькулятора и Escape для остановки"),
		TEXT("Как пользоваться?"),
		MB_OK
	);
	while(GetMessage(&lpMsg, NULL, 0, 0))
	{
		TranslateMessage(&lpMsg);	
		DispatchMessage(&lpMsg);	
	}
	return lpMsg.wParam;
}

VOID CALLBACK TimerProc(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
	HWND h = FindWindow(TEXT("CalcFrame"), TEXT("Калькулятор"));
		MoveWindow (
			h, 
			NUM,
			0, 
			230, 
			320,
			true 
		);
	NUM++;
}

LRESULT CALLBACK WindowProc (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		case WM_DESTROY: 
			PostQuitMessage(0);
			break;
		case WM_KEYDOWN:
			if(wParam == VK_RETURN)
				SetTimer(hWnd, 1, 50, TimerProc);
			else if(wParam == VK_ESCAPE)
				KillTimer(hWnd, 1);
			break;	
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}




