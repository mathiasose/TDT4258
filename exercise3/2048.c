#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int b[16] = { };

void init() {
    srand(time(NULL));
    int r1 = rand() % 16;
    int r2 = rand() % 16;
    while (r1 == r2) {
	r2 = rand() % 16;
    }

    b[r1] = 2;
    b[r2] = 2;
}

void printBoard(){
    for(int i = 0; i < 16; i++) {
	printf("%d ", b[i]);
	if((i+1) % 4 == 0) {
	    printf("\n");
	}
    }
}

int main() {
    init();
    printBoard();

    return 0;
}
