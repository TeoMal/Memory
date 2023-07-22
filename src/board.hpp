#include "../include/raylib.h"
#include <cstdlib>
#include <random>
#include <algorithm>
#include <iostream>
enum State{MENU,VISIBLE,BLIND};
enum Difficulty{NONE,EASY,MEDIUM,HARD};
class board{
    private:
        int size;
        int **grid;
        Vector2 spacing,sizing;
    public:
        int score;
        board(int);
        ~board(void);
        void shuffle(int);
        void draw(State &);
};
