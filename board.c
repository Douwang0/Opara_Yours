#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "board.h"

// Constant pieces, le code commence ligne 265 :3


const int piece_blue_east_height = 4;
const int piece_blue_east_width = 2;
const element piece_blue_east[4][2] = {
    {{'B', 3}, {'I', -1}},
    {{'B', 0}, {'B', 3}},
    {{'B', 0}, {'B', 1}},
    {{'B', 1}, {'I', -1}}
};
const position piece_blue_east_main_relative_position = {0,0};

const int piece_blue_north_height = 2;
const int piece_blue_north_width = 4;
const element piece_blue_north[2][4] = {
    {{'I', -1}, {'B', 4}, {'B', 3}, {'I', -1}},
    {{'B', 4}, {'B', 0}, {'B', 0}, {'B', 3}},
};
const position piece_blue_north_main_relative_position = {0,1};

const int piece_blue_west_height = 4;
const int piece_blue_west_width = 2;
const element piece_blue_west[4][2] = {
    {{'I', -1}, {'B', 4}},
    {{'B', 4}, {'B', 0}},
    {{'B', 2}, {'B', 0}},
    {{'I', -1}, {'B', 2}}
};
const position piece_blue_west_main_relative_position = {1,3};

const int piece_blue_south_height = 2;
const int piece_blue_south_width = 4;
const element piece_blue_south[2][4] = {
    {{'B', 2}, {'B', 0}, {'B', 0}, {'B', 1}},
    {{'I', -1}, {'B', 2}, {'B', 1}, {'I', -1}}
};
const position piece_blue_south_main_relative_position = {3,0};

const int piece_yellow_height = 2;
const int piece_yellow_width = 2;
const element piece_yellow[2][2] = {
    {{'Y', 2}, {'Y', 0}},
    {{'I', -1}, {'Y', 2}}
};
const position piece_yellow_main_relative_position = {1,0};

const element piece_yellow_west[2][2] = {
    {{'Y', 0}, {'Y', 1}},
    {{'Y', 1}, {'I', -1}}
};
const position piece_yellow_west_main_relative_position = {0,0};

const element piece_yellow_south[2][2] = {
    {{'Y', 3}, {'I', -1}},
    {{'Y', 0}, {'Y', 3}}
};
const position piece_yellow_south_main_relative_position = {0,1};

const element piece_yellow_east[2][2] = {
    {{'I', -1}, {'Y', 4}},
    {{'Y', 4}, {'Y', 0}}
};
const position piece_yellow_east_main_relative_position = {1,1};

const int piece_red_height = 1;
const int piece_red_width = 3;
const element piece_red[1][3] = {
    {{'R', 4}, {'R', 0}, {'R', 1}}
};
const position piece_red_main_relative_position = {1,0};

const int piece_red_vertical_height = 3;
const int piece_red_vertical_width = 1;
const element piece_red_vertical[3][1] = {
    {{'R', 3}},
    {{'R', 0}},
    {{'R', 2}}
};
const position piece_red_vertical_main_relative_position = {0,1};

const int piece_white_triangle_height = 2;
const int piece_white_triangle_width = 4;
const element piece_white_triangle[2][4] = {
    {{'I', -1}, {'W', 4}, {'W', 3}, {'I', -1}},
    {{'W', 4}, {'W', 0}, {'W', 0}, {'W', 3}}
};
const position piece_white_triangle_main_relative_position = {0,1};

const int piece_white_triangle_west_height = 4;
const int piece_white_triangle_west_width = 2;
const element piece_white_triangle_west[4][2] = {
    {{'I', -1}, {'W', 4}},
    {{'W', 4}, {'W', 0}},
    {{'W', 2}, {'W', 0}},
    {{'I', -1}, {'W', 2}}
};
const position piece_white_triangle_west_main_relative_position = {1,3};

const int piece_white_triangle_south_height = 2;
const int piece_white_triangle_south_width = 4;
const element piece_white_triangle_south[2][4] = {
    {{'W', 2}, {'W', 0}, {'W', 0}, {'W', 1}},
    {{'I', -1}, {'W', 2}, {'W', 1}, {'I', -1}}
};
const position piece_white_triangle_south_main_relative_position = {3,0};

const int piece_white_triangle_east_height = 4;
const int piece_white_triangle_east_width = 2;
const element piece_white_triangle_east[4][2] = {
    {{'W', 3}, {'I', -1}},
    {{'W', 0}, {'W', 3}},
    {{'W', 0}, {'W', 1}},
    {{'W', 1}, {'I', -1}}
};
const position piece_white_triangle_east_main_relative_position = {0,0};

const int piece_white_diamond_height = 2;
const int piece_white_diamond_width = 2;
const element piece_white_diamond[2][2] = {
    {{'w', 4}, {'w', 3}},
    {{'w', 2}, {'w', 1}}
};
const position piece_white_diamond_main_relative_position = {0,1};


