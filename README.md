# COMP2113_Group43 - Zombie Rush

![WhatsApp Image 2025-05-02 at 22 43 48_1f132676](https://github.com/user-attachments/assets/742e527f-63f5-40aa-8e77-18144c782c6b)

## Team Members
 [Choi Tsz Yin](https://github.com/RicoCTY) (3036259176)
 
 [Yau Tik Hang](https://github.com/YauTikHang) (3036262018)

## Description
🧟 **Zombie Rush** is an intense 2D survival shooter game written in C++ where you must defend against waves of undead!

🫨 Oh no! Zombies are invading the University of Hong Kong! Grab your weapon and defend your campus before it's overrun! Your goal is simple - survive wave after wave of relentless zombies to see tomorrow's dawn.

⁉️ These aren't your ordinary slow zombies - they move with terrifying intelligence, sometimes heading straight for you, sometimes taking unpredictable paths. Carefully aim your shots!

⚔️ Random power-ups will spawn throughout the map - grab them to upgrade your firepower, armor, or health. Think you're good? Try our brutal Hard mode where items don't spawn at all!

💥 With multiple difficulty levels and increasingly challenging waves, Zombie Rush offers endless undead-slaying action. If you love fast-paced shooting games with survival elements, this is your next addiction!

## How to Play

### Quick DEMO

https://drive.google.com/file/d/1A7skSvggePRmOMAEJOeDP2SuS30qjcDD/view?usp=drivesdk

### Running the Program
To compile and run the game:
```bash
make run
```
To clean up compiled files:

```bash
make clean
```
### Controls
- `W` / `A` / `S` / `D` : **Move your character**

- `E` : **Shoot in your facing direction**

- `1` /`2` /`3` : **Select menu options**

- `ENTER` : **Confirm selections**

- `Q` : **Open quit menu**

## Features Implemented

### **1. Generation of Random Events (see map.cpp, player.cpp)** ###

   - Zombies spawn in random locations each wave

   - Zombie movement has random elements while still tracking player

   - Power-ups (health, armor, range) spawn randomly when:

      - Killing zombies ***(higher chance)***

      - Moving around the map ***(lower chance)***

   - Walls are procedurally generated in different configurations (Straight or horizontal)

### **2. Data Structures For Storing Data (see game.h, player.h)** ###

   - Player struct stores all character stats (health, armor, money, position)

   - GameState struct manages:

      - Current map layout

      - Zombie positions (vector of pairs)

      - Coin positions (vector of pairs)

      - Wave progression

### **3. Dynamic Memory Management (see player.cpp)** ###

   - Vectors used for zombie and coin positions automatically handle dynamic memory

   - Efficient memory usage through proper data structure selection

### **4. File Input/Output (see terminal.cpp)** ###

   - Terminal state management for real-time input handling

   - Game state preserved during gameplay sessions

### **5. Program Codes in Multiple Files** ###

   - Clean separation of concerns across:

     - Core game logic (game.cpp/h)

     - Player mechanics (player.cpp/h)

     - Map generation (map.cpp/h)

     - Terminal handling (terminal.cpp/h)

     - Main entry point (main.cpp)

   Architecture:
   ```bash
       src/
       ├── Makefile       # For code compilation
       ├── README.md      # This file
       ├── game.cpp/h     # Core game logic
       ├── player.cpp/h   # Player mechanics
       ├── map.cpp/h      # Map generation
       ├── terminal.cpp/h # Terminal handling
       └── main.cpp       # Entry point
   ```

### **6. Multiple Difficulty Levels (see game.cpp)**

  - Three distinct levels:
      | Difficulty | Health | Armor | Range | Items available |
     |------------|--------|-------|-------|-------|
     | Easy       | 100    | 50    | 4     | Yes   |
     | Normal     | 80     | 30    | 3     | Yes   |
     | Hard       | 60     | 0     | 3     | No    |

     > Hard: Only for true zombie slayers!

## Non-Standard Libraries
This game uses only standard C++ libraries

- no external dependencies required!

