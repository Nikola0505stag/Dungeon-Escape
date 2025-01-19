#include <iostream>
#include "login.h"
#include <cstdlib>
#include "map.h"
#include "game.h"

int main() {
    welcomeText();
    
    regOrLog();
    system("cls");

   // std::cout << logged;
     
    if (logged) {
        
        std::cout << "Logged" << std::endl<<std::endl;

        insertMap("11.txt");
        insertMatrix();
        welcome();
    }
    else std::cout << "Error";
    
    //system("cls");

    return 0;
}
