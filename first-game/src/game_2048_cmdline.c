// #include "raylib.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

int grid[16*sizeof(int)];
static const float rand_chance_4 = 0.1;
int game_won = 0;
static const int win_num = 11;
int count = 0;

void generate_number(void);         // Add new number to grid
void UpdateDrawFrame(void);         // Display grid
void new_move(void);                // Get user move
void move(int (*f)(int, int));      // Move all blocks in a direction
int move_left(int,int);             // Move all blocks left
int move_right(int,int);            // Move all blocks right
int move_up(int,int);               // Move all blocks up
int move_down(int,int);             // Move all blocks down
int check_for_loss(void);           // Checks for game loss

int main(void) {
    srand(time(NULL));
    generate_number();
    generate_number();
    UpdateDrawFrame();
    while(1) {
        new_move();
    }
    return 0;
}

void generate_number(void) {
    int x = rand()%16;
    while(grid[x] != 0) {
        x = rand()%16;
    }
    if (rand()%100 <= rand_chance_4*100) {
        grid[x] = 2;
    } else {
        grid[x] = 1;
    }
    count ++;
}

void UpdateDrawFrame(void) {
    for(int i = 0; i < 4; i++) {
        printf("%4d %4d %4d %4d\n", 1<<grid[i*4], 1<<grid[i*4+1], 1<<grid[i*4+2], 1<<grid[i*4+3]);
    }
    printf("\n");
}

void new_move(void) {
    char dir[2];
    printf("Move direction: ");
    scanf("%s", &dir[0]);
    dir[1] = '\0';
    if (!strcmp(dir,"L")) {
        move(move_left);
    } else if(!strcmp(dir,"R")) {
        move(move_right);
    } else if (!strcmp(dir,"U")) {
        move(move_up);
    } else if (!strcmp(dir,"D")) {
        move(move_down);
    } else {
        exit(1);
    }
    if(game_won) {
        UpdateDrawFrame();
        printf("You won by getting %d! Congratuations!\n", 1<<win_num);
        exit(0);
    }
    if(count < 16) {
        generate_number();
    }
    if (count == 16) {
        if(check_for_loss()) {
            UpdateDrawFrame();
            printf("You lost. Better luck next time!\n");
            exit(0);
        }
    }
    UpdateDrawFrame();
}

void move( int (*f)(int, int)) {
    for(int row = 0; row < 4; row++) {
        for(int col = 0; col < 4; col++) {
            if(grid[(*f)(row,col)] == 0) { continue; }
            for(int col2 = col+1; col2 < 4; col2++) {
                if(grid[(*f)(row,col2)] == 0) { continue; }
                if(grid[(*f)(row,col)] != grid[(*f)(row,col2)]) { break; }
                grid[(*f)(row,col)]++;
                if(grid[(*f)(row,col)] == win_num) {game_won = 1;}
                grid[(*f)(row,col2)] = 0;
                count--;
                break;
            }
        }
        for(int col = 0; col < 4; col++) {
            if(grid[(*f)(row,col)] > 0) { continue; }
            for(int col2 = col+1; col2 < 4; col2++) {
                if(grid[(*f)(row,col2)] > 0) {
                    grid[(*f)(row,col)] = grid[(*f)(row,col2)];
                    grid[(*f)(row,col2)] = 0;
                    break;
                }
            }
        }
    }
}

int move_left(int x, int y) { return 4*x+y; }
int move_right(int x, int y) { return 4*x+3-y; }
int move_up(int x, int y) { return 4*y+x; }
int move_down(int x, int y) { return 12-4*y+x; }

int check_for_loss() {
    for(int row = 0; row < 4; row++) {
        for(int col = 0; col < 4; col++) {
            if(grid[4*row+col] == 0) { exit(2); }
            if(row > 0 && grid[4*row+col] == grid[4*row+col-4]) {
                return 0;
            }
            if(row < 3 && grid[4*row+col] == grid[4*row+col+4]) {
                return 0;
            }
            if(col > 0 && grid[4*row+col] == grid[4*row+col-1]) {
                return 0;
            }
            if(col < 3 && grid[4*row+col] == grid[4*row+col+1]) {
                return 0;
            }
        }
    }
    return 1;
}