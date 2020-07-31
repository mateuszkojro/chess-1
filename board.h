//
// Created by piotr on 28.06.2020.
//

#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H


#include <vector>
#include "piece.h"
#include "mov.h"
#include "compare.h"

class board { //0 białe i czarne
public:
    int king_position[2];
    piece *grid;
    std::vector<std::string> list_of_moves;

    board() {
        grid = new piece[64];

        //black
        grid[0] = new piece('r', true);

        grid[1] = new piece('n', true);
        grid[2] = new piece('b', true);
        grid[3] = new piece('q', true);
        grid[4] = new piece('k', true);
        king_position[0]=4;
        grid[5] = new piece('b', true);
        grid[6] = new piece('n', true);
        grid[7] = new piece('r', true);
        for (int i = 8; i < 16; i++) grid[i] = new piece('p', true);


        //white
        grid[56] = new piece('r', false);
        grid[57] = new piece('n', false);
        grid[58] = new piece('b', false);
        grid[59] = new piece('q', false);
        grid[60] = new piece('k', false);
        king_position[1]=60;
        grid[61] = new piece('b', false);
        grid[62] = new piece('n', false);
        grid[63] = new piece('r', false);

        for (int i = 48; i < 56; i++) grid[i] = new piece('p', false);

    }

    board(bool) {
        grid = new piece[64];

        for (int i = 0; i < 64; i++) {
            grid[i] = new piece(true);


        }


        grid[13] = new piece('q', false);
    };

    ~board() {
        delete[] grid;
    }

    void pvp();

    void pvc();

    void cvc(int deep);

    void show();

    int move(bool color);

    double evaluate();

    void admin();

    void admin_l(std::string temp);

    arr castle(bool color);

    arr stuff_with_lil_ones(bool color, int position);

    mov bip(bool color, int deepth);

    double minmax(int deep, bool color_to_start, bool color_now);
};


#endif //CHESS_BOARD_H
