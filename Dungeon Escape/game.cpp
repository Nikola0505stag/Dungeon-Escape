#include "game.h"
#include <iostream>
#include "map.h"
#include <cstdlib>
#include <windows.h>

int lives, coins, level;
bool key;
int i = 0;
bool play = true;


int kurx, kury;
int newx, newy;

void welcome() {
	
	lives = 3, coins = 0, level = 1;
	key = false;
	
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
	system("cls");
	if (i != 0) {
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
	if (!play) goto endGame;

	printMatrix();

	move:

	player();
	
	move();
	printMatrix();
	endGame:
	if (play)
		goto move;
	else {
		system("cls");
		std::cout << "Thank you for playin";
		std::cout << std::endl << std::endl;
	}
}

void player() {
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			if (matrix[i][j] == '@') {
				kurx = j;
				kury = i;
			}
		}
	}
	std::cout << kurx << kury;
}

void move() {
	std::cout << "Choose a direction" << std::endl;
	std::cout << "Up(w), down(s),left(a),right(d) or if you want to exit the game(e)";

	char ch; std::cin >> ch;

	newx = kurx;
	newy = kury;

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
		std::cout << "exit";
		// exit metod
		Sleep(2000);
		//return;
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
	std::cout << matrix[kury][kurx]; std::cout << std::endl;
	swapC = matrix[y][x];
	matrix[y][x] = matrix[kury][kurx];
	matrix[kury][kurx] = swapC;
	kurx = x; kury = y;
}



void checking() {
	if (matrix[newy][newx] == 'C') {
		matrix[newy][newx] = ' ';
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
		matrix[newy][newx] = ' ';
		swap(newx, newy);
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
		insertMatrix();
		lives = 3;
		start();
	}
	else if (ch == 'n') {
		play = false;
		start();
	}
	else {
		std::cout << "Wrong input!";
		goto again;
	}

}

void win() {

	std::string levelName;
	int option = 1;
	level++;
	levelName = std::to_string(level) + std::to_string(option) + ".txt";

	insertnewMap(levelName);


	std::cout << "Well done, you passed the level! Do you want to move on?";
	std::cout << "Yes(y) or No(n)";
	char ch;
	again:
	std::cin >> ch;
	if (ch == 'y') {
		play = true;
		insertMatrix();
		start();
	}
	else if (ch == 'n') {
		play = false;
		start();
	}
	else {
		goto again;
	}
}