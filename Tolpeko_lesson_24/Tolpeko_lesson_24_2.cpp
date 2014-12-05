#include <iostream>
#include <ctime>

using namespace std;

class Matrix {
private:
	int row;
	int col;
	int **arr;
public:
	Matrix() {
		row = 5;
		col = 5;
		arr = new int* [row];
		for(int i = 0; i < row; i++) {
			arr[i] = new int [col];
		}
	}

	void initArr() {
		for(int i = 0; i < row; i++) {
			for(int j = 0; j < col; j++) {
				arr[i][j] = rand() % 10;
			}
		}
	}

	void showArr() {
		for(int i = 0; i < row; i++) {
			for(int j = 0; j < col; j++) {
				cout << arr[i][j] << " ";
			}
			cout << "\n";
		}
		cout << "\n\n";
	}

	void setElement(int i, int j, int set) {
		arr[i - 1][j - 1] = set;
	}

	int getElement(int i, int j) {
		return arr[i - 1][j - 1];
	}

	Matrix& operator + (const Matrix &pl) {
		for(int i = 0; i < row; i++) {
			for(int j = 0; j < col; j++) {
				arr[i][j] += pl.arr[i][j];
			}
		}
		return *this;
	}

	Matrix& operator * (const Matrix &mult) {
		for(int i = 0; i < row; i++) {
			for(int j = 0; j < col; j++) {
				arr[i][j] *= mult.arr[i][j];
			}
		}
		return *this;
	}

	Matrix& operator ++ () { //transposition
		int k;
		for(int i = 0; i < row; i++) {
			for(int j = i; j < col; j++) {
				k = arr[i][j];
				arr[i][j] = arr[j][i];
				arr[j][i] = k;
			}
		}
		return *this;
	}

	~Matrix() {
		for(int i = 0; i < row; i++) {
			delete [] arr[i];
		}
		delete [] arr;
	}
};

void main() {
	int go_on = 1;
	int choice;
	while(go_on) {
		cout << "What would you like to do?\n";
		cout << "1. To fold the matrices\n";
		cout << "2. To multiply matrices\n";
		cout << "3. To transpose matrices\n";
		cout << "4. To set an arbitrary element\n";
		cout << "5. To get an arbitrary element\n\n";
		cin >> choice;

		while(choice < 1 || choice > 5) {
			cout << "Wrong digit! Enter 1, 2, 3, 4 or 5\n";
			cin >> choice;
		}
		system("cls");

		Matrix x;
		x.initArr();
		x.showArr();
		Matrix y;
		y.initArr();
		y.showArr();
		Matrix z;

		switch(choice) {
			case 1: {
				z = x + y;
				cout << "The result is:\n";
				z.showArr();
				break;
			}
			case 2: {
				z = x * y;
				cout << "The result is:\n";
				z.showArr();
				break;
			}
			case 3: {
				x++;
				y++;
				cout << "The result is (first matrix):\n";
				x.showArr();
				cout << "The result is (second matrix):\n";
				y.showArr();
				break;
			}
			case 4: {
				int row, col, dig, ch;
				cout << "Enter the number of the row:\n";
				cin >> row;

				while(row < 1 || row > 5) {
					cout << "Wrong digit! Try again!\n";
					cin >> row;
				}

				cout << "Enter the number of the column:\n";
				cin >> col;

				while(col < 1 || col > 5) {
					cout << "Wrong digit! Try again!\n";
					cin >> col;
				}

				cout << "What digit is to enter?\n";
				cin >> dig;
				cout << "What matrix should to be changed? First or second? (Enter 1 or 2):\n";
				cin >> ch;

				while(ch < 1 || ch > 2) {
					cout << "Wrong digit! Enter 1 or 2:\n";
					cin >> ch;
				}

				if(ch == 1) {
					x.setElement(row, col, dig);
					cout << "The result is:\n";
					x.showArr();
				}
				else {
					y.setElement(row, col, dig);
					cout << "The result is:\n";
					y.showArr();
				}
				break;
			}
			case 5: {
				int row, col, ch;
				cout << "Enter the number of the row:\n";
				cin >> row;

				while(row < 1 || row > 5) {
					cout << "Wrong digit! Try again!\n";
					cin >> row;
				}

				cout << "Enter the number of the column:\n";
				cin >> col;

				while(col < 1 || col > 5) {
					cout << "Wrong digit! Try again!\n";
					cin >> col;
				}
				cout << "From what matrix should to get the digit? First or second? (Enter 1 or 2):\n";
				cin >> ch;

				while(ch < 1 || ch > 2) {
					cout << "Wrong digit! Enter 1 or 2:\n";
					cin >> ch;
				}

				if(ch == 1) {
					cout << "The result is:\n";
					cout << x.getElement(row, col);
				}
				else {
					cout << "The result is:\n";
					cout << y.getElement(row, col);
				}
				break;
			}
		}
		cout << "\n";
		cout << "Anything else? (1 - yes, 0 - no)\n";
		cin >> go_on;
		while(go_on < 0 || go_on > 1) {
			cout << "Wrong digit! Enter 1 or 0!\n";
			cin >> go_on;
		}
		system("cls");
	}
}