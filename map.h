// map.h
// Map-related structures and functions
#ifndef MAP_H
#define MAP_H

#include "game.h"

// Map functions
void initializeGameState(GameState& state, Player& player);
void drawGame(const GameState& state, const Player&);

#endif