#include "raylib.h"
#include "stdio.h"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

//----------------------------------------------------------------------------------
// Some Defines
//----------------------------------------------------------------------------------
#define WIN_EXP         11
#define GAME_PLAY       0
#define GAME_CONT       1
#define GAME_WON        2
#define GAME_LOST       3

//------------------------------------------------------------------------------------
// Global Variables Declaration
//------------------------------------------------------------------------------------
static const int screenWidth = 800;
static const int screenHeight = 450;
static const float rand4chance = 0.1;

static int framesCounter = 0;
static int gameState = GAME_PLAY;
static int gameEndFrames = 0;
static Vector2 offset = { 0 };

int grid[16];
static Rectangle grid_rects[16];
static int count;
static int score;
static float squareSize;
static Color colors[15] = {
    (Color) {204, 192, 179, 255}, (Color) {238, 228, 218, 255},
    (Color) {237, 224, 200, 255}, (Color) {242, 177, 121, 255},
    (Color) {245, 149,  99, 255}, (Color) {246,  124, 95, 255},
    (Color) {246,  94,  59, 255}, (Color) {237, 207, 114, 255},
    (Color) {237, 204,  97, 255}, (Color) {237, 200,  80, 255}, 
    (Color) {237, 197,  63, 255}, (Color) {204, 194,  46, 255},
    GREEN,  SKYBLUE, PURPLE
};

//------------------------------------------------------------------------------------
// Module Functions Declaration (local)
//------------------------------------------------------------------------------------
static void InitGame(void);                // Initialize game
static void UpdateGame(void);              // Update game (one frame)
static void DrawGame(void);                // Draw game (one frame)
static void UnloadGame(void);              // Unload game
static void UpdateDrawFrame(void);         // Update and Draw (one frame)
static void move(int (*f)(int, int));      // Move all blocks in a direction
static int move_left(int,int);             // Move all blocks left
static int move_right(int,int);            // Move all blocks right
static int move_up(int,int);               // Move all blocks up
static int move_down(int,int);             // Move all blocks down
static void generate_number(void);         // Add new number to grid
static int check_for_loss(void);           // Checks for game loss

int main(void)
{
    // Initialization (Note windowTitle is unused on Android)
    //---------------------------------------------------------
    InitWindow(screenWidth, screenHeight, "classic game: 2048");

    InitGame();
    SetTargetFPS(60);
    
#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 60, 1);
#else
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update and Draw
        //----------------------------------------------------------------------------------
        UpdateDrawFrame();
        //----------------------------------------------------------------------------------
    }
#endif
    
    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadGame();         // Unload loaded data (textures, sounds, models...)

    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}


//------------------------------------------------------------------------------------
// Module Functions Definitions (local)
//------------------------------------------------------------------------------------

// Initialize game variables
void InitGame(void)
{
    framesCounter = 0;
    gameState = GAME_PLAY;
    gameEndFrames = 0;
    count = 0;
    score = 0;
    for (int i = 0; i < 16; i++) { grid[i] = 0; }
    generate_number();
    generate_number();

    if (screenHeight <= screenWidth) {
        squareSize = screenHeight*0.2;
    } else {
        squareSize = screenWidth*0.2;
    }
    offset.x = screenWidth*0.5 - squareSize*2;
    offset.y = screenHeight*0.5 - squareSize*2;

    for(int row=0; row < 4; row++) {
        for(int col=0; col<4; col++) {
            grid_rects[4*row+col].x = offset.x + col*squareSize;
            grid_rects[4*row+col].y = offset.y + row*squareSize;
            grid_rects[4*row+col].width = squareSize;
            grid_rects[4*row+col].height = squareSize;
        }
    }
}

// Update game (one frame)
void UpdateGame(void)
{
    if (gameState > 1) 
    {
        gameEndFrames++;
        if (IsKeyPressed(KEY_ENTER))
        {
            InitGame();
            gameState = GAME_PLAY;
        } 
        if (IsKeyPressed(KEY_SPACE))
        {
            gameState = GAME_CONT;
            gameEndFrames = 0;
        }
    } else
    {
        // Player control
        if (IsKeyPressed(KEY_RIGHT))
        {
            move(move_right);
        }
        if (IsKeyPressed(KEY_LEFT))
        {
            move(move_left);
        }
        if (IsKeyPressed(KEY_UP))
        {
            move(move_up);
        }
        if (IsKeyPressed(KEY_DOWN))
        {
            move(move_down);
        }

        framesCounter++;
    }
}

