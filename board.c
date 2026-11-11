#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "board.h"

// Constant pieces


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

grid generate_empty_grid(int nbx, int nby){
    grid g;
    element **m = malloc(sizeof(element*) * nbx * nby);
    for(int i = 0; i<nby;i++){
        for(int j = 0;j<nbx;j++){
            m[i*nbx + j] = NULL;
        }
    }
    g.m = m;
    g.nbx = nbx;
    g.nby = nby;
    return g;
};

element *get_template_piece()