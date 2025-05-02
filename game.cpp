// game.cpp
// Core game functions
#include "game.h"
#include "player.h"
#include "map.h"
#include "terminal.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <algorithm>
#include <chrono>

using namespace std;

Difficulty selectDifficulty() {
    int selection = 1; // Default to Easy (option 1)
    char input;
    
    while (true) {
        clearScreen();   
        cout << COLOR_BOLD << "SELECT DIFFICULTY:\n" << COLOR_RESET;
        
        // Option 1
        if (selection == 1) cout << COLOR_GREEN << "> 1. Easy ";
        else cout << "  1. Easy ";
        cout << COLOR_RESET << "(100HP, 50 armor, range 4)\n";
        
        // Option 2
        if (selection == 2) cout << COLOR_YELLOW << "> 2. Normal ";
        else cout << "  2. Normal ";
        cout << COLOR_RESET << "(80HP, 30 armor, range 3)\n";
        
        // Option 3
        if (selection == 3) cout << COLOR_RED << "> 3. Hard ";
        else cout << "  3. Hard ";
        cout << COLOR_RESET << "(60HP, 0 armor, range 2)\n";
        
        cout << COLOR_CYAN << "\nUse 1-3 to select, ENTER to confirm\n";
        cout << "====================\n" << COLOR_RESET;
        
        input = getch();
        
        // Only process valid inputs
        switch(input) {
            case '1':
                selection = 1;
                break;
            case '2':
                selection = 2;
                break;
            case '3':
                selection = 3;
                break;
            case '\n':  // Enter key
            case '\r':
                return static_cast<Difficulty>(selection - 1);
            default:
                continue;
        }
    }
}

void gameLoop() {
    srand(time(nullptr));
    
    Difficulty difficulty = selectDifficulty();
    Player player = initializePlayer(difficulty);
    GameState state;
    initializeGameState(state, player);
    
    auto lastZombieMove = chrono::steady_clock::now();
    const chrono::milliseconds zombieMoveInterval(500);
    
    while (!state.gameOver) {
        drawGame(state, player);

        if (state.currentWave > MAX_WAVES) {
            cout << "\n\nCONGRATULATIONS! You survived all waves!\n";
            break;
        }
        
        if (kbhit()) {
            char input = getch();
            input = tolower(input);
            
            switch (input) {
                case 'w': case 'a': case 's': case 'd':
                    movePlayer(state, player, input);
                    break;
                case 'e': // Shoot bullet
                    shootBullet(state, player);
                    break;
                case 'q':
                    state.gameOver = true;
                    break;
            }
        }
        
        auto now = chrono::steady_clock::now();
        if (now - lastZombieMove >= zombieMoveInterval) {
            moveZombies(state, player);
            lastZombieMove = now;
        }
        
        usleep(10000);
        
        if (player.health <= 0) {
            state.gameOver = true;
        }
    }
    
    if (state.currentWave <= MAX_WAVES) {
        cout << "\n\nGAME OVER! You survived until wave " << state.currentWave << "\n";
    }
}