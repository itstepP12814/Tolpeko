#include <windows.h>
#include <tchar.h>
#include <string>
#include <vector>

struct Resume {
	TCHAR *title;
	TCHAR *text;
};

std::vector<Resume> vect;

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nCmdShow) {

	Resume x, y, z;
	x.title = TEXT("First");
	x.text = TEXT("Name: Ivan Pupkin");
	vect.push_back(x);
	y.title = TEXT("Second");
	y.text = TEXT("Age: 32 years old");
	vect.push_back(y);
	z.title = TEXT("Third");
	z.text = TEXT("Last job: Programmer, EPAM");
	vect.push_back(z);

	unsigned int countWin = 0;
	unsigned int countText = 0;
	for(std::vector<Resume>::iterator ii = vect.begin(); ii != vect.end(); ii++) {
		countWin += 1;
		countText += lstrlen(ii -> text);
		if(ii == vect.end() - 1) {
			unsigned int mid = (countText/countWin);
			TCHAR buf[40];
			wsprintf(buf, L"Average number is %d", mid);
			MessageBox(
				0,
				ii -> text,
				buf,
				MB_OK
			);
		}
		else {
			MessageBox(
				0,
				ii -> text,
				ii -> title,
				MB_OK
			);
		}
	}
	return 0;
}
