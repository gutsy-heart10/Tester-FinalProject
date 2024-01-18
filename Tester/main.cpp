#include<iostream>
#include<vector>
#include<string>
#include"Tester.h"
using namespace std;


int main() {
	User us;
	OpenType t;
	
    while (true) {
        int choice;
        cout << "Welcome!" << endl;
        cout << "1. Registration." << endl;
        cout << "2. Autorization." << endl;
        cout << "Select a category: ";
        cin >> choice;

        switch (choice) {
        case 1:
            us.registration();
            system("cls");
            us.regisLogin();
            system("pause");
            break;

        case 2:
            int choice1;
            us.authorization();
            cout << "---------------------------" << endl;
            cout << "1. Take the test." << endl;
            cout << "2. View previous test results." << endl;
            cin >> choice1;
            system("cls");
            switch (choice1)
            {
            case 1:
                t.displayTest();
                system("pause");
                break;
            case 2:

            default:
                cout << "Incorrect choice!" << endl;
                break;
            }
            break;

        default:
            cout << "Incorrect choice. Please choose 1 or 2." << endl;
            break;
        }
    }
	
}