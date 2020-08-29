////0 białe i czarne


#include <iostream>
#include <fstream>
#include <cstdio>

#ifdef _WIN32

#include <conio.h>
#include <windows.h>
#include <chrono>
#include <mutex>
#include <thread>

void w8(unsigned milliseconds) {
    Sleep(milliseconds);
}

void clear() {
    system("cls");

}

#else
//
// Created by piotr on 28.06.2020.
#include <unistd.h>

void w8(unsigned milliseconds){


    usleep(milliseconds * 1000); // takes microseconds
}
void clear(){}
char getch(){
    char a;
    printf("it's 4 getch");
    std::cin>>a;
    return a;
}

#endif

#include "board.h"


#define BLACK true
#define WHITE false

#define UNDER_CONTROLL false  //znaczy to jest na odwrót

int ctn(char x, char y) {
    return ((static_cast<int>(x) - 56) * (-8)) + (static_cast<int>(y) - 97);
}

bool binary(int check, int tab[8]) {
    int l = 0, r = 7;

    while (l <= r) {
        int m = l + (r - l) / 2;
        if (tab[m] == check)
            return true;

        if (tab[m] < check)
            l = m + 1;
        else
            r = m - 1;
    }
    return false;
}

bool binary(int check, array tab) {
    int l = 0, r = tab.size();

    while (l <= r) {
        int m = l + (r - l) / 2;
        if (tab[m] == check)
            return true;

        if (tab[m] < check)
            l = m + 1;
        else
            r = m - 1;
    }
    return false;
}

int max(dynamic_arr<mov> row) {
    int k = 0;
    for (int i = 1; i < row.size(); ++i) {
        if (row[i].eva > row[k].eva) k = i;
    }
    return k;
}

int min(dynamic_arr<mov> row) {
    int k = 0;
    for (int i = 1; i < row.size(); ++i) {
        if (row[i].eva < row[k].eva) k = i;
    }
    return k;
}

void board::show() {
    double eva = this->evaluate();
    //24  ...###...###...### ###...###...###...###...
    //std::string grid_background_lite = "8..###...###...###...###...###...###...###...###...###...###...###...###7##...###...###...###...###...###...###...###...###...###...###...###...6..###...###...###...###...###...###...###...###...###...###...###...###5##...###...###...###...###...###...###...###...###...###...###...###...4..###...###...###...###...###...###...###...###...###...###...###...###3##...###...###...###...###...###...###...###...###...###...###...###...2..###...###...###...###...###...###...###...###...###...###...###...###1##...###...###...###...###...###...###...###...##a..b##c..d##e..f##g..h";
    std::string grid_background = "8  ...   ...   ...   ...   ...   ...   ...   ...   ...   ...   ...   ...7..   ...   ...   ...   ...   ...   ...   ...   ...   ...   ...   ...   6  ...   ...   ...   ...   ...   ...   ...   ...   ...   ...   ...   ...5..   ...   ...   ...   ...   ...   ...   ...   ...   ...   ...   ...   4  ...   ...   ...   ...   ...   ...   ...   ...   ...   ...   ...   ...3..   ...   ...   ...   ...   ...   ...   ...   ...   ...   ...   ...   2  ...   ...   ...   ...   ...   ...   ...   ...   ...   ...   ...   ...1..   ...   ...   ...   ...   ...   ...   ...   ..a  b..c  d..e  f..g  h";
    for (int i = 0; i < 8; i++) {

        for (int j = 0; j < 8; j++) {
            if (grid[i * 8 + j].emblem != '*') {

                if (!grid[i * 8 + j].color) grid_background[(i * 72) + 24 + j * 3 + 1] = grid[i * 8 + j].emblem;

                else grid_background[(i * 72) + 24 + j * 3 + 1] = grid[i * 8 + j].emblem - 32;
            }
        }
        printf("\n");

    }

    for (int i = 0; i < grid_background.size(); i++) {

        if (i == 23)printf("%c  %f\n", grid_background[i], eva);
        else if (i % 24 == 23)printf("%c \n", grid_background[i]);
        else printf("%c ", grid_background[i]);

    }

    for (int i = 0; i < list_of_moves.size(); i++) {
        printf("%d.\t", i);
        for (char k:list_of_moves[i]) printf("%c", k);

    }
    printf("\n");

}

int board::move(bool color) {


    std::string holder;
    while (1 < 2) {
        printf(": ");
        std::cin >> holder;

        switch (holder.size()) {
            case 3: {
                if (color) {
                    if (grid[0].emblem == 'r' && grid[1].emblem == '*' && grid[2].emblem == '*' &&
                        grid[3].emblem == '*' && grid[4].emblem == 'k')
                        if (grid[0].is_moved == 0 && grid[4].is_moved == 0) {
                            for (int i = 0; i < 64; i++) {
                                if (grid[i].color != color)
                                    if (this->possible(i, 0) || this->possible(i, 1) ||
                                        this->possible(i, 2) || this->possible(i, 3) ||
                                        this->possible(i, 4))
                                        break;
                                if (i == 63) {
                                    grid[0] = new piece();
                                    grid[2] = new piece('k', color, 1);
                                    grid[3] = new piece('r', color, 1);
                                    grid[4] = new piece();


                                    list_of_moves.back().push_back('o');
                                    list_of_moves.back().push_back('-');
                                    list_of_moves.back().push_back('o');
                                    list_of_moves.back().push_back('-');
                                    list_of_moves.back().push_back('o');
                                    list_of_moves.back().push_back('\n');

                                    return 0;
                                }
                            }
                        }
                } else {
                    if (grid[56].emblem == 'r' && grid[57].emblem == '*' && grid[58].emblem == '*' &&
                        grid[59].emblem == '*' && grid[60].emblem == 'k')
                        if (grid[56].is_moved == 0 && grid[60].is_moved == 0) {
                            for (int i = 0; i < 64; i++) {
                                if (grid[i].color != color)
                                    if (this->possible(i, 56) || this->possible(i, 57) ||
                                        this->possible(i, 58) || this->possible(i, 59) ||
                                        this->possible(i, 60))
                                        break;
                                if (i == 63) {
                                    grid[56] = new piece();
                                    grid[58] = new piece('k', color, 1);
                                    grid[59] = new piece('r', color, 1);
                                    grid[60] = new piece();
                                    std::string all_of_possible_moves;
                                    all_of_possible_moves.push_back('o');
                                    all_of_possible_moves.push_back('-');
                                    all_of_possible_moves.push_back('o');
                                    all_of_possible_moves.push_back('-');
                                    all_of_possible_moves.push_back('o');
                                    all_of_possible_moves.push_back('\t');
                                    list_of_moves.push_back(all_of_possible_moves);
                                    return 0;
                                }
                            }
                        }

                }
            }
                printf("opsie illegal move!");
                break;
            case 2: {
                if (color) {
                    if (grid[4].emblem == 'k' && grid[5].emblem == '*' && grid[6].emblem == '*' &&
                        grid[7].emblem == 'r')
                        if (grid[7].is_moved == 0 && grid[4].is_moved == 0) {
                            for (int i = 0; i < 64; i++) {
                                if (grid[i].color != color)
                                    if (this->possible(i, 4) || this->possible(i, 5) ||
                                        this->possible(i, 6) || this->possible(i, 7))
                                        break;
                                if (i == 63) {
                                    grid[7] = new piece();
                                    grid[4] = new piece();
                                    grid[5] = new piece('r', color, true);
                                    grid[6] = new piece('k', color);

                                    list_of_moves.back().push_back('o');
                                    list_of_moves.back().push_back('-');
                                    list_of_moves.back().push_back('o');
                                    list_of_moves.back().push_back('\n');
                                    return 0;
                                }
                            }
                        }
                } else {
                    if (grid[60].emblem == 'k' && grid[61].emblem == '*' && grid[62].emblem == '*' &&
                        grid[63].emblem == 'r')
                        if (grid[63].is_moved == 0 && grid[60].is_moved == 0) {
                            for (int i = 0; i < 64; i++) {
                                if (grid[i].color != color)
                                    if (this->possible(i, 60) || this->possible(i, 61) ||
                                        this->possible(i, 62) || this->possible(i, 63))
                                        break;
                                if (i == 63) {
                                    grid[63] = new piece();
                                    grid[60] = new piece();
                                    grid[61] = new piece('r', color, true);
                                    grid[62] = new piece('k', color, true);


                                    std::string all_of_possible_moves;
                                    all_of_possible_moves.push_back('o');
                                    all_of_possible_moves.push_back('-');
                                    all_of_possible_moves.push_back('o');
                                    all_of_possible_moves.push_back('\t');
                                    list_of_moves.push_back(all_of_possible_moves);

                                    return 0;
                                }
                            }
                        }

                }
            }
                printf("opsie illegal move!");
                break;
            case 5:
                return -1;
            default: {

                int position, go_to;

                position = ctn(holder[1], holder[0]);
                go_to = ctn(holder[3], holder[2]);

                if (grid[position].color != color || grid[position].emblem == '*') {
                    printf("opsie illegal move!");
                    break;
                }
                if (!this->possible(position, go_to)) { // todo tutaj daj bicie w przelocie



                    if (color) {
                        int hold12 = ctn(list_of_moves.back()[2], list_of_moves.back()[1]);
                        int hold45 = ctn(list_of_moves.back()[5], list_of_moves.back()[4]);
                        printf("hold12 %d,hold45 %d", hold12, hold45);
                        if (position / 8 == 4 && list_of_moves.back()[0] == 'p' && hold12 - hold45 == 16) {

                            if (hold45 == position - 1 ||
                                hold45 == position + 1) {

                                grid[go_to] = new piece('p', color, true);
                                grid[hold45] = new piece();
                                grid[position] = new piece();


                                list_of_moves.back().push_back(grid[go_to].emblem);
                                list_of_moves.back().push_back(holder[0]);
                                list_of_moves.back().push_back(holder[1]);
                                list_of_moves.back().push_back('-');
                                list_of_moves.back().push_back(holder[2]);
                                list_of_moves.back().push_back(holder[3]);
                                list_of_moves.back().push_back('\n');
                                return 0;

                            }
                        }
                    } else {
                        if (position / 8 == 3) {
                            int i = 0;
                            for (; i < list_of_moves.back().size(); i++) if (list_of_moves.back()[i] == '\t') break;

                            i++;

                            int hold21 = ctn(list_of_moves.back()[i + 2], list_of_moves.back()[i + 1]);
                            int hold54 = ctn(list_of_moves.back()[i + 5], list_of_moves.back()[i + 4]);

                            if (list_of_moves.back()[i] == 'p' && hold21 - hold54 == 16) {
                                if (hold21 == position - 1 || hold21 == position + 1) {

                                    grid[go_to] = new piece('p', color, true);
                                    grid[hold54] = new piece();
                                    grid[position] = new piece();

                                    std::string all_of_possible_moves;
                                    all_of_possible_moves.push_back(grid[go_to].emblem);
                                    all_of_possible_moves.push_back(holder[0]);
                                    all_of_possible_moves.push_back(holder[1]);
                                    all_of_possible_moves.push_back('-');
                                    all_of_possible_moves.push_back(holder[2]);
                                    all_of_possible_moves.push_back(holder[3]);
                                    all_of_possible_moves.push_back('\t');
                                    list_of_moves.push_back(all_of_possible_moves);
                                    return 0;
                                }
                            }
                        }
                    }
                    printf("opsie illegal move!");
                    break;

                }


                char bzdek = grid[position].emblem;
                grid[go_to] = new piece(bzdek, color, true);
                grid[position] = new piece();

                /// add to list of moves \/
                if (color) {
                    list_of_moves.back().push_back(grid[go_to].emblem);
                    list_of_moves.back().push_back(holder[0]);
                    list_of_moves.back().push_back(holder[1]);
                    list_of_moves.back().push_back('-');
                    list_of_moves.back().push_back(holder[2]);
                    list_of_moves.back().push_back(holder[3]);
                    list_of_moves.back().push_back('\n');
                } else {
                    std::string all_of_possible_moves;
                    all_of_possible_moves.push_back(grid[go_to].emblem);
                    all_of_possible_moves.push_back(holder[0]);
                    all_of_possible_moves.push_back(holder[1]);
                    all_of_possible_moves.push_back('-');
                    all_of_possible_moves.push_back(holder[2]);
                    all_of_possible_moves.push_back(holder[3]);
                    all_of_possible_moves.push_back('\t');
                    list_of_moves.push_back(all_of_possible_moves);
                }

                int j = 0;
                if (color) j += 56;

                for (int i = j; i < 8 + j; i++) {
                    if (grid[i].emblem == 'p') {
                        char a;
                        printf("ok but which one \n>");
                        a = getch();
                        switch (a) {
                            case 'q':
                                grid[go_to] = new piece('q', color, true);
                                list_of_moves[list_of_moves.size() - 1].erase(
                                        list_of_moves[list_of_moves.size() - 1].size() - 1);
                                list_of_moves.back().push_back('=');
                                list_of_moves.back().push_back('q');
                                if (color) list_of_moves.back().push_back('\n');
                                else list_of_moves.back().push_back('\t');
                                break;
                            case 'n':
                                grid[go_to] = new piece('n', color, true);
                                list_of_moves[list_of_moves.size() - 1].erase(
                                        list_of_moves[list_of_moves.size() - 1].size() - 1);
                                list_of_moves.back().push_back('=');
                                list_of_moves.back().push_back('n');
                                if (color) list_of_moves.back().push_back('\n');
                                else list_of_moves.back().push_back('\t');

                                break;
                            case 'r':
                                grid[go_to] = new piece('r', color, true);
                                list_of_moves[list_of_moves.size() - 1].erase(
                                        list_of_moves[list_of_moves.size() - 1].size() - 1);
                                list_of_moves.back().push_back('=');
                                list_of_moves.back().push_back('r');
                                if (color) list_of_moves.back().push_back('\n');
                                else list_of_moves.back().push_back('\t');

                                break;
                            case 'b':
                                grid[go_to] = new piece('b', color, true);
                                list_of_moves[list_of_moves.size() - 1].erase(
                                        list_of_moves[list_of_moves.size() - 1].size() - 1);
                                list_of_moves.back().push_back('=');
                                list_of_moves.back().push_back('b');
                                if (color) list_of_moves.back().push_back('\n');
                                else list_of_moves.back().push_back('\t');

                                break;
                        }
                    }
                    if (i - j == 7) break;
                } // it's 4 upgrade
                return 0;
            }
        }
    }
    return 0;
}

