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
    element* m; // matice applatie d'élements :3
    int nbx;
    int nby;
};
typedef struct grid_s grid;

element access(int x, int y, grid board);
grid generate_empty_grid(int nbx, int nby);
bool try_pieces(piece* pieces,int nb_pieces, int rows, int cols);
void fill_grid(piece* pieces, int nb_pieces, grid board);
void display_grid(grid board, int COLS, int ROWS);
#endif
