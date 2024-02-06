#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;

struct Contact {
    string firstName;
    string lastName;
    string address;
    string phoneNumber;
    string emailAddress;
};

map<string, Contact> addressBook;

void addContacts();
void viewContacts();
void searchContact();
void editContact();
void deleteContact();
void loadContacts();
void saveContacts();

int main() {
    loadContacts();

    bool run = true;
    do {
        int option;

        while (true) {
        cout << "\n\n---Search Address Book---" << endl;
        cout << "\n--- Address Book Menu ---" << endl;
        cout << "1. Add Contact" << endl;
        cout << "2. Edit Contact" << endl;
        cout << "3. Delete Contact" << endl;
        cout << "4. View All Contacts" << endl;
        cout << "5. Search Address Book" << endl;
        cout << "6. Exit" << endl;
        cout << "Please enter your choice (1-6): ";
        cin >> option;
        cin.ignore();
        if ( option >= 1 && option <= 6) {
            break;
        } else {
            cout << "Invalid input. Please enter a number from 1 to 6." << endl;
            saveContacts();
            return 1;
        }
        }
        switch (option) {
            case 1:
                cout << "\n--- Add a New Contact ---" << endl;
                addContacts();
                break;
            case 2:
                cout << "\n--- Edit an Existing Contact ---" << endl;
                editContact();
                break;
            case 3:
                cout << "\n--- Delete a Contact ---" << endl;
                deleteContact();
                break;
            case 4:
                cout << "\n--- View All Contacts ---" << endl;
                viewContacts();
                break;
            case 5:
                cout << "\n--- Search in Address Book ---" << endl;
                searchContact();
                break;
            case 6:
                run = false;
                break;
            default:
                cout << "\nInvalid choice. Please choose between 1 to 6." << endl;
        }
    } while (run);

    saveContacts();

    cout << "\nProgram Terminated. All changes have been saved." << endl;
}



void loadContacts() {
    ifstream file("contacts.csv");
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string firstName, lastName, address, phoneNumber, emailAddress;

        getline(ss, firstName, ',');
        getline(ss, lastName, ',');
        getline(ss, address, ',');
        getline(ss, phoneNumber, ',');
        getline(ss, emailAddress, ',');

        Contact contact = {firstName, lastName, address, phoneNumber, emailAddress};
        string key = firstName + " " + lastName;
        addressBook[key] = contact;
    }

    file.close();
}

void saveContacts() {
    ofstream file("contacts.csv");

    for (const auto &pair : addressBook) {
        const Contact &contact = pair.second;
        file << contact.firstName << ',';
        file << contact.lastName << ',';
        file << contact.address << ',';
        file << contact.phoneNumber << ',';
        file << contact.emailAddress << '\n';
    }

    file.close();
}
void addContacts() {
    Contact contact;
    cout << "Enter First Name: ";
    getline(cin, contact.firstName);
    cout << "Enter Last Name: ";
    getline(cin, contact.lastName);
    string key = contact.firstName + " " + contact.lastName;

    if (addressBook.find(key) != addressBook.end()) {
        cout << "Contact already exists. Please enter a unique first name and last name." << endl;
        cout<<"Would you like to edit the existing contact? (Y/N): ";
        char ch;
        cin>>ch;
        cin.ignore();
        if(ch=='Y' || ch=='y'){
            editContact();
        }
        return;
    }

    cout << "Enter Address: ";
    getline(cin, contact.address);
    cout << "Enter Contact Number: ";
    getline(cin, contact.phoneNumber);
    cout << "Enter Email Address: ";
    getline(cin, contact.emailAddress);

    addressBook[key] = contact;
    cout << "Contact added successfully!" << endl;
}
void viewContacts() {
    cout << left << setw(20) << "First Name" << setw(20) << "Last Name" << setw(20) << "Phone Number" << setw(30) << "Email Address" << setw(30) << "Address" << endl;
    cout << "-----------------------------------------------------------------------------------------------------------" << endl;

    for (const auto &pair : addressBook) {
        const Contact &contact = pair.second;
        cout << left << setw(20) << contact.firstName << setw(20) << contact.lastName << setw(20) << contact.phoneNumber << setw(30) << contact.emailAddress << setw(30) << contact.address << endl;
    }
}
void searchContact() {
    int choice;
    string searchCriteria;

    while (true) {
        cout << "\n\n---Search Address Book---" << endl;
        cout << "1.) First name" << endl;
        cout << "2.) Last name" << endl;
        cout << "3.) Address" << endl;
        cout << "4.) Contact " << endl;
        cout << "Enter Choice: ";
        cin >> choice;
        cin.ignore();

        if (choice >= 1 && choice <= 4) {
            break;
        } else {
            cout << "Please Enter choice from 1 to 4" << endl;
        }
    }

    switch (choice) {
        case 1:
            cout << "Enter First Name: ";
            break;
        case 2:
            cout << "Enter Last Name: ";
            break;
        case 3:
            cout << "Enter Address: ";
            break;
        case 4:
            cout << "Enter Contact: ";
            break;
    }

    getline(cin, searchCriteria);
    bool visited=false;
    bool found = false;
    for (const auto &pair : addressBook) {
        const Contact &contact = pair.second;
        switch (choice) {
            case 1:
                if (contact.firstName == searchCriteria) {
                    found = true;
                }
                break;
            case 2:
                if (contact.lastName == searchCriteria) {
                    found = true;
                }
                break;
            case 3:
                if (contact.address == searchCriteria) {
                    found = true;
                }
                break;
            case 4:
                if (contact.phoneNumber == searchCriteria) {
                    found = true;
                }
                break;
        }
        if (found) {
            if(visited==false){
                cout << "\n--- Search in Address Book ---" << endl;
                cout << left << setw(20) << "First Name" << setw(20) << "Last Name" << setw(20) << "Phone Number" << setw(30) << "Email Address" << setw(30) << "Address" << endl;
                cout << "-----------------------------------------------------------------------------------------------------------------------------------------------" << endl;
                visited = true;
                found=false;
            }
            cout << left << setw(20) << contact.firstName << setw(20) << contact.lastName << setw(20) << contact.phoneNumber << setw(30) << contact.emailAddress << setw(30) << contact.address << endl;
        }
    }

    if (!visited) {
        cout << "No matches found." << endl;
    }
}

