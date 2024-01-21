#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<conio.h>
using namespace std;

string root = "../files/";

class Person {
protected:
	string fullName;
	string homeAdress;
	string phoneNumber;
public:
	Person() : fullName(""), homeAdress(""), phoneNumber("")
	{}
	virtual void registration() = 0;
	virtual void regisLogin() = 0;
	virtual bool isLoginUnique(const string& newLogin) = 0;
	virtual bool isPasswordCorrect(const string& login, const string& enteredPass) = 0;
	virtual void authorization() = 0;
	virtual void encrypt(string& log, string pass) = 0;
	virtual string getName() {
		return fullName;
	}
	virtual string getAdress() {
		return homeAdress;
	}
	virtual string getPhonenumber() {
		return phoneNumber;
	}
	virtual ~Person() = 0 {};
	
};

void mainMenu() {
	cout << "Welcome!" << endl;
	cout << "1. Registration." << endl;
	cout << "2. Autorization." << endl;
	cout << "0. Exit." << endl;
	cout << "Select a category: ";
}

class User : public Person
{
protected:
	string login;
	string password;
public:
	User() : login(""), password("")
	{}
	virtual string getLogin() {
		return login;
	}

	void registration() override {
		cout << "Enter your fullname: ";
		cin.ignore();
		getline(cin, fullName);
		cout << "Enter your home adress: ";
		getline(cin, homeAdress);
		cout << "Enter your phone number: ";
		cin >> phoneNumber;
		cout << "Registration was successful!!" << endl;
	}

	void regisLogin() override {
		cout << "Registration your login and password ^^" << endl;
		cout << "Login: ";	
		cin >> login;
		if (!isLoginUnique(login)) {
			cout << "This login already exists!" << endl;
			return;
		}
		else {
			cout << "Password: ";
			cin >> password;
			cout << "Welcome! " << login << endl;
		}
		writeRegistrationFile();
		writeLoginsPassFile();
	}

	void authorization() override {
		cout << "Sign in" << endl;
		cout << "Login: ";
		cin >> login;
		cout << "Password: ";
		cin >> password;
		if (isPasswordCorrect(login, password)) {
			cout << "Welcome " << login << endl;
			encrypt(login, password);
			
		}
		else {
			cout << "Incorrect login or password!" << endl;
			system("pause");
			system("cls");
			return mainMenu();
		}

	}

	void encrypt(string& log, string pass) override {
		for (char& ch : login) {
			ch = static_cast<char>(ch + 1);
		}
		for (char& ch : pass) {
			ch = static_cast<char>(ch + 1);
		}
		cout << "Encrypt login: " << log << endl;
		cout << "Encrypt password: " << pass << endl;
	}
	
	bool isLoginUnique(const string& newLogin) override {
		ifstream file(root+"log.txt", ios::in);
		if (file.is_open()) {
			string existingLogin;
			while (file >> existingLogin) {
				if (existingLogin == newLogin) {
					file.close();
					return false;
				}
			}
			file.close();
		}
		return true;
	}

	bool isPasswordCorrect(const string& login, const string& enteredPass) override {
		ifstream fileLogin(root + "log.txt", ios::in);
		ifstream filePass(root + "pass.txt", ios::in);
		if (fileLogin.is_open() && filePass.is_open()) {
			string existingLogin;
			string existingPass;
			while (fileLogin >> existingLogin && filePass >> existingPass) {
				if (login == existingLogin && enteredPass == existingPass) {
					fileLogin.close();
					filePass.close();
					return true;
				}
			}
			fileLogin.close();
			filePass.close();
		}
		return false;
	}

	void writeRegistrationFile() {
		ofstream file(root + "userData.txt", ios::out | ios::app);
		if (file.is_open()) {
			file << "User information:" << endl;
			file << "Fullname: " << fullName << endl;
			file << "Home Adress: " << homeAdress << endl;
			file << "Phone number: " << phoneNumber << endl;
			file << "Login: " << login << endl;
			file << "Password: " << password << endl;
			file << "-----------------------------------" << endl;
		}
		file.close();
	}
	
	void writeLoginsPassFile() {
		ofstream log(root + "log.txt",  ios::out | ios::app);
		ofstream pass(root + "pass.txt", ios::out | ios::app);

		if (log.is_open() && pass.is_open()) {
			log << login << endl;
			log << "-----------------------------------" << endl;
			pass << password << endl;
			pass << "-----------------------------------" << endl;
		}
		log.close();
		pass.close();
	}

	~User()
	{}
};

class Questions
{
protected:
	string question, answer;
	string chapter;
	int trueCount, falseCount,
	currentQuestionIndex, savedTrueCount;
public:
	Questions() 
	{
		question = "";
		answer = "";
		chapter = "";
		trueCount = 0;
		falseCount = 0;
		currentQuestionIndex = 0;
		savedTrueCount = 0;
	}
	virtual void displayTest() = 0;
	virtual void answersCheck() = 0;
	virtual ~Questions() = 0 {};
	
};
class OpenType : public Questions, public User {
private:
	// ƒобавим приватные переменные дл€ хранени€ информации о текущем прогрессе
	int currentQuestionIndex;
	int savedTrueCount;
	bool interruptTest;


public:
	string root = "../files/";

	OpenType() : currentQuestionIndex(0), savedTrueCount(0), interruptTest(false){}

