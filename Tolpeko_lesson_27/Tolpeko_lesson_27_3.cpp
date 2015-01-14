#include <iostream>
using namespace std;

template <typename T>
class Array {
private:
	T *arrData;
	int arrSize;
	int arrGrow;
	int arrCounter;
public:
	Array();
	~Array();
	int getSize();
	void setSize(int size, int grow = 1);
	bool isEmpty();
	void removeAll();
	T getAt(int index);
	void setAt(int index, T data);
	T &operator[](int index);
	void Add(T data);
	T** getData();
	void insertAt(int pos, int data);
	void removeAt(int pos);
};

template <typename T>
Array<T> :: Array() {
	arrData = NULL;
	arrSize = 0;
	arrGrow = 1;
	arrCounter = 0;
}

template <typename T>
Array<T> :: ~Array() {
	if(arrData) {
		free(arrData);
	}
	arrData = NULL;
}

template <typename T>
int Array<T> :: getSize() {
	return arrSize;
}

template <typename T>
void Array<T> :: setSize(int size, int grow = 1) {
	if(size == arrSize) {
		return;
	}
	arrSize = size;
	arrData = (T*) realloc(arrData,sizeof(T) * arrSize);
}

template <typename T>
bool Array<T> :: isEmpty() {
	if(arrCounter == 0) {
		return true;
	}
	else {
		return false;
	}
}

template <typename T>
void Array<T> :: removeAll() {
	free(arrData);
	arrData = NULL;
	arrSize = 0;
	arrCounter = 0;
}

template <typename T>
T Array<T> :: getAt(int index) {
	while(index <= 0 && index > arrSize) {
		cout << "Wrong! Enter a digit between 0 and " << arrSize; 
	}
	return arrData[index];
}

template <typename T>
void Array<T> :: setAt(int index, T data) {
	while(index <= 0 && index > arrSize) {
		cout << "Wrong! Enter a digit between 0 and " << arrSize; 
	}
	arrData[index] = data;
}

template <typename T>
T &Array<T> :: operator[](int index) {
	if(index >= 0 && index < arrSize) {
		return arrData[index];
	}
}

template <typename T>
void Array<T> :: Add(T data) {
	if(arrCounter < arrSize) {
		arrData[arrCounter++] = data;
	}
	else if(arrCounter >= arrSize) {
		setSize(arrSize + 1);
		arrData[arrSize - 1] = data;
		arrCounter++;
	}
}

template <typename T>
T** Array<T> :: getData() {
	return &arrData;
}

template <typename T>
void Array<T> :: insertAt(int pos, int data) {
	if(arrCounter >= arrSize) {
		setSize(arrSize+1);
	}
	for(int i = arrSize; i >= pos; i--) {
		arrData[i] = arrData[i - 1];
	}
	arrData[pos] = data;
	arrCounter++;
}

template <typename T>
void Array<T> :: removeAt(int pos) {
	for(int i = pos; i < arrSize; i++) {
		arrData[i] = arrData[i + 1];
	}
	arrCounter--;
}

void main() {
	Array<int> x;
	cout << "Set size 10. The result is:\n";
	x.setSize(10);
	cout << x.getSize() << endl;
	cout << "Set 8 to 4 position. The result is:\n";
	x.setAt(4, 8);
	cout << x.getAt(4) << endl;
	cout << "Show 4 position by operator []:\n";
	cout << x[4] << endl;
	cout << "Insert 9 into 6 position. The result is:\n";
	x.insertAt(6, 9);
	cout << x.getAt(6) << endl;
	cout << "Remove 9 from 6 position. The result is:\n";
	x.removeAt(6);
	cout << x.getAt(6) << endl;
}