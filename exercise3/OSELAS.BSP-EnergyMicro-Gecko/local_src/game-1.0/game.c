#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

int b[16] = { };
int high_score = 0;
int curr_score;

/* Maintenance */
void addRandom()
{
    srand(time(NULL));
    int i = rand() % 16;

    while (b[i] != 0) {
        i = rand() % 16;
    }

    int r = rand() % 10;

    if (r == 0) {
        b[i] = 4;
    } else {
        b[i] = 2;
    }
}

void printBoard()
{
    printf("+------------+\n");
    for(int i = 0; i < 16; i++) {
        if (i % 4 == 0) {
            printf("|");
        }
        if (b[i] == 0) {
            printf("   ");
        } else {
            printf(" %d ", b[i]);
        }
        if ((i+1) % 4 == 0) {
            printf("|\n");
        }
    }
    printf("+------------+\n");
    printf("Curr: %d, High: %d", curr_score, high_score);
}

void clearBoard()
{
    for (int i = 0; i < 16; i++) {
        b[i] = 0;
    }
}

void init()
{
    clearBoard();
    curr_score = 0;
    addRandom();
    addRandom();
}


/* Move functions */
void moveUp()
{
    for (int i = 4; i < 16; i++) {
        int j = i;
        while (j >= 4) {
            if (b[j] != 0 && b[j-4] == 0) {
                b[j-4] = b[j];
                b[j] = 0;
                j -= 4;
            } else break;
        }
    }
}

void moveDown()
{
    for (int i = 11; i >= 0; i--) {
        int j = i;
        while (j <= 11) {
            if (b[j] != 0 && b[j+4] == 0) {
                b[j+4] = b[j];
                b[j] = 0;
                j += 4;
            } else break;
        }
    }
}

void moveLeft()
{
    for (int i = 1; i < 16; i++) {
        int j = i;
        while (j % 4 != 0) {
            if (b[j] != 0 && b[j-1] == 0) {
                b[j-1] = b[j];
                b[j] = 0;
                j -= 1;
            } else break;
        }
    }
}

void moveRight()
{
    for (int i = 14; i >= 0; i--) {
        int j = i;
        while ((j+1) % 4 != 0) {
            if (b[j] != 0 && b[j+1] == 0) {
                b[j+1] = b[j];
                b[j] = 0;
                j += 1;
            } else break;
        }
    }
}

/* Merge functions */
void mergeUp()
{
    for (int i = 4; i < 16; i++) {
        if (b[i] == b[i-4]) {
            b[i-4] = 2*b[i];
            curr_score += 2*b[i];
            b[i] = 0;
        }
    }
}

void mergeDown()
{
    for (int i = 11; i >= 0; i--) {
        if (b[i] == b[i+4]) {
            b[i+4] = 2*b[i];
            curr_score += 2*b[i];
            b[i] = 0;
        }
    }
}

void mergeLeft()
{
    for (int i = 1; i < 16; i++) {
        if (i % 4 == 0) {
            continue;
        }
        if (b[i] == b[i-1]) {
            b[i-1] = 2*b[i];
            curr_score += 2*b[i];
            b[i] = 0;
        }
    }
}

void mergeRight()
{
    for (int i = 14; i >= 0; i--) {
        if ((i+1) % 4 == 0) {
            continue;
        }
        if (b[i] == b[i+1]) {
            b[i+1] = 2*b[i];
            curr_score += 2*b[i];
            b[i] = 0;
        }
    }
}

/* General directional functions */
void up()
{
    moveUp();
    mergeUp();
    moveUp();
    addRandom();
}

void down()
{
    moveDown();
    mergeDown();
    moveDown();
    addRandom();
}

void left()
{
    moveLeft();
    mergeLeft();
    moveLeft();
    addRandom();
}

void right()
{
    moveRight();
    mergeRight();
    moveRight();
    addRandom();
}

/* Entry point */
int main()
{
    char input;
    init();
    printBoard();
    bool running = true;
    while (running) {
        input = getchar();
        switch (input) {
            case 'h':   
                left();
                break;
            case 'j':
                down();
                break;
            case 'k':
                up();
                break;
            case 'l':
                right();
                break;
            default:
                continue;
        }
        printBoard();
    }
    return 0;
}
