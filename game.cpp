// game.cpp
// Core game functions
#include "game.h"
#include "player.h"
#include "map.h"
#include "terminal.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <algorithm>
#include <chrono>

using namespace std;

Difficulty selectDifficulty() {
    int selection = 1; // Default to Easy (option 1)
    char input;
    
    while (true) {
        clearScreen();   
        cout << COLOR_BOLD << "SELECT DIFFICULTY:\n\n" << COLOR_RESET;
        
        // Option 1
        if (selection == 1) cout << COLOR_GREEN << "> 1. Easy ";
        else cout << "  1. Easy ";
        cout << COLOR_RESET << "   (100HP | 50 armor | range 4)\n" << endl;
        
        // Option 2
        if (selection == 2) cout << COLOR_YELLOW << "> 2. Normal ";
        else cout << "  2. Normal ";
        cout << COLOR_RESET << " (80HP  | 30 armor | range 3)\n" << endl;
        
        // Option 3
        if (selection == 3) cout << COLOR_RED << "> 3. Hard ";
        else cout << "  3. Hard ";
        cout << COLOR_RESET << "   (60HP  |  0 armor | range 2)\n";
        
        cout << COLOR_CYAN << "\nUse 1-3 to select, ENTER to confirm\n" << COLOR_RESET;;
        cout << "====================\n";
        
        
        input = getch();
        
        // Only process valid inputs
        switch(input) {
            case '1':
                selection = 1;
                break;
            case '2':
                selection = 2;
                break;
            case '3':
                selection = 3;
                break;
            case '\n':  // Enter key
            case '\r':
                return static_cast<Difficulty>(selection - 1);
            default:
                continue;
        }
    }
}

void showGameOverScreen(int wave) {
    clearScreen();
    cout << COLOR_RED << COLOR_BOLD;
    cout << "  _____                         ____                 \n";
    cout << " / ____|                       / __ \\                \n";
    cout << "| |  __  __ _ _ __ ___   ___  | |  | |_   _____ _ __ \n";
    cout << "| | |_ |/ _` | '_ ` _ \\ / _ \\ | |  | \\ \\ / / _ \\ '__|\n";
    cout << "| |__| | (_| | | | | | |  __/ | |__| |\\ V /  __/ |   \n";
    cout << " \\_____|\\__,_|_| |_| |_|\\___|  \\____/  \\_/ \\___|_|   \n\n";
    cout << COLOR_RESET;
    cout << COLOR_YELLOW << "You survived until wave " << wave << "\n\n" << COLOR_RESET;
    cout << COLOR_CYAN << "Press any key to return to the main menu..." << COLOR_RESET;
    getch();
}

void showVictoryScreen() {
    clearScreen();
    cout << COLOR_GREEN << COLOR_BOLD;
    cout << " __     __                    _       _ \n";
    cout << " \\ \\   / /                   (_)     | |\n";
    cout << "  \\ \\_/ /__  _   _  __      ___ _ __ | |\n";
    cout << "   \\   / _ \\| | | | \\ \\ /\\ / / | '_ \\| |\n";
    cout << "    | | (_) | |_| |  \\ V  V /| | | | |_|\n";
    cout << "    |_|\\___/ \\__,_|   \\_/\\_/ |_|_| |_(_)\n\n";
    cout << COLOR_RESET;
    cout << COLOR_YELLOW << "CONGRATULATIONS! You survived all " << MAX_WAVES << " waves!\n\n" << COLOR_RESET;
    cout << COLOR_CYAN << "Press any key to return to the main menu..." << COLOR_RESET;
    getch();
}

void gameLoop() {
    srand(time(nullptr));
    
    Difficulty difficulty = selectDifficulty();
    Player player = initializePlayer(difficulty);
    GameState state;
    initializeGameState(state, player);
    
    auto lastZombieMove = chrono::steady_clock::now();
    const chrono::milliseconds zombieMoveInterval(500);
    
    while (!state.gameOver) {
        drawGame(state, player);

        if (state.currentWave > MAX_WAVES) {
            showVictoryScreen();
            break;
        }
        
        if (kbhit()) {
            char input = getch();
            input = tolower(input);
            
            switch (input) {
                case 'w': case 'a': case 's': case 'd':
                    movePlayer(state, player, input);
                    break;
                case 'e': // Shoot bullet
                    shootBullet(state, player);
                    break;
                case 'q': {
                    bool shouldQuit = showQuitConfirmation();
                    if (shouldQuit) {
                        state.gameOver = true;
                        exit(0); // Exit game completely
                    }
                    break;
            }
        }
    }
        auto now = chrono::steady_clock::now();
        if (now - lastZombieMove >= zombieMoveInterval) {
            moveZombies(state, player);
            lastZombieMove = now;
        }
        
        usleep(10000);
        
        if (player.health <= 0) {
            state.gameOver = true;
            showGameOverScreen(state.currentWave);
            break;
        }
    }
}

bool showQuitConfirmation() {
    int selection = 1; // Default to "Return to Main Menu"
    char input;
    
    while (true) {
        clearScreen();
        cout << COLOR_BOLD << COLOR_RED << "QUIT GAME?\n" << COLOR_RESET;
        cout << COLOR_YELLOW << "Are you sure you want to quit?\n\n" << COLOR_RESET;
        
        // Option 1
        if (selection == 1) cout << COLOR_GREEN << "> 1. Return to The Game\n" << endl;
        else cout << COLOR_RESET << "  1. Return to The Game\n" << endl;;
        
        // Option 2
        if (selection == 2) cout << COLOR_RED << "> 2. Quit Game\n";
        else cout << COLOR_RESET << "  2. Quit Game\n";
        
        cout << COLOR_CYAN << "\nUse 1-2 to select, ENTER to confirm\n" << COLOR_RESET;
        cout << "====================\n";
        
        input = getch();
        
        switch(input) {
            case '1':
                selection = 1;
                break;
            case '2':
                selection = 2;
                break;
            case '\n':  // Enter key
            case '\r':
                return (selection == 2); // true if quit game, false if return to menu
            case 'q':    // Allow q to cancel
                return false;
            default:
                continue;
        }
    }
}