void board::admin() {
    bool color = false;
    std::string all_of_possible_moves;
    bool do_it = true;
    while (1 < 2) {

        if (do_it) {
            clear();
            this->show();
        }
        do_it = true;
        printf("> ");
        std::cin >> all_of_possible_moves;
        switch (all_of_possible_moves[0]) {
            case 'q':
                return;
            case 'o':
                for (int i = 0; i < 64; i++) {
                    grid[i].color = !grid[i].color;
                }

                break;
            case 'h':
                printf("to add a piece use command \"a(piece type)(position)(color)\"\n"
                       "to subtract a piece use command \"s(position)\"\n"
                       "to clear console use command \"c\"\n"
                       "to exit use \"q\"\n"
                       "to download a board use \"d(file name)\"\n"
                       "to load a board use \"l(file path)\"\n"
                       "to show legal moves use \"p(position)\"\n"
                       "to simply move a piece \"m(color)\"\n");

                do_it = false;
                break;
            case 'a':
                grid[ctn(all_of_possible_moves[3], all_of_possible_moves[2])] = new piece(
                        all_of_possible_moves[1], static_cast<int>(all_of_possible_moves[4]) - 48);
                break;

                break;
            case 'c':
                for (int i = 0; i < 64; ++i) grid[i] = new piece();
                break;
            case 's':
                grid[ctn(all_of_possible_moves[2], all_of_possible_moves[1])] = new piece();
                break;
            case '*': {
                if (all_of_possible_moves.size() == 3) {
                    bool players_color = static_cast<bool>(static_cast<int>(all_of_possible_moves[1]) - 48);
                    int deepth = static_cast<int>(all_of_possible_moves[2]) - 48;
                    mov tp = bip(players_color, deepth);
                    printf("%c%d -> ", (char) tp.pos % 8 + 97, ((tp.pos / 8) - 8) * (-1));
                    printf("%c%d  ", (char) tp.g_t % 8 + 97, ((tp.g_t / 8) - 8) * (-1));
                    printf("%f  \a\n", tp.eva);
                    do_it = false;
                } else {

                    bool players_color = static_cast<bool>(static_cast<int>(all_of_possible_moves[1]) - 48);
                    int deepth = static_cast<int>(all_of_possible_moves[2]) - 48;
                    int threads = static_cast<int>(all_of_possible_moves[3]) - 48;
                    mov tp = bip(players_color, deepth, threads);
                    printf("%c%d -> ", (char) tp.pos % 8 + 97, ((tp.pos / 8) - 8) * (-1));
                    printf("%c%d  ", (char) tp.g_t % 8 + 97, ((tp.g_t / 8) - 8) * (-1));
                    printf("%f  \a\n", tp.eva);
                    do_it = false;


                }
            }
                break;
            case 'p': {
                if (all_of_possible_moves.size() == 5)
                    printf("%d ", this->possible(ctn(all_of_possible_moves[2], all_of_possible_moves[1]),
                                                 ctn(all_of_possible_moves[4], all_of_possible_moves[3])));
                else {
                    array legal;
                    this->array_of_possible(ctn(all_of_possible_moves[2], all_of_possible_moves[1]),
                                            legal);
                    if (all_of_possible_moves.size() == 4 && all_of_possible_moves[3] == 's') {
                        std::vector<char> char_legal;
                        std::vector<bool> color_legal;
                        std::vector<bool> moved_legal;

                        for (int i = 0; i < legal.size(); i++) {
                            char_legal.push_back(grid[i].emblem);
                            color_legal.push_back(grid[i].color);
                            moved_legal.push_back(grid[i].is_moved);
                        }
                        for (int i = 0; i < legal.size(); i++) grid[legal[i]] = new piece('@', false);
                        clear();
                        this->show();
                        for (int i = 0; i < legal.size(); i++)
                            grid[legal[i]] = new piece(char_legal[i], color_legal[i], moved_legal[i]);


                    }
                    for (int i = 0; i < legal.size(); i++)
                        printf("%c%d  ", (char) legal[i] % 8 + 97, ((legal[i] / 8) - 8) * (-1));
                    printf(">%d<", legal.size());
                }

                do_it = false;
            }
                break;
            case 'k':
                this->pvp();
                break;
            case 'l': {
                std::ifstream myfile;
                myfile.open(all_of_possible_moves.substr(1, all_of_possible_moves.size()), std::ios::in);
                if (myfile.good()) {
                    char a;
                    for (int i = 0; i < 64; ++i) {
                        myfile >> a;
                        if (a != '*') {
                            if (static_cast<int>(a) >= 97) {
                                if (a != 'P') grid[i] = new piece(a, false, true);
                                else grid[i] = new piece(a, false, i / 8 != 1);


                            } else {
                                if (a != 'p') grid[i] = new piece((char) (a + 32), true, true);
                                else grid[i] = new piece((char) (a + 32), true, i / 8 != 6);
                            }
                        } else grid[i] = new piece();

                    }

                    printf("loaded\n");

                } else printf("file error");

                myfile.close();

            }
                break;
            case 'd': {
                std::ofstream myfile;
                myfile.open(all_of_possible_moves.substr(1, all_of_possible_moves.size()), std::ios::out);
                if (myfile.good()) {

                    for (int i = 0; i < 64; ++i) {
                        if (grid[i].color && grid[i].emblem != '*') myfile << (char) (grid[i].emblem - 32);
                        else myfile << grid[i].emblem;
                    }

                    printf("file saved\n");

                } else printf("file error");

                myfile.close();
                do_it = false;

            }
                break;
            case '-': {
                grid[ctn(all_of_possible_moves[4], all_of_possible_moves[3])] = grid[ctn(all_of_possible_moves[2],
                                                                                         all_of_possible_moves[1])];
                grid[ctn(all_of_possible_moves[2], all_of_possible_moves[1])] = new piece();

            }
                break;
            default:
                break;

        }
    }
}

void board::pvp() {

    int sum = 0;
    bool color = false;
    std::string all_of_possible_moves = "white\tblack\n";
    if (list_of_moves.empty())list_of_moves.push_back(all_of_possible_moves);
    while (1 < 2) {
        if (list_of_moves.back().back() == '\n') color = BLACK;
        else if (list_of_moves.back().back() == '\t') color = WHITE;
        else printf("error!");
        for (int i = 0; i < 64; i++) if (grid[i].emblem == 'k') grid[i].color ? (sum--) : (sum++);
        if (sum != 0) break;
        clear();
        this->show();
        if (this->move(color) == -1) return;

    }

    clear();

    if (sum < 0) {
        printf("black won");
        w8(5000);
        printf("even tho this is chess not basketball");
    } else {
        printf("white won");
        w8(5000);
        printf("obviously");
        w8(5000);
        printf("i mean daaaa");
    }
    w8(50000);
    printf("jebaczuzietermosem");


}

double board::evaluate() { // k q r b n p
    int w_tab[6];
    double bias = 0;
    int w_moves = 0, b_moves = 0;

    int b_tab[6];
    for (int j = 0; j < 6; ++j) {
        w_tab[j] = 0;
        b_tab[j] = 0;
    }
    array all_of_possible_moves_moves;
    for (int i = 0; i < 64; i++) {

        b_moves += castle(BLACK).size();
        w_moves += castle(WHITE).size();

        switch (grid[i].emblem) {
            case 'k':
                if (grid[i].color) {
                    b_tab[0]++;
                    this->array_of_possible(i, all_of_possible_moves_moves);
                    b_moves += all_of_possible_moves_moves.size();
                } else {
                    w_tab[0]++;
                    this->array_of_possible(i, all_of_possible_moves_moves);
                    w_moves += all_of_possible_moves_moves.size();
                }
                break;
            case 'q':
                if (grid[i].color) {
                    b_tab[1]++;
                    this->array_of_possible(i, all_of_possible_moves_moves);
                    b_moves += all_of_possible_moves_moves.size();
                } else {
                    w_tab[1]++;
                    this->array_of_possible(i, all_of_possible_moves_moves);
                    w_moves += all_of_possible_moves_moves.size();
                }
                break;
            case 'r':
                if (grid[i].color) {
                    b_tab[2]++;
                    this->array_of_possible(i, all_of_possible_moves_moves);
                    b_moves += all_of_possible_moves_moves.size();
                } else {
                    w_tab[2]++;
                    this->array_of_possible(i, all_of_possible_moves_moves);
                    w_moves += all_of_possible_moves_moves.size();
                }
            case 'b':
                if (grid[i].color) {
                    b_tab[3]++;
                    this->array_of_possible(i, all_of_possible_moves_moves);
                    b_moves += all_of_possible_moves_moves.size();
                } else {
                    w_tab[3]++;
                    this->array_of_possible(i, all_of_possible_moves_moves);
                    w_moves += all_of_possible_moves_moves.size();
                }
                break;
            case 'n':
                if (grid[i].color) {
                    b_tab[4]++;
                    this->array_of_possible(i, all_of_possible_moves_moves);
                    b_moves += all_of_possible_moves_moves.size();
                } else {
                    w_tab[4]++;
                    this->array_of_possible(i, all_of_possible_moves_moves);
                    w_moves += all_of_possible_moves_moves.size();
                }
                break;
            case 'p': {
                int p_p_for_bias[4] = {i - 9, i - 7, i + 7, i + 9};

                if (grid[i].color) {
                    b_tab[5]++;

                    for (int ni = 1; ni < 6; ni++) {
                        if (grid[ni].emblem == 'p' && grid[ni].color && ni != i) bias += 0.5;

                    }

                    for (int ni = 0; ni < 4; ni++) if (grid[ni].emblem == 'p' && grid[ni].color) bias -= 0.2;


                    this->array_of_possible(i, all_of_possible_moves_moves);
                    b_moves += all_of_possible_moves_moves.size();
                } else {
                    w_tab[5]++;

                    for (int ni = 1; ni < 6; ni++) {
                        if (grid[ni].emblem == 'p' && !grid[ni].color && ni != i) bias -= 0.5;
                    }
                    for (int ni = 0; ni < 4; ni++) if (grid[ni].emblem == 'p' && !grid[ni].color) bias += 0.2;

                    this->array_of_possible(i, all_of_possible_moves_moves);
                    w_moves += all_of_possible_moves_moves.size();
                }
            }
                break;
            default:
                break;

        }

    }

    double eva = 500 * (w_tab[0] - b_tab[0]) + 9 * (w_tab[1] - b_tab[1]) + 5 * (w_tab[2] - b_tab[2]) +
                 3.15 * (w_tab[3] - b_tab[3]) + 3 * (w_tab[4] - b_tab[4]) + (w_tab[5] - b_tab[5]);
    eva += 0.1 * (w_moves - b_moves) + bias;

    return eva;
}

void board::pvc(int deepth, bool player_s_color) {

    int sum = 0;
    bool color = false;
    std::string all_of_possible_moves = "white\tblack\n";

    if (list_of_moves.empty())list_of_moves.push_back(all_of_possible_moves);
    while (1 < 2) {
        for (int i = 0; i < 64; i++) if (grid[i].emblem == 'k') grid[i].color ? (sum--) : (sum++);
        if (sum != 0) break;
        clear();
        this->show();
        if (this->move(player_s_color) == -1) return;

        mov temp = bip(!player_s_color, deepth);
        if (!player_s_color) {
            list_of_moves.back().push_back(grid[temp.pos].emblem);
            list_of_moves.back().push_back((char) temp.pos % 8 + 97);
            list_of_moves.back().push_back(((char) (temp.pos / 8) - 8) * (-1) + 48);
            list_of_moves.back().push_back('-');
            list_of_moves.back().push_back((char) temp.g_t % 8 + 97);
            list_of_moves.back().push_back(((char) (temp.g_t / 8) - 8) * (-1) + 48);
            list_of_moves.back().push_back('\n');

        } else {
            std::string tp;
            tp.push_back(grid[temp.pos].emblem);
            tp.push_back((char) temp.pos % 8 + 97);
            tp.push_back(((char) (temp.pos / 8) - 8) * (-1) + 48);
            tp.push_back('-');
            tp.push_back((char) temp.g_t % 8 + 97);
            tp.push_back(((char) (temp.g_t / 8) - 8) * (-1) + 48);
            tp.push_back('\t');
            list_of_moves.push_back(tp);
        }
        grid[temp.g_t] = grid[temp.pos];
        grid[temp.g_t].is_moved = true;
        grid[temp.pos] = new piece();

        for (int i = 0; i < 64; i++) if (grid[i].emblem == 'k') grid[i].color ? (sum--) : (sum++);
        if (sum != 0) break;

    }
    clear();

    if (sum < 0) {
        printf("black won");
        w8(5000);
        printf("even tho this is chess not basketball");
    } else {
        printf("white won");
        w8(5000);
        printf("obviously");
        w8(5000);
        printf("i mean daaaa");
    }
    w8(50000);
    printf("jebaczuzietermosem");


}

