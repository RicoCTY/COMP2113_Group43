// game.h
// Game constants and forward declarations
#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>
#include <utility>

using namespace std;

// Difficulty levels
enum Difficulty {
    EASY,
    NORMAL,
    HARD
};

// Game constants
const int MAP_WIDTH = 67;
const int MAP_HEIGHT = 23;
const int MAX_COINS = 5;

// Game symbols
const char PLAYER = '@';
const char WALL = '#';
const char EMPTY = ' ';
const char COIN = '$';
const char ZOMBIE = 'Z';
const char BLOCK = '=';

const char HEALTH_ITEM = 'H';
const char ARMOR_ITEM = 'A';
const char RANGE_ITEM = 'R';

const int MAX_WAVES = 10;
const int INITIAL_ZOMBIES = 1;
const int ZOMBIE_INCREMENT = 1;  // Each wave adds this many zombies

enum FacingDirection {
    DIR_NONE,
    DIR_UP,
    DIR_DOWN,
    DIR_LEFT,
    DIR_RIGHT
};

// Player structure
struct Player {
    int x, y;
    int money;
    int health;
    int armor;
    int maxHealth;
    int maxArmor;
    int attackRange;
    Difficulty difficulty;
    FacingDirection facing;
};

// Game state
struct GameState {
    char map[MAP_HEIGHT][MAP_WIDTH];
    vector<pair<int, int>> coin;
    vector<pair<int, int>> zombie;
    int zombiesRemaining;
    int currentWave;
    bool gameOver;
};

// Function declarations
void initializeGameState(GameState& state, Player& player);
void gameLoop();

#endif