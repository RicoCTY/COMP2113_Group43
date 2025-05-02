// main.cpp
#include "game.h"
#include "terminal.h"
#include <iostream>

using namespace std;

void showTitleScreen() {
    clearScreen();
    cout << COLOR_RED << COLOR_BOLD;
    cout << "_______                    _                 \n";
    cout << "(_____  )                  ( )     _         \n";
    cout << "     /'/'   _     ___ ___  | |_   (_)   __   \n";
    cout << "   /'/'   /'_`\\ /' _ ` _ `\\| '_`\\ | | /'__`\\ \n";
    cout << " /'/'___ ( (_) )| ( ) ( ) || |_) )| |(  ___/ \n";
    cout << "(_______)`\\___/'(_) (_) (_)(_,__/'(_)`\\____) \n\n\n"; 
                                          
    cout << " ___                 _                      \n";
    cout << "|  _`\\              ( )                     \n";
    cout << "| (_) ) _   _   ___ | |__                   \n";
    cout << "| ,  / ( ) ( )/',__)|  _ `\\                 \n";
    cout << "| |\\ \\ | (_) |\\__, \\| | | |                 \n";
    cout << "(_) (_)`\\___/'(____/(_) (_)                 \n";
    cout << COLOR_RESET << "\n";
    
    cout << COLOR_YELLOW << "==================== HKU COMP2113 Group43 ====================\n\n" << COLOR_RESET;
    
    cout << COLOR_CYAN << "DESCRIPTION:\n" << COLOR_RESET;
    cout << COLOR_GREEN << PLAYER << COLOR_RESET << " - You (the player)\n";
    cout << COLOR_WHITE << WALL << COLOR_RESET << " - Wall (can't pass)\n";
    cout << COLOR_YELLOW << COIN << COLOR_RESET << " - Equipment (collect to upgrade)\n";
    cout << COLOR_RED << ZOMBIE << COLOR_RESET << " - Zombie (kill them)\n";
    cout << COLOR_BLUE << HEALTH_ITEM << COLOR_RESET << " - Health upgrade ($10)\n";
    cout << COLOR_MAGENTA << ARMOR_ITEM << COLOR_RESET << " - Armor upgrade ($15)\n";
    cout << COLOR_CYAN << RANGE_ITEM << COLOR_RESET << " - Range upgrade ($20)\n\n";
    
    cout << COLOR_YELLOW << "Press any key to continue..." << COLOR_RESET;
    getch();
}

int main() {
    showTitleScreen();
    gameLoop();
    return 0;
}