std::mutex array_lock;
dynamic_arr<mov> tab_of_possible_moves_4_threads;

double board::standard_move(mov suspect, bool color, int deepth) {


    grid[suspect.g_t] = grid[suspect.pos];
    grid[suspect.g_t].is_moved = true;

    return minmax(deepth, !color, -100000, 10000);


}

double board::specjal_moves(mov suspect, bool color, int deepth) {
    switch (suspect.g_t) {
        case 100:


            grid[suspect.g_t] = new piece('n', color, true);
            grid[suspect.pos].emblem = '*';

            return minmax(deepth, !color, -100000, 100000);
        case 101:

            grid[suspect.g_t] = new piece('q', color, true);
            grid[suspect.pos].emblem = '*';

            return minmax(deepth, !color, -100000, 100000);
        case 66:
            if (color) {
                grid[4].emblem = '*';
                grid[5] = new piece('r', color, true);
                grid[6] = new piece('k', color, true);
                grid[7].emblem = '*';
                return minmax(deepth, !color, -100000, 100000);

            } else {
                grid[60].emblem = '*';
                grid[61] = new piece('r', color, true);
                grid[62] = new piece('k', color, true);
                grid[63].emblem = '*';
                return minmax(deepth, !color, -100000, 100000);

            }
        case 666:
            if (color) {
                grid[0].emblem = '*';
                grid[1].emblem = '*';
                grid[2] = new piece('k', color, true);
                grid[3] = new piece('r', color, true);
                grid[4].emblem = '*';
                return minmax(deepth, !color, -100000, 100000);

            } else {
                grid[46].emblem = '*';
                grid[47].emblem = '*';
                grid[48] = new piece('k', color, true);
                grid[49] = new piece('r', color, true);
                grid[50].emblem = '*';
                return minmax(deepth, !color, -100000, 100000);
            }
        case (72, 73, 74, 75, 76, 77, 78, 79): {

            int shift_in_x = -16;

            grid[suspect.g_t] = grid[suspect.pos];
            grid[suspect.pos].emblem = '*';
            grid[suspect.g_t + shift_in_x].emblem = '*';

            return minmax(deepth, !color, -100000, 100000);
        }
        case (80, 81, 82, 83, 84, 85, 86, 87): {
            int shift_in_x = 16;

            grid[suspect.g_t] = grid[suspect.pos];

            grid[suspect.pos].emblem = '*';
            grid[suspect.g_t + shift_in_x].emblem = '*';

            return minmax(deepth, !color, -100000, 100000);
        }

        default:

            grid[suspect.g_t] = grid[suspect.pos];

            grid[suspect.g_t].is_moved = true;

            grid[suspect.pos].emblem = '*';

            return minmax(deepth, !color, -100000, 100000);


    }
}

double board::do_the_move(mov suspect, bool color, int deepth) {

    piece all_of_possible_moves[2];
    switch (suspect.g_t) {
        case 100:

            all_of_possible_moves[0] = grid[suspect.g_t]; //i+1
            all_of_possible_moves[1] = grid[suspect.pos];

            grid[suspect.g_t] = new piece('n', color, true);
            grid[suspect.pos].emblem = '*';

            suspect.eva = this->minmax(deepth, !color, -100000, 100000);

            grid[suspect.g_t] = all_of_possible_moves[0];
            grid[suspect.pos] = all_of_possible_moves[1];
            break;
        case 101:
            all_of_possible_moves[0] = grid[suspect.g_t];
            all_of_possible_moves[1] = grid[suspect.pos];

            grid[suspect.g_t] = new piece('q', color, true);
            grid[suspect.pos].emblem = '*';

            suspect.eva = this->minmax(deepth, !color, -100000, 100000);

            grid[suspect.g_t] = all_of_possible_moves[0];
            grid[suspect.pos] = all_of_possible_moves[1];
            break;
        case 66:
            if (color) {
                grid[4].emblem = '*';
                grid[5] = new piece('r', color, true);
                grid[6] = new piece('k', color, true);
                grid[7].emblem = '*';
                suspect.eva = this->minmax(deepth, !color, -100000, 100000);
                grid[4] = new piece('k', color, false);
                grid[5].emblem = '*';
                grid[6].emblem = '*';
                grid[7] = new piece('r', color, false);
            } else {
                grid[60].emblem = '*';
                grid[61] = new piece('r', color, true);
                grid[62] = new piece('k', color, true);
                grid[63].emblem = '*';
                suspect.eva = this->minmax(deepth, !color, -100000, 100000);
                grid[60] = new piece('k', color, false);
                grid[61].emblem = '*';
                grid[62].emblem = '*';
                grid[63] = new piece('r', color, false);

            }
            break;
        case 666:
            if (color) {
                grid[0].emblem = '*';
                grid[1].emblem = '*';
                grid[2] = new piece('k', color, true);
                grid[3] = new piece('r', color, true);
                grid[4].emblem = '*';
                suspect.eva = this->minmax(deepth, !color, -100000, 100000);
                grid[0] = new piece('r', color, false);
                grid[1].emblem = '*';
                grid[2].emblem = '*';
                grid[3].emblem = '*';
                grid[4] = new piece('k', color, false);
            } else {
                grid[46].emblem = '*';
                grid[47].emblem = '*';
                grid[48] = new piece('k', color, true);
                grid[49] = new piece('r', color, true);
                grid[50].emblem = '*';
                suspect.eva = this->minmax(deepth, !color, -100000, 100000);
                grid[46] = new piece('r', color, false);
                grid[47].emblem = '*';
                grid[48].emblem = '*';
                grid[49].emblem = '*';
                grid[50] = new piece('k', color, false);
            }
            break;
        case (72, 73, 74, 75, 76, 77, 78, 79): {
            int shift_in_x = -16;
            all_of_possible_moves[0] = grid[suspect.g_t + shift_in_x];
            all_of_possible_moves[1] = grid[suspect.pos];

            grid[suspect.g_t] = grid[suspect.pos];
            //  grid[suspect.g_t].is_moved = true;

            grid[suspect.pos].emblem = '*';
            grid[suspect.g_t + shift_in_x].emblem = '*';

            suspect.eva = this->minmax(deepth, !color, -100000, 100000);

            grid[suspect.g_t + shift_in_x] = all_of_possible_moves[0];
            grid[suspect.g_t].emblem = '*';
            grid[suspect.pos] = all_of_possible_moves[1];


        }
            break;
        case (80, 81, 82, 83, 84, 85, 86, 87): {
            int shift_in_x = 16;
            all_of_possible_moves[0] = grid[suspect.g_t + shift_in_x];
            all_of_possible_moves[1] = grid[suspect.pos];

            grid[suspect.g_t] = grid[suspect.pos];
            //  grid[suspect.g_t].is_moved = true;

            grid[suspect.pos].emblem = '*';
            grid[suspect.g_t + shift_in_x].emblem = '*';

            suspect.eva = this->minmax(deepth, !color, -100000, 100000);

            grid[suspect.g_t + shift_in_x] = all_of_possible_moves[0];
            grid[suspect.g_t].emblem = '*';
            grid[suspect.pos] = all_of_possible_moves[1];


        }
            break;
        default:

            all_of_possible_moves[0] = grid[suspect.pos];
            all_of_possible_moves[1] = grid[suspect.g_t];

            grid[suspect.g_t] = grid[suspect.pos];

            grid[suspect.g_t].is_moved = true;

            grid[suspect.pos].emblem = '*';

            suspect.eva = this->minmax(deepth, !color, -100000, 100000);

            grid[suspect.g_t] = all_of_possible_moves[1];

            grid[suspect.pos] = all_of_possible_moves[0];
    }
    return suspect.eva;
}


std::mutex numbr_lock;
int numbr_of_permutations = 0;

void hold_the_move(int position_of_suspected, bool color, int deepth, board *frame) {
    // array_lock.lock();
    mov suspect = tab_of_possible_moves_4_threads[position_of_suspected];
    // array_lock.unlock();

    if (suspect.g_t < 64) suspect.eva = frame->standard_move(suspect, color, deepth);

    else suspect.eva = frame->specjal_moves(suspect, color, deepth);

    //  array_lock.lock();
    tab_of_possible_moves_4_threads[position_of_suspected].eva = suspect.eva;

    //   array_lock.unlock();


}

mov board::bip(bool color, int deepth, int number_of_th) {
    tab_of_possible_moves_4_threads.clear();
    numbr_of_permutations = 0;

    auto start = std::chrono::steady_clock::now();
    array all_of_possible_moves_moves;


    for (int i = 0; i < 64; ++i) {
        if (grid[i].emblem != '*' && grid[i].color == color) {
            this->array_of_possible(i, all_of_possible_moves_moves);
            for (int j = 0; j < all_of_possible_moves_moves.size(); j++) {
                mov tp(i, all_of_possible_moves_moves[j], 0);
                tab_of_possible_moves_4_threads.push_back(tp);
            }
        }
    }


    int weird_stuff = tab_of_possible_moves_4_threads.size();


    all_of_possible_moves_moves = castle(color);

    for (int j = 0; j < all_of_possible_moves_moves.size(); j++) {
        mov tp(j, all_of_possible_moves_moves[j], 0);
        tab_of_possible_moves_4_threads.push_back(tp);
    }

    if (color) {
        for (int i = 48; i < 56; i++) {
            if (grid[i].emblem == 'p' && grid[i].color == color) {

                all_of_possible_moves_moves = upgrade(color, i);

                for (int j = 0; j < all_of_possible_moves_moves.size(); j++) {
                    mov tp(i, all_of_possible_moves_moves[j], 0);
                    tab_of_possible_moves_4_threads.push_back(tp);
                }

            }
        }
        for (int i = 40; i < 48; i++) {
            if (grid[i].emblem == 'p' && grid[i].color == color) {

                all_of_possible_moves_moves = en_passant(color, i);

                for (int j = 0; j < all_of_possible_moves_moves.size(); j++) {
                    mov tp(i, all_of_possible_moves_moves[j], 0);
                    tab_of_possible_moves_4_threads.push_back(tp);
                }
            }
        }
    } else {
        for (int i = 8; i < 16; i++) {
            if (grid[i].emblem == 'p' && grid[i].color == color) {

                all_of_possible_moves_moves = upgrade(color, i);

                for (int j = 0; j < all_of_possible_moves_moves.size(); j++) {
                    mov tp(i, all_of_possible_moves_moves[j], 0);
                    tab_of_possible_moves_4_threads.push_back(tp);
                }

            }
        }
        for (int i = 16; i < 32; i++) {
            if (grid[i].emblem == 'p' && grid[i].color == color) {

                all_of_possible_moves_moves = en_passant(color, i);

                for (int j = 0; j < all_of_possible_moves_moves.size(); j++) {
                    mov tp(i, all_of_possible_moves_moves[j], 0);
                    tab_of_possible_moves_4_threads.push_back(tp);
                }
            }
        }


    }
/// stuff

    std::vector<std::thread> thread_vector;

    int thread_start = 0;
    number_of_th = tab_of_possible_moves_4_threads.size();

    board boards_for_threads[number_of_th];

    for (int i = 0; i < number_of_th; i++) {

        board tp(*this);
        boards_for_threads[i] = tp;

    }

    for (int i = 0; i < number_of_th; i++) {

        thread_vector.emplace_back(hold_the_move, i, color, deepth,
                                   &boards_for_threads[i]);

    }
    for (auto &t:thread_vector)t.join();




//// end of stuff
    auto end = std::chrono::steady_clock::now();
    tab_of_possible_moves_4_threads.show();
    std::cout << "in " << std::chrono::duration_cast<std::chrono::seconds>(end - start).count() << " seconds\n";
    std::cout << "or " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " milliseconds\n";
    printf("number of permutations: %d,\a", numbr_of_permutations);
    if (!color) {

        return tab_of_possible_moves_4_threads[min(tab_of_possible_moves_4_threads)];
    } else {

        return tab_of_possible_moves_4_threads[max(tab_of_possible_moves_4_threads)];
    }
}

