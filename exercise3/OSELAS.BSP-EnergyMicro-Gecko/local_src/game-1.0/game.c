#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int b[16] = { };

void addRandom() {
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

void printBoard(){
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
}

void moveUp() {
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

void mergeUp() {
    for (int i = 4; i < 16; i++) {
	if(b[i] == b[i-4]) {
	    b[i-4] = 2*b[i];
	    b[i] = 0;
	}
    }
}

void up() {
    moveUp();
    mergeUp();
    moveUp();
    addRandom();
}

int main() {
    addRandom();
    addRandom();
    printBoard();
    up();
    printBoard();

    return 0;
}
