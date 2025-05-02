// player.h
// Player-related structures and functions
#ifndef PLAYER_H
#define PLAYER_H

#include "game.h"

void drawGame(const GameState& state, const Player& player);

// Player functions
Player initializePlayer(Difficulty difficulty);

void movePlayer(GameState& state, Player& player, char input);
void moveZombies(GameState& state, Player& player);

void shootBullet(GameState& state, Player& player);
void meleeAttack(GameState& state, Player& player);

#endif