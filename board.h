#ifndef BOARD_H
#define BOARD_H

struct position_s
{
    int x;
    int y;
};
typedef struct position_s position;

struct piece_s {
    char col;
    position pos;
    char ori;
};
typedef struct piece_s piece;

// Couleur: "I" pour case vide a remplacer par Null,  puis rot : 0 bloc plein 1-4 position coin triangle -1 case vide
struct element_s
{
    char col;
    int rot;
};
typedef struct element_s element;

struct grid_s
{
    element** m; // matice applatie de pointeur :3
    int nbx;
    int nby;
};
typedef struct grid_s grid;

struct board {
    piece* p;
    grid g;
};


#endif
