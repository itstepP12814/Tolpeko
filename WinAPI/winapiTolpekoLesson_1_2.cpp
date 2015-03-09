#include <windows.h>
#include <tchar.h>
#include <ctime>

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nCmdShow) {
	int play = 1;
	do {
		srand(time(NULL));
		int num = rand() % 100 + 1;
		TCHAR buf[5];
		wsprintf(buf, L"%d", num);
		int count = 1;
		while ( 
			MessageBox (
				0,
				buf,
				TEXT("Вы это число загадали?"),
				MB_YESNO | MB_ICONQUESTION
			) != IDYES
		) {
			srand(time(NULL));
			num = rand() % 100 + 1;
			wsprintf(buf, L"%d", num);
			count++;
		}
	
		TCHAR bufn[50];
		wsprintf(bufn, L"Количество попыток: %d. Сыграем еще?", count);

		play = MessageBox (
			0,
			bufn,
			TEXT("Спасибо за игру!"),
			MB_OKCANCEL | MB_ICONINFORMATION
		);
	} while(play == IDOK);

	return 0;
}