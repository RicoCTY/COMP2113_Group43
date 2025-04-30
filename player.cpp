// player.cpp
// Player implementation
#include "player.h"
#include <algorithm>

Player initializePlayer() {
    Player p;
    p.x = MAP_WIDTH / 2;
    p.y = MAP_HEIGHT / 2;
    p.money = 0;
    p.health = 100;
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

        if (target == COIN) {
            auto it = find(state.coin.begin(), state.coin.end(), std::make_pair(newX, newY));
            if (it != state.coin.end()) {
                state.coin.erase(it);
                player.money += 1;
            }
        }

        if (target == ZOMBIE) {
            auto it = find(state.zombie.begin(), state.zombie.end(), std::make_pair(newX, newY));
            if (it != state.zombie.end()) {
                state.zombie.erase(it);
                player.health -= 50;
                if (player.health == 0) {
                    state.gameOver = true;
                }
            }
        }
        
        state.map[player.y][player.x] = EMPTY;
        player.x = newX;
        player.y = newY;
        state.map[player.y][player.x] = PLAYER;
    }
}