void editContact() {
    char ch;
    string firstName, lastName;
    cout << "Enter First Name of the contact you want to edit: ";
    getline(cin, firstName);
    cout << "Enter Last Name of the contact you want to edit: ";
    getline(cin, lastName);
     string oldKey = firstName + " " + lastName;
    string key = firstName + " " + lastName;
    if (addressBook.find(key) != addressBook.end()) {
        Contact contact = addressBook[oldKey]; 
        cout<<"Do you wish to edit the First Name? (Y/N): ";
        cin>>ch;
        cin.ignore();
        if (ch == 'Y' || ch == 'y')
        {
            cout << "Enter new First Name: ";
            getline(cin, contact.firstName);
        }
        cout<<"Do you wish to edit the last Name? (Y/N): ";
        cin>>ch;
        cin.ignore();
        if (ch == 'Y' || ch == 'y')
        {
            cout << "Enter new Last Name: ";
            getline(cin, contact.lastName);
        }else{
            contact.lastName = lastName;
        }
        cout<<"Do you wish to edit the address? (Y/N): ";
        cin>>ch;
        cin.ignore();
        if (ch == 'Y' || ch == 'y')
        {
            cout << "Enter new Address: ";
            getline(cin, contact.address);
        }else{
            contact.address = addressBook[oldKey].address;
        }
        cout<<"Do you wish to edit the contact number? (Y/N): ";
        cin>>ch;
        cin.ignore();
        if (ch == 'Y' || ch == 'y')
        {
            cout << "Enter new Contact Number: ";
            getline(cin, contact.phoneNumber);
        }else{
            contact.phoneNumber = addressBook[oldKey].phoneNumber;
        }
        cout<<"Do you wish to edit the e-mail address? (Y/N): ";
        cin>>ch;
        cin.ignore();
        if (ch == 'Y' || ch == 'y')
        {
        cout << "Enter new Email Address: ";
        getline(cin, contact.emailAddress);
        }else{
            contact.emailAddress = addressBook[oldKey].emailAddress;
        }

        addressBook.erase(oldKey); // Remove the old contact
        string newKey = contact.firstName + " " + contact.lastName;
        addressBook[newKey] = contact; // Add the updated contact with the new key
        cout << "Contact updated." << endl;
    } else {
        cout << "Contact not found." << endl;
    }
}

void deleteContact() {
    string firstName, lastName;
    cout << "Enter First Name of the contact you want to delete: ";
    getline(cin, firstName);
    cout << "Enter Last Name of the contact you want to delete: ";
    getline(cin, lastName);

    string key = firstName + " " + lastName;
    if (addressBook.find(key) != addressBook.end()) {
        addressBook.erase(key);
        cout << "Contact deleted." << endl;
    } else {
        cout << "Contact not found." << endl;
    }
}
