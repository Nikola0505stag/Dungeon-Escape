﻿#include "game.h"
#include <iostream>
#include "map.h"
#include <cstdlib>
#include <windows.h>
#include "login.h";
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>


int lives, coins, level, option;
bool key;
int i = 0;

const int MAX_LEVEL = 7;


int curx, cury;
int newx, newy;

bool wasPortal = false;

void welcome() {
	
	std::string fullname = firstname + lastname;

	givingInitialData();
	
	if (reg) {
		insertMatrix();
	}
	else if (logged) {
		chooseStartingMap();
	}


	std::cout << "Hello, this is the map you will be playing on.";
	std::cout << std::endl << std::endl;



	printMatrix(); i++;

	std::cout << std::endl << std::endl;

	std::cout << " " " - empty field" << std::endl;
	std::cout << "@ - field occupied by the user" << std::endl;
	std::cout << "C - coin" << std::endl;
	std::cout << "% - portal" << std::endl;
	std::cout << "& - key" << std::endl;
	std::cout << "X - chest" << std::endl;

	std::cout << std::endl << std::endl;
	
	std::cout << "You have three lives.";
	
	std::cout << std::endl << std::endl;
	
	go:
	
	std::cout << "Are you ready for the game to begin? Yes(y) or No(n)";

	char ch; std::cin >> ch;
	if (ch == 'y') {
	yes:

		system("cls");

		start();
	}
	else if (ch == 'n') {
		std::cout << "Your problem.The option here was an illusion. You chose yes!";
		Sleep(2000);
		goto yes;
	}
	else {
		std::cout << "Wrong input!";
		goto go;
	}
	

	
}

void printMatrix() {
	
	if (i != 0) {
		system("cls");
		std::cout << "Level: " << level;
		std::cout << std::endl << "Lives: " << lives;
		std::cout << std::endl << "Coins: " << coins;
		std::cout << std::endl << "Key: ";
		if (key) std::cout << "Found!";
		else std::cout << "Not found!"; std::cout << std::endl;
	}
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			std::cout << matrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

void start() {


	printMatrix();

	move:

	player();
	
	move();
	printMatrix();
	endGame:
		goto move;
}
void chooseStartingMap() {
	std::cout << "You would like to start from the last saved level or from a new level?";
againn:

	std::cout << std::endl << "Last saved level(l),new level(n)";
	char answer;
	std::cin >> answer;
	if (answer == 'l') {
		insertMatrix();
		lives = 3;
		coins = 0;
		key = false;

	}
	else if (answer == 'n') {
	go:
		lives = 3;
		coins = 0;
		std::cout << "What level would you like to start at?";
		int levelToStart;
		std::cin >> levelToStart;
		if (levelToStart <= level) {

			std::string levelName;

			option = std::rand() % 3 + 1;
		
			levelName = std::to_string(levelToStart) + std::to_string(option) + ".txt";

			key = false;

			insertnewMap(levelName);
			insertMatrix();
			level = levelToStart;

		}
		else {
			std::cout << "You cannot start from a level you have not passed try again!";
			goto go;
		}

	}
	else goto againn;
}
void player() {
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			if (matrix[i][j] == '@') {
				curx = j;
				cury = i;
			}
		//	else setColor(11);
		}
	}
	std::cout << curx << cury;
}

void move() {
	std::cout << "Choose a direction" << std::endl;
	std::cout << "Up(w), down(s),left(a),right(d) or if you want to exit the game(e)";

	char ch; std::cin >> ch;

	newx = curx;
	newy = cury;

	if (ch == 'w' || ch == 'W') {
		newy -= 1;
	}
	else if (ch == 's' || ch == 'S') {
		newy += 1;
	}
	else if (ch == 'a' || ch == 'A') {
		newx -= 1;
	}
	else if (ch == 'd' || ch == 'D') {
		newx += 1;
	}
	else if (ch == 'e' || ch == 'E') {

		Sleep(1000);

		std::cout << "Want to save how far you've come? Yes(y) or No(n).";

		again:

		char ans; std::cin >> ans;
		
		if (ans == 'y') {
			system("cls");

			addProgress();
			saveCurrentMap();
			
			Sleep(2000);
			system("cls");
			std::cout << "Thank you for playing!";
			Sleep(1000);
			leaderBoard();
			system("pause");
			exit(0); // Изход от програмата
		
		}
		else if (ans == 'n') {
			system("cls");
			std::cout << "Thank you for playing!";
			Sleep(1000);
			leaderBoard();
			system("pause");
			exit(0); // Изход от програмата
		}
		else {
			std::cout << "Wrong input";
			goto again;
		}




	}
	else {
		std::cout << "Wrong input!Try again!";
		move();
	}
	checking();
	
}

