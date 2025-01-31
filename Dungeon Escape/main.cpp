#include <iostream>
#include "login.h"
#include <cstdlib>
#include "map.h"
#include "game.h"
#include<string>

using namespace std;

int main() {
    std::srand(std::time(nullptr));
    welcomeText();
    

    regOrLog();
    system("cls");

   // std::cout << logged;
     
    if (logged) {
        
        std::cout << "Logged" << std::endl<<std::endl;
        std::string LevelName;

        option = std::rand() % 3 + 1;
       // std::cout << option;
        LevelName = "1" + to_string(option) + ".txt";
        insertMap(LevelName);
        insertMatrix();
        welcome();
    }
    else std::cout << "Error";
    
    //system("cls");

    return 0;
}
