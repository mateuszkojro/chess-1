//
// Created by piotr on 28.06.2020.
//

#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H
#define BLACK true
#define WHITE false
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
        king_position[0] = 4;
        grid[5] = new piece('b', BLACK);
        grid[6] = new piece('n', BLACK);
        grid[7] = new piece('r', BLACK);
        for (int i = 8; i < 16; i++) grid[i] = new piece('p', BLACK);


        //WHITE
        grid[56] = new piece('r', WHITE);
        grid[57] = new piece('n', WHITE);
        grid[58] = new piece('b', WHITE);
        grid[59] = new piece('q', WHITE);
        grid[60] = new piece('k', WHITE);
        king_position[1] = 60;
        grid[61] = new piece('b', WHITE);
        grid[62] = new piece('n', WHITE);
        grid[63] = new piece('r', WHITE);

        for (int i = 48; i < 56; i++) grid[i] = new piece('p', WHITE);

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

    board(const board &old) {
        grid = new piece[64];
        king_position[0] = old.king_position[0];
        king_position[1] = old.king_position[1];
        for (int i = 0; i < 64; i++) grid[i] = old.grid[i];

        for(auto &i:old.list_of_moves)list_of_moves.push_back(i);


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
    board&operator = (const board &old){
        king_position[0] = old.king_position[0];
        king_position[1] = old.king_position[1];
        for (int i = 0; i < 64; i++) grid[i] = old.grid[i];

        for(auto &i:old.list_of_moves)list_of_moves.push_back(i);


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
return *this;

    }

    ~board() {
        delete[] grid;
    }

    void pvp();

    void pvc(int deepth, bool player_s_color);



    void show();

    int move(bool color);

    double evaluate();

    void admin();

    void admin_l(std::string temp);

    array castle(bool color);

    double standard_move(mov suspect, bool color, int deepth);

    double specjal_moves(mov suspect, bool color, int deepth);

    array upgrade(bool color, int position);

    array en_passant(bool color, int position);

    mov bip(bool color, int deepth);

    double do_the_move(mov suspect, bool color, int deepth);

    mov bip(bool color, int deepth, int number_of_threads);

    double minmax(int deep, bool color_now, double alpha, double beta);

    void array_of_possible(int position, array &all_of_possible_moves);

    bool possible(int position, int go_to);

    bool check(int position);

    void cvc(bool color, int time_2_move, int time_2_w8,std::string location, bool who_on_top, int deepth_for_bip);
    void cc();
};


#endif //CHESS_BOARD_H
