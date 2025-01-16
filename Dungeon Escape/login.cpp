#include<iostream>
#include "login.h"
#include<string>
#include<fstream>


bool logged = false;
std::string firstname, password, lastname , name; 


void welcomeText() { // Начално съобщение
	std::cout << "Welcome to Maze escape!" << "\n";
	std::cout << "The objective of the game is for the user to escape from a maze." << "\n";
	std::cout<<"To complete this challenge, he has to go through the different difficulty levels successfully" 
		"and with the maximum number of coins.";
	std::cout << std::endl << std::endl;



}

void regOrLog() { // проверка дали потребителя иска да се регистрира или да се лог ин- не

	std::cout << "Choose whether to register(r) or login to the game(l)";
	std::cout << std::endl;
	char ch; std::cin >> ch;


	if (ch == 'r') {
		myRegister();
	}
	else if (ch == 'l') myLog();
	else {
		std::cout << "Wrong input! Try again!" << std::endl;
		regOrLog();
	}
}



void myRegister() { // регистрация
	std::cout << "Innsert first name: "; std::cin >> firstname;
	std::cout << "Insert second name:"; std::cin >> lastname; std::cout << std::endl;
	//personName = name;


	name = firstname + lastname;

	if (name.length() > 50) {   // проверка дали името е над 50 символа
		std::cout << "Name too long. Try a shorter one" << std::endl;
		myRegister(); // връщане да въведе наново
	}

	//isReg();

	if (name.length() <= 50) { // проверка дали името е коректно

		std::ofstream list("Register.txt", std::ios::app); // за записване в края на файла без триене на предишното съдържание

		if (!list.is_open()) {
			std::cout << "Error";
			return;
		}
		if (isReg(name)) { // ако е регистриран да избере наново
			std::cout << "You are already registered, try logging in or creating a new account." << std::endl;
			regOrLog();

		}
		else {

			list << "\n" << name; // добавя в листа новото име

			name += ".txt";
			std::ofstream ofs(name);

			if (!ofs.is_open()) {
				std::cout << "Error!";
				return;
			}
			//ofs << "in";
			ofs.close();
			
		}
		list.close();

		Registered();

	}
	
	
}
void Registered() { // регистриран
	std::cout << "Registration successful. Do you want to continue? Yes(y) or No(n)";
	char ch;
	std::cin >> ch;
	if (ch == 'y') { //дали иска да продължи
		std::cout << std::endl;
		std::cout << "Welcome!";
		
		logged = true;
		std::cout << std::endl;
		return;
		//myLog();
	}
	else if (ch == 'n') { // дали не иска
		std::cout << "Thanks for registering. Play when you want!" << std::endl;
		return;
	}
	else { // грешен вход
		std::cout << "Wrong input! Try again!";
		Registered();
	}
}

bool isReg(std::string name) { // проверка дали човека е регистриран
	std::ifstream ifs("Register.txt");
	if (!ifs.is_open()) {
		std::cout << "The file can't be opened";
		std::cout << std::endl;

	}
	//std::string q = "NikolaNeychev";
	std::string line;
	while (std::getline(ifs, line)) {	
		if (name == line) return true;
	}
	return false;
	ifs.close();
}

void myLog() { // Форма за лог ин - ване
	std::cout << "Insert first name: "; std::cin >> firstname;
	std::cout << "Insert second name:"; std::cin >> lastname; std::cout << std::endl;
	//personName = name;

	
	name = firstname + lastname;
	
	if (isReg(name)) { // проверка дали човека е регистриран
		logged = true;
	}
	else {
		std::cout << "Your account could not be found, please try again" << std::endl;
		regOrLog(); //ако не е го връща обратно в началната форма
	}
	
}
