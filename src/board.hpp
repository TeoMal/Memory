#include "../include/raylib.h"
#include <cstdlib>
#include <random>
#include <algorithm>
#include <iostream>
enum State{MENU,VISIBLE,BLIND,LOST,WON};
enum Difficulty{NONE,EASY,MEDIUM,HARD};
class board{
    private:
        int size;
        int **grid;
        int next_number,goal;
        Vector2 spacing,sizing;
        Sound correct,wrong;
    public:
        int score;
        board(int);
        ~board(void);
        void shuffle(int);
        void draw(State &);
};
