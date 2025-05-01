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
    p.maxHealth = 100;
    p.armor = 0;
    p.maxArmor = 50;
    p.attackRange = 3; // Default range
    return p;
}

void spawnRandomItem(GameState& state, bool isZombieKill) {
    // Higher chance to spawn if zombie was killed
    int spawnChance = isZombieKill ? 3 : 10; // 1 in 3 vs 1 in 10 chance
    
    if ((rand() % spawnChance) == 0) {
        int ex, ey;
        int attempts = 0;
        const int maxAttempts = 50;
        
        // Try to find an empty spot
        do {
            ex = rand() % (MAP_WIDTH - 2) + 1;
            ey = rand() % (MAP_HEIGHT - 2) + 1;
            attempts++;
        } while (state.map[ey][ex] != EMPTY && attempts < maxAttempts);
        
        if (attempts < maxAttempts) {
            char itemType;
            int itemRand = rand() % 3;
            switch (itemRand) {
                case 0: itemType = HEALTH_ITEM; break;
                case 1: itemType = ARMOR_ITEM; break;
                case 2: itemType = RANGE_ITEM; break;
            }
            state.map[ey][ex] = itemType;
        }
    }
}

bool killZombiesInDirection(GameState& state, Player& player, char direction) {
    int dx = 0, dy = 0;
    bool killedAny = false;
    
    switch (direction) {
        case 'w': dy = -1; break; // Up
        case 's': dy = 1; break;  // Down
        case 'a': dx = -1; break; // Left
        case 'd': dx = 1; break;  // Right
        default: return false;
    }
    
    // Check each tile in range for zombies
    for (int i = 1; i <= player.attackRange; i++) {
        int checkX = player.x + (dx * i);
        int checkY = player.y + (dy * i);
        
        // Skip if out of bounds
        if (checkX < 0 || checkX >= MAP_WIDTH || checkY < 0 || checkY >= MAP_HEIGHT) {
            continue;
        }
        
        // If we find a zombie, kill it and stop checking further
        if (state.map[checkY][checkX] == ZOMBIE) {
            auto it = find(state.zombie.begin(), state.zombie.end(), make_pair(checkX, checkY));
            if (it != state.zombie.end()) {
                state.zombie.erase(it);
                state.map[checkY][checkX] = EMPTY;
                player.money += 20;
                killedAny = true;
                break; // Stop after killing one zombie
            }
        }
        else if (state.map[checkY][checkX] == WALL) {
            break; // Stop if we hit a wall
        }
    }

    if (killedAny) {
        spawnRandomItem(state, true); // Higher chance since zombie was killed
    }
    
    return killedAny;
}

void movePlayer(GameState& state, Player& player, char input) {
    // First try to kill zombies in the direction
    bool killedZombies = killZombiesInDirection(state, player, input);
    
    // Only move if no zombies were killed
    if (!killedZombies) {
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

            // Handle store items
            if (target == HEALTH_ITEM) {
                if (player.money >= 10 && player.health < player.maxHealth) {
                    player.money -= 10;
                    player.health = min(player.health + 10, player.maxHealth);
                    state.map[newY][newX] = EMPTY;
                }
                return;
            }
            if (target == ARMOR_ITEM) {
                if (player.money >= 15 && player.armor < player.maxArmor) {
                    player.money -= 15;
                    player.armor = min(player.armor + 10, player.maxArmor);
                    state.map[newY][newX] = EMPTY;
                }
                return;
            }
            if (target == RANGE_ITEM) {
                if (player.money >= 20 && player.attackRange < 8) {
                    player.money -= 20;
                    player.attackRange++;
                    state.map[newY][newX] = EMPTY;
                }
                return;
            }

            if (target == COIN) {
                auto it = find(state.coin.begin(), state.coin.end(), std::make_pair(newX, newY));
                if (it != state.coin.end()) {
                    state.coin.erase(it);
                    player.money += 1;
                }
            }
            
            if (target == EMPTY || target == COIN) {
                state.map[player.y][player.x] = EMPTY;
                player.x = newX;
                player.y = newY;
                state.map[player.y][player.x] = PLAYER;

                // Small chance to spawn item when moving
                if ((rand() % 20) == 0) { // 1 in 20 chance
                    spawnRandomItem(state, false);
                }
            }
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
        
        // Check if x move is valid (don't allow moving onto player position)
        if (newX > 0 && newX < MAP_WIDTH - 1 && newY > 0 && newY < MAP_HEIGHT - 1) {
            char target = state.map[newY][newX];
            if (target == EMPTY) {  // Only allow moving to empty spaces
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
            if (target == EMPTY) {  // Only allow moving to empty spaces
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