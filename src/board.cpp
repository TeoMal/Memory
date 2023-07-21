#include "board.hpp"
#include "../include/raygui.h"
board::board(int size){
        this->size=size;
        this->score=0;
        grid=new int*[size];
        for(int i=0;i<size;i++){
            grid[i]=new int[size];
            for(int j=0;j<size;j++){
                grid[i][j]=0;
            }
        }
        switch(this->size){
            case 3:
                spacing={25,25};
                sizing={200,82};
            break;
            case 4:
                spacing={33,33};
                sizing={150,50};
            break;
            case 5:
                spacing={25,25};
                sizing={120,40};
            break;
        }
};
board::~board(void){
    for(int i=0;i<size;i++){
        delete[] grid[i];
    }
    delete[] grid;
}

void board::shuffle(int n){
    int total_elements = size * size;
    int* all_numbers = new int[total_elements];
    for (int i = 0; i < total_elements; ++i) {
        all_numbers[i] = i + 1;
    }

    // Step 2: Shuffle the list of numbers using the Fisher-Yates shuffle algorithm
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(all_numbers, all_numbers + total_elements, g);

    // Step 3: Allocate memory for the 2D array and fill it with the shuffled numbers
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if(all_numbers[i * size + j]<=n){
                grid[i][j] = all_numbers[i * size + j];
            }
        }
    }

    // Step 4: Clean up the memory used for all_numbers array
    delete[] all_numbers;
}

State board::draw(void){
    Vector2 offset={100,100};
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            if(grid[i][j]!=0){
                GuiButton({offset.x+i*(spacing.x+sizing.x),offset.y+j*(spacing.y+sizing.y),sizing.x,sizing.y},std::to_string(grid[i][j]).c_str());
            }
            else{
                GuiButton({offset.x+i*(spacing.x+sizing.x),offset.y+j*(spacing.y+sizing.y),sizing.x,sizing.y},"");
            }
        }
    }
    if(GuiButton({750,10,100,75},"Menu")){
        return MENU;
    }
    else{
        return GAME;
    }
}