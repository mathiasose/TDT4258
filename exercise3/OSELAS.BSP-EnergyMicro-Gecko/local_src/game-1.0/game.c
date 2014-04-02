#include "game.h"

FILE* device;
int b[16] = { };
int high_score = 0;
int curr_score;

/* Maintenance */
void add_random()
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

void print_board()
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

void clear_board()
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
    clear_board();
    curr_score = 0;
    add_random();
    add_random();
}

int init_gamepad()
{
    device = fopen("/dev/gamepad", "rb");
    if (!device) {
        printf("Unable to open driver device, maybe you didn't load the module?");
        return EXIT_FAILURE;
    }
    if (signal(SIGIO, &sigio_handler) == SIG_ERR) {
        printf("An error occurred while register a signal handler.\n");
        return EXIT_FAILURE;
    }
    if (fcntl(fileno(device), F_SETOWN, getpid()) == -1) {
        printf("Error setting pid as owner.\n");
        return EXIT_FAILURE;
    }
    long oflags = fcntl(fileno(device), F_GETFL);
    if (fcntl(fileno(device), F_SETFL, oflags | FASYNC) == -1) {
        printf("Error setting FASYNC flag");
        return EXIT_FAILURE;
    }
    return 0;
}

bool is_game_over()
{
    for (int i = 0; i < 15; i++) {
        if (b[i] == 0) {
            return false;
        }

        // check left/right merge
        if ((i + 1) % 4 != 0 && b[i] == b[i+1]) {
            return false;
        }

        // check up/down merge
        if (i < 12 && b[i] == b[i+4]) {
            return false;
        }
    }
    return true;
}

/* Move functions */
bool move_up()
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

bool move_down()
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

bool move_left()
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

bool move_right()
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
bool merge_up()
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

bool merge_down()
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

bool merge_left()
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

bool merge_right()
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
    bool b1 = move_up();
    bool b2 = merge_up();
    if (b1 || b2) {
        move_up();
        add_random();
    }
}

void down()
{
    bool b1 = move_down();
    bool b2 = merge_down();
    if (b1 || b2) {
        move_down();
        add_random();
    }
}

void left()
{
    bool b1 = move_left();
    bool b2 = merge_left();
    if (b1 || b2) {
        move_left();
        add_random();
    }
}

void right()
{
    bool b1 = move_right();
    bool b2 = merge_right();
    if (b1 || b2) {
        move_right();
        add_random();
    }
}


/* Signal handler */

void sigio_handler(int signo)
{
    printf("Signal nr.: %d\n", signo);
    int input = map_input(fgetc(device));
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
    }
    print_board();
}

/* Entry point */
int main()
{
    if (init_gamepad() == EXIT_FAILURE) {
        return EXIT_FAILURE;
    }
    init();
    print_board();
    /* Suspend process until it receives a signal it has a registered signal handler for */
    while (1) {
        pause();
    }
    return 0;
}
