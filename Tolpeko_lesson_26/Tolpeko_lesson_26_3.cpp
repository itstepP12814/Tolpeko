#include <iostream>
#include <ctime>
#include <string>
using namespace std;

class Printer {
private:
	int *queue;
	int *priority;
	int queueLength;
	int maxQueueLength;
	int numExtract;
	int *username;
public:
	Printer();
	~Printer();
	bool isEmpty();
	bool isFull();
	void add(int q, int p);
	int extract();
	void show();
	void showStat();
};

Printer :: Printer() {
	numExtract = 0;
	maxQueueLength = 10;
	queue = new int[maxQueueLength];
	priority = new int[maxQueueLength];
	username = new int[numExtract];
	queueLength = 0;
}

Printer :: ~Printer() {
	delete [] queue;
	delete [] priority;
	delete [] username;
}

bool Printer :: isEmpty() {
	return queueLength == 0;
}

bool Printer :: isFull() {
	return queueLength == maxQueueLength;
}

void Printer :: add(int q, int p) {
	if(!isFull()) {
		queue[queueLength] = q; 
		priority[queueLength] = p; 
		username[numExtract] = numExtract + 1;
		numExtract++;
		queueLength++;
	}
}

int Printer :: extract() {
	
	if(!isEmpty()) {
		int maxPri = priority[0];
		int indMaxPri = 0;
		for(int i = 1; i < queueLength; i++) {
			if(maxPri < priority[i]) {
				maxPri = priority[i];
				indMaxPri = i;
			}
		}
		int temp1 = queue[indMaxPri];
		int temp2 = priority[indMaxPri];
		for(int i = indMaxPri; i < queueLength - 1; i++) {
			queue[i] = queue[i + 1]; 
			priority[i] = priority[i + 1]; 
		}
		queueLength--;
		return temp1;	
	}
	else {
		return -1;
	}
}

void Printer :: show() {
	for(int i = 0; i < queueLength; i++) {
		cout << "The document " << queue[i] << " - " << "priority " << priority[i] << "\n\n";
	}
}

void Printer :: showStat() {
	for(int i = 0; i < numExtract; i++) {
		cout << "Username N" << username[i] << " printed the document N" << queue[i] << endl;
	}
}

void main() {
	Printer x;
	int needPrint = 1, add = 1;
	cout << "Add the print queue.\n\n";
	while(add) {
		int num, prior;
		cout << "Enter a document number:\n";
		cin >> num;
		cout << "Enter a priority of the document (1 - 10):\n";
		cin >> prior;
		x.add(num, prior);
		cout << "More? (1 - yes, 0 - no)\n";
		cin >> add;
	}
	x.show();
	cout << "Need to print? (1 - yes, 0 - no)\n";
	cin >> needPrint;
	while(needPrint) {
		cout << "Printed document N" << x.extract();
		cout << "\n";
		cout << "Rest for the print:\n";
		if(!x.isEmpty()) {
			x.show();
			cout << "\n";
		}
		else {
			cout << "The are no documents for the print!\n";
			break;
		}
		cout << "Need to print? (1 - yes, 0 - no):\n";
		cin >> needPrint;
	}
}