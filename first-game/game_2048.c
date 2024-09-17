// #include "raylib.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

int grid[16*sizeof(int)];
static const float rand_chance_4 = 0.2;
int game_won = 0;
static const int win_num = 11;
int count = 0;

void generate_number(void);         // Add new number to grid
void UpdateDrawFrame(void);         // Display grid
void move(void);                    // Get user move
void move_left(void);               // Move all blocks left
void move_right(void);              // Move all blocks right
void move_up(void);                 // Move all blocks down
void move_down(void);               // Move all blocks up
int check_for_loss(void);          // Checks for game loss

int main(void) {
    srand(time(NULL));
    generate_number();
    generate_number();
    UpdateDrawFrame();
    while(1) {
        move();
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

void move(void) {
    char dir[2];
    printf("Move direction: ");
    scanf("%s", &dir[0]);
    dir[1] = '\0';
    if (!strcmp(dir,"L")) {
        move_left();
    } else if(!strcmp(dir,"R")) {
        move_right();
    } else if (!strcmp(dir,"U")) {
        move_up();
    } else if (!strcmp(dir,"D")) {
        move_down();
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

void move_left(void) {
    for(int row = 0; row < 4; row++) {
        for(int col = 0; col < 3; col++) {
            if(grid[4*row+col] == 0) { continue; }
            for(int col2 = col+1; col2 < 4; col2++) {
                if(grid[4*row+col2] == 0) { continue; }
                if(grid[4*row+col] != grid[4*row+col2]) { break; }
                grid[4*row+col]++;
                if(grid[4*row+col] == win_num) {game_won = 1;}
                grid[4*row+col2] = 0;
                count--;
            }
        }
        for(int col = 0; col < 4; col++) {
            if(grid[4*row+col] > 0) { continue; }
            for(int col2 = col+1; col2 < 4; col2++) {
                if(grid[4*row+col2] > 0) {
                    grid[4*row+col] = grid[4*row+col2];
                    grid[4*row+col2] = 0;
                    break;
                }
            }
        }
    }
}

void move_right(void) {
    for(int row = 0; row < 4; row++) {
        for(int col = 0; col < 3; col++) {
            if(grid[4*row+3-col] == 0) { continue; }
            for(int col2 = col+1; col2 < 4; col2++) {
                if(grid[4*row+3-col2] == 0) { continue; }
                if(grid[4*row+3-col] != grid[4*row+3-col2]) { break; }
                grid[4*row+3-col]++;
                if(grid[4*row+3-col] == win_num) {game_won = 1;}
                grid[4*row+3-col2] = 0;
                count--;
            }
        }
        for(int col = 0; col < 4; col++) {
            if(grid[4*row+3-col] > 0) { continue; }
            for(int col2 = col+1; col2 < 4; col2++) {
                if(grid[4*row+3-col2] > 0) {
                    grid[4*row+3-col] = grid[4*row+3-col2];
                    grid[4*row+3-col2] = 0;
                    break;
                }
            }
        }
    }
}

void move_up(void) {
    for(int col = 0; col < 4; col++) {
        for(int row = 0; row < 3; row++) {
            if(grid[4*row+col] == 0) { continue; }
            for(int row2 = row+1; row2 < 4; row2++) {
                if(grid[4*row2+col] == 0) { continue; }
                if(grid[4*row+col] != grid[4*row2+col]) { break; }
                grid[4*row+col]++;
                if(grid[4*row+col] == win_num) {game_won = 1;}
                grid[4*row2+col] = 0;
                count--;
            }
        }
        for(int row = 0; row < 4; row++) {
            if(grid[4*row+col] > 0) { continue; }
            for(int row2 = row+1; row2 < 4; row2++) {
                if(grid[4*row2+col] > 0) {
                    grid[4*row+col] = grid[4*row2+col];
                    grid[4*row2+col] = 0;
                    break;
                }
            }
        }
    }
}

void move_down(void) {
    for(int col = 0; col < 4; col++) {
        for(int row = 0; row < 3; row++) {
            if(grid[12-4*row+col] == 0) { continue; }
            for(int row2 = row+1; row2 < 4; row2++) {
                if(grid[12-4*row2+col] == 0) { continue; }
                if(grid[12-4*row+col] != grid[12-4*row2+col]) { break; }
                grid[12-4*row+col]++;
                if(grid[12-4*row+col] == win_num) {game_won = 1;}
                grid[12-4*row2+col] = 0;
                count--;
            }
        }
        for(int row = 0; row < 4; row++) {
            if(grid[12-4*row+col] > 0) { continue; }
            for(int row2 = row+1; row2 < 4; row2++) {
                if(grid[12-4*row2+col] > 0) {
                    grid[12-4*row+col] = grid[12-4*row2+col];
                    grid[12-4*row2+col] = 0;
                    break;
                }
            }
        }
    }
}

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