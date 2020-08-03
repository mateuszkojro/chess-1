//
// Created by piotr on 28.06.2020.
//

#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H
#define BLACK true

#include <vector>

#include "piece.h"
#include "mov.h"
#include "compare.h"

class board { //0 białe i czarne
public:
    int king_position[2];
    piece *grid;
    std::vector<std::string> list_of_moves;
    dynamic_arr<dynamic_arr<array>> full_board_of_moves_4_bishop;
    dynamic_arr<dynamic_arr<array>> full_board_of_moves_4_rook;


    board() {
        grid = new piece[64];

        //black
        grid[0] = new piece('r', BLACK);
        grid[1] = new piece('n', BLACK);
        grid[2] = new piece('b', BLACK);
        grid[3] = new piece('q', BLACK);
        grid[4] = new piece('k', BLACK);
        king_position[0]=4;
        grid[5] = new piece('b', BLACK);
        grid[6] = new piece('n', BLACK);
        grid[7] = new piece('r', BLACK);
        for (int i = 8; i < 16; i++) grid[i] = new piece('p', BLACK);


        //WHITE
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

        full_board_of_moves_4_rook.size(64);
        full_board_of_moves_4_bishop.size(64);

        int ni, nj;
        for (int i = 0; i < 64; i++) {
            full_board_of_moves_4_bishop[i].size(4);
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

        for (int i = 0; i < 64; i++) {
            full_board_of_moves_4_rook[i].size(4);
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

    array castle(bool color);

    array stuff_with_lil_ones(bool color, int position);

    mov bip(bool color, int deepth);

    double minmax(int deep, bool color_to_start, bool color_now);

    array array_of_possible(int position);

    bool possible(int position, int go_to);

    array pin(int position);

    bool check(int position);
};


#endif //CHESS_BOARD_H
