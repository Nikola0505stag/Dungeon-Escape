#include<string>

extern char matrix[10][15];
extern const int ROWS;
extern const int COLS;

void colorPlayer();

bool isFileEmpty(const std::string& filename);

void insertMap(std::string map);
void insertnewMap(std::string map);

void insertMatrix();
void saveCurrentMap();

