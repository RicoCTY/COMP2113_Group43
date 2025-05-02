// player.cpp
// Player implementation
#include "player.h"
#include <algorithm>
#include <random>
#include "map.h"
#include <unistd.h>

const char PLAYER_UP[] = "/@\\";
const char PLAYER_DOWN[] = "\\@/";
const char PLAYER_LEFT[] = "<@";
const char PLAYER_RIGHT[] = "@>";

Player initializePlayer(Difficulty difficulty) {
    Player p;
    p.x = MAP_WIDTH / 2;
    p.y = MAP_HEIGHT / 2;
    p.money = 0;
    p.difficulty = difficulty;
    p.facing = DIR_NONE;
    
    switch(difficulty) {
        case EASY:
            p.health = 100;
            p.maxHealth = 100;
            p.armor = 20;
            p.maxArmor = 50;
            p.attackRange = 4;
            break;
        case NORMAL:
            p.health = 80;
            p.maxHealth = 80;
            p.armor = 10;
            p.maxArmor = 30;
            p.attackRange = 3;
            break;
        case HARD:
            p.health = 60;
            p.maxHealth = 60;
            p.armor = 0;
            p.maxArmor = 10;
            p.attackRange = 2;
            break;
    }
    
    return p;
}

void spawnRandomItem(GameState& state, bool isZombieKill) {
    // Higher chance to spawn if zombie was killed
    int spawnChance = isZombieKill ? 3 : 10; // 1 in 3 vs 1 in 10 chance
    
    if ((rand() % spawnChance) == 0) {
        // First check if there are any existing items of each type
        bool hasHealth = false;
        bool hasArmor = false;
        bool hasRange = false;
        
        for (int y = 0; y < MAP_HEIGHT; y++) {
            for (int x = 0; x < MAP_WIDTH; x++) {
                if (state.map[y][x] == HEALTH_ITEM) hasHealth = true;
                else if (state.map[y][x] == ARMOR_ITEM) hasArmor = true;
                else if (state.map[y][x] == RANGE_ITEM) hasRange = true;
            }
        }
        
        // Determine which item types are available to spawn
        vector<char> availableItems;
        if (!hasHealth) availableItems.push_back(HEALTH_ITEM);
        if (!hasArmor) availableItems.push_back(ARMOR_ITEM);
        if (!hasRange) availableItems.push_back(RANGE_ITEM);
        
        // If no items are available to spawn, return
        if (availableItems.empty()) return;
        
        // Choose a random item from available types
        char itemType = availableItems[rand() % availableItems.size()];
        
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
            state.map[ey][ex] = itemType;
        }
    }
}

void shootBullet(GameState& state, Player& player) {
    int dx = 0, dy = 0;
    switch (player.facing) {
        case DIR_UP: dy = -1; break;
        case DIR_DOWN: dy = 1; break;
        case DIR_LEFT: dx = -1; break;
        case DIR_RIGHT: dx = 1; break;
        case DIR_NONE: return;
    }

    // Adjust starting position based on facing direction
    int startOffset = (player.facing == DIR_RIGHT) ? 1 : 0;

    // Animate bullet
    for (int i = 1; i <= player.attackRange; i++) {
        int bulletX = player.x + dx * i + (dx > 0 ? startOffset : 0);
        int bulletY = player.y + dy * i;

        // Check bounds
        if (bulletX <= 0 || bulletX >= MAP_WIDTH-1 || bulletY <= 0 || bulletY >= MAP_HEIGHT-1)
            break;

        // Check if hit zombie
        if (state.map[bulletY][bulletX] == ZOMBIE) {
            // Find and remove zombie
            auto it = find(state.zombie.begin(), state.zombie.end(), make_pair(bulletX, bulletY));
            if (it != state.zombie.end()) {
                state.zombie.erase(it);
                state.map[bulletY][bulletX] = EMPTY;
                player.money += 20;
                state.zombiesRemaining--;
                
                // Check wave completion
                if (state.zombiesRemaining <= 0) {
                    state.currentWave++;
                    if (state.currentWave <= MAX_WAVES) {
                        state.zombiesRemaining = INITIAL_ZOMBIES + (state.currentWave - 1) * ZOMBIE_INCREMENT;
                        // Spawn new zombies
                        for (int i = 0; i < state.zombiesRemaining; i++) {
                            int zx, zy;
                            do {
                                zx = rand() % (MAP_WIDTH - 2) + 1;
                                zy = rand() % (MAP_HEIGHT - 2) + 1;
                            } while (state.map[zy][zx] != EMPTY);
                            state.zombie.push_back({zx, zy});
                            state.map[zy][zx] = ZOMBIE;
                        }
                    }
                }
                spawnRandomItem(state, true);
            }
            break;
        }
        // Stop at walls
        else if (state.map[bulletY][bulletX] == WALL) {
            break;
        }

        // Show bullet animation
        state.map[bulletY][bulletX] = '*';
        drawGame(state, player);
        usleep(50000); // 50ms delay
        state.map[bulletY][bulletX] = EMPTY;
    }
}

