// map.cpp
// Map generation and rendering
#include "map.h"
#include <iostream>
#include <algorithm>

using namespace std;

void initializeGameState(GameState& state, Player& player) {
    state.gameOver = false;
    state.currentWave = 1;
    state.zombiesRemaining = INITIAL_ZOMBIES + (state.currentWave - 1) * ZOMBIE_INCREMENT;

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

    // Place player in center
    player.x = MAP_WIDTH / 2;
    player.y = MAP_HEIGHT / 2;
    state.map[player.y][player.x] = PLAYER;

    // Place coins
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
    for (int i = 0; i < state.zombiesRemaining; i++) {
        int zx, zy;
        do {
            zx = rand() % (MAP_WIDTH - 2) + 1;
            zy = rand() % (MAP_HEIGHT - 2) + 1;
        } while (state.map[zy][zx] != EMPTY);
        state.zombie.push_back({zx, zy});
        state.map[zy][zx] = ZOMBIE;
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
    cout << " | Health: " << player.health << "/" << player.maxHealth;
    cout << " | Armor: " << player.armor << "/" << player.maxArmor;
    cout << " | Range: " << player.attackRange;
    cout << " | Money: $" << player.money;

    // Add wave information
    cout << " | Wave: " << state.currentWave << "/" << MAX_WAVES;
    cout << " | Zombies: " << state.zombiesRemaining;
    
    cout << "\n\nControls: WASD to move, Q to quit" << endl;
    cout << "\nStore items: H(Health $10) A(Armor $15) R(Range $20)";
}