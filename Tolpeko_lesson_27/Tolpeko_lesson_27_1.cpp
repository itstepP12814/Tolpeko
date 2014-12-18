#include <iostream>
using namespace std;
 

struct Element
{
	char data;
	Element * next;
};

class List
{
	Element * head;
	Element * tail;
	int count;

public:
	List();
	~List();
	void add(char data);
	void addPos(char data, int pos);	
	void del();
	void delPos(int pos);	
	int search(char data);
	void delAll();
	void print();
	int getCount();
};

List :: List()
{
   head = tail = NULL;   
   count = 0;
}

List :: ~List()
{
   delAll();
}

int List :: getCount()
{
   return count;
}

void List :: add(char data)
{
	Element * temp = new Element;
	temp -> data = data;
	temp -> next = NULL;
	if(head != NULL){
		tail -> next = temp;
		tail = temp;
	}
	else{
		head = tail = temp;
	}
	count++;
}

void List :: addPos(char data, int pos) {
	if(pos == 1) {
		Element *temp = head;
		head = new Element;
		head -> data = data;
		head -> next = temp;
	}
	else if(pos == count) {
		Element *temp = tail;
		tail = new Element;
		tail -> data = data;
		tail -> next = NULL;
		temp -> next = tail;
	}
	else {
		Element *temp = head;
		for(int i = 1; i < pos - 1; i++) {
			temp = temp -> next;
		}
		Element *prev = temp;
		Element *cur = new Element;
		Element *next = temp -> next;
		prev -> next = cur;
		cur -> data = data;
		cur -> next = next;
	}
	count++;
}

void List :: del()
{
	Element * temp = head;
	head = head -> next;
	delete temp;
	count--;
}

void List :: delPos(int pos) {
	if(pos == 1) {
		Element *temp = head;
		head = head -> next;
		delete temp;
	}
	else if(pos == count) {
		Element *temp = head;
		for(int i = 1; i < pos - 2; i++) {
			temp = temp -> next;
		}
		tail = temp;
		delete tail -> next;
		tail -> next = NULL;
	}
	else {
		Element *temp = head;
		for(int i = 1; i < pos - 1; i++) {
			temp = temp -> next;
		}
		Element *prev = temp;
		Element *cur = temp -> next;
		Element *next = cur -> next;
		prev -> next = next;
		delete cur;
	}
	count--;
}

int List :: search(char data) {
	Element *temp = head;
	int i = 1;
	while(temp) {
		if(temp -> data == data) {
			return i;
		}
		temp = temp -> next;
		i++;
	}
	return NULL;
}

void List :: delAll()
{
   while(head != 0)
      del();
}

void List :: print()
{
   Element *temp = head;
   while(temp != 0)
   {
      cout << temp->data << " ";
      temp = temp->next;
   }
   cout << "\n\n";
}

void main()
{
	int go_on = 1, len, choice;
	cout << "Enter a number of symbols:\n";
	cin >> len;
	char *s = new char[len];
	List lst;
	for(int i = 0; i < len; i++) {
		cout << "Number " << i + 1 << " ";
		cin >> s[i];
	}
	cout << "\n\n";
	cout << "Your string is:\n";
	for(int i = 0; i < len; i++) {
		cout << s[i];
	}
	cout << "\n\n";
	for(int i = 0; i < len; i++) {
		lst.add(s[i]);
	}
	while(go_on) {
		cout << "What would you like to do?\n";
		cout << "1. To add a symbol into any position of the string\n";
		cout << "2. To delete a symbol from any position\n";
		cout << "3. To find a symbol\n";
		cin >> choice;
		while(choice < 1 || choice > 3) {
			cout << "Wrong digit! Enter 1, 2 or 3!\n";
			cin >> choice;
		}
		system("cls");
		if(choice == 1) {
			int pos;
			char sym;
			cout << "What position?\n";
			cin >> pos;
			cout << "What symbol?\n";
			cin >> sym;
			lst.addPos(sym, pos);
			cout << "The result is:\n";
			lst.print();
		}
		else if(choice == 2) {
			int pos;
			cout << "What position?\n";
			cin >> pos;
			lst.delPos(pos);
			cout << "The result is:\n";
			lst.print();
		}
		else {
			char sym;
			int res;
			cout << "What symbol is to be found?\n";
			cin >> sym;
			res = lst.search(sym);
			if(res) {
				cout << "The position of the symbol is: " << res << "\n";
			}
			else {
				cout << "The are no such symbols!\n";
			}
		}
		cout << "Anything else? (1 - yes, 0 - no)\n";
		cin >> go_on;
		while(go_on < 0 || go_on > 1) {
			cout << "Wrong digit! Enter 1 (yes) or 0 (no)\n";
			cin >> go_on;
		}
		system("cls");
	}
}