// Modify movePlayer to update facing direction
void movePlayer(GameState& state, Player& player, char input) {
    // Update facing direction
    switch (input) {
        case 'w': player.facing = DIR_UP; break;
        case 'a': player.facing = DIR_LEFT; break;
        case 's': player.facing = DIR_DOWN; break;
        case 'd': player.facing = DIR_RIGHT; break;
    }

    int newX = player.x;
    int newY = player.y;
    
    switch (input) {
        case 'w': newY--; break;
        case 'a': newX--; break;
        case 's': newY++; break;
        case 'd': newX++; break;
        default: return; // Only handle movement keys here
    }
    
    // Adjust boundary check for right-facing movement
    if (player.facing == DIR_RIGHT && newX >= MAP_WIDTH - 2) {
        return; // Prevent moving too close to the right wall
    }

    if (newX > 0 && newX < MAP_WIDTH-1 && newY > 0 && newY < MAP_HEIGHT-1) {
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
            if ((rand() % 20) == 0) {
                spawnRandomItem(state, false);
            }
        }
    }
}

void moveZombies(GameState& state, Player& player) {
    // Create random number generator
    static std::random_device rd;
    static std::mt19937 gen(rd());
    
    for (auto& zombie : state.zombie) {
        int zx = zombie.first;
        int zy = zombie.second;
        
        // Calculate direction towards player
        int dx = player.x - zx;
        int dy = player.y - zy;
        
        // Normalize directions (-1, 0, 1)
        int dirX = (dx > 0) ? 1 : ((dx < 0) ? -1 : 0);
        int dirY = (dy > 0) ? 1 : ((dy < 0) ? -1 : 0);
        
        // Possible moves (prioritize moving toward player)
        vector<pair<int, int>> possibleMoves;
        
        // Always include the direction toward player
        if (dirX != 0) possibleMoves.emplace_back(dirX, 0);
        if (dirY != 0) possibleMoves.emplace_back(0, dirY);
        
        // Sometimes add random directions (25% chance for each)
        std::uniform_int_distribution<> dis(0, 3);
        if (dis(gen) == 0) possibleMoves.emplace_back(-1, 0);  // left
        if (dis(gen) == 0) possibleMoves.emplace_back(1, 0);   // right
        if (dis(gen) == 0) possibleMoves.emplace_back(0, -1);  // up
        if (dis(gen) == 0) possibleMoves.emplace_back(0, 1);   // down
        
        // Shuffle possible moves using std::shuffle
        std::shuffle(possibleMoves.begin(), possibleMoves.end(), gen);
        
        bool moved = false;
        for (const auto& move : possibleMoves) {
            int newX = zx + move.first;
            int newY = zy + move.second;
            
            // Check boundaries and valid moves
            if (newX > 0 && newX < MAP_WIDTH - 1 && 
                newY > 0 && newY < MAP_HEIGHT - 1) {
                
                char target = state.map[newY][newX];
                
                // Allow moving to empty spaces or coins
                if (target == EMPTY || target == COIN) {
                    // Move zombie
                    state.map[zy][zx] = EMPTY;
                    zombie.first = newX;
                    zombie.second = newY;
                    state.map[newY][newX] = ZOMBIE;
                    moved = true;
                    break;
                }
                // Check if zombie is moving onto player
                else if (newX == player.x && newY == player.y) {
                    // Reduce player health (armor absorbs damage first)
                    if (player.armor > 0) {
                        player.armor -= 10;
                        if (player.armor < 0) player.armor = 0;
                    } else {
                        player.health -= 10;
                        if (player.health <= 0) {
                            state.gameOver = true;
                        }
                    }
                    moved = true;
                    break;
                }
            }
        }
    
        // If zombie couldn't move toward player, try any valid move
        if (!moved) {
            vector<pair<int, int>> fallbackMoves = {{-1,0}, {1,0}, {0,-1}, {0,1}};
            std::shuffle(fallbackMoves.begin(), fallbackMoves.end(), gen);
            
            for (const auto& move : fallbackMoves) {
                int newX = zx + move.first;
                int newY = zy + move.second;
                
                if (newX > 0 && newX < MAP_WIDTH - 1 && 
                    newY > 0 && newY < MAP_HEIGHT - 1) {
                    
                    char target = state.map[newY][newX];
                    if ((target == EMPTY || target == COIN) && 
                        !(newX == player.x && newY == player.y)) {
                        
                        state.map[zy][zx] = EMPTY;
                        zombie.first = newX;
                        zombie.second = newY;
                        state.map[newY][newX] = ZOMBIE;
                        break;
                    }
                }
            }
        }
    }
}