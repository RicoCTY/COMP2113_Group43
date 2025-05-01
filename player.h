// player.h
// Player-related structures and functions
#ifndef PLAYER_H
#define PLAYER_H

#include "game.h"

// Player functions
Player initializePlayer(Difficulty difficulty);
void movePlayer(GameState& state, Player& player, char input);
void moveZombies(GameState& state, Player& player);
bool killZombiesInDirection(GameState& state, Player& player, char direction);

#endif