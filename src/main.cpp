
#define RAYGUI_IMPLEMENTATION
#include "../include/raylib.h"
#include "../include/raygui.h"
#include "../styles/jungle/jungle.h"
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 900;
    const int screenHeight = 500;
    InitWindow(screenWidth, screenHeight, "Memory Game");
    Texture2D background=LoadTexture("assets/background.png");
    GuiLoadStyleJungle();
    GuiSetStyle(DEFAULT, TEXT_SIZE, 30);
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground({255, 255, 255, 255});
            DrawTexture(background, 0, 0, WHITE);
            if(GuiButton({ 300, 25, 300, 120 }, "Easy")){

            }
            if(GuiButton({ 300, 170, 300, 120 }, "Medium")){

            }
            if(GuiButton({ 300, 315, 300, 120 }, "Hard")){

            }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    CloseWindow();        // Close window and OpenGL context
    
    return 0;
}