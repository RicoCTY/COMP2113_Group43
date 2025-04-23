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
    
    while (!state.gameOver) {
        drawGame(state, player);
        int currentTime = time(nullptr);
        if (currentTime - lastSpawnTime >= 5) { // Spawn every 5 seconds
            Dummy dummy;
            do {
                dummy.x = rand() % (MAP_WIDTH - 2) + 1;
                dummy.y = rand() % (MAP_HEIGHT - 2) + 1;
            } while (dummy.x == player.x && dummy.y == player.y); // Ensure not at player location
            dummy.health = 1;
            dummy.isAlive = true;
            state.dummies.push_back(dummy);
            state.map[dummy.y][dummy.x] = 'D'; // Placeholder for dummy
            lastSpawnTime = currentTime; // Update last spawn time
        }
        for (int i = 0; i < 4; ++i) { // Spawn 4 citizens
        Citizen citizen;
        do {
            citizen.x = rand() % (MAP_WIDTH - 2) + 1;
            citizen.y = rand() % (MAP_HEIGHT - 2) + 1;
        } while (citizen.x == player.x && citizen.y == player.y); // Ensure citizen does not spawn at player location
        citizen.needsave = true; // Initialize as alive
        state.citizens.push_back(citizen);
        state.map[citizen.y][citizen.x] = 'C'; // Placeholder for citizen
        
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
        checkCitizenInteraction(state, player);
        if (player.health <= 0) {
            state.gameOver = true; 
        }
    }
}
