// game.h
// Game constants and forward declarations
#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>
#include <utility>

// Game constants
const int MAP_WIDTH = 67;
const int MAP_HEIGHT = 23;
const int MAX_COINS = 5;

// Game symbols
const char PLAYER = '@';
const char WALL = '#';
const char EMPTY = '.';
const char COIN = '$';

// Player structure
struct Player {
    int x, y;
    int money;
};

// Game state
struct GameState {
    char map[MAP_HEIGHT][MAP_WIDTH];
    std::vector<std::pair<int, int>> coin;
    bool gameOver;
};

// Function declarations
void initializeGameState(GameState& state, Player& player);
void gameLoop();

#endif