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

struct Dummy {
    int x, y;
    int health; // Add health property
    bool isAlive; // To check if the dummy is alive
};

void initializeGameState(GameState& state, Player& player) {
    // Existing initialization code...

    // Spawn Dummies
    for (int i = 0; i < NUMBER_OF_DUMMIES; ++i) {
        Dummy dummy;
        do {
            dummy.x = rand() % (MAP_WIDTH - 2) + 1;
            dummy.y = rand() % (MAP_HEIGHT - 2) + 1;
        } while (dummy.x == player.x && dummy.y == player.y); // Ensure dummy does not spawn at player location
        dummy.health = 1; // Initialize health
        dummy.isAlive = true; // Initialize as alive
        state.dummies.push_back(dummy);
        state.map[dummy.y][dummy.x] = 'D'; // Placeholder for dummy
    }
}

void moveDummies(GameState& state, Player& player) {
    for (auto& dummy : state.dummies) {
        if (dummy.isAlive) {
            // Move towards player
            if (dummy.x < player.x) dummy.x++;
            else if (dummy.x > player.x) dummy.x--;
            if (dummy.y < player.y) dummy.y++;
            else if (dummy.y > player.y) dummy.y--;
            
            // Check if dummy touches the player
            if (dummy.x == player.x && dummy.y == player.y) {
                player.health--; // Deduct health
            }
        }
    }
}

void shootDummy(GameState& state, Player& player) {
    // Check if player shoots (for example, 'space' key)
    if (input == ' ') {
        for (auto& dummy : state.dummies) {
            if (dummy.isAlive && dummy.x == player.x && dummy.y == player.y) {
                dummy.isAlive = false; // Dummy disappears
                state.map[dummy.y][dummy.x] = EMPTY; // Clear the map position
                break; // Stop checking after shooting one
            }
        }
    }
}

struct Citizen {
    int x, y;
    bool needsave; 
};

void initializeGameState(GameState& state, Player& player) {
    

    
    for (int i = 0; i < NUMBER_OF_CITIZENS; ++i) {
        Citizen citizen;
        do {
            citizen.x = rand() % (MAP_WIDTH - 2) + 1;
            citizen.y = rand() % (MAP_HEIGHT - 2) + 1;
        } while (citizen.x == player.x && citizen.y == player.y);
        citizen.needsave = true; 
        state.citizens.push_back(citizen);
        state.map[citizen.y][citizen.x] = 'C'; 
    }
}

void checkCitizenInteraction(GameState& state, Player& player) {
    for (auto& citizen : state.citizens) {
        if (citizen.needsave && citizen.x == player.x && citizen.y == player.y) {
            citizen.needsave = false;
            state.map[citizen.y][citizen.x] = EMPTY; 
            break; // Stop checking after interacting with one
        }
    }
}