// Draw game (one frame)
void DrawGame(void)
{
    BeginDrawing();

        ClearBackground(RAYWHITE);

        if ((gameState < 2) || ((gameState > 1) && (gameEndFrames < 50)))
        {
            // draw grid
            for (int i = 0; i < 16; i++) {
                DrawRectangleRec(grid_rects[i],colors[grid[i]]);
                char num[5] = "\0\0\0\0\0";
                sprintf(num,"%d",1<<grid[i]);
                DrawText(num, grid_rects[i].x + squareSize/2 - MeasureText(num, 30)/2, grid_rects[i].y + squareSize/2 - 15, 30, GRAY);
            }

            // Draw grid lines
            for (int i = 0; i < 5; i++) DrawLineV((Vector2){offset.x + squareSize*i, offset.y}, (Vector2){squareSize*i + offset.x, screenHeight - offset.y}, LIGHTGRAY);
            for (int i = 0; i < 5; i++) DrawLineV((Vector2){offset.x, squareSize*i + offset.y}, (Vector2){screenWidth - offset.x, squareSize*i + offset.y}, LIGHTGRAY);
        }
        else {
            if(gameState == GAME_WON) {
                DrawText("CONGRATULATIONS, YOU WON!!!", GetScreenWidth()/2 - MeasureText("CONGRATULATIONS, YOU WON!!!", 20)/2, GetScreenHeight()/2 - 50, 20, GRAY);
                DrawText("PRESS [SPACE] TO CONTINUE", GetScreenWidth()/2 - MeasureText("PRESS [SPACE] TO CONTINUE", 20)/2, GetScreenHeight()/2 + 10, 20, GRAY);
            }
            else {
                DrawText("YOU LOST. BETTER LUCK NEXT TIME!", GetScreenWidth()/2 - MeasureText("YOU LOST. BETTER LUCK NEXT TIME!", 20)/2, GetScreenHeight()/2 - 50, 20, GRAY);
            }
            DrawText("PRESS [ENTER] TO PLAY AGAIN", GetScreenWidth()/2 - MeasureText("PRESS [ENTER] TO PLAY AGAIN", 20)/2, GetScreenHeight()/2 - 20, 20, GRAY);
        }
    
    char scoreStr[14] = "Score: ";
    sprintf(scoreStr+7,"%d",score);
    DrawText(scoreStr, GetScreenWidth() - 130, GetScreenHeight() - 30, 20, GRAY);
    EndDrawing();
}

// Unload game variables
void UnloadGame(void)
{
    // TODO: Unload all dynamic loaded data (textures, sounds, models...)
}

// Update and Draw (one frame)
void UpdateDrawFrame(void)
{
    UpdateGame();
    DrawGame();
}

void generate_number(void) {
    int* positions = LoadRandomSequence(16,0,15);
    for(int i = 0; i<16; i++) {
        if(grid[positions[i]] > 0) {continue;}
        if (GetRandomValue(0,100) <= rand4chance*100) {
            grid[positions[i]] = 2;
        } else {
            grid[positions[i]] = 1;
        }
        count++;
        break;
    }
}

void move(int (*f)(int, int)) {
    int moves = 0;
    for(int row = 0; row < 4; row++) {
        for(int col = 0; col < 4; col++) {
            if(grid[(*f)(row,col)] == 0) { continue; }
            for(int col2 = col+1; col2 < 4; col2++) {
                if(grid[(*f)(row,col2)] == 0) { continue; }
                if(grid[(*f)(row,col)] != grid[(*f)(row,col2)]) { break; }
                grid[(*f)(row,col)]++;
                score += 1<<grid[(*f)(row,col)];
                if(grid[(*f)(row,col)] == WIN_EXP && !gameState) {
                    gameState = GAME_WON;
                }
                grid[(*f)(row,col2)] = 0;
                count--;
                moves++;
                break;
            }
        }
        for(int col = 0; col < 4; col++) {
            if(grid[(*f)(row,col)] > 0) { continue; }
            for(int col2 = col+1; col2 < 4; col2++) {
                if(grid[(*f)(row,col2)] > 0) {
                    grid[(*f)(row,col)] = grid[(*f)(row,col2)];
                    grid[(*f)(row,col2)] = 0;
                    moves++;
                    break;
                }
            }
        }
    }
    if(count < 16 && moves) {
        generate_number();
    }
    if (count == 16) {
        if(check_for_loss()) {
            gameState = GAME_LOST;
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
            if(grid[4*row+col] == 0) { return 0; }
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