// game.cpp
// Core game functions
#include "game.h"
#include "player.h"
#include "map.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <algorithm>

using namespace std;

// Linux/Mac specific functions
void clearScreen() {
    cout << "\033[2J\033[1;1H";
}

int kbhit() {
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}

char getch() {
    char c;
    system("stty raw");
    c = getchar();
    system("stty sane");
    return c;
}

void gameLoop() {
    srand(time(nullptr));
    
    Player player = initializePlayer();
    GameState state;
    initializeGameState(state, player);
    
    while (!state.gameOver) {
        drawGame(state, player);
        
        char input;
        if (kbhit()) {
            input = getch();
            input = tolower(input);
        } else {
            usleep(100000);
            continue;
        }
        
        switch (input) {
            case 'w': case 'a': case 's': case 'd':
                movePlayer(state, player, input);
                break;
            case 'q':
                state.gameOver = true;
                break;
        }
        
    }
}