mov board::bip(bool color, int deepth) {
    numbr_of_permutations = 0;
    auto start = std::chrono::steady_clock::now();
    //std::vector<int> local_possible_moves;
    array local_possible_moves;
    dynamic_arr<mov> tab_of_possible_moves;
    for (int i = 0; i < 64; ++i) {
        if (grid[i].emblem != '*' && grid[i].color == color) {
            this->array_of_possible(i, local_possible_moves);
            for (int j = 0; j < local_possible_moves.size(); j++) {
                mov tp(i, local_possible_moves[j], 0);
                tab_of_possible_moves.push_back(tp);
            }
        }
    }

    int weird_stuff = tab_of_possible_moves.size();
// TODO here is weitd stuff to get done

    /*
    for (int i = 0; i < 64; ++i)
        if (grid[i].emblem == 'p' && grid[i].color == color) {
            local_possible_moves = upgrade(color, i);
            for (int j = 0; j < local_possible_moves.size(); j++) {
                mov tp(i, local_possible_moves[j], 0);
                tab_of_possible_moves.push_back(tp);
            }
        }

*/
    local_possible_moves = castle(color);

    for (int j = 0; j < local_possible_moves.size(); j++) {
        mov tp(j, local_possible_moves[j], 0);
        tab_of_possible_moves.push_back(tp);

    }


    piece temp_piece_storage[2]; // it's just to hold value


    for (int i = 0; i < weird_stuff; i++) {
        temp_piece_storage[0] = grid[tab_of_possible_moves[i].pos];
        temp_piece_storage[1] = grid[tab_of_possible_moves[i].g_t];

        grid[tab_of_possible_moves[i].g_t] = grid[tab_of_possible_moves[i].pos];

        grid[tab_of_possible_moves[i].g_t].is_moved = true;

        grid[tab_of_possible_moves[i].pos].emblem = '*';

        tab_of_possible_moves[i].eva = this->minmax(deepth, !color, -100000, 100000);

        grid[tab_of_possible_moves[i].g_t] = temp_piece_storage[1];

        grid[tab_of_possible_moves[i].pos] = temp_piece_storage[0];
    }


    for (int i = weird_stuff; i < tab_of_possible_moves.size(); i++) {
        switch (tab_of_possible_moves[i].g_t) {
            case 100:

                temp_piece_storage[0] = grid[tab_of_possible_moves[i].g_t]; //i+1
                temp_piece_storage[1] = grid[tab_of_possible_moves[i].pos];

                grid[tab_of_possible_moves[i].g_t] = new piece('n', color, true);
                grid[tab_of_possible_moves[i].pos].emblem = '*';

                tab_of_possible_moves[i].eva = this->minmax(deepth, !color, -100000, 100000);

                grid[tab_of_possible_moves[i].g_t] = temp_piece_storage[0];
                grid[tab_of_possible_moves[i].pos] = temp_piece_storage[1];
                break;
            case 101:
                temp_piece_storage[0] = grid[tab_of_possible_moves[i].g_t];
                temp_piece_storage[1] = grid[tab_of_possible_moves[i].pos];

                grid[tab_of_possible_moves[i].g_t] = new piece('q', color, true);
                grid[tab_of_possible_moves[i].pos].emblem = '*';

                tab_of_possible_moves[i].eva = this->minmax(deepth, !color, -100000, 100000);

                grid[tab_of_possible_moves[i].g_t] = temp_piece_storage[0];
                grid[tab_of_possible_moves[i].pos] = temp_piece_storage[1];
                break;
            case 66:
                if (color) {
                    grid[4].emblem = '*';
                    grid[5] = new piece('r', color, true);
                    grid[6] = new piece('k', color, true);
                    grid[7].emblem = '*';
                    tab_of_possible_moves[i].eva = this->minmax(deepth, !color, -100000, 10000);
                    grid[4] = new piece('k', color, false);
                    grid[5].emblem = '*';
                    grid[6].emblem = '*';
                    grid[7] = new piece('r', color, false);
                } else {
                    grid[60].emblem = '*';
                    grid[61] = new piece('r', color, true);
                    grid[62] = new piece('k', color, true);
                    grid[63].emblem = '*';
                    tab_of_possible_moves[i].eva = this->minmax(deepth, !color, -100000, 10000);
                    grid[60] = new piece('k', color, false);
                    grid[61].emblem = '*';
                    grid[62].emblem = '*';
                    grid[63] = new piece('r', color, false);

                }
                break;
            case 666:
                if (color) {
                    grid[0].emblem = '*';
                    grid[1].emblem = '*';
                    grid[2] = new piece('k', color, true);
                    grid[3] = new piece('r', color, true);
                    grid[4].emblem = '*';
                    tab_of_possible_moves[i].eva = this->minmax(deepth, !color, -100000, 10000);
                    grid[0] = new piece('r', color, false);
                    grid[1].emblem = '*';
                    grid[2].emblem = '*';
                    grid[3].emblem = '*';
                    grid[4] = new piece('k', color, false);
                } else {
                    grid[46].emblem = '*';
                    grid[47].emblem = '*';
                    grid[48] = new piece('k', color, true);
                    grid[49] = new piece('r', color, true);
                    grid[50].emblem = '*';
                    tab_of_possible_moves[i].eva = this->minmax(deepth, !color, -100000, 10000);
                    grid[46] = new piece('r', color, false);
                    grid[47].emblem = '*';
                    grid[48].emblem = '*';
                    grid[49].emblem = '*';
                    grid[50] = new piece('k', color, false);
                }
                break;

            default:
                int shift_in_x = -16;
                if (color) shift_in_x = 16;

                temp_piece_storage[0] = grid[tab_of_possible_moves[i].g_t + shift_in_x];
                temp_piece_storage[1] = grid[tab_of_possible_moves[i].pos];

                grid[tab_of_possible_moves[i].g_t] = grid[i];
                grid[tab_of_possible_moves[i].g_t].is_moved = true;

                grid[tab_of_possible_moves[i].pos].emblem = '*';
                grid[tab_of_possible_moves[i].g_t + shift_in_x].emblem = '*';

                tab_of_possible_moves[i].eva = this->minmax(deepth, !color, -100000, 10000);

                grid[tab_of_possible_moves[i].g_t + shift_in_x] = temp_piece_storage[0];
                grid[tab_of_possible_moves[i].g_t].emblem = '*';
                grid[tab_of_possible_moves[i].pos] = temp_piece_storage[1];
                break;
        }
    }

    //     todo weź wymyśl jak zrobić castle w sensie bo on zajmuje jedno miejsce a wszystko inne dwa
    auto end = std::chrono::steady_clock::now();
    tab_of_possible_moves.show();
    std::cout << "in " << std::chrono::duration_cast<std::chrono::seconds>(end - start).count() << " seconds\n";
    std::cout << "or " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " milliseconds\n";
    printf("number of permutations: %d,\a", numbr_of_permutations);

    if (color) {

        return tab_of_possible_moves[min(tab_of_possible_moves)];
    } else {

        return tab_of_possible_moves[max(tab_of_possible_moves)];
    }
}

double board::minmax(int deep, bool color_now, double alpha, double beta) {


    if (deep == 0) {

        return this->evaluate();
    }

    int no_more_kings[2] = {0, 0};
    int oposite_king_position;


    for (int i = 0; i < 64; i++)
        if (grid[i].emblem == 'k')
            grid[i].color ? no_more_kings[0] = i : no_more_kings[1] = i;


    if (no_more_kings[0] - no_more_kings[1] == no_more_kings[0]) return 1069;
    if (no_more_kings[0] - no_more_kings[1] == no_more_kings[1]) return -1069;


    array local_array_of_moves;
    dynamic_arr<mov> array_of_moves; // the global thing one per

///normal stuff
    for (int i = 0; i < 64; ++i) {
        if (grid[i].emblem != '*' && grid[i].color == color_now) {

            this->array_of_possible(i, local_array_of_moves);

            for (int j = 0; j < local_array_of_moves.size(); j++) {

                mov tp(i, local_array_of_moves[j], 0);
                array_of_moves.push_back(tp);
            }
        }
    }

    /// weird stuff
    int weird_stuff = array_of_moves.size();
/*
        local_array_of_moves = castle(color_now);

        for (int j = 0; j < local_array_of_moves.size(); j++) {
            mov tp(j, local_array_of_moves[j], 0);
            array_of_moves.push_back(tp);
        }

        if (color_now) {
            for (int i = 48; i < 56; i++) {
                if (grid[i].emblem == 'p' && grid[i].color == color_now) {

                    local_array_of_moves = upgrade(color_now, i);

                    for (int j = 0; j < local_array_of_moves.size(); j++) {
                        mov tp(i, local_array_of_moves[j], 0);
                        array_of_moves.push_back(tp);
                    }

                }
            }
            for (int i = 40; i < 48; i++) {
                if (grid[i].emblem == 'p' && grid[i].color == color_now) {

                    local_array_of_moves = en_passant(color_now, i);

                    for (int j = 0; j < local_array_of_moves.size(); j++) {
                        mov tp(i, local_array_of_moves[j], 0);
                        array_of_moves.push_back(tp);
                    }
                }
            }
        } else {
            for (int i = 8; i < 16; i++) {
                if (grid[i].emblem == 'p' && grid[i].color == color_now) {

                    local_array_of_moves = upgrade(color_now, i);

                    for (int j = 0; j < local_array_of_moves.size(); j++) {
                        mov tp(i, local_array_of_moves[j], 0);
                        array_of_moves.push_back(tp);
                    }

                }
            }
            for (int i = 16; i < 32; i++) {
                if (grid[i].emblem == 'p' && grid[i].color == color_now) {

                    local_array_of_moves = en_passant(color_now, i);

                    for (int j = 0; j < local_array_of_moves.size(); j++) {
                        mov tp(i, local_array_of_moves[j], 0);
                        array_of_moves.push_back(tp);
                    }
                }
            }
        }
*/
/// if there are no moves left it means pat or glorius mate and i mean like last man standing shiet
    double evaluation_at_this_point;
    piece all_of_possible_moves[2];
    if (color_now) {
        evaluation_at_this_point = 100000;


        if (array_of_moves.empty()) {
            if (this->check(no_more_kings[0])) {
                printf("blacked");
                return 10000;
            }
            return 0;
        }

    } else {
        evaluation_at_this_point = -100000;
        if (array_of_moves.empty()) {
            if (this->check(no_more_kings[1])) {
                printf("NOT blacked");
                return -10000;
            }
            return 0;
        }

    }


    double min_max = 0.0;
    // reku dla
/// evaluation & stuff
    if (color_now == WHITE) { // white
        for (int i = 0; i < weird_stuff; i++) {

            all_of_possible_moves[0] = grid[array_of_moves[i].g_t];
            all_of_possible_moves[1] = grid[array_of_moves[i].pos];


            grid[array_of_moves[i].g_t] = grid[array_of_moves[i].pos];

            grid[array_of_moves[i].g_t].is_moved = true;

            grid[array_of_moves[i].pos].emblem = '*';

            min_max = minmax(deep - 1, !color_now, alpha, beta);

            if (min_max > evaluation_at_this_point) evaluation_at_this_point = min_max;

            grid[array_of_moves[i].g_t] = all_of_possible_moves[0];
            grid[array_of_moves[i].pos] = all_of_possible_moves[1];
            if (alpha > evaluation_at_this_point) alpha = evaluation_at_this_point;
            if (beta <= alpha) {
                break;

            }

        }

        for (int i = weird_stuff; i < array_of_moves.size(); i++) {
            switch (array_of_moves[i].g_t) {
                case 100:

                    all_of_possible_moves[0] = grid[array_of_moves[i].g_t]; //i+1
                    all_of_possible_moves[1] = grid[array_of_moves[i].pos];

                    grid[array_of_moves[i].g_t] = new piece('n', color_now, true);
                    grid[array_of_moves[i].pos].emblem = '*';

                    min_max = minmax(deep - 1, !color_now, alpha, beta);

                    if (min_max > evaluation_at_this_point) evaluation_at_this_point = min_max;

                    grid[array_of_moves[i].g_t] = all_of_possible_moves[0];
                    grid[array_of_moves[i].pos] = all_of_possible_moves[1];
                    if (alpha > evaluation_at_this_point) alpha = evaluation_at_this_point;
                    if (beta >= alpha) { break; }
                    break;
                case 101:

                    all_of_possible_moves[0] = grid[array_of_moves[i].g_t];
                    all_of_possible_moves[1] = grid[array_of_moves[i].pos];

                    grid[array_of_moves[i].g_t] = new piece('q', color_now, true);
                    grid[array_of_moves[i].pos].emblem = '*';

                    min_max = minmax(deep - 1, !color_now, alpha, beta);

                    if (min_max > evaluation_at_this_point) evaluation_at_this_point = min_max;

                    grid[array_of_moves[i].g_t] = all_of_possible_moves[0];
                    grid[array_of_moves[i].pos] = all_of_possible_moves[1];

                    break;
                case 66:

                    grid[60].emblem = '*';
                    grid[61] = new piece('r', color_now, true);
                    grid[62] = new piece('k', color_now, true);
                    grid[63].emblem = '*';

                    min_max = minmax(deep - 1, !color_now, alpha, beta);
                    if (min_max > evaluation_at_this_point) evaluation_at_this_point = min_max;

                    grid[60] = new piece('k', color_now, false);
                    grid[61].emblem = '*';
                    grid[62].emblem = '*';
                    grid[63] = new piece('r', color_now, false);
                    if (alpha > evaluation_at_this_point) alpha = evaluation_at_this_point;
                    if (beta >= alpha) { break; }

                    break;
                case 666:

                    grid[46].emblem = '*';
                    grid[47].emblem = '*';
                    grid[48] = new piece('k', color_now, true);
                    grid[49] = new piece('r', color_now, true);
                    grid[50].emblem = '*';

                    min_max = minmax(deep - 1, !color_now, alpha, beta);

                    if (min_max > evaluation_at_this_point) evaluation_at_this_point = min_max;

                    grid[46] = new piece('r', color_now, false);
                    grid[47].emblem = '*';
                    grid[48].emblem = '*';
                    grid[49].emblem = '*';
                    grid[50] = new piece('k', color_now, false);
                    if (alpha > evaluation_at_this_point) alpha = evaluation_at_this_point;
                    if (beta >= alpha) { break; }
                    break;
                default:
                    int shift_in_x = -16;

                    all_of_possible_moves[0] = grid[array_of_moves[i].g_t + shift_in_x];
                    all_of_possible_moves[1] = grid[array_of_moves[i].pos];

                    grid[array_of_moves[i].g_t] = grid[i];
                    grid[array_of_moves[i].g_t].is_moved = true;

                    grid[array_of_moves[i].pos].emblem = '*';
                    grid[array_of_moves[i].g_t + shift_in_x].emblem = '*';


                    min_max = minmax(deep - 1, !color_now, alpha, beta);

                    if (min_max > evaluation_at_this_point) evaluation_at_this_point = min_max;


                    grid[array_of_moves[i].g_t + shift_in_x] = all_of_possible_moves[0];
                    grid[array_of_moves[i].g_t].emblem = '*';
                    grid[array_of_moves[i].pos] = all_of_possible_moves[1];
                    if (alpha > evaluation_at_this_point) alpha = evaluation_at_this_point;
                    if (beta >= alpha) { break; }
                    break;
            }


        }
    } else { // if black
        for (int i = 0; i < weird_stuff; i++) {
            //if(grid[array_of_moves[i].g_t].emblem == 'k') return -1000;
            all_of_possible_moves[0] = grid[array_of_moves[i].g_t];
            all_of_possible_moves[1] = grid[array_of_moves[i].pos];


            grid[array_of_moves[i].g_t] = grid[array_of_moves[i].pos];

            grid[array_of_moves[i].g_t].is_moved = true;

            grid[array_of_moves[i].pos].emblem = '*';


            min_max = minmax(deep - 1, !color_now, alpha, beta);

            if (min_max < evaluation_at_this_point) evaluation_at_this_point = min_max;


            grid[array_of_moves[i].g_t] = all_of_possible_moves[0];
            grid[array_of_moves[i].pos] = all_of_possible_moves[1];
            if (beta < evaluation_at_this_point) beta = evaluation_at_this_point;
            if (beta < alpha) { break; }
        }

        for (int i = weird_stuff; i < array_of_moves.size(); i++) {
            switch (array_of_moves[i].g_t) {
                case 100:
                    //      if(grid[array_of_moves[i].g_t].emblem == 'k') return -1000;
                    all_of_possible_moves[0] = grid[array_of_moves[i].g_t]; //i+1
                    all_of_possible_moves[1] = grid[array_of_moves[i].pos];

                    grid[array_of_moves[i].g_t] = new piece('n', color_now, true);
                    grid[array_of_moves[i].pos].emblem = '*';


                    min_max = minmax(deep - 1, !color_now, alpha, beta);

                    if (min_max < evaluation_at_this_point) evaluation_at_this_point = min_max;


                    grid[array_of_moves[i].g_t] = all_of_possible_moves[0];
                    grid[array_of_moves[i].pos] = all_of_possible_moves[1];
                    if (beta < evaluation_at_this_point) beta = evaluation_at_this_point;
                    if (beta <= alpha) { break; }
                    break;
                case 101:
                    //    if(grid[array_of_moves[i].g_t].emblem == 'k') return -1000;
                    all_of_possible_moves[0] = grid[array_of_moves[i].g_t];
                    all_of_possible_moves[1] = grid[array_of_moves[i].pos];

                    grid[array_of_moves[i].g_t] = new piece('q', color_now, true);
                    grid[array_of_moves[i].pos].emblem = '*';


                    min_max = minmax(deep - 1, !color_now, alpha, beta);

                    if (min_max < evaluation_at_this_point) evaluation_at_this_point = min_max;


                    grid[array_of_moves[i].g_t] = all_of_possible_moves[0];
                    grid[array_of_moves[i].pos] = all_of_possible_moves[1];
                    if (beta < evaluation_at_this_point) beta = evaluation_at_this_point;
                    if (beta <= alpha) { break; }
                    break;
                case 66: {

                    grid[4].emblem = '*';
                    grid[5] = new piece('r', color_now, true);
                    grid[6] = new piece('k', color_now, true);
                    grid[7].emblem = '*';
                    min_max = minmax(deep - 1, !color_now, alpha, beta);

                    if (min_max < evaluation_at_this_point) evaluation_at_this_point = min_max;
                    grid[4] = new piece('k', color_now, false);
                    grid[5].emblem = '*';
                    grid[6].emblem = '*';

                }
                    if (beta < evaluation_at_this_point) beta = evaluation_at_this_point;
                    if (beta < alpha) { break; }
                    break;
                case 666: {

                    grid[2] = grid[4];
                    grid[3] = grid[0];
                    grid[0].emblem = '*';
                    grid[1].emblem = '*';
                    grid[4].emblem = '*';
                    min_max = minmax(deep - 1, !color_now, alpha, beta);
                    if (min_max < evaluation_at_this_point) evaluation_at_this_point = min_max;

                    grid[0] = grid[3];
                    grid[0].is_moved = false;
                    grid[4] = grid[2];
                    grid[4].is_moved = false;

                    grid[1].emblem = '*';
                    grid[2].emblem = '*';
                    grid[3].emblem = '*';

                    if (beta < evaluation_at_this_point) beta = evaluation_at_this_point;
                    if (beta < alpha) { break; }
                }
                    break;
                default:
                    int shift_in_x = 16;

                    all_of_possible_moves[0] = grid[array_of_moves[i].g_t + shift_in_x];
                    all_of_possible_moves[1] = grid[array_of_moves[i].pos];

                    grid[array_of_moves[i].g_t] = grid[i];
                    grid[array_of_moves[i].g_t].is_moved = true;

                    grid[array_of_moves[i].pos].emblem = '*';
                    grid[array_of_moves[i].g_t + shift_in_x].emblem = '*';

                    min_max = minmax(deep - 1, !color_now, alpha, beta);
                    if (min_max < evaluation_at_this_point) evaluation_at_this_point = min_max;

                    grid[array_of_moves[i].g_t + shift_in_x] = all_of_possible_moves[0];
                    grid[array_of_moves[i].g_t].emblem = '*';
                    grid[array_of_moves[i].pos] = all_of_possible_moves[1];
                    if (beta < evaluation_at_this_point) beta = evaluation_at_this_point;
                    if (beta < alpha) { break; }
                    break;
            }
        }
    }


    return evaluation_at_this_point; //i guess they never max huh?
    // u've got a boyfriend i bet he never kiss ya?
}

