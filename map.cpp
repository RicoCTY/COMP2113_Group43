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
    // Ensure center is empty
    state.map[player.y][player.x] = EMPTY;
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

    const int WALL_LENGTH = 14;
    const int NUM_WALLS = 5;
    
    for (int i = 0; i < NUM_WALLS; i++) {
        bool placed = false;
        int attempts = 0;
        const int MAX_ATTEMPTS = 50;
        
        while (!placed && attempts < MAX_ATTEMPTS) {
            attempts++;
            
            // Randomly choose horizontal or vertical
            bool horizontal = (rand() % 2) == 0;
            
            // Get random starting position
            int startX = rand() % (MAP_WIDTH - WALL_LENGTH - 2) + 1;
            int startY = rand() % (MAP_HEIGHT - WALL_LENGTH - 2) + 1;
            
            // Check if we can place the wall here
            if (canPlaceWall(state, startX, startY, WALL_LENGTH, horizontal)) {
                // Place the wall
                if (horizontal) {
                    for (int x = startX; x < startX + WALL_LENGTH; x++) {
                        state.map[startY][x] = WALL;
                    }
                } else { // vertical
                    for (int y = startY; y < startY + WALL_LENGTH; y++) {
                        state.map[y][startX] = WALL;
                    }
                }
                placed = true;
            }
        }
    }
}

bool canPlaceWall(const GameState& state, int x, int y, int length, bool horizontal) {
    if (horizontal) {
        if (x + length >= MAP_WIDTH - 1) return false;
        for (int i = 0; i < length; i++) {
            if (state.map[y][x + i] != EMPTY) return false;
        }
    } else { // vertical
        if (y + length >= MAP_HEIGHT - 1) return false;
        for (int i = 0; i < length; i++) {
            if (state.map[y + i][x] != EMPTY) return false;
        }
    }
    return true;
}

void drawGame(const GameState& state, const Player& player) {
    clearScreen();
    
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            if (x == player.x && y == player.y) {
                cout << COLOR_GREEN << COLOR_BOLD;
                // Default: Just show '@' if no facing direction
                if (player.facing == DIR_RIGHT || player.facing == DIR_LEFT || 
                    player.facing == DIR_UP || player.facing == DIR_DOWN) {
                    // Show directional symbol only if player has moved
                    switch (player.facing) {
                        case DIR_UP: cout << "/@\\ "; x += 1; break;
                        case DIR_DOWN: cout << "\\@/ "; x += 1; break;
                        case DIR_LEFT: cout << "<@"; x += 0; break;
                        case DIR_RIGHT: cout << "@>"; x += 0; break;
                        case DIR_NONE: cout << "@  "; break;
                    }
                }
                else {
                    cout << "@ "; // Default player symbol
                }
                cout << COLOR_RESET;
                continue; // Skip adding space after player
            }
            
            char c = state.map[y][x];
            switch(c) {
                case WALL: cout << COLOR_WHITE << c << COLOR_RESET; break;
                case COIN: cout << COLOR_YELLOW << c << COLOR_RESET; break;
                case ZOMBIE: cout << COLOR_RED << c << COLOR_RESET; break;
                case HEALTH_ITEM: cout << COLOR_BLUE << c << COLOR_RESET; break;
                case ARMOR_ITEM: cout << COLOR_MAGENTA << c << COLOR_RESET; break;
                case RANGE_ITEM: cout << COLOR_CYAN << c << COLOR_RESET; break;
                default: cout << c; break;
            }
            if (x < MAP_WIDTH - 1) cout << " ";
        }
        cout << endl;
    }

    cout << COLOR_BOLD << COLOR_YELLOW << "\nMode: " << COLOR_RESET;
    switch(player.difficulty) {
        case EASY:
            cout << COLOR_GREEN << "Easy" << COLOR_RESET;
            break;
        case NORMAL:
            cout << COLOR_YELLOW << "Normal" << COLOR_RESET;
            break;
        case HARD:
            cout << COLOR_RED << "Hard" << COLOR_RESET;
            break;
    }
    cout << "\n";
    
    cout << COLOR_CYAN << "\n╔══════════════════════════════════════════════════╗\n";
    cout << "║ " << COLOR_BOLD << "STATUS" << COLOR_RESET << COLOR_CYAN << "                                           ║\n";
    cout << "╠══════════════════════════════════════════════════╣\n";
    
    // Health bar
    cout << "║ " << COLOR_RED << "Health: " << COLOR_RESET;
    int healthBars = (player.health * 20) / player.maxHealth;
    for (int i = 0; i < 20; i++) {
        cout << (i < healthBars ? "█" : " ");
    }
    if (player.maxHealth == 100 && player.health == 100) {
        cout << " " << player.health << "/" << player.maxHealth << COLOR_CYAN << "             ║\n";
    } 
    else if (player.maxHealth == 100 && player.health < 100) {
        cout << " " << player.health << "/" << player.maxHealth << COLOR_CYAN << "              ║\n";
    } 
    else {
        cout << " " << player.health << "/" << player.maxHealth << COLOR_CYAN << "               ║\n";
    }

    // Armor bar
    if (player.maxArmor >= 0) {
        cout << "║ " << COLOR_MAGENTA << "Armor:  " << COLOR_RESET;
        int armorBars = (player.armor * 20) / player.maxArmor;
        for (int i = 0; i < 20; i++) {
            cout << (i < armorBars ? "█" : " ");
        }
        if (player.maxArmor >= 10 && player.armor >= 10) {
            cout << " " << player.armor << "/" << player.maxArmor << COLOR_CYAN << "               ║\n";
        } 
        else if (player.maxArmor >= 10 && player.armor == 0) {
            cout << " " << player.armor << "/" << player.maxArmor << COLOR_CYAN << "                ║\n";
        }
    }
    
    cout << "║ " << COLOR_YELLOW << "Money: $" << player.money << COLOR_RESET;
    cout << string(36 - to_string(player.money).length(), ' ') << COLOR_CYAN << "     ║\n";
    
    cout << "║ " << COLOR_GREEN << "Wave: " << state.currentWave << "/" << MAX_WAVES;
    cout << "  Zombies: " << state.zombiesRemaining;
    cout << string(18 - to_string(state.currentWave).length() - to_string(MAX_WAVES).length() - to_string(state.zombiesRemaining).length(), ' ');
    cout << COLOR_CYAN << "             ║\n";
    
    cout << "║ " << COLOR_BLUE << "Range: " << player.attackRange;
    cout << string(37 - to_string(player.attackRange).length(), ' ') << COLOR_CYAN << "     ║\n";
    
    cout << "╚══════════════════════════════════════════════════╝\n" << COLOR_RESET;

    cout << "\n" << COLOR_YELLOW << "Controls: " << COLOR_RESET;
    cout << COLOR_GREEN << "WASD" << COLOR_RESET << " to move, ";
    cout << COLOR_GREEN << "E" << COLOR_RESET << " to shoot, ";
    cout << COLOR_GREEN << "Q" << COLOR_RESET << " to quit\n";
    
    cout << COLOR_YELLOW << "Item: " << COLOR_RESET;
    cout << COLOR_BLUE << "H" << COLOR_RESET << "(Health $10) ";
    cout << COLOR_MAGENTA << "A" << COLOR_RESET << "(Armor $15) ";
    cout << COLOR_CYAN << "R" << COLOR_RESET << "(Range $20)\n";


}