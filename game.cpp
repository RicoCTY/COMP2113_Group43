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
    clearScreen();
    cout << "Select difficulty:\n";
    cout << "1. Easy (100HP, 50 armor, range 3)\n"; 
    cout << "2. Normal (80HP, 30 armor, range 2)\n";
    cout << "3. Hard (60HP, 0 armor, range 1)\n";
    cout << "====================\n";
    cout << "Enter choice (1-3): ";
    
    while(true) {
        char input = getch();
        if(input >= '1' && input <= '3') {
            return static_cast<Difficulty>(input - '1');
        }
    }
}

void gameLoop() {
    srand(time(nullptr));
    
    Difficulty difficulty = selectDifficulty();
    Player player = initializePlayer(difficulty);
    player.facing = DIR_RIGHT; // Default facing direction
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
                case 'r': // Melee attack
                    meleeAttack(state, player);
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