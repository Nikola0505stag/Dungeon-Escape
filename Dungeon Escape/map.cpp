#include "map.h"
#include <iostream>
#include "login.h"
#include <fstream>
#include<string>

const int ROWS = 10;
const int COLS = 15;

char matrix[ROWS][COLS];


bool isFileEmpty(const std::string& filename) {
	std::ifstream file(filename, std::ios::binary | std::ios::ate); // Отваряме файла в бинарен режим и на края
	return file.tellg() == 0; // Ако позицията в края на файла е 0, значи файлът е празен
}


void insertMap(std::string map) {
	std::string name = firstname + lastname;
	name += ".txt";
	if (isFileEmpty(name)) {
		std::ofstream ofs(name);
		std::ifstream level1(map);

		char ch;
		while (level1.get(ch)) {
			ofs << ch;
		}
		ofs.close();
		level1.close();
	}
}
void insertnewMap(std::string map) {
	std::string name = firstname + lastname;
	name += ".txt";
		std::ofstream ofs(name);
		std::ifstream level1(map);

		char ch;
		while (level1.get(ch)) {
			ofs << ch;
		}
		ofs.close();
		level1.close();
}
void insertMatrix() {
	name = firstname + lastname;
	name += ".txt";

	std::ifstream ifs(name);

	for (int i = 0; i < ROWS; ++i) {
		for (int j = 0; j < COLS; ++j) {
			ifs >> matrix[i][j];  // Четем стойностите в матрицата
		}
	}
	ifs.close();
}

void saveCurrentMap() {

	std::string filename = firstname + lastname + ".txt";

	std::ofstream file(filename);

	if (!file) {
		std::cout << "Не може да се отвори файла за запис!" << std::endl;
	}
	else {
		for (int i = 0; i < ROWS; ++i) {
			for (int j = 0; j < COLS; ++j) { 
				file << matrix[i][j] << " ";  // Записваме всеки елемент с интервал
			}
			file << std::endl;  // Записваме нов ред след всеки ред на матрицата
		}
	}
	file.close();
}