void swap(int x, int y) {
	char swapC;
	std::cout << x << y;
	std::cout << matrix[y][x];
	std::cout << matrix[cury][curx]; std::cout << std::endl;
	swapC = matrix[y][x];
	matrix[y][x] = matrix[cury][curx];
	matrix[cury][curx] = swapC;
	curx = x; cury = y;
}

void findPortal() {
	bool found = false;
	int q = 0;
	//Sleep(2000);

	for (int i = cury; i < ROWS; i++) {
		for (int j = curx ; j < COLS; j++) {
			if (matrix[i][j] == '%') {
				//std::cout << i << " " << j;
				found = true;
				char swap = matrix[cury][curx];
				matrix[i][j] = matrix[cury][curx];
				matrix[cury][curx] = '%';
				wasPortal = true;
				break;
			}
		}
		q++;
	}
	if (!found) {
		for (int i = 0; i < ROWS; i++) {
			for (int j = 0; j < COLS; j++) {
				if (matrix[i][j] == '%') {
					//found = true;
					char swap = matrix[cury][curx];
					matrix[i][j] = matrix[cury][curx];
					matrix[cury][curx] = '%';
					wasPortal = true;
					break;
				}
			}
		}
	}
}

void checking() {
	if (matrix[newy][newx] == 'C') {
		if (wasPortal) {
			matrix[newy][newx] = '%';
			wasPortal = false;
		}
		else matrix[newy][newx] = ' ';
		coins++;
		swap(newx, newy);
	}
	else if (matrix[newy][newx] == '#') {
		lives--;
		if (lives == 0) {
			gameOver();
		}
	}
	else if (matrix[newy][newx] == '&') {
		key = true;
		if (wasPortal) {
			matrix[newy][newx] = '%';
			wasPortal = false;
		}
		else matrix[newy][newx] = ' ';
		swap(newx, newy);
	}
	else if (matrix[newy][newx] == '%') {
		
		if (wasPortal) {
			matrix[newy][newx] = '%';
			wasPortal = false;
		}
		else matrix[newy][newx] = ' ';

		swap(newx, newy);
		findPortal();
		
	}
	else if (matrix[newy][newx] == 'X') {
		if (key == true) {
			matrix[newy][newx] = ' ';
			swap(newx, newy);
			Sleep(1000);
			win();
		}
		else {
			std::cout << "You did not find the key, try to find it!";
			Sleep(1000);
			printMatrix();
			move();
		}
	}
	else if (matrix[newy][newx] = ' ') {
		if (wasPortal) {
			matrix[newy][newx] = '%';
			wasPortal = false;
		}
		else matrix[newy][newx] = ' ';
		swap(newx, newy);
	}
}
void gameOver() {
	system("cls");
	std::cout << "Your lives are over, you lose!" << std::endl << "Do you want to try again ?"<<std::endl<<"Yes(y) or No(n)!";
	
	char ch;
	again:
	std::cin >> ch;
	if (ch == 'y') {
		lives = 3;
		coins = 0;
		key = false;

		insertMatrix();

		start();
	}
	else if (ch == 'n') {
		system("cls");
		std::cout << "Thank you for playing!";
		Sleep(1000);
		
		leaderBoard();
		system("pause");
		
		exit(0); // Изход от програмата	
	}
	else {
		std::cout << "Wrong input!";
		goto again;
	}


}

void win() {
	std::srand(std::time(nullptr));
	if (level == MAX_LEVEL) {
		system("cls");

		std::cout << "Good job, you passed all the levels!";

		std::cout << std::endl;

		std::cout << "Thank you for playing";

		Sleep(2000);

		leaderBoard();
		system("pause");

		exit(0); // Изход от програмата	
	}
	else {

		std::string levelName;

		option = std::rand() % 3 + 1;
			
		std::cout << option;
	//		Sleep(2000);
		level++;
		levelName = std::to_string(level) + std::to_string(option) + ".txt";
		key = false;

		insertnewMap(levelName);
		addProgress();

		std::cout << "Well done, you passed the level! Do you want to move on?";
		std::cout << "Yes(y) or No(n)";
		char ch;
	again:
		std::cin >> ch;
		if (ch == 'y') {
			insertMatrix();
			start();
		}
		else if (ch == 'n') {

			system("cls");
			std::cout << "Thank you for playing!";
			Sleep(1000);

			leaderBoard();
			system("pause");
			exit(0); // Изход от програмата

		}
		else {
			goto again;
		}
	}
}

