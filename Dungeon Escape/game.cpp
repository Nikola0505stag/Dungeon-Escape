#include "game.h"
#include <iostream>
#include "map.h"
#include <cstdlib>
#include <windows.h>

int lives, coins, level;
bool key;

int kurx, kury;


void welcome() {
	
	lives = 3, coins = 0, level = 1;
	key = false;
	
	std::cout << "Hello, this is the map you will be playing on.";
	std::cout << std::endl << std::endl;

	printMatrix();

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
		goto go;
	}
	
}

void printMatrix() {
	system("cls");

	std::cout << "Level: " << level;
	std::cout << std::endl << "Lives: " << lives;
	std::cout << std::endl << "Coins: " << coins;
	std::cout << std::endl << "Key: ";
	if (key) std::cout << "Found!";
	else std::cout << "Not found!"; std::cout << std::endl;

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
	goto move;
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
	std::cout << "Choose a direction" <<  std::endl;
	std::cout << "Up(w), down(s),left(a),right(d)";

	char ch; std::cin >> ch;
	int newx, newy;
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
	else {
		std::cout << "Wrong input!Try again!";
		move();
	}
	swap(newx, newy);


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
