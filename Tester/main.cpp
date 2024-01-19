#include<iostream>
#include<vector>
#include<string>
#include"Tester.h"
using namespace std;

void MenuMain(OpenType& t);


int main() {
	User us;
	OpenType t;
#pragma region MyRegion

    //while (true) {
    //    int choice;
    //    mainMenu();
    //    cin >> choice;
    //    system("cls");
    //    switch (choice) {
    //    case 0:
    //        system("cls");
    //        cout << "GoodBye!" << endl;
    //        exit(1);
    //    case 1:
    //        us.registration();
    //        system("cls");
    //        us.regisLogin();
    //        system("pause");
    //        break;

    //    case 2:
    //        int choice1;
    //        t.displayTest();
    //        cout << "---------------------------" << endl;
    //        cout << "1. Take the test." << endl;
    //        cout << "2. View previous test results." << endl;
    //        cin >> choice1;
    //        system("cls");

    //        switch (choice1)
    //        {
    //        case 1:
    //            t.displayTest();
    //            system("pause");
    //            break;
    //        case 2:
    //            t.writeResultTestFile();

    //        case 3:
    //            cout << "GoodBye!" << endl;
    //            exit(1);
    //        default:
    //            cout << "Incorrect choice!" << endl;
    //            break;
    //        }
    //        break;

    //    default:
    //        cout << "Incorrect choice. Please choose 1 or 2." << endl;
    //        break;
    //    }
    //}

    /*int choice, choice2{};*/

    //while (true) {
    //    mainMenu();
    //    cin >> choice;
    //    switch (choice)
    //    {
    //    case 1:
    //        t.registration();
    //        system("pause");
    //        system("cls");
    //        t.regisLogin();
    //        system("pause");
    //        system("cls");
    //        break;

    //    case 2:
    //        system("cls");
    //        t.authorization();
    //        cin >> choice2;
    //        switch (choice2)
    //        {
    //        case 1:
    //            t.displayTest();
    //            system("pause");
    //            break;
    //        case 2:
    //            t.readResultTestFile();
    //            system("pause");
    //            break;
    //        case 3:
    //            mainMenu();
    //            break;
    //        default:
    //            break;
    //        }
    //    case 0:
    //        cout << "Goodbye!" << endl;
    //        exit(1);
    //    default:
    //        break;
    //    }
    //} 




    //while (true) {
    //    mainMenu();

    //    int choice;
    //    cin >> choice;
    //    cin.ignore();

    //    switch (choice) {
    //    case 1:
    //        t.registration();
    //        t.regisLogin();
    //        break;
    //    case 2:
    //        t.authorization();
    //        /*t.displayTest();*/
    //        break;
    //    case 0:
    //        cout << "Goodbye!" << endl;
    //        return 0;
    //    default:
    //        cout << "Invalid choice. Please enter a valid option." << endl;
    //        break;
    //    }
    //}
#pragma endregion
    MenuMain(t);
}