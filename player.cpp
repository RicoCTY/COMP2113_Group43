// player.cpp
// Player implementation
#include "player.h"
#include <algorithm>

Player initializePlayer() {
    Player p;
    p.x = MAP_WIDTH / 2;
    p.y = MAP_HEIGHT / 2;
    return p;
}

void movePlayer(GameState& state, Player& player, char input) {
    int newX = player.x;
    int newY = player.y;
    
    switch (input) {
        case 'w': newY--; break;
        case 'a': newX--; break;
        case 's': newY++; break;
        case 'd': newX++; break;
    }
    
    if (newX >= 0 && newX < MAP_WIDTH && newY >= 0 && newY < MAP_HEIGHT) {
        char target = state.map[newY][newX];
        
        if (target == WALL) return;
        
        state.map[player.y][player.x] = EMPTY;
        player.x = newX;
        player.y = newY;
        state.map[player.y][player.x] = PLAYER;
    }
}