void get_template(piece p, int* height, int* width, element** template, position* relative_main_position){
    // Default values, used when the colour or orientation is unknown
    *height = 0;
    *width = 0;
    *template = NULL;
    relative_main_position->x = 0;
    relative_main_position->y = 0;

    switch (p.col)
    {
    case 'R':
        switch (p.ori)
        {
        case 'V':
            *height = piece_red_vertical_height;
            *width = piece_red_vertical_width;
            *template = (element*)piece_red_vertical;
            *relative_main_position = piece_red_vertical_main_relative_position;
            break;
        case 'H':
            *height = piece_red_height;
            *width = piece_red_width;
            *template = (element*)piece_red;
            *relative_main_position = piece_red_main_relative_position;
            break;
        default:
            break;
        }
        break;
    case 'B':
        switch (p.ori)
        {
        case 'N':
            *height = piece_blue_north_height;
            *width = piece_blue_north_width;
            *template = (element*)piece_blue_north;
            *relative_main_position = piece_blue_north_main_relative_position;
            break;
        case 'S':
            *height = piece_blue_south_height;
            *width = piece_blue_south_width;
            *template = (element*)piece_blue_south;
            *relative_main_position = piece_blue_south_main_relative_position;
            break;
        case 'E':
            *height = piece_blue_east_height;
            *width = piece_blue_east_width;
            *template = (element*)piece_blue_east;
            *relative_main_position = piece_blue_east_main_relative_position;
            break;
        case 'W':
            *height = piece_blue_west_height;
            *width = piece_blue_west_width;
            *template = (element*)piece_blue_west;
            *relative_main_position = piece_blue_west_main_relative_position;
            break;
        default:
            break;
        }
        break;
    case 'Y':
        switch (p.ori)
        {
        case 'N':
            *height = piece_yellow_height;
            *width = piece_yellow_width;
            *template = (element*)piece_yellow;
            *relative_main_position = piece_yellow_main_relative_position;
            break;
        case 'S':
            *height = piece_yellow_height;
            *width = piece_yellow_width;
            *template = (element*)piece_yellow_south;
            *relative_main_position = piece_yellow_south_main_relative_position;
            break;
        case 'E':
            *height = piece_yellow_height;
            *width = piece_yellow_width;
            *template = (element*)piece_yellow_east;
            *relative_main_position = piece_yellow_east_main_relative_position;
            break;
        case 'W':
            *height = piece_yellow_height;
            *width = piece_yellow_width;
            *template = (element*)piece_yellow_west;
            *relative_main_position = piece_yellow_west_main_relative_position;
            break;
        default:
            break;
        }
        break;
    case 'W':
        switch (p.ori)
        {
        case 'N':
            *height = piece_white_triangle_height;
            *width = piece_white_triangle_width;
            *template = (element*)piece_white_triangle;
            *relative_main_position = piece_white_triangle_main_relative_position;
            break;
        case 'S':
            *height = piece_white_triangle_south_height;
            *width = piece_white_triangle_south_width;
            *template = (element*)piece_white_triangle_south;
            *relative_main_position = piece_white_triangle_south_main_relative_position;
            break;
        case 'E':
            *height = piece_white_triangle_east_height;
            *width = piece_white_triangle_east_width;
            *template = (element*)piece_white_triangle_east;
            *relative_main_position = piece_white_triangle_east_main_relative_position;
            break;
        case 'W':
            *height = piece_white_triangle_west_height;
            *width = piece_white_triangle_west_width;
            *template = (element*)piece_white_triangle_west;
            *relative_main_position = piece_white_triangle_west_main_relative_position;
            break;
        default:
            break;
        }
        break;
    case 'w':
        *height = piece_white_diamond_height;
        *width = piece_white_diamond_width;
        *template = (element*)piece_white_diamond;
        *relative_main_position = piece_white_diamond_main_relative_position;
        break;
    default:
        break;
    }
}

// le code commence ici :3

element access(int x, int y, grid board){
    return board.m[(y%board.nby)*board.nbx + (x%board.nbx)];
}

grid generate_empty_grid(int nbx, int nby){
    grid g;
    element *m = malloc(sizeof(element) * nbx * nby);
    element miaw = {'I', -1};
    for(int i = 0; i<nby;i++){
        for(int j = 0;j<nbx;j++){
            m[i*nbx + j] = miaw;
        }
    }
    g.m = m;
    g.nbx = nbx;
    g.nby = nby;
    return g;
};

bool place_in_grid(grid board, piece p){ // Place piece en place et renvoie false si probleme de placement
    element miaw = {'I', -1};
    int height;
    int width;
    element* template;
    position relative_main_position;

    get_template(p, &height, &width, &template, &relative_main_position);
    if (height <= 0 || width <= 0 || template == NULL) {
        return false;
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            position pos;
            pos.x = p.pos.x - relative_main_position.x + j;
            pos.y = p.pos.y - relative_main_position.y + i;

            if (pos.x < 0 || pos.y < 0 || pos.x >= board.nbx || pos.y >= board.nby) {
                return false;
            }

            element* current = &board.m[pos.y * board.nbx + pos.x];
            if (current->col != miaw.col || current->rot != miaw.rot) {
                return false;
            }

            current->col = template[i*width+j].col;
            current->rot = template[i*width+j].rot;
        }
    }

    return true;
}

bool try_pieces(piece* pieces,int nb_pieces, int rows, int cols){// Revoie le succes du placement des pieces dans une grille vide
    grid board = generate_empty_grid(cols,rows);
    for(int i = 0;i<nb_pieces;i++){
        if(!place_in_grid(board,pieces[i])){
            return false;
        }
    }
    free(board.m);
    return true;
}

void fill_grid(piece* pieces, int nb_pieces, grid board){ //Remplie la grille en place
    for(int i = 0;i<nb_pieces;i++){
        place_in_grid(board,pieces[i]);
    }
}

void display_grid(grid board, int COLS, int ROWS){
    #define FILLER '.'
    for(int i = 0; i<ROWS;i++){
        for (int j = 0; j < COLS; j++){
            char c = access(j,i,board).col;
            if (c == 'I'){
                c = FILLER;
            }
            printf("%c ",c);
        }
        printf("\n");
    }
}