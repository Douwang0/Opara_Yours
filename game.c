#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "board.h"
#include "game.h"
#include "input.h"
#include <assert.h>

// Aléa : tire aléatoirement entre 0 et int_max-1
int random_int(int int_max) {
    int n = rand() ;
    return n % int_max ;
}

void randomise_pieces(piece* pieces, int NB_PIECES,grid board){
    char orientations[4] = {'N','S','E','W'};
    char sens[2] = {'V','H'};
    for(int i = 0; i<NB_PIECES; i++){
        switch (pieces[i].col){
        case 'B':
        case 'Y':
        case 'W':
            pieces[i].ori = orientations[random_int(4)];
            break;
        case 'R':
            pieces[i].ori = sens[random_int(2)];
            break;
        }
        position random_position = {random_int(board.nbx),random_int(board.nby)};
        pieces[i].pos = random_position;
    }
}

bool e_in_list(char e, char* list, int len){
    for(int i =0; i<len;i++){
        if(list[i] == e){return true;}
    }
    return false;
}

int compute_angle(int a, int forme) {
    //                          0°   90°  180°  270°
    static const int table[5][4] = {
        /* 0: block        */ { 180, 270,   0,  90 },
        /* 1: top-left     */ { 180,   0, 270,  90 },
        /* 2: top-right    */ { 270, 180,   0,  90 },
        /* 3: bottom-left  */ { 180, 270,  90,   0 },
        /* 4: bottom-right */ {  90, 270,   0, 180 },
    };

    a = ((a % 360) + 360) % 360;

    return table[forme][a / 90];
}

char *colors_to_output(char colors[], int n) {
    int r = 0, y = 0, b = 0, w = 0;

    for (int i = 0; i < n; i++) {
        if (colors[i] == 'R') r = 1;
        else if (colors[i] == 'Y') y = 1;
        else if (colors[i] == 'B') b = 1;
        else if (colors[i] == 'W') w = 1;
    }

    if (!w) {
        if (r && y && b) return "N";
        if (r && y)      return "O";
        if (b && y)      return "V";
        if (r && b)      return "P";
        if (r)           return "R";
        if (y)           return "Y";
        if (b)           return "B";
        return "I";
    } else {
        if (r && y && b) return "G";
        if (r && y)      return "OC";
        if (b && y)      return "VC";
        if (r && b)      return "PC";
        if (r)           return "PI";
        if (y)           return "JC";
        if (b)           return "BC";
        return "W";
    }
}

ray cast_ray(grid board, ray rwar, int COLS, int ROWS){ // debut hors de la grille, fin hors de la grille
    // Entrée dans la grille
    switch (rwar.angle){
            case 0:
                rwar.pos.x++;
                break;
            case 90:
                rwar.pos.y--;
                break;
            case 180:
                rwar.pos.x--;
                break;
            case 270:
                rwar.pos.y++;
                break;
    }

    char colors[4] = {'I','I','I','I'};
    
    while (!(rwar.pos.x < 0 || rwar.pos.x >= COLS || rwar.pos.y < 0 || rwar.pos.y >= ROWS)){
        
        element current = access(rwar.pos.x,rwar.pos.y,board);

        // Ajout de couleur
        if (current.col != 'I' && e_in_list(current.col, colors, 4) == false){
            int i = 0;
            while(colors[i] != 'I'){
                i++;
            }
            assert(i<4);
            colors[i] = current.col;
        }

        // Rotation du rayon
        if (current.rot != -1){
            rwar.angle = compute_angle(rwar.angle,current.rot);
        }

        switch (rwar.angle){
        case 0:
            rwar.pos.x++;
            break;
        case 90:
            rwar.pos.y--;
            break;
        case 180:
            rwar.pos.x--;
            break;
        case 270:
            rwar.pos.y++;
            break;
        }

    }
    
    rwar.col = colors_to_output(colors,4);

    return rwar;

}

ray int_to_ray(int entry, int COLS, int ROWS){ // Crée un rayon hors de la liste
    ray rwar;
    rwar.col = "I";
    entry--; // eww humans
    assert(entry>=0 && entry < (2*COLS + 2*ROWS));
    if(entry < COLS){
        rwar.angle = 270;
        rwar.pos.x = entry;
        rwar.pos.y = -1;
    } else if (entry < (COLS + ROWS)){
        rwar.angle = 180;
        rwar.pos.x = COLS;
        rwar.pos.y = entry - COLS;
    } else if (entry < (2*COLS + ROWS)){
        rwar.angle = 90;
        rwar.pos.x = (COLS-1) - (entry - (COLS + ROWS));
        rwar.pos.y = ROWS;
    } else {
        rwar.angle = 0;
        rwar.pos.x = -1;
           rwar.pos.y = (ROWS-1) - (entry - (2*COLS + ROWS));;
    }
    return rwar;
}

