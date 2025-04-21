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

// Game symbols
const char PLAYER = '@';
const char WALL = '#';
const char EMPTY = '.';

// Player structure
struct Player {
    int x, y;
};

// Game state
struct GameState {
    char map[MAP_HEIGHT][MAP_WIDTH];
    bool gameOver;
};

// Function declarations
void initializeGameState(GameState& state, Player& player);
void gameLoop();

#endif