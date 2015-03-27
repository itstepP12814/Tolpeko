#include <windows.h>
#include <windowsx.h>
#include <vector>
#include "resource.h"

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

HWND hStatic;
TCHAR szCoordinates[300];
HINSTANCE hInst;
int x1, x2, z1, z2, x3, y3, width, height; 
TCHAR buf[10];
struct StaticInfo {
	HWND hWndStatic;
	int num;
	int height;
	int width;
	RECT Coord;
};
std::vector<StaticInfo> vect;
int count = 1;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nCmdShow)
{
	hInst = hInstance;
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc); 
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		case WM_CLOSE:
			EndDialog(hWnd, 0);
			return TRUE;

		case WM_LBUTTONDOWN:
			x1 = GET_X_LPARAM(lParam);
			z1 = GET_Y_LPARAM(lParam);
			return TRUE;

		case WM_LBUTTONUP:
			x2 = GET_X_LPARAM(lParam);
			z2 = GET_Y_LPARAM(lParam);
			width = x2 - x1;
			height = z2 - z1;
			if(width >= 10 && height >= 10) {
				hStatic = CreateWindowEx(0, TEXT("STATIC"), 0, 
					WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER | WS_EX_CLIENTEDGE,
					x1, z1, width, height, hWnd, 0, hInst, 0);
				StaticInfo v;
				v.hWndStatic = hStatic;
				v.num = count;
				v.height = height;
				v.width = width;
				v.Coord.left = x1;
				v.Coord.bottom = z1;
				v.Coord.right = x2;
				v.Coord.top = z2;
				vect.push_back(v);
				wsprintf(buf, TEXT("%d"), count++);
				SetWindowText(hStatic, buf);

			}
			else if(x1 != x2 && z1 != z2) {
				MessageBox(hWnd, TEXT("Слишком маленький Static!"), TEXT("Внимание!"), MB_OK);
			}
			return TRUE;

		case WM_RBUTTONDOWN:
			int w, h;
			x3 = GET_X_LPARAM(lParam);
			y3 = GET_Y_LPARAM(lParam);
			for (std::vector<StaticInfo>::iterator ii = vect.begin(); ii != vect.end(); ii++){
				w = ii -> Coord.right - ii -> Coord.left;
				h = ii -> Coord.top - ii -> Coord.bottom;
				if ((x3 >= ii -> Coord.left && x3 <= ii -> Coord.right) && (y3 <= ii -> Coord.top && y3 >= ii -> Coord.bottom)) {
					wsprintf(szCoordinates, TEXT("top %d, right %d, bottom %d, left %d, width %d, height %d"), 
						ii -> Coord.top, ii -> Coord.right, ii -> Coord.bottom, ii -> Coord.left, w, h);
					SetWindowText(hWnd, szCoordinates);
				}
			}
			return TRUE;

			case WM_LBUTTONDBLCLK:
				x3 = GET_X_LPARAM(lParam);
				y3 = GET_Y_LPARAM(lParam);
				for (std::vector<StaticInfo>::iterator ii = vect.begin(); ii != vect.end(); ii++){
					if ((x3 >= ii -> Coord.left && x3 <= ii -> Coord.right) && (y3 <= ii -> Coord.top && y3 >= ii -> Coord.bottom)) {
						DestroyWindow(ii -> hWndStatic);
					}
				}
			return TRUE;
	}
	return FALSE;
}