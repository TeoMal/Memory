#include "board.hpp"
#include "../include/raygui.h"
board::board(int size){
        this->size=size;
        this->score=0;
        this->correct=LoadSound("assets/correct.mp3");
        this->wrong=LoadSound("assets/fail.mp3");
        grid=new int*[size];
        this->next_number=1;
        for(int i=0;i<size;i++){
            grid[i]=new int[size];
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
    this->goal=n;
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
            else{
                grid[i][j]=0;
            }
        }
    }

    // Step 4: Clean up the memory used for all_numbers array
    delete[] all_numbers;
}

void board::draw(State &cur_state){
    Vector2 offset={100,100};
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            if(grid[i][j]!=0){
                if(cur_state==VISIBLE){
                    GuiButton({offset.x+i*(spacing.x+sizing.x),offset.y+j*(spacing.y+sizing.y),sizing.x,sizing.y},std::to_string(grid[i][j]).c_str());
                }
                else if(cur_state==BLIND){
                    if(GuiButton({offset.x+i*(spacing.x+sizing.x),offset.y+j*(spacing.y+sizing.y),sizing.x,sizing.y},"")){
                        if(grid[i][j]==next_number){
                            PlaySound(correct);
                            if(next_number==goal){
                                if(goal==size*size){
                                    cur_state=WON;
                                    return;
                                }
                                cur_state=VISIBLE;
                                this->shuffle(goal+1);
                                next_number=1;
                                score++;
                                return;
                            }
                            next_number++;
                            grid[i][j]=0;
                        }    
                        else{
                            PlaySound(wrong);
                            cur_state=LOST;
                            return;
                        }
                    }
                }
            }
            
            
        }
    }
    GuiButton({50,10,200,75},TextFormat("Score: %i",score));
    if(GuiButton({400,10,100,75},"Ready")){
        cur_state= BLIND;
    }
    if(GuiButton({750,10,100,75},"Menu")){
        cur_state = MENU;
    }
   
}