// player.h
// Player-related structures and functions
#ifndef PLAYER_H
#define PLAYER_H

#include "game.h"

// Player functions
Player initializePlayer();
void movePlayer(GameState& state, Player& player, char input);
void moveZombies(GameState& state, const Player& player);

#endif