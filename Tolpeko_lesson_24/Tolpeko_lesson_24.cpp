#include <iostream>

using namespace std;

class Time {
private:
	int hour;
	int min;
	int sec;
public:
	Time() {
		hour = 0;
		min = 0;
		sec = 0;
	}

	Time(int h, int m, int s) {
		hour = h;
		min = m;
		sec = s;
	}

	Time(int h, int m, int s, int apm) {
		if(apm == 1) {
			hour = h;
			min = m;
			sec = s;
		}
		else {
			int pm[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
			int rus[] = {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 0};
			for(int i = 0; i < 12; i++) {
				if(h == pm[i]) {
					hour = rus[i];
				}
			}
			min = m;
			sec = s;
		}
	}

	void show() {
		cout << "The time is ";
		if(hour < 10) {
			cout << "0"; 
		}
		cout << hour << ":";
		if(min < 10) {
			cout << "0"; 
		}
		cout << min << ":";
		if(sec < 10) {
			cout << "0"; 
		}
		cout << sec << "\n\n";
	}

	Time& operator + (const Time &pl) {
		Time buff; 
		int res;
		res = (hour + pl.hour)*3600 + (min + pl.min)*60 + sec + pl.sec;
		buff.hour = res / 3600;
		buff.min = (res % 3600) / 60;
		buff.sec = (res % 3600) % 60;
		return buff;
	}

	Time& operator - (const Time &m) {
		Time buff; 
		int res;
		res = (hour - m.hour)*3600 + (min - m.min)*60 + sec - m.sec;
		buff.hour = res / 3600;
		buff.min = (res % 3600) / 60;
		buff.sec = (res % 3600) % 60;
		return buff;
	}

	Time& operator == (const Time &gr) {
		Time buff;
		int res, res1, res2;
		res1 = hour*3600 + min*60 + sec;
		res2 = gr.hour*3600 + gr.hour*60 + gr.sec;
		if(res1 > res2) {
			res = (hour - gr.hour)*3600 + (min - gr.min)*60 + sec - gr.sec;
			buff.hour = res / 3600;
			buff.min = (res % 3600) / 60;
			buff.sec = (res % 3600) % 60;
			return buff;
		}
		else if(res1 < res2) {
			res = (gr.hour - hour)*3600 + (gr.min - min)*60 + gr.sec - sec;
			buff.hour = res / 3600;
			buff.min = (res % 3600) / 60;
			buff.sec = (res % 3600) % 60;
			return buff;
		}
		else {
			buff.hour = 0;
			buff.min = 0;
			buff.sec = 0;
			return buff;
		}
	}

	~Time() {}
};

void setTime(int *h, int *m, int *s) {
	cout << "Enter hours:\n";
	cin >> *h;
	while(*h < 0 || *h > 23) {
		cout << "Wrong digit! Enter digit from 0 to 23:\n";
		cin >> *h;
	}
	cout << "Enter minutes:\n";
	cin >> *m;
	while(*m < 0 || *m > 60) {
		cout << "Wrong digit! Enter digit from 0 to 60:\n";
		cin >> *m;
	}
	cout << "Enter seconds:\n";
	cin >> *s;
	while(*s < 0 || *s > 60) {
		cout << "Wrong digit! Enter digit from 0 to 60:\n";
		cin >> *s;
	}
}

void setUSTime(int *h, int *m, int *s, int *apm) {
	cout << "Enter am (1) or pm (2):\n";
	cin >> *apm;
	while(*apm < 1 || *apm > 2) {
		cout << "Wrong digit! Enter 1 or 2:\n";
		cin >> *apm;
	}
	cout << "Enter hours:\n";
	cin >> *h;
	while(*h < 1 || *h > 12) {
		cout << "Wrong digit! Enter digit from 1 to 12:\n";
		cin >> *h;
	}
	cout << "Enter minutes:\n";
	cin >> *m;
	while(*m < 0 || *m > 60) {
		cout << "Wrong digit! Enter digit from 0 to 60:\n";
		cin >> *m;
	}
	cout << "Enter seconds:\n";
	cin >> *s;
	while(*s < 0 || *s > 60) {
		cout << "Wrong digit! Enter digit from 0 to 60:\n";
		cin >> *s;
	}
}

void main() {
	int choice, format;
	int go_on = 1;
	while(go_on) {
		cout << "What would you like to do?\n";
		cout << "1. To add one time to another\n";
		cout << "2. To substract one time from another\n";
		cout << "3. To find the differences between two times\n";
		cin >> choice;
		while(choice < 1 || choice > 3) {
			cout << "Wrong digit! Enter 1, 2 or 3:\n";
			cin >> choice;
		}
		system("cls");
		cout << "What time format is it? (1 - European, 2 - US)\n";
		cin >> format;
		while(format < 1 || format > 2) {
			cout << "Wrong digit! Enter 1 or 2:\n";
			cin >> format;
		}
		system("cls");
		switch(format) {
			case 1: {
				int h, m, s;
				setTime(&h, &m, &s);
				Time x(h, m, s);
				x.show();
				setTime(&h, &m, &s);
				Time y(h, m, s);
				y.show();
				Time z;

				if(choice == 1) {
					z = x + y;
					cout << "Result:\n";
					z.show();
				}
			
				if(choice == 2) {
					z = x - y;
					cout << "Result:\n";
					z.show();
				}
			
				if(choice == 3) {
					z = (x == y);
					cout << "Result:\n";
					z.show();
				}
				break;
			}
			case 2: {
				int h, m, s, apm;
				setUSTime(&h, &m, &s, &apm);
				Time x(h, m, s, apm);
				x.show();
				setUSTime(&h, &m, &s, &apm);
				Time y(h, m, s, apm);
				y.show();
				Time z;

				if(choice == 1) {
					z = x + y;
					cout << "Result:\n";
					z.show();
				}
			
				if(choice == 2) {
					z = x - y;
					cout << "Result:\n";
					z.show();
				}
			
				if(choice == 3) {
					z = (x == y);
					cout << "Result:\n";
					z.show();
				}
				break;
			}
		}
		cout << "Anything else? (1 - yes, 0 - no):\n";
		cin >> go_on;
		while(go_on < 0 || go_on > 1) {
			cout << "Wrong digit! Enter 1 (yes) or 0 (no):\n";
			cin >> go_on;
		}
		system("cls");
	}
}