array board::castle(bool color) {
    array possible_moves;
    if (color) {
        if (grid[0].emblem == 'r' && grid[1].emblem == '*' && grid[2].emblem == '*' && grid[3].emblem == '*' &&
            grid[4].emblem == 'k')
            if (grid[0].is_moved == 0 && grid[4].is_moved == 0) {
                for (int i = 0; i < 64; i++) {
                    if (grid[i].color != color)
                        if (possible(i, 0) || possible(i, 1) ||
                            possible(i, 2) || possible(i, 3) ||
                            possible(i, 4))
                            break;
                    if (i == 63) {
                        possible_moves.push_back(666);
                    }
                }
            }
    } else {
        if (grid[56].emblem == 'r' && grid[57].emblem == '*' && grid[58].emblem == '*' && grid[59].emblem == '*' &&
            grid[60].emblem == 'k')
            if (grid[56].is_moved == 0 && grid[60].is_moved == 0) {
                for (int i = 0; i < 64; i++) {
                    if (grid[i].color != color)
                        if (possible(i, 56) || possible(i, 57) ||
                            possible(i, 58) || possible(i, 59) ||
                            possible(i, 60))
                            break;
                    if (i == 63) {
                        possible_moves.push_back(666);
                    }
                }
            }
    }

    if (color) {
        if (grid[4].emblem == 'k' && grid[5].emblem == '*' && grid[6].emblem == '*' && grid[7].emblem == 'r')
            if (grid[7].is_moved == 0 && grid[4].is_moved == 0) {
                for (int i = 0; i < 64; i++) {
                    if (grid[i].color != color)
                        if (possible(i, 4) || possible(i, 5) ||
                            possible(i, 6) || possible(i, 7))
                            break;
                    if (i == 63) {
                        possible_moves.push_back(66);
                    }
                }
            }
    } else {
        if (grid[60].emblem == 'r' && grid[61].emblem == '*' && grid[62].emblem == '*' && grid[63].emblem == 'r')
            if (grid[63].is_moved == 0 && grid[60].is_moved == 0) {
                for (int i = 0; i < 64; i++) {
                    if (grid[i].color != color)
                        if (possible(i, 60) || possible(i, 61) ||
                            possible(i, 62) || possible(i, 63))
                            break;
                    if (i == 63) {
                        possible_moves.push_back(66);
                    }
                }
            }
    }
    /// ok więć to jest tak weź to i wklaej do bool array_of_possible  i to będzie lepszze tam
    /// na na na pierdolić
    return possible_moves;

}

array board::upgrade(bool color, int position) {
    array possible_moves;
    if (grid[position].emblem != 'p') return possible_moves;
    switch (position / 8) {
        case 1:
            if (possible(position, position - 8) || possible(position, position - 9) ||
                possible(position, position - 7)) {

                possible_moves.push_back(100);

                possible_moves.push_back(101);
            }
            break;
        case 6:
            if (possible(position, position + 8) || possible(position, position + 9) ||
                possible(position, position + 7)) {

                possible_moves.push_back(100);

                possible_moves.push_back(101);
            }
            break;
        default:
            break;

    }
    return possible_moves;
}

array board::en_passant(bool color, int position) {
// 72+

    array possible_moves;
    if (grid[position].emblem != 'p') return possible_moves;

    switch (position / 8) {
        case 3: // white
            if (!color && list_of_moves.size() > 3) {
                int i = 0;
                for (; i < list_of_moves.back().size(); i++) if (list_of_moves.back()[i] == '\t') break;
                i++;
                int hold21 = ctn(list_of_moves.back()[i + 2], list_of_moves.back()[i + 1]);
                int hold54 = ctn(list_of_moves.back()[i + 5], list_of_moves.back()[i + 4]);

                if (list_of_moves.back()[i] == 'p' && hold21 - hold54 == 16) {

                    if (hold54 == position - 1 && position % 8 != 0) {
                        possible_moves.push_back(hold21 + 48);// 8 do 16
                    }
                    if (hold54 == position + 1 && position % 8 != 7) {
                        possible_moves.push_back(hold21 + 48);
                    }

                }
            }
            break;
        case 4:  // black
            if (color && list_of_moves.size() > 3) {
                int i = 0;
                for (; i < list_of_moves.back().size(); i++) if (list_of_moves.back()[i] == '\t') break;
                i++;
                int hold21 = ctn(list_of_moves.back()[i + 2], list_of_moves.back()[i + 1]);
                int hold54 = ctn(list_of_moves.back()[i + 5], list_of_moves.back()[i + 4]);

                if (list_of_moves.back()[i] == 'p' && hold21 - hold54 == 16) {

                    if (hold54 == position - 1 && position % 8 != 0) {

                        possible_moves.push_back(hold21 + 48);
                    }
                    if (hold54 == position + 1 && position % 8 != 7) {


                        possible_moves.push_back(hold21 + 48);
                    }
                }
            }
            break;

    }
    return possible_moves;
}

