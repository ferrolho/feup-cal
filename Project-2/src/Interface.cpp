#include "Interface.h"

#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

const string contactsListPath = "contacts.txt";

Interface::Interface() {
	done = false;
	loadContacts();
}

Interface::~Interface() {
	foreach(contacts, it)
		delete (*it);
}

bool Interface::isDone() {
	return done;
}

void Interface::clearStdInAndPressEnterToContinue() {
	// clearing buffer
	cin.clear();
	cin.ignore(10000, '\n');

	cout << "Press <Enter> to continue...";
	cin.get();
}

void Interface::loadContacts() {
	// clearing vector current content
	contacts.clear();

	// trying to open file
	ifstream fin;
	fin.open(contactsListPath.c_str());
	if (!fin) {
		cerr << "Error: Unable to open file: " << contactsListPath << endl;
		exit(1);
	}

	// reading number of contacts to be read from file
	int nContacts;
	fin >> nContacts;

	// loading each contact from file
	string firstName, lastName, phoneNumber, email, address;
	for (int i = 0; i < nContacts; i++) {
		// reading firstName, lastName, phoneNumber and email
		fin >> firstName >> lastName >> phoneNumber >> email;

		// reading address
		getline(fin, address);
		address.erase(address.begin());

		/*
		 // Debugging block
		 cout << "firstName: <" << firstName << ">" << endl;
		 cout << "lastName: <" << lastName << ">" << endl;
		 cout << "phoneNumber: <" << phoneNumber << ">" << endl;
		 cout << "email: <" << email << ">" << endl;
		 cout << "address: <" << address << ">" << endl;
		 cout << endl;
		 */

		Contact* contact = new Contact(firstName, lastName, phoneNumber, email,
				address);
		contacts.insert(contact);
	}
}

void Interface::saveContacts() {
	cout << endl;
	cout << "Updating: " << contactsListPath << endl;

	// trying to open output stream
	ofstream fout;
	fout.open(contactsListPath.c_str());
	if (!fout) {
		cerr << "Error: Unable to open file: " << contactsListPath << endl;
		exit(1);
	}

	// saving number of contacts
	fout << contacts.size() << endl;
	foreach(contacts, it)
	{
		// saving firstName and lastName
		fout << (*it)->getFirstName() << " " << (*it)->getLastName();

		// saving phoneNumber
		fout << " " << (*it)->getPhoneNumber();

		// saving email
		fout << " " << (*it)->getEmail();

		// saving address
		fout << " " << (*it)->getAddress();

		fout << endl;
	}
}

void Interface::showMainMenu() {
	cout << endl;
	cout << "-------------------" << endl;
	cout << "Contacts management" << endl;
	cout << "-------------------" << endl;
	cout << endl;
	cout << "1. Contacts List" << endl;
	cout << "2. Search" << endl;
	cout << "3. Add Contact" << endl;
	cout << "4. Remove Contact" << endl;
	cout << "5. Exit" << endl;
	cout << endl;
	cout << "Choose an option:" << endl;
	cout << "> ";

	int input;
	cin >> input;
	input--;

	switch ((Action) input) {
	case LIST_ALL:
		showContactsList();
		break;
	case SEARCH:
		break;
	case ADD:
		break;
	case REMOVE:
		break;
	case EXIT:
		saveContacts();
		done = true;
		break;
	default:
		cout << endl;
		cout << "Invalid input." << endl;
		clearStdInAndPressEnterToContinue();
		break;
	}
}
void Interface::showContactsList() {
	cout << endl;
	foreach(contacts, it)
		cout << **it << endl;

	clearStdInAndPressEnterToContinue();
}
