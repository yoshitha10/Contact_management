#include <iostream>
#include <fstream>
using namespace std;

class contact
{
private:
    string name,phone_no,address;
    string search;
    fstream file;
public:
    void add_contact()
    {
        //taking inputs from the user
        cout<<"\n--------------------------";
        cout<<"\nEnter Name: ";
        getline(cin,name);
        cout<<"\nEnter Phone Number: ";
        getline(cin,phone_no);
        cout<<"\nEnter address: ";
        getline(cin,address);
        cout<<"----------------------------";

        //adding the information to the data
        file.open("contacts.csv",ios::out | ios::app);
        file<<name<<","<<phone_no<<","<<address<<"\n";
        file.close();
    }

    void show_contacts()
    {
        //fetches the first contact details
        file.open("contacts.csv", ios::in);

        getline(file,name,',');
        getline(file,phone_no,',');
        getline(file,address,'\n');
        //displays the next contacts until all contacts are fetched from the file
        cout<<"\n------Available Contacts-------";
        while(!file.eof())
        {
            cout<<"\nName: "<<name;
            cout<<"\nPhone No: "<<phone_no;
            cout<<"\nAddress: "<<address;
            cout<<"\n-------------------------------";
 
            getline(file,name,',');
            getline(file,phone_no,',');
            getline(file,address,'\n');
        }
        file.close();
        return;
    }

    void delete_contact()
    {
        fstream filein,fileout;
        string phone,phone_del;
        cout<<"\nEnter the phone number to be deleted: ";
        getline(cin,phone_del);

        //here we use two file pointers
        filein.open("contacts.csv", ios::in);
        fileout.open("newcontacts.csv", ios::out | ios::app);

        getline(filein,name,',');                //fetch the details from contacts file
        getline(filein,phone_no,',');
        getline(filein,address,'\n');
        while(!filein.eof())
        {
            if(phone_no != phone_del)
            {
                fileout<<name<<","<<phone_no<<","<<address<<"\n";      //fill them in newcontacts file except the one which is to be deleted
            }
            getline(filein,name,',');
            getline(filein,phone_no,',');
            getline(filein,address,'\n');
        }
        filein.close();
        fileout.close();

        remove("contacts.csv");                      //removing the old file and renaming the new file
        rename("newcontacts.csv","contacts.csv");
        return;
    }

    void search_contact()
    {
        cout<<"\nEnter the phone number to be searched: ";
        getline(cin,search);

        file.open("contacts.csv", ios::in);          //opening the file and fetching details of the contacts

        getline(file,name,',');
        getline(file,phone_no,',');
        getline(file,address,'\n');
        while(!file.eof())
        {
            if(phone_no == search)                //details of the contact are displayed if found
            {
                cout<<"\nContact Found!------";
                cout<<"\nName: "<<name;
                cout<<"\nPhone No: "<<phone_no;
                cout<<"\nAddress: "<<address;
                cout<<"\n--------------------";
                return;
            }
            else
            {               
                getline(file,name,',');           //fetch the other contacts till end of the file if we didn't find the contact
                getline(file,phone_no,',');
                getline(file,address,'\n');
            }
        }
        cout<<"\nContact is not found!";
        file.close();
        return;
    }

}object;

int main()
{
    int choice;
    do
    {
        cout<<"\n0)Exit";
        cout<<"\n1)Add Contact";
        cout<<"\n2)Show Contacts";
        cout<<"\n3)Search Contact";
        cout<<"\n4)Delete Contact";
        cout<<"\nEnter your choice: ";
        cin>>choice;
        cin.ignore();
        switch(choice)
        {
            case 0:
                exit;
                break;

            case 1:
                object.add_contact();
                break;

            case 2:
                object.show_contacts();
                break;

            case 3:
                object.search_contact();
                break;

            case 4:
                object.delete_contact();
                break;
            default:
                cout<<"\nEnter a valid choice";
                break;
        }
    }while (choice);
    return 0;
}