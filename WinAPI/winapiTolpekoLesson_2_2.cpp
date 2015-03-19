#include <windows.h>
#include <tchar.h>
#include <time.h>

int right = 0;
int down = 0;

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
	hWnd = CreateWindowEx(0, szClassWindow, TEXT("Передвижение окна калькулятора клавишами стрелок"), WS_OVERLAPPEDWINDOW,	
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInst, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	MessageBox(
		0,
		TEXT("Управляйте клавишами стрелок для передвижения калькулятора. Нажмите Escape для остановки движения"),
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

VOID CALLBACK TimerProcRight(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
	HWND h = FindWindow(TEXT("CalcFrame"), TEXT("Калькулятор"));
		MoveWindow (
			h, 
			right,
			down, 
			230, 
			320,
			true 
		);
	right++;
}

VOID CALLBACK TimerProcDown(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
	HWND h = FindWindow(TEXT("CalcFrame"), TEXT("Калькулятор"));
		MoveWindow (
			h, 
			right,
			down, 
			230, 
			320,
			true 
		);
	down++;
}

VOID CALLBACK TimerProcUp(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
	HWND h = FindWindow(TEXT("CalcFrame"), TEXT("Калькулятор"));
		MoveWindow (
			h, 
			right,
			down, 
			230, 
			320,
			true 
		);
	down--;
}

VOID CALLBACK TimerProcLeft(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
	HWND h = FindWindow(TEXT("CalcFrame"), TEXT("Калькулятор"));
		MoveWindow (
			h, 
			right,
			down, 
			230, 
			320,
			true 
		);
	right--;
}

LRESULT CALLBACK WindowProc (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		case WM_DESTROY: 
			PostQuitMessage(0);
			break;
		case WM_KEYDOWN:
			if(wParam == VK_RIGHT)
				SetTimer(hWnd, 1, 50, TimerProcRight);
			else if(wParam == VK_DOWN)
				SetTimer(hWnd, 1, 50, TimerProcDown);
			else if(wParam == VK_UP)
				SetTimer(hWnd, 1, 50, TimerProcUp);
			else if(wParam == VK_LEFT)
				SetTimer(hWnd, 1, 50, TimerProcLeft);
			else if(wParam == VK_ESCAPE)
				KillTimer(hWnd, 1);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}