void addProgress() {
	//std::cout << firstname << lastname;
	std::string fullname = firstname + lastname;
	std::string strLives, strCoins, strLevel, strKey;
	strLives = std::to_string(lives);
	strCoins = std::to_string(coins);
	strLevel = std::to_string(level);
	if (key) {
		strKey = "true";
	}
	else strKey = "false";


	if (nameExistsInFile()) {
		std::ifstream file("Progress.txt");
		if (!file) {
			std::cout << "Error!";
		}
		else {
			std::vector<std::string> lines;
			std::string line;

			//Прочитаме всички редове и провевяраме дали реда съдържа търсеното име

			while (std::getline(file, line)) {
				std::stringstream ss(line);
				std::string name;

				ss >> name;

				if (name == fullname) {
					line = fullname + " " + strLevel + " " + strLives + " " + strCoins + " " + strKey;
				}
				lines.push_back(line);
			}
			file.close();

			std::ofstream outFile("Progress.txt", std::ofstream::trunc);  // Отваряме с "trunc", за да изтрием старото съдържание
			if (!outFile) {
				std::cerr << "Не може да се отвори файлът за запис!" << std::endl;
			}
			else {

				for (const auto& updatedLine : lines) {
					outFile << updatedLine << std::endl;
				}
			}
			outFile.close();
			
		}
	}
	else {
		std::ofstream progress("Progress.txt", std::ios::app); // за записване в края на файла без триене на предишното съдържание
		if (!progress.is_open()) {
			std::cout << "Error";
			return;
		}

		//std::cout << lives << coins << level;

		progress << "\n" << fullname << " " << strLevel << " " << strLives << " " << strCoins << " " << strKey; // добавя в листа новото име
		progress.close();
	}
}

bool nameExistsInFile() {
	std::ifstream file("Progress.txt");

	if (!file) {
		std::cout << "Не може да се отвори файлът!" << std::endl;
		return false;
	}
	std::string fullname = firstname + lastname;
	std::string line;
	while (std::getline(file, line)) {
		std::stringstream name(line);
		std::string currentName;
		name >> currentName;  // Чете първото име от реда



		if (currentName == fullname) {
			return true;  // Намерено е съвпадение на името
		}
	}

	return false;  // Няма съвпадение
}

void givingInitialData() {
	std::string fullname = firstname + lastname;
	std::string targetName = fullname;  // Търсеното име
	//std::cout << targetName;
	std::ifstream file("Progress.txt");   // Отваряме файла

	if (!file) {
		std::cout << "Не може да се отвори файлът!" << std::endl;
	}

	std::string line;
	bool found = false;

	while (std::getline(file, line)) {
		std::stringstream ss(line);
		std::string name;
		std::string strLives, strCoins, strLevel,strKey;

		// Четем името на човека
		ss >> name;

		// Проверяваме дали името съвпада с търсеното
		if (name == targetName) {
			// Ако името съвпада, взимаме останалите данни
			ss >> strLevel >> strLives >> strCoins >> strKey;

			lives = stoi(strLives);
			coins = stoi(strCoins);
			level = stoi(strLevel);
			if (strKey == "true") key = 1;
			else key = 0;
			
			found = true;
			break;
		}
	}

	if (!found) {
		lives = 3, coins = 0, level = 1, key = false;
	}
}



void leaderBoard() {
	struct Player {
		std::string nameP;
		int levelP;
		int livesP;
		int coinsP;
		std::string keyP;
	};

	std::vector<Player> players;

	std::ifstream ifs("Progress.txt");

	if (!ifs) {
		std::cout << "Error!";
		return;
	}
	Player p;
	while (ifs >> p.nameP >> p.levelP >> p.livesP >> p.coinsP >> p.keyP) {
		players.push_back(p);
	}
	
	int n = players.size();
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - i - 1; j++) {
			if (players[j].levelP < players[j + 1].levelP  
				|| (players[j].levelP == players[j + 1].levelP && players[j].coinsP < players[j + 1].coinsP) ||
				(players[j].levelP == players[j + 1].levelP && players[j].livesP < players[j + 1].livesP && players[j].coinsP == players[j + 1].coinsP)
				
				) {
				Player temp = players[j];
				players[j] = players[j + 1];
				players[j + 1] = temp;
			}
		}
	}
	


	system("cls");

	std::cout << "LEADER BOARD";
	std::cout << std::endl << std::endl;

	for (const auto& player : players) {
		std::cout << "Name: " << player.nameP
			<< ", Level: " << player.levelP
			<< ", HP: " << player.livesP
			<< ", Coins: " << player.coinsP
			<< ", Key: " << player.keyP << std::endl;
	}

	ifs.close();

	std::cout << std::endl;

}