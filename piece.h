//
// Created by piotr on 28.06.2020.
//

#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H


#include <string>
#include <vector>
#include "mov.h"


class piece {//0 białe i czarne
public:
    char emblem;
    bool is_moved;
    bool color;

    piece() {

        emblem = '*';
        is_moved = false;
        color = false;
    };

    piece(char em, bool col) {
        emblem = em;
        is_moved = false;
        color = col;
    };
    piece(char em, bool col, bool moved) {
        emblem = em;
        is_moved = moved;
        color = col;
    };

    piece(bool x) {
        int a = rand() % 12;
        switch (a) {
            case 0:
                emblem = 'p';
                break;
            case 1:
                emblem = 'n';
                break;
            case 2:
                emblem = 'k';
                break;
            case 3:
                emblem = 'q';
                break;
            case 4:
                emblem = 'b';
                break;
            case 5:
                emblem = 'r';
                break;
            default:
                emblem = '*';
                break;

        }
        if (a % 2 == 1) color = true;
        else color = false;
        is_moved = false;


    };

    //virtual int conditions() = 0;

    piece &operator=(piece *a);

};

#endif //CHESS_PIECE_H
