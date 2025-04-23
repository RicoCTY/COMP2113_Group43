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
    int lastZombieSpawnTime = time(nullptr); // Track last spawn time for zombies
    int lastStoneSpawnTime = time(nullptr);

    moveZombies(state);

        // Check if it's time to spawn a new zombie
        int currentTime = time(nullptr);
        if (currentTime - lastZombieSpawnTime >= 5) { // Spawn every 5 seconds
            Zombie zombie;
            do {
                zombie.x = rand() % (MAP_WIDTH - 2) + 1;
                zombie.y = rand() % (MAP_HEIGHT - 2) + 1;
            } while (state.map[zombie.y][zombie.x] != EMPTY); // Ensure not at occupied position
            zombie.isAlive = true;
            state.zombies.push_back(zombie);
            state.map[zombie.y][zombie.x] = 'Z'; // Placeholder for zombie
            lastZombieSpawnTime = currentTime; // Update last spawn time
        }

        // Check if it's time to spawn a new stone
        if (currentTime - lastStoneSpawnTime >= 3) { // Spawn every 3 seconds
            Stone stone;
            do {
                stone.x = rand() % (MAP_WIDTH - 2) + 1;
                stone.y = rand() % (MAP_HEIGHT - 2) + 1;
            } while (state.map[stone.y][stone.x] != EMPTY); // Ensure not at occupied position
            stone.isPlaced = true;
            state.stones.push_back(stone);
            state.map[stone.y][stone.x] = 'S'; // Placeholder for stone
            lastStoneSpawnTime = currentTime; // Update last spawn time
        }

    
    while (!state.gameOver) {
        drawGame(state, player);
        
        char input;
        if (kbhit()) {
            input = getch();
            input = tolower(input);
        } else {
            usleep(100000);
            continue;
        }
        
        switch (input) {
            case 'w': case 'a': case 's': case 'd':
                movePlayer(state, player, input);
                break;
            case 'q':
                state.gameOver = true;
                break;
        }
        
    }
}