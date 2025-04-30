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
                // Don't set to EMPTY here - we'll handle that below
            }
        }
        
        // Handle zombie collision
        if (target == ZOMBIE) {
            auto it = find(state.zombie.begin(), state.zombie.end(), std::make_pair(newX, newY));
            if (it != state.zombie.end()) {
                state.zombie.erase(it);
                player.health -= 50;
                if (player.health <= 0) {
                    state.gameOver = true;
                }
            }
        }
        
        // Only clear old position if moving to empty or coin
        if (target == EMPTY || target == COIN) {
            state.map[player.y][player.x] = EMPTY;
            player.x = newX;
            player.y = newY;
            state.map[player.y][player.x] = PLAYER;
        }
    }
}

void moveZombies(GameState& state, const Player& player) {
    for (auto& zombie : state.zombie) {
        int zx = zombie.first;
        int zy = zombie.second;
        
        // Calculate direction towards player
        int dx = 0, dy = 0;
        if (zx < player.x) dx = 1;
        else if (zx > player.x) dx = -1;
        
        if (zy < player.y) dy = 1;
        else if (zy > player.y) dy = -1;
        
        // Try to move in x direction first
        int newX = zx + dx;
        int newY = zy;
        
        // Check if x move is valid
        if (newX > 0 && newX < MAP_WIDTH - 1 && newY > 0 && newY < MAP_HEIGHT - 1) {
            char target = state.map[newY][newX];
            if (target == EMPTY || target == PLAYER) {
                // Move zombie
                state.map[zy][zx] = EMPTY;
                zx = newX;
                state.map[zy][zx] = ZOMBIE;
                zombie.first = zx;
                continue;
            }
        }
        
        // If x move failed, try y direction
        newX = zx;
        newY = zy + dy;
        
        if (newX > 0 && newX < MAP_WIDTH - 1 && newY > 0 && newY < MAP_HEIGHT - 1) {
            char target = state.map[newY][newX];
            if (target == EMPTY || target == PLAYER) {
                // Move zombie
                state.map[zy][zx] = EMPTY;
                zy = newY;
                state.map[zy][zx] = ZOMBIE;
                zombie.second = zy;
                continue;
            }
        }
    }
}