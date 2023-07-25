
#define RAYGUI_IMPLEMENTATION
#include "./board.hpp"
#include "../include/raygui.h"
#include "../styles/jungle/jungle.h"
Difficulty DrawMenu(void);
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 900;
    const int screenHeight = 500;
    InitWindow(screenWidth, screenHeight, "Memory Game");
    InitAudioDevice();
    Texture2D background=LoadTexture("assets/background.png");
    State cur_state=MENU;
    Difficulty cur_diff=NONE;
    board *b;
    Music background_s = LoadMusicStream("assets/background.mp3");
    SetMusicVolume(background_s, 0.3f);
    PlayMusicStream(background_s);
    GuiLoadStyleJungle();
    GuiSetStyle(DEFAULT, TEXT_SIZE, 30);
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        UpdateMusicStream(background_s);
        

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground({255, 255, 255, 255});
            DrawTexture(background, 0, 0, WHITE);
            if(GuiButton({ 750, 425, 100, 50 }, "Exit")){
                EndDrawing();
                break;
            }
            if(cur_state==MENU){
                //Menu State
                cur_diff=DrawMenu();
                if(cur_diff!=NONE){
                    cur_state=VISIBLE;
                    switch (cur_diff)
                    {
                    case EASY:
                        b=new board(3);
                        b->shuffle(3);
                        break;
                    case MEDIUM:
                        b=new board(4);
                        b->shuffle(4);
                        break;
                    case HARD:
                        b=new board(5);
                        b->shuffle(5);
                        break;
                    default:
                        break;
                    }
                }    
            }
            else if(cur_state==VISIBLE || cur_state==BLIND){
                //Game State
                b->draw(cur_state);
                if(cur_state==MENU){
                    delete b;
                }
            }
            else if(cur_state==WON){
                //Won State
                GuiButton({300,100,300,100},"You Won!");
                if(GuiButton({300,250,300,100},"Play Again")){
                    cur_state=MENU;
                }
            }
            else if(cur_state==LOST){
                //Lost State
                GuiButton({300,100,300,100},"You Lost!");
                if(GuiButton({300,250,300,100},"Play Again")){
                    cur_state=MENU;
                }
            }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    CloseWindow();        // Close window and OpenGL context
    
    return 0;
}

Difficulty DrawMenu(void){
    if(GuiButton({ 300, 25, 300, 120 }, "Easy")){

        return EASY;
    }
    else if(GuiButton({ 300, 170, 300, 120 }, "Medium")){

        return MEDIUM;
    }
    else if(GuiButton({ 300, 315, 300, 120 }, "Hard")){
    
        return HARD;
    }
    else{
        return NONE;
    }
}