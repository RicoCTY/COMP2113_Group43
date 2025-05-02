#include "terminal.h"
#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

using namespace std;

void clearScreen() {
    cout << "\033[2J\033[1;1H";
}

// Function to get a single character input without waiting for Enter
char getch() {
    char c;
    system("stty raw");
    c = getchar();
    system("stty sane");
    return c;
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