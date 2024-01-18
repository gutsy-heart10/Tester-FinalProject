#include<iostream>
#include<fstream>
#include<vector>
#include<string>
using namespace std;

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
};

class User : public Person
{
private:
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
		cin >> homeAdress;
		cout << "Enter your phone number: ";
		cin >> phoneNumber;
		writeRegistrationFile();
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
			cout << "Welcome!" << endl;
		}
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
		ifstream file("studentsLogin.txt", ios::in);
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
		ifstream fileLogin("studentsLogin.txt", ios::in);
		ifstream filePass("studentsPassword.txt", ios::in);
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
		ofstream file("studentsRegistration.txt", ios::out | ios::app);
		if (file.is_open()) {
			file << "User information:" << endl;
			file << "Fullname: " << fullName << endl;
			file << "Home Adress: " << homeAdress << endl;
			file << "Phone number: " << phoneNumber << endl;
			file << "-----------------------------------" << endl;
		}
		file.close();
	}
	
	void writeLoginsPassFile() {
		ofstream loginFile("studentsLogin.txt", ios::out | ios::app);
		ofstream passwordFile("studentsPassword.txt", ios::out | ios::app);

		if (loginFile.is_open() && passwordFile.is_open()) {
			loginFile <<"Login: " << login << endl;
			passwordFile <<"Password: " << password << endl;
			loginFile << "-----------------------------------" << endl;
			passwordFile << "-----------------------------------" << endl;
		}

		loginFile.close();
		passwordFile.close();
	}
};

class Questions
{
protected:
	string text;
	string chapter;
	string answers;
public:
	Questions() 
	{
		text = "";
		vector<string> answers{};
	}
	virtual void displayTest() = 0;
	virtual void answersCheck() = 0;
	
};
class OpenType : public Questions, public User
{
private:
	int trueCount;
public:
	OpenType() {trueCount = 0;}
	void displayTest() override {
		int choice, choice2;
		readChapterFile();
		cin >> choice;
		switch (choice)
		{
		case 1:
			readQuestionsFile("logicQuestions.txt", "logicAnswers.txt");
			// writeResult()
			break;
		case 2:
			cout << "1. Quiz city names." << endl;
			cout << "2. Quiz car brand names." << endl;
			cout << "Select category :)";
			cin >> choice2;
			if (choice2 == 1) {
				readQuestionsFile("citiesQuizQues.txt","citiesQuizAnsw.txt");
			}
			else if (choice2 == 2) {
				readQuestionsFile("carsQuizQues.txt", "carsQuizAnsw.txt");
			}
			break;
		default:
			cout << "Incorrect selection. Choose 1 or 2 :)" << endl;
			break;
		}	
	}
	void answersCheck() override {
		const int totalQuestions = 12;
		double percentage = static_cast<double>(trueCount) / totalQuestions * 100;
		cout << "Percentage of Correct Answers: " << percentage << "%" << endl;
	}
	
	void readQuestionsFile(string fileQuestions, string fileAnswers) {
		ifstream FileQues(fileQuestions, ios::in);
		ifstream FileAnsw(fileAnswers, ios::in);

		if (FileQues.is_open() && FileAnsw.is_open()) {
			string question, answer;
			int falseCount{};
			while (getline(FileQues, question) && getline(FileAnsw, answer)) {
				cout << "Question: " << question << endl;

				string userAnswer;
				cout << "Your Answer: ";
				getline(cin, userAnswer);

				for (char& c : userAnswer) {
					c = tolower(c);
				}

				for (char& c : answer) {
					c = tolower(c);
				}

				if (userAnswer == answer) {
					cout << "Correct Answer!" << endl;
					trueCount++;
				}
				else {
					cout << "Incorrect Answer. Correct Answer: " << answer << endl;
					falseCount++;
				}
				cout << "-------------------" << endl;
			}
				cout << "Total Answers :) " << endl;
				cout << "Correct answers: " << trueCount << endl;
				cout << "Incorrect answers: " << falseCount << endl;
				cout << "Mark: " << trueCount << endl;
				answersCheck();
			FileQues.close();
			FileAnsw.close();
		}
		else {
			cout << "Unable to open the files." << endl;
		}
	}
	void readChapterFile() {
		ifstream fileChapter("chapters.txt", ios::in);
		if (fileChapter.is_open()) {
			string chapter;
			
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
	
	/*void writeResultTestFile() {
	
		ofstream fileResult("resultStudents.txt", ios::out | ios::app);
		if (fileResult.is_open()) {
			fileResult << "Results:" << endl;
			fileResult << "Login: " << getLogin() << endl;
			
		}
	}*/
};