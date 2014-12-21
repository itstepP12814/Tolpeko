#include <iostream>
using namespace std;

template <typename T>
struct Elem {
	T data;
	Elem *prev, *next;
};

template <typename T>
class Queue {
private:
	Elem<T> *head, *tail;
	int count;
public:
	Queue();
	~Queue();
	int getCount();
	void addTail(T n);
	void delHead();
	void show();
	void del();
	void delAll();
};

template <typename T>
Queue<T> :: Queue() {
	head = tail = 0;
	count = 0;
}

template <typename T>
int Queue<T> :: getCount() {
	return count;
}

template <typename T>
Queue<T> :: ~Queue() {
	delAll();
}

template <typename T>
void Queue<T> :: addTail(T n) {
	Elem<T> *temp = new Elem<T>;
	temp -> next = NULL;
	temp -> data = n;
	temp -> prev = tail;
	if(tail != 0) {
		tail -> next = temp;
	}
	if(count == 0) {
		head = tail = temp;
	}
	else {
		tail = temp;
	}
	count++;
}

template <typename T>
void Queue<T> :: delHead() {
	if(count == 1) {
		delete head;
		head = NULL;
		tail = NULL;
	}
	else {
		Elem<T> *temp = head -> next;
		temp -> prev = NULL;
		delete head;
		head = temp;
	}
	count--;
}

template <typename T>
void Queue<T> :: show() {
	if(count == 0) {
		cout << "The queue is empty!\n";
	}
	else {
		Elem<T> *temp = head;
		while(temp != 0) {
			cout << temp -> data;
			temp = temp -> next;
		}
		cout << "\n";
	}
}

template <typename T>
void Queue<T> :: del() {
	Elem<T> * temp = head;
	head = head -> next;
	delete temp;
	count--;
}

template <typename T>
void Queue<T> :: delAll() {
   while(head != 0) {
      del();
   }
}

void main() {
	int len, choice;
	int go_on = 1;
	char el;
	Queue<char> x;
	cout << "Enter the queue length:\n";
	cin >> len;
	while(len < 1) {
		cout << "Wrong digit! The length must be at least 1! Try again:\n";
		cin >> len;
	}
	for(int i = 1; i <= len; i++) {
		cout << "Enter the " << i << " element:\n";
		cin >> el;
		x.addTail(el);
	}
	system("cls");
	cout << "Your queue is:\n";
	x.show();
	while(go_on) {
		cout << "What would you like to do?\n";
		cout << "1. To increase the queue\n";
		cout << "2. To decrease the queue\n";
		cin >> choice;
		while(choice < 1 || choice > 2) {
			cout << "Wrong digit! Enter 1 or 2:\n";
			cin >> choice;
		}
		if(choice == 1) {
			int num;
			cout << "How many elements are to be added?\n";
			cin >> num;
			for(int i = 1; i <= num; i++) {
				cout << "Enter the " << i << " element:\n";
				cin >> el;
				x.addTail(el);
			}
		}
		else {
			int num;
			cout << "How many elements are to be deleted?\n";
			cin >> num;
			while(num > x.getCount()) {
				cout << "Enter a digit which is less than or equal to " << x.getCount() << "\n";
				cin >> num;
			}
			for(int i = 1; i <= num; i++) {
				x.delHead();
			}
		}
		system("cls");
		cout << "The result is:\n";
		x.show();
		cout << "Anything else? (Enter 1 - yes or 0 - no)\n";
		cin >> go_on;
		while(go_on < 0 || go_on > 1) {
			cout << "Wrong digit! Enter 1 or 0:\n";
			cin >> go_on;
		}
		system("cls");
	}
}