// main.cpp
// Main game loop and entry point
#include "game.h"
#include "terminal.h"
#include <iostream>

using namespace std;

int main() {
    cout << "ZOMBIE RUSH\n";
    cout << "====================\n";
    cout << "HKU COMP2113 Group43\n\n";
    cout << "DESCRIPTION:\n";
    cout << PLAYER << " - You (the player)\n";
    cout << WALL << " - Wall (can't pass)\n";
    cout << COIN << " - Equipment (collect to upgrade)\n";
    cout << ZOMBIE << " - Zombie (kill them)\n";
    
    cout << "Press any key to start...";
    getch();
    
    gameLoop();
    
    return 0;
}