void board::array_of_possible(int position, array &all_of_possible_moves) {
#if 0
    all_of_possible_moves.clear();
    int px = position / 8, py = position % 8;


    char emblem = grid[position].emblem;

    bool color = grid[position].color;

    bool is_moved = grid[position].is_moved;


    if (emblem == '*') {
        printf("error, it's not a pown \n");
        return;
    }


    switch (emblem) {
        case 'p':

            if (color) {   // czarne czyli \/

                if (grid[position + 8].emblem == '*') {
                    all_of_possible_moves.push_back(position + 8);
                    if (!is_moved && grid[position + 16].emblem == '*') all_of_possible_moves.push_back(position + 16);

                }

                if (py != 7 && grid[position + 9].emblem != '*' && grid[position + 9].color == !color)
                    all_of_possible_moves.push_back(position + 9);
                if (py != 0 && grid[position + 7].emblem != '*' && grid[position + 7].color == !color)
                    all_of_possible_moves.push_back(position + 7);


                break;
            } else {

                if (grid[position - 8].emblem == '*') {
                    all_of_possible_moves.push_back(position - 8);
                    if (!is_moved && grid[position - 16].emblem == '*')
                        all_of_possible_moves.push_back(position - 16);
                }

                if (py != 0 && grid[position - 9].emblem != '*' && grid[position - 9].color == !color)
                    all_of_possible_moves.push_back(position - 9);
                if (py != 7 && grid[position - 7].emblem != '*' && grid[position - 7].color == !color)
                    all_of_possible_moves.push_back(position - 7);

            }

            break;

        case 'n': {

            all_of_possible_moves[0] = position - 15;
            all_of_possible_moves[1] = position - 17;
            all_of_possible_moves[2] = position - 6;
            all_of_possible_moves[3] = position - 10;
            all_of_possible_moves[4] = position + 15;
            all_of_possible_moves[5] = position + 17;
            all_of_possible_moves[6] = position + 6;
            all_of_possible_moves[7] = position + 10;
            all_of_possible_moves.size(8);


            switch (py) {
                case 0:
                    all_of_possible_moves[1] = -101;
                    all_of_possible_moves[3] = -101;
                    all_of_possible_moves[4] = -101;
                    all_of_possible_moves[6] = -101;
                    all_of_possible_moves.rejects(4);
                    break;
                case 1:

                    all_of_possible_moves[3] = -101;
                    all_of_possible_moves[6] = -101;
                    all_of_possible_moves.rejects(2);

                    break;
                case 6:

                    all_of_possible_moves[2] = -101;
                    all_of_possible_moves[7] = -101;

                    all_of_possible_moves.rejects(2);

                    break;
                case 7:

                    all_of_possible_moves[0] = -101;
                    all_of_possible_moves[2] = -101;
                    all_of_possible_moves[5] = -101;
                    all_of_possible_moves[7] = -101;
                    all_of_possible_moves.rejects(4);

                    break;
                default:
                    break;
            }



            switch (px) {
                case 0:
                    all_of_possible_moves.erase(0, 4);

                    break;
                case 1:
                    all_of_possible_moves.erase(0, 2);

                    break;
                case 6:

                    all_of_possible_moves.erase(4, 6);


                    break;
                case 7:
                    all_of_possible_moves.erase(4, 8);

                    break;
                default:
                    break;
            }

            all_of_possible_moves.clr();

            for (int i = 0; i < all_of_possible_moves.size(); i++) {
                if (grid[all_of_possible_moves[i]].emblem != '*' &&
                    grid[all_of_possible_moves[i]].color == color)
                    all_of_possible_moves.erase(i);
            }

            all_of_possible_moves.clr();

        }
            break;
        case 'k':

            all_of_possible_moves[0] = position - 7;
            all_of_possible_moves[1] = position - 8;
            all_of_possible_moves[2] = position - 9;
            all_of_possible_moves[3] = position - 1;
            all_of_possible_moves[4] = position + 1;
            all_of_possible_moves[5] = position + 7;
            all_of_possible_moves[6] = position + 8;
            all_of_possible_moves[7] = position + 9;
            all_of_possible_moves.size(8);


            switch (px) {
                case 0:

                    all_of_possible_moves[0] = -101;
                    all_of_possible_moves[1] = -101;
                    all_of_possible_moves[2] = -101;
                    all_of_possible_moves.rejects(3);

                    break;
                case 7:

                    all_of_possible_moves[5] = -101;
                    all_of_possible_moves[6] = -101;
                    all_of_possible_moves[7] = -101;
                    all_of_possible_moves.rejects(3);

                    break;
                default:
                    break;
            }
            switch (py) {
                case 0:
                    all_of_possible_moves.erase(2);
                    all_of_possible_moves.erase(5);
                    all_of_possible_moves.erase(3);

                    break;
                case 7:
                    all_of_possible_moves.erase(4);
                    all_of_possible_moves.erase(0);
                    all_of_possible_moves.erase(7);
                    break;
                default:
                    break;
            }

            all_of_possible_moves.clr();

            for (int i = 0; i < all_of_possible_moves.size(); i++)
                if (grid[all_of_possible_moves[i]].emblem != '*' &&
                    grid[all_of_possible_moves[i]].color == color)
                    all_of_possible_moves.erase(i);

            all_of_possible_moves.clr();

            for (int i = 0; i < all_of_possible_moves.size(); i++)
                if (this->check(all_of_possible_moves[i]))all_of_possible_moves.erase(i);


            break;
        case 'q': {
            int temp_x = px, temp_y = py;
            int i = 0;

            while (temp_x > 0 && 7 > temp_y) all_of_possible_moves.push_back((--temp_x) * 8 + ++temp_y);


            for (; i < all_of_possible_moves.size(); i++)
                if (grid[all_of_possible_moves[i]].emblem != '*') {
                    if (grid[all_of_possible_moves[i]].color == color)
                        all_of_possible_moves.erase(i, all_of_possible_moves.size());
                    else all_of_possible_moves.erase(i + 1, all_of_possible_moves.size());
                    break;
                }



            i = all_of_possible_moves.size();
            temp_x = px;
            temp_y = py;

            while (temp_x < 7 && 7 > temp_y)
                all_of_possible_moves.push_back((++temp_x) * 8 + ++temp_y);
            temp_x = px;
            temp_y = py;
            for (; i < all_of_possible_moves.size(); i++)
                if (grid[all_of_possible_moves[i]].emblem != '*') {
                    if (grid[all_of_possible_moves[i]].color == color)
                        all_of_possible_moves.erase(i, all_of_possible_moves.size());
                    else all_of_possible_moves.erase(i + 1, all_of_possible_moves.size());
                    break;
                }//y
            i = all_of_possible_moves.size();
            while (temp_x < 7 && 0 < temp_y)
                all_of_possible_moves.push_back((++temp_x) * 8 + --temp_y);
            temp_x = px;
            temp_y = py;
            for (; i < all_of_possible_moves.size(); i++)
                if (grid[all_of_possible_moves[i]].emblem != '*') {
                    if (grid[all_of_possible_moves[i]].color == color)
                        all_of_possible_moves.erase(i, all_of_possible_moves.size());
                    else all_of_possible_moves.erase(i + 1, all_of_possible_moves.size());
                    break;
                }
            i = all_of_possible_moves.size();
            while (temp_x > 0 && 0 < temp_y)
                all_of_possible_moves.push_back((--temp_x) * 8 + --temp_y);
            for (; i < all_of_possible_moves.size(); i++)
                if (grid[all_of_possible_moves[i]].emblem != '*') {
                    if (grid[all_of_possible_moves[i]].color == color)
                        all_of_possible_moves.erase(i, all_of_possible_moves.size());
                    else all_of_possible_moves.erase(i + 1, all_of_possible_moves.size());
                    break;
                }//r
            i = all_of_possible_moves.size();
            for (int z = 1; z <= px; z++)all_of_possible_moves.push_back(position - (z * 8));
            for (; i < all_of_possible_moves.size(); i++)
                if (grid[all_of_possible_moves[i]].emblem != '*') {
                    if (grid[all_of_possible_moves[i]].color == color)
                        all_of_possible_moves.erase(i, all_of_possible_moves.size());
                    else all_of_possible_moves.erase(i + 1, all_of_possible_moves.size());
                    break;
                }
            i = all_of_possible_moves.size();
            for (int z = 1; z < 8 - px; z++)all_of_possible_moves.push_back(position + (z * 8));
            for (; i < all_of_possible_moves.size(); i++)
                if (grid[all_of_possible_moves[i]].emblem != '*') {
                    if (grid[all_of_possible_moves[i]].color == color)
                        all_of_possible_moves.erase(i, all_of_possible_moves.size());
                    else all_of_possible_moves.erase(i + 1, all_of_possible_moves.size());
                    break;
                }//y


            i = all_of_possible_moves.size();

            for (int z = 1; z <= py; z++)all_of_possible_moves.push_back(position - z);
            for (; i < all_of_possible_moves.size(); i++)
                if (grid[all_of_possible_moves[i]].emblem != '*') {
                    if (grid[all_of_possible_moves[i]].color == color)
                        all_of_possible_moves.erase(i, all_of_possible_moves.size());
                    else all_of_possible_moves.erase(i + 1, all_of_possible_moves.size());
                    break;
                }
            i = all_of_possible_moves.size();
            for (int z = 1; z < 8 - py; z++)all_of_possible_moves.push_back(position + z);
            for (; i < all_of_possible_moves.size(); i++)
                if (grid[all_of_possible_moves[i]].emblem != '*') {
                    if (grid[all_of_possible_moves[i]].color == color)
                        all_of_possible_moves.erase(i, all_of_possible_moves.size());
                    else all_of_possible_moves.erase(i + 1, all_of_possible_moves.size());
                    break;
                }
        }
            break;
        case 'b': {// x
            int temp_x = px, temp_y = py;
            int i = 0;
            while (temp_x > 0 && 7 > temp_y)all_of_possible_moves.push_back((--temp_x) * 8 + ++temp_y);
            temp_x = px;
            temp_y = py;
            for (; i < all_of_possible_moves.size(); i++)
                if (grid[all_of_possible_moves[i]].emblem != '*') {
                    if (grid[all_of_possible_moves[i]].color == color)
                        all_of_possible_moves.erase(i, all_of_possible_moves.size());
                    else all_of_possible_moves.erase(i + 1, all_of_possible_moves.size());
                    break;
                }
            i = all_of_possible_moves.size();
            while (temp_x < 7 && 7 > temp_y)all_of_possible_moves.push_back((++temp_x) * 8 + ++temp_y);
            temp_x = px;
            temp_y = py;
            for (; i < all_of_possible_moves.size(); i++)
                if (grid[all_of_possible_moves[i]].emblem != '*') {
                    if (grid[all_of_possible_moves[i]].color == color)
                        all_of_possible_moves.erase(i, all_of_possible_moves.size());
                    else all_of_possible_moves.erase(i + 1, all_of_possible_moves.size());
                    break;
                }//y
            i = all_of_possible_moves.size();
            while (temp_x < 7 && 0 < temp_y)all_of_possible_moves.push_back((++temp_x) * 8 + --temp_y);
            temp_x = px;
            temp_y = py;
            for (; i < all_of_possible_moves.size(); i++)
                if (grid[all_of_possible_moves[i]].emblem != '*') {
                    if (grid[all_of_possible_moves[i]].color == color)
                        all_of_possible_moves.erase(i, all_of_possible_moves.size());
                    else all_of_possible_moves.erase(i + 1, all_of_possible_moves.size());
                    break;
                }
            i = all_of_possible_moves.size();
            while (temp_x > 0 && 0 < temp_y)all_of_possible_moves.push_back((--temp_x) * 8 + --temp_y);
            for (; i < all_of_possible_moves.size(); i++)
                if (grid[all_of_possible_moves[i]].emblem != '*') {
                    if (grid[all_of_possible_moves[i]].color == color)
                        all_of_possible_moves.erase(i, all_of_possible_moves.size());
                    else all_of_possible_moves.erase(i + 1, all_of_possible_moves.size());
                    break;
                }
        }
            break;
        case 'r': {
            int i = 0;//x
            for (int z = 1; z <= px; z++)all_of_possible_moves.push_back(position - (z * 8));
            for (; i < all_of_possible_moves.size(); i++)
                if (grid[all_of_possible_moves[i]].emblem != '*') {
                    if (grid[all_of_possible_moves[i]].color == color)
                        all_of_possible_moves.erase(i, all_of_possible_moves.size());
                    else all_of_possible_moves.erase(i + 1, all_of_possible_moves.size());
                    break;
                }
            i = all_of_possible_moves.size();
            for (int z = 1; z < 8 - px; z++)all_of_possible_moves.push_back(position + (z * 8));
            for (; i < all_of_possible_moves.size(); i++)
                if (grid[all_of_possible_moves[i]].emblem != '*') {
                    if (grid[all_of_possible_moves[i]].color == color)
                        all_of_possible_moves.erase(i, all_of_possible_moves.size());
                    else all_of_possible_moves.erase(i + 1, all_of_possible_moves.size());
                    break;
                }//y
            i = all_of_possible_moves.size();
            for (int z = 1; z <= py; z++)all_of_possible_moves.push_back(position - z);
            for (; i < all_of_possible_moves.size(); i++)
                if (grid[all_of_possible_moves[i]].emblem != '*') {
                    if (grid[all_of_possible_moves[i]].color == color)
                        all_of_possible_moves.erase(i, all_of_possible_moves.size());
                    else all_of_possible_moves.erase(i + 1, all_of_possible_moves.size());
                    break;
                }
            i = all_of_possible_moves.size();
            for (int z = 1; z < 8 - py; z++)all_of_possible_moves.push_back(position + z);
            for (; i < all_of_possible_moves.size(); i++)
                if (grid[all_of_possible_moves[i]].emblem != '*') {
                    if (grid[all_of_possible_moves[i]].color == color)
                        all_of_possible_moves.erase(i, all_of_possible_moves.size());
                    else
                        all_of_possible_moves.erase(i + 1, all_of_possible_moves.size());
                    break;

                }


        }
            break;
        default:
            printf("well %d not a pon u dumbas \n", position);
            break;
    }
    all_of_possible_moves.clr();

    return;
#else
    all_of_possible_moves.clear();
    int px = position / 8, py = position % 8;


    char emblem = grid[position].emblem;

    bool color = grid[position].color;

    bool is_moved = grid[position].is_moved;


    if (emblem == '*') {
        printf("error, it's not a pown \n");
        return;
    }


    switch (emblem) {
        case 'p':

            if (color) {   // czarne czyli \/

                if (grid[position + 8].emblem == '*') {
                    all_of_possible_moves.push_back(position + 8);
                    if (!is_moved && grid[position + 16].emblem == '*') all_of_possible_moves.push_back(position + 16);

                }

                if (py != 7 && grid[position + 9].emblem != '*' && grid[position + 9].color == !color)
                    all_of_possible_moves.push_back(position + 9);
                if (py != 0 && grid[position + 7].emblem != '*' && grid[position + 7].color == !color)
                    all_of_possible_moves.push_back(position + 7);


                break;
            } else {

                if (grid[position - 8].emblem == '*') {
                    all_of_possible_moves.push_back(position - 8);
                    if (!is_moved && grid[position - 16].emblem == '*')
                        all_of_possible_moves.push_back(position - 16);
                }

                if (py != 0 && grid[position - 9].emblem != '*' && grid[position - 9].color == !color)
                    all_of_possible_moves.push_back(position - 9);
                if (py != 7 && grid[position - 7].emblem != '*' && grid[position - 7].color == !color)
                    all_of_possible_moves.push_back(position - 7);

            }

            return;

        case 'n': {

            all_of_possible_moves[0] = position - 15;
            all_of_possible_moves[1] = position - 17;
            all_of_possible_moves[2] = position - 6;
            all_of_possible_moves[3] = position - 10;
            all_of_possible_moves[4] = position + 15;
            all_of_possible_moves[5] = position + 17;
            all_of_possible_moves[6] = position + 6;
            all_of_possible_moves[7] = position + 10;
            all_of_possible_moves.size(8);


            switch (py) {
                case 0:
                    all_of_possible_moves[1] = -101;
                    all_of_possible_moves[3] = -101;
                    all_of_possible_moves[4] = -101;
                    all_of_possible_moves[6] = -101;
                    all_of_possible_moves.rejects(4);
                    break;
                case 1:

                    all_of_possible_moves[3] = -101;
                    all_of_possible_moves[6] = -101;
                    all_of_possible_moves.rejects(2);

                    break;
                case 6:

                    all_of_possible_moves[2] = -101;
                    all_of_possible_moves[7] = -101;

                    all_of_possible_moves.rejects(2);

                    break;
                case 7:

                    all_of_possible_moves[0] = -101;
                    all_of_possible_moves[2] = -101;
                    all_of_possible_moves[5] = -101;
                    all_of_possible_moves[7] = -101;
                    all_of_possible_moves.rejects(4);

                    break;
                default:
                    break;
            }


            switch (px) {
                case 0:
                    all_of_possible_moves.erase(0, 4);

                    break;
                case 1:
                    all_of_possible_moves.erase(0, 2);

                    break;
                case 6:

                    all_of_possible_moves.erase(4, 6);


                    break;
                case 7:
                    all_of_possible_moves.erase(4, 8);

                    break;
                default:
                    break;
            }

            all_of_possible_moves.clr();

            for (int i = 0; i < all_of_possible_moves.size(); i++) {
                if (grid[all_of_possible_moves[i]].emblem != '*' &&
                    grid[all_of_possible_moves[i]].color == color)
                    all_of_possible_moves.erase(i);
            }

            all_of_possible_moves.clr();

        }
            return;
        case 'k':

            all_of_possible_moves[0] = position - 7;
            all_of_possible_moves[1] = position - 8;
            all_of_possible_moves[2] = position - 9;
            all_of_possible_moves[3] = position - 1;
            all_of_possible_moves[4] = position + 1;
            all_of_possible_moves[5] = position + 7;
            all_of_possible_moves[6] = position + 8;
            all_of_possible_moves[7] = position + 9;
            all_of_possible_moves.size(8);


            switch (px) {
                case (0):

                    all_of_possible_moves[0] = -101;
                    all_of_possible_moves[1] = -101;
                    all_of_possible_moves[2] = -101;
                    all_of_possible_moves.rejects(3);

                    break;
                case 7:

                    all_of_possible_moves[5] = -101;
                    all_of_possible_moves[6] = -101;
                    all_of_possible_moves[7] = -101;
                    all_of_possible_moves.rejects(3);

                    break;
                default:
                    break;
            }
            switch (py) {
                case 0:
                    all_of_possible_moves.erase(2);
                    all_of_possible_moves.erase(5);
                    all_of_possible_moves.erase(3);

                    break;
                case 7:
                    all_of_possible_moves.erase(4);
                    all_of_possible_moves.erase(0);
                    all_of_possible_moves.erase(7);
                    break;
                default:
                    break;
            }

            all_of_possible_moves.clr();

            for (int i = 0; i < all_of_possible_moves.size(); i++)
                if (grid[all_of_possible_moves[i]].emblem != '*' &&
                    grid[all_of_possible_moves[i]].color == color)
                    all_of_possible_moves.erase(i);

            all_of_possible_moves.clr();

            for (int i = 0; i < all_of_possible_moves.size(); i++)
                if (this->check(all_of_possible_moves[i]))all_of_possible_moves.erase(i);
            all_of_possible_moves.clr();

            return;
        case 'q': {
            int temp_x = px, temp_y = py;
            int aktual_position;
            while (temp_x > 0 && 7 > temp_y) {
                aktual_position = (--temp_x) * 8 + (++temp_y);

                if (grid[aktual_position].emblem != '*') {
                    if (grid[aktual_position].color == color) break;
                    all_of_possible_moves.push_back(aktual_position);
                    break;


                }
                all_of_possible_moves.push_back(aktual_position);


            }

            temp_x = px;
            temp_y = py;

            while (temp_x < 7 && 7 > temp_y) {
                aktual_position = (++temp_x) * 8 + (++temp_y);
                if (grid[aktual_position].emblem != '*') {
                    if (grid[aktual_position].color == color) break;
                    all_of_possible_moves.push_back(aktual_position);
                    break;


                }
                all_of_possible_moves.push_back(aktual_position);
            }
            temp_x = px;
            temp_y = py;

            while (temp_x < 7 && 0 < temp_y) {
                aktual_position = (++temp_x) * 8 + (--temp_y);
                if (grid[aktual_position].emblem != '*') {
                    if (grid[aktual_position].color == color) break;
                    all_of_possible_moves.push_back(aktual_position);
                    break;


                }
                all_of_possible_moves.push_back(aktual_position);

            }
            temp_x = px;
            temp_y = py;
            while (temp_x > 0 && 0 < temp_y) {
                aktual_position = (--temp_x) * 8 + (--temp_y);

                if (grid[aktual_position].emblem != '*') {
                    if (grid[aktual_position].color == color) break;
                    all_of_possible_moves.push_back(aktual_position);
                    break;


                }
                all_of_possible_moves.push_back(aktual_position);
            }


            for (int z = 1; z <= px; z++) {
                aktual_position = position - (z * 8);


                if (grid[aktual_position].emblem != '*') {
                    if (grid[aktual_position].color == color) break;
                    all_of_possible_moves.push_back(aktual_position);
                    break;


                }
                all_of_possible_moves.push_back(aktual_position);
            }


            for (int z = 1; z < 8 - px; z++) {
                aktual_position = position + (z * 8);


                if (grid[aktual_position].emblem != '*') {
                    if (grid[aktual_position].color == color) break;
                    all_of_possible_moves.push_back(aktual_position);
                    break;


                }
                all_of_possible_moves.push_back(aktual_position);
            }

            for (int z = 1; z <= py; z++) {
                aktual_position = position - z;

                if (grid[aktual_position].emblem != '*') {
                    if (grid[aktual_position].color == color) break;
                    all_of_possible_moves.push_back(aktual_position);
                    break;


                }
                all_of_possible_moves.push_back(aktual_position);
            }


            for (int z = 1; z < 8 - py; z++) {
                aktual_position = position + z;

                if (grid[aktual_position].emblem != '*') {
                    if (grid[aktual_position].color == color) break;
                    all_of_possible_moves.push_back(aktual_position);
                    break;
                }
                all_of_possible_moves.push_back(aktual_position);
            }
        }
            return;
        case 'b': {
            int temp_x = px, temp_y = py;
            int aktual_position;
            while (temp_x > 0 && 7 > temp_y) {
                aktual_position = (--temp_x) * 8 + (++temp_y);
                if (grid[aktual_position].emblem != '*') {
                    if (grid[aktual_position].color == color) break;
                    all_of_possible_moves.push_back(aktual_position);
                    break;


                }
                all_of_possible_moves.push_back(aktual_position);


            }

            temp_x = px;
            temp_y = py;

            while (temp_x < 7 && 7 > temp_y) {
                aktual_position = (++temp_x) * 8 + (++temp_y);
                if (grid[aktual_position].emblem != '*') {
                    if (grid[aktual_position].color == color) break;
                    all_of_possible_moves.push_back(aktual_position);
                    break;


                }
                all_of_possible_moves.push_back(aktual_position);
            }
            temp_x = px;
            temp_y = py;
            while (temp_x < 7 && 0 < temp_y) {
                aktual_position = (++temp_x) * 8 + (--temp_y);
                if (grid[aktual_position].emblem != '*') {
                    if (grid[aktual_position].color == color) break;
                    all_of_possible_moves.push_back(aktual_position);
                    break;


                }
                all_of_possible_moves.push_back(aktual_position);

            }
            temp_x = px;
            temp_y = py;
            while (temp_x > 0 && 0 < temp_y) {
                aktual_position = (--temp_x) * 8 + (--temp_y);

                if (grid[aktual_position].emblem != '*') {
                    if (grid[aktual_position].color == color) break;
                    all_of_possible_moves.push_back(aktual_position);
                    break;


                }
                all_of_possible_moves.push_back(aktual_position);
            }


        }
            return;
        case 'r': {
            int aktual_position;
            for (int z = 1; z <= px; z++) {
                aktual_position = position - (z * 8);


                if (grid[aktual_position].emblem != '*') {
                    if (grid[aktual_position].color == color) break;
                    all_of_possible_moves.push_back(aktual_position);
                    break;


                }
                all_of_possible_moves.push_back(aktual_position);
            }


            for (int z = 1; z < 8 - px; z++) {
                aktual_position = position + (z * 8);

                if (grid[aktual_position].emblem != '*') {
                    if (grid[aktual_position].color == color) break;
                    all_of_possible_moves.push_back(aktual_position);
                    break;
                }
                all_of_possible_moves.push_back(aktual_position);
            }

            for (int z = 1; z <= py; z++) {
                aktual_position = position - z;

                if (grid[aktual_position].emblem != '*') {
                    if (grid[aktual_position].color == color) break;
                    all_of_possible_moves.push_back(aktual_position);
                    break;


                }
                all_of_possible_moves.push_back(aktual_position);
            }
            for (int z = 1; z < 8 - py; z++) {
                aktual_position = position + z;

                if (grid[aktual_position].emblem != '*') {
                    if (grid[aktual_position].color == color) break;
                    all_of_possible_moves.push_back(aktual_position);
                    break;
                }
                all_of_possible_moves.push_back(aktual_position);
            }
        }

            return;
        default:
            printf("well %d not a pon u dumbas \n", position);
            break;
    }
    all_of_possible_moves.clr();

    return;
#endif

}

