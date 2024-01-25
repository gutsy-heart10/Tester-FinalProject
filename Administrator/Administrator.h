#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include <sstream>
using namespace std;

string root = "../files/";

class InfoAdmin {
protected:
	string fullName;
	string email;
	string login;
	string password;
public:
	InfoAdmin() : fullName(""), email(""), login(""), password("")
	{}
	virtual void registration() = 0;
	virtual void authorization() = 0;
	virtual void encrypt(string& log, string pass) = 0;
	virtual ~InfoAdmin() = 0 {};
};

class Admin : public InfoAdmin
{
public:
	Admin() {}
	// osushitvlayet vxod libo registraciyu
	void AdminMenu() {
		char choice[5];
		registration();
		cout << "If you want to change your login or password (y/n) ?";
		cin >> choice;
		if (choice == "Y" || choice == "y") {
			ChangeLogPass();
		}
		delete[] choice;
	};

	void registration() override {
		cout << "Enter your full name: ";
		getline(cin, fullName);
		cin.ignore();
		cout << "Enter your email: ";
		getline(cin, email);
		cout << "Enter your login: ";
		cin >> login;
		cout << "Enter your password: ";
		cin >> password;
		writeAdminData(login);
		writeAdminLogPass(login, password);
		authorization();
	}
	void authorization() override {
		cout << "Login: ";
		getline(cin, login);
		cin.ignore();
		cout << "Password: ";
		getline(cin, password);
		cin.ignore();
		if (IsPasswordCorrect(login, password)) {
			cout << "Welcome Admin " << fullName << endl;
			encrypt(login, password);
		}
		else {
			cout << "Incorrect login or password!" << endl;
			return authorization();
		}
	}

	// metod
	void checkWork() {
		return CheckAdminAccount();
	}
	// proverka parol
	bool IsPasswordCorrect(const string& login, const string& enteredPass) {
		ifstream fileLog(root + "adminLog.dat", ios::in);
		ifstream filePass(root + "adminPass.dat", ios::in);
		if (fileLog.is_open() && filePass.is_open()) {
			string existingLogin;
			string existingPass;
			while (fileLog >> existingLogin && filePass >> existingPass)
			{
				if (login == existingLogin && enteredPass == existingPass) {
					fileLog.close();
					filePass.close();
					return true;
				}
			}
			fileLog.close();
			filePass.close();
		}
		return false;
	}
	// smena log i pass
	void ChangeLogPass() {
		readAdminLogPass();
		string log, pass;
		cout << "Enter new login: ";
		cin >> log;
		cout << "Enter new password: ";
		cin >> pass;
		updateData(log, pass);
	}
	void updateData(const string& newLog, const string& newPass) {
		writeAdminData(newLog);
		writeAdminLogPass(newLog, newPass);
	}
	// shifr
	void encrypt(string& log, string pass) override {
		for (char& ch : login) {
			ch = static_cast<char>(ch + 1);
		}
		for (char& ch : pass) {
			ch = static_cast<char>(ch + 1);
			ch = '*';
		}
		cout << "Encrypt login: " << log << endl;
		cout << "Encrypt password: " << pass << endl;
	}
	// zapis vsex dannix
	void writeAdminData(const string& login) {
		ofstream file(root + "adminData.dat", ios::out | ios::app);
		if (file.is_open()) {
			file << "Full Name: " << fullName << endl;
			file << "E-mail: " << email << endl;
			file << "Login: " << login << endl;
			file << "Password: " << password << endl;
		}
		file.close();
	}
	// chteniye dannix
	void readAdminData() {
		ifstream file(root + "adminData.dat", ios::in);
		if (file.is_open()) {
			string fullname, email, login, password;
			while (file >> fullName && file >> email && file >> login && file >> password) {
				cout << "Full Name: " << fullname << endl;
				cout << "E-mail: " << email << endl;
				cout << "Login: " << login << endl;
				cout << "Password: " << password << endl;
			}
		}
		file.close();
	}
	// zapis log i pass
	void writeAdminLogPass(const string& login, const string& password) {
		ofstream fileLog(root + "adminLog.dat", ios::out | ios::app);
		ofstream filePass(root + "adminPass.dat", ios::out | ios::app);
		if (fileLog.is_open() && filePass.is_open()) {
			fileLog << "-----------------------------------" << endl;
			fileLog << "Login: " << login << endl;
			fileLog << "-----------------------------------" << endl;
			filePass << "-----------------------------------" << endl;
			filePass << "Password: " << password << endl;
			filePass << "-----------------------------------" << endl;
		}
		fileLog.close();
		filePass.close();
	}
	// chteniye log i pass
	void readAdminLogPass() {
		ifstream fileLog(root + "adminLog.dat", ios::in);
		ifstream filePass(root + "adminPass.dat", ios::in);
		if (fileLog.is_open() && filePass.is_open()) {
			string log;
			string pass;
			while (fileLog >> log && filePass >> pass) {
				cout << "Login: " << log << ", Password: " << pass << endl;
			}
		}
		fileLog.close();
		filePass.close();
	}
	// proverka nalicii admina
	void CheckAdminAccount() {
		ifstream file(root + "adminLog.dat", ios::in);
		if (file.is_open()) {
			string storedLogin;
			string storedPassword;
			file >> storedLogin >> storedPassword;
			if (!file.fail()) {
				return AdminMenu();
			}
			else {
				return registration();
			}
			file.close();
		}
	}
	~Admin()
	{}
};


