/*Function "del" contains errors!!! Don't know how to fix them.*/
#include <iostream>
#include <string>
#include <stdio.h>

struct Abonent {
	std::string name;
	std::string phone;
	Abonent *parent, *left, *right;
};

class PhoneBook {
private:
	Abonent *root;
public:
	PhoneBook() {
		root = nullptr;
	}
	~PhoneBook() {
		root = nullptr;
	}
	void add(std::string name, std::string phone);
	Abonent *search(std::string name);
	Abonent *max(Abonent *node);
	void del(std::string name);
	void edit(std::string name);
	void print();
	void printNode(Abonent *node);
	void save(Abonent *node);
	void read();
	Abonent *getRoot();
};

Abonent *PhoneBook::getRoot() {
	return root;
}

void PhoneBook::add(std::string name, std::string phone) {
	Abonent *newAb = new Abonent;
	newAb -> name = name;
	newAb -> phone = phone;
	newAb -> left = newAb -> right = nullptr;
	Abonent *prev = nullptr;
	Abonent *temp = root;
	
	while(temp) {
		prev = temp;
		if(temp -> name.length() > newAb -> name.length()) {
			temp = temp -> left;
		}
		else {
			temp = temp -> right;
		}
	}

	newAb -> parent = prev;

	if(prev == nullptr) {
		root = newAb;
	}
	else if(prev -> name.length() > newAb -> name.length()) {
		prev -> left = newAb;
	}
	else {
		prev -> right = newAb;
	}
	
}

Abonent *PhoneBook::search(std::string name) {
	Abonent *s = root;
	while(strcmp(s -> name.data(), name.data()) != 0 && s != nullptr) {
		if(s -> name.length() > name.length()) {
			s = s -> left;
		}
		else {
			s = s -> right;
		}
	}
	return s;
}

Abonent *PhoneBook::max(Abonent *node) {
	if(node) {
		while(node -> right != nullptr) {
			node = node -> right;
		}
	}
	return node;
}

void PhoneBook::del(std::string name) {
	Abonent *node;
	node = search(name);
	Abonent *cur = nullptr;
	Abonent *next = nullptr;
	Abonent *prev = nullptr;
	
	if(node) {
		
		if(node -> left == nullptr && node -> right == nullptr) {
			cur = node;
			prev = node -> parent;
			if(cur -> name.length() > prev -> name.length()) {
				prev -> right = nullptr;
			}
			else {
				prev -> left = nullptr;
			}
			delete cur;
		}
		
		if((node -> left == nullptr && node -> right != nullptr) || (node -> right == nullptr && node -> left != nullptr)) {
			cur = node;
			prev = node -> parent;
			if(cur -> left != nullptr) {
				next = cur -> left;
			}
			else {
				next = cur -> right;
			}
			if(cur -> name.length() > prev -> name.length()) {
				prev -> right = next;
				next -> parent = prev;
			}
			else {
				prev -> left = next;
				next -> parent = prev;
			}
			delete node;
		}


		if(node -> left != nullptr && node -> right != nullptr) {
			Abonent *exch = nullptr;
			Abonent *parExch = nullptr;
			next = node -> left;
			cur = node;
			prev = node -> parent;
			exch = max(cur -> left);
			if(exch -> left == nullptr) {
				exch = cur;
				if(cur -> name.length() > prev -> name.length()) {
					prev -> right = exch;
				}
				else {
					prev -> left = exch;
				}
				parExch = exch -> parent;
				if(exch -> name.length() > parExch -> name.length()) {
					parExch -> right == nullptr;
				}
				else {
					parExch -> left == nullptr;
				}
				exch -> right = cur -> right;
			}
			else if(exch -> left == nullptr) {
				exch = cur;
				if(cur -> name.length() > prev -> name.length()) {
					prev -> right = exch;
				}
				else {
					prev -> left = exch;
				}
				parExch = exch -> parent;
				parExch -> right = exch -> left;
				exch -> right = cur -> right;
			}
		}
	}
}

void PhoneBook::edit(std::string name) {
	Abonent *node;
	node = search(name);
	std::string newName, newPhone;
	if(node) {
		std::cout << "Enter a new name of " << name << ":\n";
		std::getline(std::cin, newName);
		node -> name = newName;
		std::cout << "Enter a new phone of " << name << ":\n";
		std::getline(std::cin, newPhone);
		node -> phone = newPhone;
	}
}

void PhoneBook::print() {
	Abonent *temp = root;
	if(temp) {
		printNode(temp -> left);
		std::cout << temp -> name.data() << std::endl;
		std::cout << temp -> phone.data() << std::endl;
		printNode(temp -> right);
	}
	if(!root) {
		std::cout << "There is no data to print!\n" << std::endl;
	}
}

void PhoneBook::printNode(Abonent *node) {
	Abonent *temp = node;
	if(temp) {
		printNode(temp -> left);
		std::cout << temp -> name.data() << std::endl;
		std::cout << temp -> phone.data() << std::endl;
		printNode(temp -> right);
	}
}

void PhoneBook::save(Abonent *node) {
	if(!node) {
		return;
	}
	FILE* database;
	if(!(database = fopen("d:\\Database.txt", "a"))) {
		std::cout << "An error has been occurred while opening the file!\n";
	}
	fputs(node -> name.data(), database);
	fputs(" ", database);
	fputs(node -> phone.data(), database);
	fputs("\n", database);
	save(node -> left);
	save(node -> right);
	fclose(database);
}

void PhoneBook::read() {
	FILE *r;
	if(!(r = fopen("d:\\Database.txt", "r"))) {
		std::cout << "An error has been occurred while opening the file!\n";
	}
	char buf[30];
	std::string name, phone;
	fgets(buf, 30, r);
	while(!feof(r)) {
		name = strtok(buf, " ");
		phone = strtok('\0', "\n");
		add(name, phone);
		fgets(buf, 30, r);
	}
	fclose(r);
}

int main() {
	PhoneBook dir;
	dir.add("Tolpeko", "568-10-14");
	dir.add("Sultanova", "332-33-33");
	dir.add("Afonya", "333-33-33");
	dir.add("Webber", "334-33-33");
	dir.print();
	std::cout << "\n\n";
	dir.del("Sultanova");
	dir.print();
	std::cout << "\n\n";
	dir.edit("Tolpeko");
	dir.print();
	std::cout << "\n\n";
	dir.save(dir.getRoot());
	dir.read();
	dir.print();
	std::cout << "\n\n";
	return 0;
}