int ray_to_int(ray rwar, int COLS, int ROWS){
    int entry;

    switch (rwar.angle) {
        case 90:
            assert(rwar.pos.y == -1 && rwar.pos.x >= 0 && rwar.pos.x < COLS);
            entry = rwar.pos.x;
            break;
        case 0:
            assert(rwar.pos.x == COLS && rwar.pos.y >= 0 && rwar.pos.y < ROWS);
            entry = COLS + rwar.pos.y;
            break;
        case 270:
            assert(rwar.pos.y == ROWS && rwar.pos.x >= 0 && rwar.pos.x < COLS);
            entry = COLS + ROWS + ((COLS - 1) - rwar.pos.x);
            break;
        case 180:
            assert(rwar.pos.x == -1 && rwar.pos.y >= 0 && rwar.pos.y < ROWS);
            entry = 2*COLS + ROWS + ((ROWS - 1) - rwar.pos.y);
            break;
    }

    return entry + 1; // back to back for humans
}

void ask(int entry,grid board,int COLS,int ROWS){

    ray rwar;
    rwar = int_to_ray(entry,COLS,ROWS);
    rwar = cast_ray(board,rwar,COLS,ROWS);
    int end;
    end = ray_to_int(rwar,COLS,ROWS);
    char* color;
    color = rwar.col;
    display_answer(end, color);
}

bool compare_pieces(piece piece1, piece piece2){ // If one of the orientations if 0, ignores this field
    if (piece1.col != piece2.col){
        return false;
    } else if (piece1.pos.x != piece2.pos.x){
        return false;
    } else if (piece1.pos.y != piece2.pos.y){
        return false;
    } else if ((piece1.ori != 0) && (piece2.ori != 0) && (piece1.ori != piece2.ori)){
        return false;
    }
    return true;
}

bool piece_in_list(piece miaw, piece* pieces, int nb_pieces){
    for(int i = 0; i<nb_pieces;i++){
        if(compare_pieces(miaw, pieces[i])){
            return true;
        }
    }   
    return false; 
}

void play(int difficulty) {
    int score = 0 ;
    int nb_questions = 0;
    bool unfold = false; // False -> unfolds y-axis, True -> x-axis
    
    int ROWS = 8;
    int COLS = 10;
    grid board = generate_empty_grid(COLS, ROWS);

    piece pieces[6] = {
    {'R',{0,0},'H'},{'Y',{0,0},'N'},{'B',{0,0},'N'},{'W',{0,0},'N'},{'W',{0,0},'N'},{'w',{0,0},0}
    };
    piece found_pieces[6];
    int NB_PIECES = 6;
    int NB_FOUND_PIECES = 0;


    randomise_pieces(pieces,NB_PIECES,board);
    int count = 0;
    while(!try_pieces(pieces,NB_PIECES,ROWS,COLS)){
        randomise_pieces(pieces,NB_PIECES,board);
        count++;
    }

    fill_grid(pieces,NB_PIECES,board);


    bool done = false;

    while (!done)
    {
        if (nb_questions >= difficulty){
            if(unfold){
                ROWS *= 2;
            } else {
                COLS *= 2;
            }
            unfold = !unfold;
            nb_questions = 0;
        }
        int question ;
        char color ;
        int x ;
        int y ;
        char orientation ;
        int rep = read_input(COLS,ROWS, &question, &color, &x, &y, &orientation) ;

        switch (rep)
        {
        case 0:
            reveal_grid(NB_PIECES,pieces);
            done = true;
            break;
        
        case 1:
            ask(question,board,COLS,ROWS);
            nb_questions++;
            score++;
            break;
        case 2:
            piece miaw = {color, (position){x%COLS,y%ROWS}, orientation};
            bool check = piece_in_list(miaw,pieces,NB_PIECES);
            display_proposition(check);
            if(check){
                if(!piece_in_list(miaw,found_pieces,NB_FOUND_PIECES)){
                    assert(NB_FOUND_PIECES<NB_PIECES);
                    found_pieces[NB_FOUND_PIECES] = miaw;
                    NB_FOUND_PIECES += 1;
                }
            }else{
                score += 100;
            }
            if(NB_FOUND_PIECES == NB_PIECES){
                done = true;
            }

        }

    }

    printf("Score : %d \n",score);

    free(board.m);
}