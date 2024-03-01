/*******************************************************************************************
*
*   raylib [core] example - Basic window
*
*   Welcome to raylib!
*
*   To test examples, just press F6 and execute raylib_compile_execute script
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   Example originally created with raylib 1.0, last time updated with raylib 1.0
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2013-2023 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#define MAZE_WIDTH 64
#define MAZE_HEIGHT 64
#define MAZE_DRAW_SCALE 6.0f

typedef struct Point
{
    int x;
    int y;
} Point;


//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    //SetRandomSeed(74218);
    Image imMaze = GenImageColor(MAZE_WIDTH, MAZE_HEIGHT, BLACK);

    Point mazePoints[MAZE_WIDTH * MAZE_HEIGHT] = {0};
    int mazePointsCounter = 0;

    for(int y = 0; y < imMaze.height; y++)
    {
        for(int x = 0; x < imMaze.width; x++)
        {
            if((x == 0) || (x == (imMaze.width - 1)) || (y == 0) || (y == (imMaze.height - 1))){
                ImageDrawPixel(&imMaze, x, y, WHITE);
            }else
            {
                if((x%4 == 0) && (y%4 == 0))
                {
                    int chance = GetRandomValue(0, 3);
                    if(chance == 2)
                    {
                        ImageDrawPixel(&imMaze, x, y, WHITE);
                        mazePoints[mazePointsCounter] = (Point) {x, y};
                        mazePointsCounter++;
                    }
                }
            }
        }
    }

    Point directions[4] = {
        {0, -1},    // Up
        {0, 1},     // Down
        {-1, 0},    // Left
        {1, 0}      // Right
    };

    for(int i = 0; i < mazePointsCounter; i++)
    {
        Point currentPoint = mazePoints[i];
        Point currentDir = directions[GetRandomValue(0, 3)];
        currentPoint.x += currentDir.x;
        currentPoint.y += currentDir.y;

        while(GetImageColor(imMaze, currentPoint.x, currentPoint.y).r != 255)
        {
            ImageDrawPixel(&imMaze, currentPoint.x, currentPoint.y, WHITE);
            currentPoint.x += currentDir.x;
            currentPoint.y += currentDir.y;
        }
    }

    Texture texMaze = LoadTextureFromImage(imMaze);

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);
            DrawTextureEx(texMaze, (Vector2){ GetScreenWidth()/2 - texMaze.width*MAZE_DRAW_SCALE/2,
                GetScreenHeight()/2 - texMaze.height*MAZE_DRAW_SCALE/2 }, 0.0f, MAZE_DRAW_SCALE, WHITE);
            DrawRectangleLines(GetScreenWidth()/2 - texMaze.width*MAZE_DRAW_SCALE/2, GetScreenHeight()/2
                - texMaze.height*MAZE_DRAW_SCALE/2,MAZE_WIDTH*MAZE_DRAW_SCALE, MAZE_HEIGHT*MAZE_DRAW_SCALE, RED);

            for(int i = 0; i < mazePointsCounter; i++)
            {
                DrawRectangle(GetScreenWidth()/2 - texMaze.width*MAZE_DRAW_SCALE/2 + mazePoints[i].x*MAZE_DRAW_SCALE,
                    GetScreenHeight()/2 - texMaze.height*MAZE_DRAW_SCALE/2 + mazePoints[i].y*MAZE_DRAW_SCALE,
                    MAZE_DRAW_SCALE, MAZE_DRAW_SCALE, SKYBLUE);
            }
            //DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
            DrawFPS(10, 10);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}