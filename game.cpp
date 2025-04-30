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

using namespace std;

void gameLoop() {
    srand(time(nullptr));
    
    Player player = initializePlayer();
    GameState state;
    initializeGameState(state, player);
    
    while (!state.gameOver) {
        drawGame(state, player);
        
        char input;
        if (kbhit()) {
            input = getch();
            input = tolower(input);
            
            switch (input) {
                case 'w': case 'a': case 's': case 'd':
                    movePlayer(state, player, input);
                    // Zombies move after player moves
                    moveZombies(state, player);
                    break;
                case 'q':
                    state.gameOver = true;
                    break;
            }
        } else {
            usleep(100000);
        }
    }
}