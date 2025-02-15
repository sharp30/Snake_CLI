// Snake2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Game.h"
#include <Windows.h>

const char PLAY = 'y';
int main()
{
    Game x(20);
    // system("mode 650");4
    SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, 0);
    std::cin.ignore();
    char choice = PLAY;
    while (choice == PLAY)
    {
        int score = x.playGame();
        system("cls");
        std::cout << "SCORE:    " << score << std::endl;
        cout << "Would you like to play again? ( enter y for yes)" << std::endl;
        std::cin>> choice;
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menus

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