bool board::possible(int position, int go_to) {

    int px = position / 8, py = position % 8, gx = go_to / 8, gy = go_to % 8;
    char emblem = grid[position].emblem;
    bool color = grid[position].color;


    switch (emblem) {
        case 'p': {
            if (color) {
                if (go_to == position + 8 && grid[go_to].emblem == '*') return true;
                if (go_to == position + 16 && grid[go_to].emblem == '*') return true;
                if (go_to == position + 7 && grid[go_to].emblem != '*' && grid[go_to].color != color) return true;
                if (go_to == position + 9 && grid[go_to].emblem != '*' && grid[go_to].color != color) return true;
            } else {
                if (go_to == position - 8 && grid[go_to].emblem == '*') return true;
                if (go_to == position - 16 && grid[go_to].emblem == '*') return true;
                if (go_to == position - 7 && grid[go_to].emblem != '*' && grid[go_to].color != color) return true;
                if (go_to == position - 9 && grid[go_to].emblem != '*' && grid[go_to].color != color) return true;

            }
        }
            break;
        case 'n': {
            int all_of_possible_moves[8] = {position - 17, position - 15, position - 10, position - 6, position + 6,
                                            position + 10,
                                            position + 15, position + 17};
            return binary(go_to, all_of_possible_moves);
        }
            break;
        case 'k': {
            int all_of_possible_moves[8] = {position - 9, position - 8, position - 7, position - 1, position + 1,
                                            position + 7,
                                            position + 8,
                                            position + 9};
            return binary(go_to, all_of_possible_moves);
        }
            break;
        case 'q': {


            int b = px + py;
            if (b == gy + gx) {/// \ <- this
                if (gy < py) {

                    for (int i = 0; i < full_board_of_moves_4_bishop[position][2].size(); i++) {
                        if (grid[full_board_of_moves_4_bishop[position][2][i]].emblem != '*')
                            if (grid[full_board_of_moves_4_bishop[position][2][i]].color != color)
                                return full_board_of_moves_4_bishop[position][2][i] == go_to;
                        return false;

                        if (full_board_of_moves_4_bishop[position][2][i] == go_to) return true;
                    }
                } else {
                    for (int i = 0; i < full_board_of_moves_4_bishop[position][0].size(); i++) {
                        if (grid[full_board_of_moves_4_bishop[position][0][i]].emblem != '*')
                            if (grid[full_board_of_moves_4_bishop[position][0][i]].color != color)
                                return full_board_of_moves_4_bishop[position][0][i] == go_to;
                        return false;

                        if (full_board_of_moves_4_bishop[position][0][i] == go_to) return true;
                    }
                }


                for (int i = 0; i < full_board_of_moves_4_bishop[position][2].size(); i++) {
                    if (grid[full_board_of_moves_4_bishop[position][2][i]].emblem != '*')
                        if (grid[full_board_of_moves_4_bishop[position][2][i]].color != color)
                            return full_board_of_moves_4_bishop[position][2][i] == go_to;
                    return false;

                    if (full_board_of_moves_4_bishop[position][2][i] == go_to) return true;
                }
            }


            b = py - px;
            if (b + gx == gy) {     /// \ <-this one
                if (gy < py) {
                    for (int i = 0; i < full_board_of_moves_4_bishop[position][3].size(); i++) {
                        if (grid[full_board_of_moves_4_bishop[position][3][i]].emblem != '*')
                            if (grid[full_board_of_moves_4_bishop[position][3][i]].color != color)
                                return full_board_of_moves_4_bishop[position][3][i] == go_to;
                        return false;

                        if (full_board_of_moves_4_bishop[position][3][i] == go_to) return true;
                    }
                } else {
                    for (int i = 0; i < full_board_of_moves_4_bishop[position][1].size(); i++) {
                        if (grid[full_board_of_moves_4_bishop[position][1][i]].emblem != '*')
                            if (grid[full_board_of_moves_4_bishop[position][1][i]].color != color)
                                return full_board_of_moves_4_bishop[position][1][i] == go_to;
                        return false;

                        if (full_board_of_moves_4_bishop[position][2][i] == go_to) return true;
                    }
                }

            }


            if (px == gx) {

                if (py < gy) {

                    for (int i = 0; i < full_board_of_moves_4_rook[position][2].size(); i++) {
                        if (grid[full_board_of_moves_4_rook[position][1][i]].emblem != '*')
                            if (grid[full_board_of_moves_4_rook[position][1][i]].color != color)
                                return full_board_of_moves_4_rook[position][1][i] == go_to;

                        return false;
                        if (full_board_of_moves_4_rook[position][1][i] == go_to) return true;
                    }
                } else {
                    for (int i = 0; i < full_board_of_moves_4_rook[position][2].size(); i++) {
                        if (grid[full_board_of_moves_4_rook[position][3][i]].emblem != '*')
                            if (grid[full_board_of_moves_4_rook[position][3][i]].color != color)
                                return full_board_of_moves_4_rook[position][3][i] == go_to;
                        return false;
                        if (full_board_of_moves_4_rook[position][3][i] == go_to) return true;
                    }
                }


            }
            if (py == gy) {


                if (px > gx) {
                    for (int i = 0; i < full_board_of_moves_4_rook[position][2].size(); i++) {
                        if (grid[full_board_of_moves_4_rook[position][0][i]].emblem != '*')
                            if (grid[full_board_of_moves_4_rook[position][0][i]].color != color)
                                return full_board_of_moves_4_rook[position][0][i] == go_to;
                        return false;
                        if (full_board_of_moves_4_rook[position][0][i] == go_to) return true;
                    }

                } else {
                    for (int i = 0; i < full_board_of_moves_4_rook[position][2].size(); i++) {
                        if (grid[full_board_of_moves_4_rook[position][2][i]].emblem != '*')
                            if (grid[full_board_of_moves_4_rook[position][2][i]].color != color)
                                return full_board_of_moves_4_rook[position][2][i] == go_to;
                        return false;
                        if (full_board_of_moves_4_rook[position][2][i] == go_to) return true;
                    }
                }
            }
        }

            break;
        case 'b': {
            int b = px + py;
            if (b == gy + gx) {/// \ <- this
                if (gy < py) {

                    for (int i = 0; i < full_board_of_moves_4_bishop[position][2].size(); i++) {
                        if (grid[full_board_of_moves_4_bishop[position][2][i]].emblem != '*')
                            if (grid[full_board_of_moves_4_bishop[position][2][i]].color != color)
                                return full_board_of_moves_4_bishop[position][2][i] == go_to;
                        return false;

                        if (full_board_of_moves_4_bishop[position][2][i] == go_to) return true;
                    }
                } else {
                    for (int i = 0; i < full_board_of_moves_4_bishop[position][0].size(); i++) {
                        if (grid[full_board_of_moves_4_bishop[position][0][i]].emblem != '*')
                            if (grid[full_board_of_moves_4_bishop[position][0][i]].color != color)
                                return full_board_of_moves_4_bishop[position][0][i] == go_to;
                        return false;

                        if (full_board_of_moves_4_bishop[position][0][i] == go_to) return true;
                    }
                }


                for (int i = 0; i < full_board_of_moves_4_bishop[position][2].size(); i++) {
                    if (grid[full_board_of_moves_4_bishop[position][2][i]].emblem != '*')
                        if (grid[full_board_of_moves_4_bishop[position][2][i]].color != color)
                            return full_board_of_moves_4_bishop[position][2][i] == go_to;
                    return false;

                    if (full_board_of_moves_4_bishop[position][2][i] == go_to) return true;
                }
            }


            b = py - px;
            if (b + gx == gy) {     /// \ <-this one
                if (gy < py) {
                    for (int i = 0; i < full_board_of_moves_4_bishop[position][3].size(); i++) {
                        if (grid[full_board_of_moves_4_bishop[position][3][i]].emblem != '*')
                            if (grid[full_board_of_moves_4_bishop[position][3][i]].color != color)
                                return full_board_of_moves_4_bishop[position][3][i] == go_to;
                        return false;

                        if (full_board_of_moves_4_bishop[position][3][i] == go_to) return true;
                    }
                } else {
                    for (int i = 0; i < full_board_of_moves_4_bishop[position][1].size(); i++) {
                        if (grid[full_board_of_moves_4_bishop[position][1][i]].emblem != '*')
                            if (grid[full_board_of_moves_4_bishop[position][1][i]].color != color)
                                return full_board_of_moves_4_bishop[position][1][i] == go_to;
                        return false;

                        if (full_board_of_moves_4_bishop[position][2][i] == go_to) return true;
                    }
                }

            }


            if (px == gx) {

                if (py < gy) {

                    for (int i = 0; i < full_board_of_moves_4_rook[position][2].size(); i++) {
                        if (grid[full_board_of_moves_4_rook[position][1][i]].emblem != '*')
                            if (grid[full_board_of_moves_4_rook[position][1][i]].color != color)
                                return full_board_of_moves_4_rook[position][1][i] == go_to;

                        return false;
                        if (full_board_of_moves_4_rook[position][1][i] == go_to) return true;
                    }
                } else {
                    for (int i = 0; i < full_board_of_moves_4_rook[position][2].size(); i++) {
                        if (grid[full_board_of_moves_4_rook[position][3][i]].emblem != '*')
                            if (grid[full_board_of_moves_4_rook[position][3][i]].color != color)
                                return full_board_of_moves_4_rook[position][3][i] == go_to;
                        return false;
                        if (full_board_of_moves_4_rook[position][3][i] == go_to) return true;
                    }
                }


            }
        }
            break;
        case 'r': {
            if (px == gx) {
                if (py < gy) {

                    for (int i = 0; i < full_board_of_moves_4_rook[position][2].size(); i++) {
                        if (grid[full_board_of_moves_4_rook[position][1][i]].emblem != '*')
                            if (grid[full_board_of_moves_4_rook[position][1][i]].color != color)
                                return full_board_of_moves_4_rook[position][1][i] == go_to;

                        return false;
                        if (full_board_of_moves_4_rook[position][1][i] == go_to) return true;
                    }
                } else {
                    for (int i = 0; i < full_board_of_moves_4_rook[position][2].size(); i++) {
                        if (grid[full_board_of_moves_4_rook[position][3][i]].emblem != '*')
                            if (grid[full_board_of_moves_4_rook[position][3][i]].color != color)
                                return full_board_of_moves_4_rook[position][3][i] == go_to;
                        return false;
                        if (full_board_of_moves_4_rook[position][3][i] == go_to) return true;
                    }
                }


            }
            if (py == gy) {
                if (px > gx) {
                    for (int i = 0; i < full_board_of_moves_4_rook[position][2].size(); i++) {
                        if (grid[full_board_of_moves_4_rook[position][0][i]].emblem != '*')
                            if (grid[full_board_of_moves_4_rook[position][0][i]].color != color)
                                return full_board_of_moves_4_rook[position][0][i] == go_to;
                        return false;
                        if (full_board_of_moves_4_rook[position][0][i] == go_to) return true;
                    }

                } else {
                    for (int i = 0; i < full_board_of_moves_4_rook[position][2].size(); i++) {
                        if (grid[full_board_of_moves_4_rook[position][2][i]].emblem != '*')
                            if (grid[full_board_of_moves_4_rook[position][2][i]].color != color)
                                return full_board_of_moves_4_rook[position][2][i] == go_to;
                        return false;
                        if (full_board_of_moves_4_rook[position][2][i] == go_to) return true;
                    }
                }
            }
        }
            break;


    }
    return false;


}