	void displayTest() override {
		int choice{}, choice2{}, menu{};
		authorization();
		system("pause");
		system("cls");

		cout << "---------------------------" << endl;
		cout << "1. Take the test." << endl;
		cout << "2. View previous test results." << endl;
		cout << "0. Exit your account." << endl;
		cin >> menu;
		if (menu == 1) {
			readChapterFile();
			cin >> choice;
			cin.ignore();
		}
		else if (menu == 2) {
			readResultTestFile();
		}
		else if (menu == 0) {
			return mainMenu();
		}

		switch (choice) {
		case 1:
			readQuestionsFile("logicQuestions.txt", "logicAnswers.txt");
			system("pause");
			break;
		case 2:
			cout << "1. Quiz city names." << endl;
			cout << "2. Quiz car brand names." << endl;
			cout << "Select category :)";
			cin >> choice2;
			cin.ignore();
			if (choice2 == 1) {
				readQuestionsFile("citiesQuizQues.txt", "citiesQuizAnsw.txt");
			}
			else if (choice2 == 2) {
				readQuestionsFile("carsQuizQues.txt", "carsQuizAnsw.txt");
				break;
			}
			system("pause");
			break;
		default:
			cout << "Incorrect selection. Choose 1 or 2 :)" << endl;
			break;
		}
		writeResultTestFile();
		
	}

	void answersCheck() override {
		const int totalQuestions = 12;
		double percentage = static_cast<double>(trueCount) / totalQuestions * 100;
		cout << "Percentage of Correct Answers: " << percentage << "%" << endl;
	}

	void askToInterruptTest() {
		char interruptChoice;
		cout << "Do you want to interrupt the test? (y/n): ";
		cin >> interruptChoice;
		if (interruptChoice == 'y' || interruptChoice == 'Y') {
			interruptTest = true;
			writeInterruptTest();
			return mainMenu();
		}
		else {
			interruptTest = false;
		}
	}

	bool hasSavedProgress() {
		ifstream progressFile(root + "progress.txt", ios::in);
		return progressFile.good();
	}

	void readQuestionsFile(string fileQuestions, string fileAnswers) {
		ifstream FileQues(root + fileQuestions, ios::in);
		ifstream FileAnsw(root + fileAnswers, ios::in);
		User u;
		if (FileQues.is_open() && FileAnsw.is_open()) {
			string question, answer;
			int falseCount{};
			for (; getline(FileQues, question) && getline(FileAnsw, answer);) {
				cout << question << endl;
				string userAnswer;

				cout << "Your Answer: ";
				getline(cin, userAnswer);

				if (_strcmpi(userAnswer.c_str(), answer.c_str()) == 0) {
					cout << "Correct Answer!" << endl;
					trueCount++;
				}
				else {
					cout << "Incorrect Answer. Correct Answer: " << answer << endl;
					falseCount++;
				}
				cout << "-------------------" << endl;
				askToInterruptTest();
			}
			cout << "Total Answers :) " << endl;
			cout << "Correct answers: " << trueCount << endl;
			cout << "Incorrect answers: " << falseCount << endl;
			cout << "Mark: " << trueCount << endl;
			answersCheck();
			writeResultTestFile();
			FileQues.close();
			FileAnsw.close();
		}
		else {
			cout << "Unable to open the files." << endl;
		}

	}

	void readChapterFile() {
		ifstream fileChapter(root + "chapters.txt", ios::in);
		if (fileChapter.is_open()) {
			cout << "Select a section:" << endl;
			while (getline(fileChapter, chapter)) {
				cout << chapter << endl;
			}
			fileChapter.close();
		}
		else {
			cout << "Unable to open the file." << endl;
		}
	}

	void writeResultTestFile() {
		ofstream fileResult(root + "resultStudents.txt", ios::out | ios::app);
		if (fileResult.is_open()) {
			fileResult << "Results:" << endl;
			fileResult << "Login: " << login << endl;
			fileResult << "Test: " << chapter << endl;
			fileResult << "Mark: " << trueCount << endl;
			fileResult.close();
		}
		else {
			cout << "Error: Unable to open the file for writing." << endl;
		}
	}

	void readResultTestFile() {
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

	void writeInterruptTest() {
		ofstream file(root + "progress.txt", ios::out | ios::trunc);
		if (file.is_open()) {
			file << "CurrentQuestionIndex: " << currentQuestionIndex << endl;
			file << "SavedTrueCount: " << savedTrueCount << endl;
			file.close();
			cout << "Test progress saved successfully." << endl;
		}
		else {
			cout << "Error: Unable to open the file for writing." << endl;
		}
	}

	void readInterruptTest() {
		ifstream file(root + "progress.txt", ios::in);
		if (file.is_open()) {
			file >> currentQuestionIndex;
			file >> savedTrueCount;
			file.close();
			cout << "Test progress loaded successfully." << endl;
		}
		else {
			cout << "Error: Unable to open the file for reading." << endl;
		}
	}

	void testMenu() {
		cout << "---------------------------" << endl;
		cout << "1. Take the test." << endl;
		cout << "2. View previous test results." << endl;
		cout << "0. Exit your account." << endl;
		if (!interruptTest && hasSavedProgress()) {
			readInterruptTest();
		}
		displayTest();
	}
};

void MenuMain(OpenType& t) {
	while (true) {
		mainMenu();

		int choice;
		cin >> choice;
		cin.ignore();

		switch (choice) {
		case 1:
			t.registration();
			system("pause");
			system("cls");
			t.regisLogin();
			system("pause");
			system("cls");
			break;
		case 2:
			
			t.displayTest();
			break;
		case 0:
			cout << "Goodbye!" << endl;
			exit(1);
		default:
			cout << "Invalid choice. Please enter a valid option." << endl;
			break;
		}

	}
}