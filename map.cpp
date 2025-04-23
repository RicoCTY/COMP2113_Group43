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

    // Place coins
    //state.coin.clear();
    for (int i = 0; i < MAX_COINS; i++) {
        int ex, ey;
        do {
            ex = rand() % (MAP_WIDTH - 2) + 1;
            ey = rand() % (MAP_HEIGHT - 2) + 1;
        } while (state.map[ey][ex] != EMPTY);
        state.coin.push_back({ex, ey});
        state.map[ey][ex] = COIN;
    }

    // Place zombies
    for (int i = 0; i < MAX_ZOMBIES; ++i) {
        int ax, ay;
        do {
            ax = rand() % (MAP_WIDTH - 2) + 1;
            ay = rand() % (MAP_HEIGHT - 2) + 1;
        } while (state.map[ay][ax] != EMPTY); 
        Zombie z;
        z.isAlive = true;
        state.zombies.push_back({ax, ay});
        state.map[ay][ax] = ZOMBIE; 
    }

    // Place rocks
    for (int i = 0; i < MAX_STONES; ++i) {
        int bx, by;
        do {
            bx = rand() % (MAP_WIDTH - 2) + 1;
            by = rand() % (MAP_HEIGHT - 2) + 1;
        } while (state.map[by][bx] != EMPTY);
        Stone s;
        s.isPlaced = true;
        state.stones.push_back({bx, by});
        state.map[by][bx] = STONE; 
    }
    // Spawn Citizens
    for (int i = 0; i < MAX_CITIZENS; ++i) {
        int cx, cy;
        do {
            cx = rand() % (MAP_WIDTH - 2) + 1;
            cy = rand() % (MAP_HEIGHT - 2) + 1;
        } while (state.map[cy][cx] != EMPTY);
        Citizen c;
        c.isAlive = true;
        state.citizens.push_back({cx, cy});
        state.map[cy][cx] = CITIZEN; 
    }
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
    cout << " | Money: $" << player.money;
    
    cout << "\n\nControls: WASD to move, Q to quit" << endl;
    }
