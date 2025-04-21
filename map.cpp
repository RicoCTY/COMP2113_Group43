// map.cpp
// Map generation and rendering
#include "map.h"
#include <iostream>
#include <algorithm>

using namespace std;

void initializeGameState(GameState& state, Player& player) {
    state.gameOver = false;

    // Clear map
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            if (x == 0 || x == MAP_WIDTH - 1 || y == 0 || y == MAP_HEIGHT - 1) {
                state.map[y][x] = WALL;
            } else {
                state.map[y][x] = EMPTY;
            }
        }
    }

    // Place player
    player.x = MAP_WIDTH / 2;
    player.y = MAP_HEIGHT / 2;
    state.map[player.y][player.x] = PLAYER;
}

void drawGame(const GameState& state, const Player& player) {
    clearScreen();
    
    // Draw map
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            cout << state.map[y][x] << " ";
        }
        cout << endl;
    }
    
    // Draw stats
    cout << " | Health: " << "dummy";
    cout << " | Bullet: " << "dummy";
    
    cout << "\n\nControls: WASD to move, Q to quit" << endl;
}