class AdminFeatures : public Admin
{
public:
	// tut budet 3 kateqorii kotoriye mojet sdelat admin
	AdminFeatures() {}

	// dobavleniye polzovatelya
	void addUser() {
		string fullName, homeAdress, phoneNumber, usLogin, usPass;
		cout << "Enter the full name of the user: ";
		cin.ignore();
		getline(cin, fullName);
		cout << "Enter the home adress of the user: " << homeAdress << endl;
		cin.ignore();
		getline(cin, homeAdress);
		
		cout << "Enter the phone number of the user: ";
		cin>>phoneNumber;
		cout << "Enter the login of the user: ";
		cin >> usLogin;
		cout << "Enter the password of the user: ";
		cin >> usPass;
		ofstream outFile(root + "userData.txt", ios::out | ios::app);
		
		if (outFile.is_open()) {
			outFile << usLogin << endl;
			outFile << usPass << endl;
			outFile << fullName << endl;
			outFile << homeAdress << endl;
			outFile << phoneNumber << endl;
			cout << "-------------------------------" << endl;
			cout << "User added successfully!" << endl;
		}
			outFile.close();
	}
	// udaleniye polzovatelya
	void deleteUser() {
		int ch{};
		ifstream file(root + "userData.txt", ios::in);
		if (!file.is_open()) {
			cout << "Unable to open the files." << endl;
			return;
		}
		vector<string> userEnter;
		string fullName, homeAdress, phoneNumber, usLogin, usPass;
		while (file >> fullName && file >> homeAdress && file >> phoneNumber && file >> usLogin && file >> usPass) {
			cout << "User " << userEnter.size() + 1 <<':' << endl;
			cout << "Login: " << usLogin << endl;
			cout << "Password: " << usPass <<endl;
			cout << "Full Name: " << fullName << endl;
			cout << "Home adress: " << homeAdress << endl;
			cout << "Phone number: " << phoneNumber << endl;
			userEnter.push_back(fullName + " " + homeAdress + " " + phoneNumber + " " + usLogin + " " + usPass);
		}
		file.close();
		if (userEnter.empty()) {
			cout << "Not found users." << endl;
			return;
		}
		cout << "Select user for delete: ";
		cin	>> ch;
		if (ch >= 1 && ch <= userEnter.size()) {
			userEnter.erase(userEnter.begin() + ch - 1);
			ofstream fileOut(root + "userData.txt", ios::out | ios::trunc);
			if (fileOut.is_open()) {
				for (const string& enter : userEnter) {
					fileOut << enter << endl;
				}
				fileOut.close();
				cout << "User is deleted!" << endl;
			}
		}
		else {
			cout << "Unable to open the files." << endl;
			return;
		}
	}
	// modifikaciya polzovatelya
	void userModification() {
		// smenit login i parol
		int ch{};
		ifstream file(root + "userData.txt", ios::in);
		if (!file.is_open()) {
			cout << "Unable to open the files." << endl;
			return;
		}
		vector<string> userEnter;
		string fullName, homeAdress, phoneNumber, usLogin, usPass;
		while (file >> fullName && file >> homeAdress && file >> phoneNumber && file >> usLogin && file >> usPass) {
			cout << "User " << userEnter.size() + 1 << ':' << endl;
			cout << "Login: " << usLogin << endl;
			cout << "Password: " << usPass << endl;
			cout << "Full Name: " << fullName << endl;
			cout << "Home adress: " << homeAdress << endl;
			cout << "Phone number: " << phoneNumber << endl;
			userEnter.push_back(fullName + " " + homeAdress + " " + phoneNumber + " " + usLogin + " " + usPass);
		}
		file.close();
		if (userEnter.empty()) {
			cout << "Not found users." << endl;
			return;
		}
		cout << "Select user: ";
		cin >> ch;
		if (ch >= 1 && ch <= userEnter.size()) {
			cout << "Enter the new login of the user: ";
			cin >> usLogin;
			cout << "Enter the new password of the user: ";
			cin >> usPass;

			userEnter[ch - 1] = usLogin + " " + usPass + fullName + " " + homeAdress + " " + phoneNumber;

			ofstream outFile(root + "userData.txt", ios::out | ios::trunc);

			if (outFile.is_open()) {
				for (const string& enter : userEnter) {
					outFile << enter << endl;
				}
				outFile.close();
				cout << "User is modified!" << endl;
			}
		}
	}

	// statistika 
	void displayStatisResults() {
		ifstream fileResult(root + "resultStudents.txt", ios::in);
		if (fileResult.is_open()) {
			string line;
			while (getline(fileResult, line)) {
				if (line.find("Login: " + login) != string::npos) {
					cout << line << endl;
					while (getline(fileResult, line) && line != "") {
						cout << line << endl;
					}
					break;
				}
			}
			fileResult.close();
		}
		else {
			cout << "Error: Unable to open the file." << endl;
			return;
		}
	}

	// osnovnoy menu
	void CategoryMenu() {
		AdminMenu();
		// metod upravleniye polzovatelyami

	}
	

};