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
    printf("Curr: %d, High: %d\n", curr_score, high_score);
}

void clearBoard()
{
    for (int i = 0; i < 16; i++) {
	b[i] = 0;
    }
}

int map_input(int input) 
{
    input = ~input;
    for ( int i = 0; i < 8; i++) {
	int match = input & (1 << i);
	if ( (1 << i) == match ) {
	    return (i+1);
	}
    }
    return 0;
}

void init()
{
    clearBoard();
    curr_score = 0;
    addRandom();
    addRandom();
}


/* Move functions */
bool moveUp()
{
    bool r = false;
    for (int i = 4; i < 16; i++) {
	int j = i;
	while (j >= 4) {
	    if (b[j] != 0 && b[j-4] == 0) {
		b[j-4] = b[j];
		b[j] = 0;
		j -= 4;
		r = true;
	    } else break;
	}
    }
    return r;
}

bool moveDown()
{
    bool r = false;
    for (int i = 11; i >= 0; i--) {
	int j = i;
	while (j <= 11) {
	    if (b[j] != 0 && b[j+4] == 0) {
		b[j+4] = b[j];
		b[j] = 0;
		j += 4;
		r = true;
	    } else break;
	}
    }
    return r;
}

bool moveLeft()
{
    bool r = false;
    for (int i = 1; i < 16; i++) {
	int j = i;
	while (j % 4 != 0) {
	    if (b[j] != 0 && b[j-1] == 0) {
		b[j-1] = b[j];
		b[j] = 0;
		j -= 1;
		r = true;
	    } else break;
	}
    }
    return r;
}

bool moveRight()
{
    bool r = false;
    for (int i = 14; i >= 0; i--) {
	int j = i;
	while ((j+1) % 4 != 0) {
	    if (b[j] != 0 && b[j+1] == 0) {
		b[j+1] = b[j];
		b[j] = 0;
		j += 1;
		r = true;
	    } else break;
	}
    }
    return r;
}

/* Merge functions */
bool mergeUp()
{
    bool r = false;
    for (int i = 4; i < 16; i++) {
	if (b[i] == b[i-4]) {
	    b[i-4] = 2*b[i];
	    curr_score += 2*b[i];
	    b[i] = 0;
	    r = true;
	}
    }
    return r;
}

bool mergeDown()
{
    bool r = false;
    for (int i = 11; i >= 0; i--) {
	if (b[i] == b[i+4]) {
	    b[i+4] = 2*b[i];
	    curr_score += 2*b[i];
	    b[i] = 0;
	    r = true;
	}
    }
    return r;
}

bool mergeLeft()
{
    bool r = false;
    for (int i = 1; i < 16; i++) {
	if (i % 4 == 0) {
	    continue;
	}
	if (b[i] == b[i-1]) {
	    b[i-1] = 2*b[i];
	    curr_score += 2*b[i];
	    b[i] = 0;
	    r = true;
	}
    }
    return r;
}

bool mergeRight()
{
    bool r = false;
    for (int i = 14; i >= 0; i--) {
	if ((i+1) % 4 == 0) {
	    continue;
	}
	if (b[i] == b[i+1]) {
	    b[i+1] = 2*b[i];
	    curr_score += 2*b[i];
	    b[i] = 0;
	    r = true;
	}
    }
    return r;
}

/* General directional functions */
void up()
{
    bool b1 = moveUp();
    bool b2 = mergeUp();
    if (b1 || b2) {
	moveUp();
	addRandom();
    }
}

void down()
{
    bool b1 = moveDown();
    bool b2 = mergeDown();
    if (b1 || b2) {
	moveDown();
	addRandom();
    }
}

void left()
{
    bool b1 = moveLeft();
    bool b2 = mergeLeft();
    if (b1 || b2) {
	moveLeft();
	addRandom();
    }
}

void right()
{
    bool b1 = moveRight();
    bool b2 = mergeRight();
    if (b1 || b2) {
	moveRight();
	addRandom();
    }
}

/* Entry point */
int main()
{
    FILE* device = fopen("/dev/gamepad", "rb");
    int input;
    if (!device) {
	printf("Unable to open driver device, maybe you didn't load the module?");
	return -1;
    }
    init();
    bool running = true;
    printBoard();
    while (running) {
	input = map_input(fgetc(device));
	switch (input) {
	    case 1:   
		left();
		break;
	    case 2:
		up();
		break;
	    case 3:
		right();
		break;
	    case 4:
		down();
		break;
	    default:
		continue;
	}
	printBoard();
    }
    return 0;
}
