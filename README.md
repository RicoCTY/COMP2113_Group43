
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

- 
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

Game story context:The year is 2077. Neo-Kyoto, a sprawling metropolis of neon-drenched skyscrapers and rain-slicked alleyways, is under siege. Not by invading armies

or corporate overlords, but by something far more insidious: The Rust. A nanite plague, unleashed by a rogue scientist, has reanimated the dead, turning them into 

grotesque, chrome-plated zombies. These aren't your typical shambling corpses; The Rust has enhanced their speed, agility, and resilience, turning them into terrifying 

predators.

You are... well, you. A former Yakuza enforcer, disgraced and left for dead after a botched mission. The Yakuza, however, doesn't let go so easily. They found you,

patched you up with scavenged cybernetics, and offered you a deal: cleanse Neo-Kyoto of The Rust, or face a fate far worse than death.

Your arsenal consists of a cybernetically enhanced katana, capable of slicing through steel and bone with ease, and a custom-built railgun, a devastating weapon that 

can vaporize hordes of zombies with a single shot. But firepower alone won't be enough. You'll need to master the art of "Blade and Bullet Ballet," seamlessly switching

between katana strikes and railgun blasts, chaining combos to maximize your damage output.

As you carve your way through the undead hordes, you'll explore the diverse districts of Neo-Kyoto. From the bustling marketplace of Akihabara, now overrun with 

zombified shoppers, to the serene gardens of Gion, defiled by the Rust's grotesque touch, each location presents unique challenges and opportunities. You'll encounter

specialized zombie variants: hulking brutes with reinforced cybernetics, agile ninjas who strike from the shadows, and grotesque bio-weapons spewing corrosive acid.

But The Rust is more than just a plague. It's a conspiracy that reaches the highest echelons of power. As you delve deeper into the city's underbelly, you'll uncover a 

web of lies, betrayal, and corporate greed. You'll encounter allies and enemies, each with their own agenda. A mysterious hacker known only as "Zero" offers you cryptic

clues and technological support. A ruthless corporate executive, obsessed with controlling The Rust for his own gain, becomes your primary target. And a former comrade,

now twisted by the plague, stands as a formidable obstacle in your path.

Your journey will be one of self-discovery and redemption. Haunted by the ghosts of your past, you'll confront your inner demons and make difficult choices that will 

determine the fate of Neo-Kyoto. Will you succumb to the darkness and become another monster, or will you rise as the city's unlikely savior?

The fate of Neo-Kyoto rests in your hands. Sharpen your katana, load your railgun, and prepare to paint the city red with the blood of the undead. The Rust awaits.

In this game, you will be spawned at a map and there are many zombie located around you. You need to kill all the zombie on the map to win the game.

On the map, there are some citizens located around the map, you need save all the citizens from the zombie before you kill all the zombies, otherise, you mark maybe 

deducted!

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
