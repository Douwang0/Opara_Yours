#ifndef GAME_H
#define GAME_H
#include "board.h"

typedef struct ray_s
{
    position pos;
    int angle;
    char* col;
} ray ;

void play(int difficulty) ;


#endif
