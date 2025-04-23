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
const int MAX_CITIZENS = 4;
const int MAX_ZOMBIES = 10;
const int MAX_STONES = 10;

// Game symbols
const char PLAYER = '@';
const char WALL = '#';
const char EMPTY = '.';
const char COIN = '$';
const char CITIZEN = 'C';
const char ZOMBIE = 'Z';
const char STONE = 'S';

// Player structure
struct Player {
    int x, y;
    int money;
    int health;
};

struct Zombie {
    int x, y; 
    bool isAlive; 
};

struct Citizen {
    int x, y;
    bool isAlive; 
};

struct Stone {
    int x, y;
    bool isPlaced;
};


// Game state
struct GameState {
    char map[MAP_HEIGHT][MAP_WIDTH];
    std::vector<std::pair<int, int>> coin;
    std::vector<Zombie> zombies;     
    std::vector<Citizen> citizens;
    std::vector<Stone> stones; 
    Player player;
    bool gameOver;
};

// Function declarations
void initializeGameState(GameState& state, Player& player);
void gameLoop();

#endif