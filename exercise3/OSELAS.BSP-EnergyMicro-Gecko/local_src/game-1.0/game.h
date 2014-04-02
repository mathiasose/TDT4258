#define _POSIX_C_SOURCE 1
#define _GNU_SOURCE 1 
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

/* Prototypes */

void add_random();
void print_board();
void clear_board();
void init();
int init_gamepad();

int map_input(int);
void init();
int init_gamepad();
bool is_game_over();
bool move_up();
bool move_down();
bool move_left();
bool move_right();
bool merge_up();
bool merge_down();
bool merge_left();
bool merge_right();
void up();
void down();
void left();
void right();
void sigio_handler();
int main();
