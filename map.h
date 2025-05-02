// map.h
// Map-related structures and functions
#ifndef MAP_H
#define MAP_H

#include "game.h"
#include "terminal.h"

// Map functions
void initializeGameState(GameState& state, Player& player);
bool canPlaceWall(const GameState& state, int x, int y, int length, bool horizontal);
void drawGame(const GameState& state, const Player&);

#endif