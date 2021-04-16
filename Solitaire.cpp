/*
Designer: Philip Ostroscki
Description: Simulates the card game Solitaire
Created: May 3 2020
Last Updated: May 15 2020
*/

//================================ HEADER ==================================

#include <iostream>
#define _WIN32_WINNT 0x0500
#include <windows.h>
#include <winuser.h>
#include "Game.h"

//===================== GLOBAL VARIABLES AND STRUCTURES ====================



//============================== PROTOTYPES ================================



//========================= FUNCTION DEFINITIONS ===========================



//================================ MAIN ====================================

int main()
{
    ShowWindow(GetConsoleWindow(), SW_SHOWMAXIMIZED);

    Game game;

    game.run();

    std::cout << "\n\n\n";
    system("pause");
    return 0;
}

















