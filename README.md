
# Menu
1. [For Player](#for-player) 
	1. [Team members](#Team-members-)
	2. [How to play](#how-to-play-)
	3. [Quick DEMO](#quick-demo)
	4. [Features implemented](#features-implemented-)
	5. [Discription](#description-)
	6. [Non-standard libraries](#non-standard-libraries-%EF%B8%8F)
2. [File discription](#File discription)
	1. [game.cpp](#game.cpp)
	2. [game.h](#game.h)
	3. [main.cpp](#main.cpp)
	4. [map.cpp](#map.cpp)
	5. [map.h](#map.h)
	6. [player.cpp](#player.cpp)
	7. [player.h](player.h)
	
# For Player
## Team members 
Choi Tsz Yin 3036259176
Yau Tik Hang 3036262018

## How to play

```bash
make run
```
- Press any key to start
- Press *w/s/a/d* to move
- Press ** to shoot
- Press *q* to quit
## Quick DEMO (link)

## Features implemented

- **Generation of random game sets or events**

    - There are random ways of spawning zombies, coins and stone
⁣⁣⁣⁣
- **Dynamic memory management**

    - We handle allocation and deallocation of dynamic memory
⁣⁣⁣⁣
- **File input/output**

    - Data of game are stored so the data will not lost when they player quit the game
⁣⁣⁣⁣
- **Data structures for storing game status**

    - We define a class to store the game status such as player health and player coins
⁣⁣⁣⁣
- **Program codes in multiple files**

    - Several file are used
⁣⁣⁣⁣
- **Multiple difficulty level**

    - Different level are created


## Game Description 

Welcome to our zombie survival shooting game written in C++! In this game, you may experience shooting zombie in 2D!

Game story context: In 2400, A virus named "Zombious Virus" outbreaked and it will infect people turns to a zombie. You are assigned by government to kill the zombie using a gun. 

In this game, you will be spawned at a map and there are many zombie located around you. You need to kill all the zombie on the map to win the game.

On the map, there are some citizens located around the map, you need save all the citizens from the zombie before you kill all the zombies, otherise, you mark maybe deducted!

Also, around the map, there are many coins randomly dropped. You can collect those coins around the map while killing zombies to upgrade your weapon!

Some rocks also located on the map, the location that spwaned with rocks are not allowed to pass by.

Your ultimate goal is to pass many level as you can. For sure, you may challenge a harder level when you already mastered the easier level.

Survive as long as possible, protect the citizens, become a zombie slayer!


## Special game feature of this game

- **Intense combat**

    - Shoot the zombies before they reach you and hurt you!
 
- **Earn and spend coins**

    - Pick up coins on the map while killing zombie and use coins to upgrade your weapons!
      
- **Save Citizens**

    - You not only need to shoot zombies, you also need to save citizens in the map from zombie at the same time！

- **Progressive difficulty**

    - If you feel that you are advanced enough in shooting zombies, you can choose to face a wave of stronger zombies!
   
## Non-standard libraries 🗂️

Not used, standard libraries only.

# File discription

## game.cpp

- For core game function, e.g. gameloop() function

## game.h

-Declare game constants, game symbols, player structure and game state

## main.cpp

-Main game loop and entry point

## map.cpp

-Include function of generating map, clear map. Also place player, coins and zombies functiona.

## map.h

-Include map related structures and functions

## player.cpp

-Player implementation. Include move player and move zombies functions

## player.h

-Player-related structures and functions
