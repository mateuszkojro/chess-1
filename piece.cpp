//
// Created by piotr on 28.06.2020.
//
#ifdef _WIN32

#include <conio.h>

#endif

#include <cstdio>
#include "piece.h"
#include "mov.h"
#include "compare.h"
#include "board.h"



void b_fun(dynamic_arr<dynamic_arr<array>> &full_board_of_moves_4_bishop) {
    int ni, nj;
    for (int i = 0; i < 64; i++) {
        ni = i / 8;
        nj = i % 8;
        while (ni > 0 && nj < 7) {
            ni--;
            nj++;
            full_board_of_moves_4_bishop[i][0].push_back(ni * 8 + nj);

        }


        ni = i / 8;
        nj = i % 8;
        while (ni < 7 && nj < 7) {
            ni++;
            nj++;
            full_board_of_moves_4_bishop[i][1].push_back(ni * 8 + nj);

        }

        ni = i / 8;
        nj = i % 8;
        while (ni < 7 && nj > 0) {
            ni++;
            nj--;
            full_board_of_moves_4_bishop[i][2].push_back(ni * 8 + nj);

        }

        ni = i / 8;
        nj = i % 8;
        while (ni > 0 && nj > 0) {
            ni--;
            nj--;
            full_board_of_moves_4_bishop[i][3].push_back(ni * 8 + nj);

        }

    }

}

void r_fun(dynamic_arr<dynamic_arr<array>> &full_board_of_moves_4_rook) {
    int ni;
    for (int i = 0; i < 64; i++) {
        ni = i;
        while (ni / 8 > 0) {
            ni -= 8;
            full_board_of_moves_4_rook[i][0].push_back(ni);
        }

        ni = i;
        while (ni % 8 < 7) {
            ni++;
            full_board_of_moves_4_rook[i][1].push_back(ni);
        }

        ni = i;
        while (ni / 8 < 7) {
            ni += 8;
            full_board_of_moves_4_rook[i][2].push_back(ni);
        }

        ni = i;
        while (ni % 8 > 0) {
            ni--;
            full_board_of_moves_4_rook[i][3].push_back(ni);
        }

    }


}


piece &piece::operator=(piece *a) {
    emblem = a->emblem;
    is_moved = a->is_moved;
    color = a->color;


    return *this;
}






