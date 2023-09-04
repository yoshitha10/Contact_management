#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class Contact 
{
private:
    string Name;
    string PhoneNo;
    string CityName;

public:
    Contact(const string& name, const string& phone_no,  const string& city_name)
        : Name(name), PhoneNo(phone_no), CityName(city_name) {}

    string getName() const { return Name; }
    string getPhone_no() const { return PhoneNo; }
    string getCityName() const { return CityName; } 

    void display() const 
    {
        cout << "Name: " << Name << "\n";
        cout << "Phone Number: " << PhoneNo << "\n";
        cout << "City: " << CityName << "\n";
    }

    string toCsvString() const {
        return Name + "," + PhoneNo + "," + CityName;;
    }
};

class ContactManager 
{
private:
    vector<Contact> contacts;

public:
    void addContact(const string& name, const string& phone_no, const string& city_name) 
    {
        for (Contact& contact : contacts) 
        {
            if (contact.getPhone_no() == phone_no) 
            {
                cout << "Contact with the same phone number already exists. Contact not added.\n";
                return;
            }
        }
        contacts.emplace_back(name, phone_no,city_name);
        cout << "Contact added successfully!\n";
        save_to_file("contacts.csv");
    }

    void displayContacts()
    {
        if (contacts.empty()) 
        {
            cout << "\nNo contacts found.\n";
        } 
        else 
        {
            cout << "\n--------Contacts-------\n";
            for (size_t i = 0; i < contacts.size(); ++i) 
            {
                cout << "Contact #" << i + 1 << ":\n";
                contacts[i].display();
                cout << "----------------------\n";
            }
        }
    }

    void updateContact(const string& phone_no) 
    {
        for (Contact& contact : contacts) 
        {
            if (contact.getPhone_no() == phone_no) 
            {
                cout << "---Contact found---\n";
                contact.display();
                string newName, newPhone_no,newCityName;

                cout << "\nDo you want to change the name? (yes/no): ";
                string changeName;
                cin >> changeName;
                if (changeName == "yes") 
                {
                    cout << "Enter the new Name: ";
                    cin.ignore();
                    getline(cin, newName);
                } 
                else {
                    newName = contact.getName();
                }

                cout << "\nDo you want to change the phone number? (yes/no): ";
                string changePhoneNo;
                cin >> changePhoneNo;
                if (changePhoneNo == "yes") 
                {
                    cout << "Enter the new Phone Number: ";
                    cin >> newPhone_no;
                    if (contact.getPhone_no() == phone_no) 
                    {
                        cout << "Contact with the same phone number already exists.Phone number not updated.\n";
                        newPhone_no = contact.getPhone_no();
                    }
                } 
                else {
                    newPhone_no = contact.getPhone_no();
                }

                cout << "\nDo you want to change the city? (yes/no): ";
                string changeCity;
                cin >> changeCity;
                if (changeCity == "yes") 
                {
                    cout << "Enter the new City: ";
                    cin.ignore();
                    getline(cin, newCityName);
                } 
                else {
                    newCityName = contact.getCityName();
                }

                contact = Contact(newName, newPhone_no,newCityName);
                save_to_file("contacts.csv");
                cout << "Contact updated successfully!\n";
                return;
            }
        }
        cout << "Contact not found with the provided phone number. Update failed.\n";
        return;
    }

    void deleteContact(const string& phone_no) 
    {
        for (auto it = contacts.begin(); it != contacts.end(); ++it) 
        {
            if (it->getPhone_no() == phone_no) 
            {
                it = contacts.erase(it);
                save_to_file("contacts.csv");
                cout << "Contact deleted successfully!\n";
                return;
            }
        }
        cout << "Contact not found with the provided phone number. Deletion failed.\n";
        return;
    }

    void load_from_file(const string& filename)
    {
        contacts.clear(); 
        ifstream inFile(filename);
        if (!inFile)
        {
            cout << "Creating a new empty " << filename << " file\n";
            ofstream outFile(filename);
            outFile.close();
            return;
        }
        string name, phone_no,city_name;
        string line;
        while (getline(inFile, line))
        {
            if (line.find(',') == string::npos)
                continue; 

            name = line.substr(0, line.find(','));
            line.erase(0, line.find(',') + 1); 

            if (line.find(',') == string::npos)
                continue; 

            phone_no = line.substr(0, line.find(','));
            city_name = line.substr(line.find(',') + 1);

            contacts.emplace_back(name, phone_no, city_name);
        }

        inFile.close();
        cout << "Contacts loaded from " << filename << "\n";
    }


    void save_to_file(const string& filename) 
    {
        ofstream outFile(filename);
        if (!outFile) 
        {
            cout << "Error opening " << filename << " for writing.\n";
            return;
        }

        for (const Contact& contact : contacts) 
        {
            outFile << contact.toCsvString() << "\n";
        }

        outFile.close();
    }
 
};

int main() 
{
    ContactManager contactManager;
    const string filename = "contacts.csv";

    contactManager.load_from_file(filename);

    while (true) {
        cout << "\n--------------Contact Management System---------------\n";
        cout << "1. Add Contact\n";
        cout << "2. Display Contacts\n";
        cout << "3. Update Contact\n";
        cout << "4. Delete Contact\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice) 
        {
            case 1: {
                string name, phone_no,city_name;
                cout << "\nEnter Name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter Phone Number: ";
                cin >> phone_no;
                cout << "Enter City Name: ";
                cin.ignore();
                getline(cin, city_name);
                contactManager.addContact(name, phone_no, city_name);
                break;
            }

            case 2:
                contactManager.displayContacts();
                break;

            case 3: 
            {
                string phone_no, newName, newPhone_no;
                cout << "\nEnter the Phone Number of the contact to update: ";
                cin >> phone_no;
                contactManager.updateContact(phone_no);
                break;
            }

            case 4: {
                string phone_no;
                cout << "\nEnter the Phone Number of the contact to delete: ";
                cin >> phone_no;
                contactManager.deleteContact(phone_no);
                break;
            }

            case 5:
                cout << "\nExiting the program\n";
                return 0;

            default:
                cout << "\nEnter a valid choice\n";
        }
    }

    return 0;
}