bool board::check(int position) {

    for (int i = 0; i < 64; i++)
        if (grid[i].emblem != '*' && grid[i].color != grid[position].color)
            if (this->possible(i, position)) return true;
    return false;

}

void board::admin_l(std::string all_of_possible_moves) {
    std::ifstream myfile;
    myfile.open(all_of_possible_moves, std::ios::in);
    if (myfile.good()) {
        char a;
        for (int i = 0; i < 64; ++i) {
            myfile >> a;
            if (a != '*') {
                if (static_cast<int>(a) >= 97) grid[i] = new piece(a, false);
                else grid[i] = new piece((char) (a + 32), true);

            } else grid[i] = new piece();

        }

        printf("loaded\n");

    } else printf("file error");

    myfile.close();

}

void board::cvc(bool color, int time_2_move, int time_2_w8, std::string location, bool who_on_top, int deepth_for_bip) {
    // i'm white in file the white is alvays up

    int no_more_kings = 0;

    bool color_now = 0;

    bool not_yet = true;

    std::fstream plik;
    plik.open(location, std::ios::trunc);
    plik.close();

    if (!color) {
        show();
        mov temp = bip(color, deepth_for_bip, 'y');
        grid[temp.g_t] = grid[temp.pos];
        grid[temp.g_t].is_moved = true;
        grid[temp.pos] = new piece();

        printf("%c%d -> ", (char) temp.pos % 8 + 97, ((temp.pos / 8) - 8) * (-1));
        printf("%c%d  ", (char) temp.g_t % 8 + 97, ((temp.g_t / 8) - 8) * (-1));
        printf("%f  \a\n", temp.eva);


        for (int i = 0; i < 64; i++) {
            if (grid[i].emblem == 'k')grid[i].color ? no_more_kings-- : no_more_kings++;
        }
        std::ofstream plik;
        plik.open(location, std::ios::app);
        if (plik.good()) {
            plik << 'p';
            for (int i = 0; i < 64; i++) {
                switch (grid[i].emblem) {
                    case 'k':
                        if (!grid[i].color)plik << 'A';
                        else plik << 'a';
                        break;
                    case 'q':
                        if (!grid[i].color)plik << 'B';
                        else plik << 'b';
                        break;
                    case 'r':
                        if (!grid[i].color)plik << 'C';
                        else plik << 'c';
                        break;
                    case 'b':
                        if (!grid[i].color)plik << 'D';
                        else plik << 'd';
                        break;
                    case 'n':
                        if (!grid[i].color)plik << 'E';
                        else plik << 'e';
                        break;
                    case 'p':
                        if (!grid[i].color)plik << 'F';
                        else plik << 'f';
                        break;
                    case '*':
                        plik << 'g';
                        break;
                }
            }
            plik << '\n';
        }

        plik.close();
    }

    while (no_more_kings == 0) {
        while (not_yet) {
            std::string slice;
            std::string sliceh;
            std::fstream plik;
            plik.open(location, std::ios::in);
            if (plik.good()) {
                slice.clear();
                while (getline(plik, sliceh)) {
                    slice.clear();
                    for (auto i:sliceh) slice.push_back(i);
                }
                std::cout << slice;
                if (slice[0] != 'p') {
                    not_yet = false;
                    for (int i = 1; i < 65; i++) {
                        if (slice[i] >= 97) {
                            grid[i-1].color = BLACK;
                        } else {
                            slice[i] += 32;
                            grid[i-1].color = WHITE;
                        }
                        switch (slice[i]) {
                            case 'a':
                                grid[i-1].emblem = 'k';
                                break;
                            case 'b':
                                grid[i-1].emblem = 'q';
                                break;
                            case 'c':
                                grid[i-1].emblem = 'r';
                                break;
                            case 'd':
                                grid[i-1].emblem = 'b';
                                break;
                            case 'e':
                                grid[i-1].emblem = 'n';
                                break;
                            case 'f':
                                grid[i-1].emblem = 'p';
                                break;
                            case 'g':
                                grid[i-1].emblem = '*';
                                break;
                        }
                    }
                }
            }
            plik.close();
            std::cout << "\r";
            std::string timer = "loading";
            for (int i = 0; i < 4; i++) {
                timer.push_back('.');
                std::cout << timer << "\t\t\t\t\t\t\t\t\t\t\t\r";
                w8(time_2_w8 / 4);
            }
            std::cout << "\rchecking...";
        }
        not_yet = true;

        show();
        // upload
        mov temp = bip(color, deepth_for_bip, 'y');

        grid[temp.g_t] = grid[temp.pos];
        grid[temp.g_t].is_moved = true;
        grid[temp.pos] = new piece();

        printf("%c%d -> ", (char) temp.pos % 8 + 97, ((temp.pos / 8) - 8) * (-1));
        printf("%c%d  ", (char) temp.g_t % 8 + 97, ((temp.g_t / 8) - 8) * (-1));
        printf("%f  \a\n", temp.eva);


        for (int i = 0; i < 64; i++) {

            if (grid[i].emblem == 'k')grid[i].color ? no_more_kings-- : no_more_kings++;
        }

        std::ofstream plik;
        plik.open(location, std::ios::app);
        if (plik.good()) {
            plik << 'p';
            for (int i = 0; i < 64; i++) {
                switch (grid[i].emblem) {
                    case 'k':
                        if (!grid[i].color)plik << 'A';
                        else plik << 'a';
                        break;
                    case 'q':
                        if (!grid[i].color)plik << 'B';
                        else plik << 'b';
                        break;
                    case 'r':
                        if (!grid[i].color)plik << 'C';
                        else plik << 'c';
                        break;
                    case 'b':
                        if (!grid[i].color)plik << 'D';
                        else plik << 'd';
                        break;
                    case 'n':
                        if (!grid[i].color)plik << 'E';
                        else plik << 'e';
                        break;
                    case 'p':
                        if (!grid[i].color)plik << 'F';
                        else plik << 'f';
                        break;
                    case '*':
                        plik << 'g';
                        break;
                }
            }
            plik << '\n';
            plik.close();
        }
    }
}

void board::cc() {
int  no_more_kings=0;
    while(true){
        printf("white:\n");
        show();
        mov temp = bip(WHITE, 4, 'y');

        grid[temp.g_t] = grid[temp.pos];
        grid[temp.g_t].is_moved = true;
        grid[temp.pos] = new piece();

        printf("%c%d -> ", (char) temp.pos % 8 + 97, ((temp.pos / 8) - 8) * (-1));
        printf("%c%d  ", (char) temp.g_t % 8 + 97, ((temp.g_t / 8) - 8) * (-1));
        printf("%f  \a\n", temp.eva);

        printf("black:\n");
        show();
        temp = bip(BLACK, 4, 'y');

        grid[temp.g_t] = grid[temp.pos];
        grid[temp.g_t].is_moved = true;
        grid[temp.pos] = new piece();

        printf("%c%d -> ", (char) temp.pos % 8 + 97, ((temp.pos / 8) - 8) * (-1));
        printf("%c%d  ", (char) temp.g_t % 8 + 97, ((temp.g_t / 8) - 8) * (-1));
        printf("%f  \a\n", temp.eva);


        for (int i = 0; i < 64; i++) {
            if (grid[i].emblem == 'k')grid[i].color ? no_more_kings-- : no_more_kings++;
        }



    }



}




