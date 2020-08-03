////0 białe i czarne


#include <iostream>
#include <fstream>
#include <cstdio>

#ifdef _WIN32

#include <conio.h>
#include <windows.h>

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
                                    std::string temp;
                                    temp.push_back('o');
                                    temp.push_back('-');
                                    temp.push_back('o');
                                    temp.push_back('-');
                                    temp.push_back('o');
                                    temp.push_back('\t');
                                    list_of_moves.push_back(temp);
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


                                    std::string temp;
                                    temp.push_back('o');
                                    temp.push_back('-');
                                    temp.push_back('o');
                                    temp.push_back('\t');
                                    list_of_moves.push_back(temp);

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

                                    std::string temp;
                                    temp.push_back(grid[go_to].emblem);
                                    temp.push_back(holder[0]);
                                    temp.push_back(holder[1]);
                                    temp.push_back('-');
                                    temp.push_back(holder[2]);
                                    temp.push_back(holder[3]);
                                    temp.push_back('\t');
                                    list_of_moves.push_back(temp);
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
                    std::string temp;
                    temp.push_back(grid[go_to].emblem);
                    temp.push_back(holder[0]);
                    temp.push_back(holder[1]);
                    temp.push_back('-');
                    temp.push_back(holder[2]);
                    temp.push_back(holder[3]);
                    temp.push_back('\t');
                    list_of_moves.push_back(temp);
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
    std::string temp;
    bool do_it = true;
    while (1 < 2) {

        if (do_it) {
            clear();
            this->show();
        }
        do_it = true;
        printf("> ");
        std::cin >> temp;
        switch (temp[0]) {
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
                grid[ctn(temp[3], temp[2])] = new piece(
                        temp[1], static_cast<int>(temp[4]) - 48);
                break;

                break;
            case 'c':
                for (int i = 0; i < 64; ++i) grid[i] = new piece();
                break;
            case 's':
                grid[ctn(temp[2], temp[1])] = new piece();
                break;
            case '*': {
                bool color = static_cast<bool>(static_cast<int>(temp[1]) - 48);
                int deepth = static_cast<int>(temp[2]) - 48;
                mov tp = bip(color, deepth);
                printf("%c%d -> ", (char) tp.pos % 8 + 97, ((tp.pos / 8) - 8) * (-1));
                printf("%c%d  ", (char) tp.g_t % 8 + 97, ((tp.g_t / 8) - 8) * (-1));
                printf("%f  \a\n", tp.eva);
                do_it = false;
            }
                break;
            case 'p': {
                if (temp.size() == 5)
                    printf("%d ", (this->possible(
                            ctn(temp[2], temp[1]),
                            ctn(temp[4], temp[3]))));
                else {
                    array legal = this->array_of_possible(ctn(temp[2], temp[1]));
                    if (temp.size() == 4 && temp[3] == 's') {
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
                myfile.open(temp.substr(1, temp.size()), std::ios::in);
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
                myfile.open(temp.substr(1, temp.size()), std::ios::out);
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
                grid[ctn(temp[4], temp[3])] = grid[ctn(temp[2], temp[1])];
                grid[ctn(temp[2], temp[1])] = new piece();

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
    std::string temp = "white\tblack\n";
    if (list_of_moves.empty())list_of_moves.push_back(temp);
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
    int w_moves = 0, b_moves = 0;

    int b_tab[6];
    for (int j = 0; j < 6; ++j) {
        w_tab[j] = 0;
        b_tab[j] = 0;
    }
    for (int i = 0; i < 64; i++) {

        b_moves += castle(BLACK).size();
        w_moves += castle(WHITE).size();

        switch (grid[i].emblem) {
            case 'k':
                if (grid[i].color) {
                    b_tab[0]++;
                    b_moves += this->array_of_possible(i).size();
                } else {
                    w_tab[0]++;
                    w_moves += this->array_of_possible(i).size();
                }
                break;
            case 'q':
                if (grid[i].color) {
                    b_tab[1]++;
                    b_moves += this->array_of_possible(i).size();
                } else {
                    w_tab[1]++;
                    w_moves += this->array_of_possible(i).size();
                }
                break;
            case 'r':
                if (grid[i].color) {
                    b_tab[2]++;
                    b_moves += this->array_of_possible(i).size();
                } else {
                    w_tab[2]++;
                    w_moves += this->array_of_possible(i).size();
                }
                break;
            case 'b':
                if (grid[i].color) {
                    b_tab[3]++;
                    b_moves += this->array_of_possible(i).size();
                } else {
                    w_tab[3]++;
                    w_moves += this->array_of_possible(i).size();
                }
                break;
            case 'n':
                if (grid[i].color) {
                    b_tab[4]++;
                    b_moves += this->array_of_possible(i).size();
                } else {
                    w_tab[4]++;
                    w_moves += this->array_of_possible(i).size();
                }
                break;
            case 'p':
                if (grid[i].color) {
                    b_tab[5]++;
                    b_moves += this->array_of_possible(i).size();
                } else {
                    w_tab[5]++;
                    w_moves += this->array_of_possible(i).size();
                }
                break;
            default:

                break;

        }

    }

    double eva = 200 * (w_tab[0] - b_tab[0]) + 9 * (w_tab[1] - b_tab[1]) + 5 * (w_tab[2] - b_tab[2]) +
                 3.15 * (w_tab[3] - b_tab[3]) + 3 * (w_tab[4] - b_tab[4]) + (w_tab[5] - b_tab[5]);
    eva += 0.1 * (w_moves - b_moves);

    return eva;
}

void board::pvc() {}

mov board::bip(bool color, int deepth) {

    //std::vector<int> temp_moves;
    dynamic_arr<mov> tab_of_possible_moves;
    array temp_moves;
    for (int i = 0; i < 64; ++i) {
        if (grid[i].emblem != '*' && grid[i].color == color) {
            temp_moves = this->array_of_possible(i);
            for (int j = 0; j < temp_moves.size(); j++) {
                mov tp(i, temp_moves[j], 0);
                tab_of_possible_moves.push_back(tp);
            }
        }
    }

    int lil = tab_of_possible_moves.size();

    for (int i = 0; i < 64; ++i)
        if (grid[i].emblem == 'p' && grid[i].color == color) {
            temp_moves = stuff_with_lil_ones(color, i);
            for (int j = 0; j < temp_moves.size(); j++) {
                mov tp(i, temp_moves[j], 0);
                tab_of_possible_moves.push_back(tp);
            }
        }

    int casle = tab_of_possible_moves.size();

    temp_moves = castle(color);
    for (int j = 0; j < temp_moves.size(); j++) {
        mov tp(j, j, 0);
        tab_of_possible_moves.push_back(tp);

    }
    piece temp[2]; // it's just to hold value



    for (int i = 0; i < lil; i++) {
        temp[0] = grid[tab_of_possible_moves[i].pos];
        temp[1] = grid[tab_of_possible_moves[i].g_t];

        grid[tab_of_possible_moves[i].g_t] = grid[tab_of_possible_moves[i].pos];

        grid[tab_of_possible_moves[i].g_t].is_moved = true;

        grid[tab_of_possible_moves[i].pos].emblem = '*';

        tab_of_possible_moves[i].eva = minmax(deepth, color, !color);

        grid[tab_of_possible_moves[i].g_t] = temp[1];

        grid[tab_of_possible_moves[i].pos] = temp[0];
    }


    for (int i = lil; i < tab_of_possible_moves.size(); i++) {
        switch (tab_of_possible_moves[i].g_t) {
            case 100:

                temp[0] = grid[tab_of_possible_moves[i].g_t]; //i+1
                temp[1] = grid[tab_of_possible_moves[i].pos];

                grid[tab_of_possible_moves[i].g_t] = new piece('n', color, true);
                grid[tab_of_possible_moves[i].pos].emblem = '*';

                tab_of_possible_moves[i].eva = minmax(deepth, color, !color);

                grid[tab_of_possible_moves[i].g_t] = temp[0];
                grid[tab_of_possible_moves[i].pos] = temp[1];
                break;
            case 101:
                temp[0] = grid[tab_of_possible_moves[i].g_t];
                temp[1] = grid[tab_of_possible_moves[i].pos];

                grid[tab_of_possible_moves[i].g_t] = new piece('q', color, true);
                grid[tab_of_possible_moves[i].pos].emblem = '*';

                tab_of_possible_moves[i].eva = minmax(deepth, color, !color);

                grid[tab_of_possible_moves[i].g_t] = temp[0];
                grid[tab_of_possible_moves[i].pos] = temp[1];
                break;
            case 66:
                if (color) {
                    grid[4].emblem = '*';
                    grid[5] = new piece('r', color, true);
                    grid[6] = new piece('k', color, true);
                    grid[7].emblem = '*';
                    tab_of_possible_moves[i].eva = minmax(deepth, color, !color);
                    grid[4] = new piece('k', color, false);
                    grid[5].emblem = '*';
                    grid[6].emblem = '*';
                    grid[7] = new piece('r', color, false);
                } else {
                    grid[60].emblem = '*';
                    grid[61] = new piece('r', color, true);
                    grid[62] = new piece('k', color, true);
                    grid[63].emblem = '*';
                    tab_of_possible_moves[i].eva = minmax(deepth, color, !color);
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
                    tab_of_possible_moves[i].eva = minmax(deepth, color, !color);
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
                    tab_of_possible_moves[i].eva = minmax(deepth, color, !color);
                    grid[46] = new piece('r', color, false);
                    grid[47].emblem = '*';
                    grid[48].emblem = '*';
                    grid[49].emblem = '*';
                    grid[50] = new piece('k', color, false);
                }
                break;

            default:
                int shift_in_x = -8;
                if (color) shift_in_x = 8;

                temp[0] = grid[tab_of_possible_moves[i].g_t + shift_in_x];
                temp[1] = grid[tab_of_possible_moves[i].pos];

                grid[tab_of_possible_moves[i].g_t] = grid[i];
                grid[tab_of_possible_moves[i].g_t].is_moved = true;

                grid[tab_of_possible_moves[i].pos].emblem = '*';
                grid[tab_of_possible_moves[i].g_t + shift_in_x].emblem = '*';

                tab_of_possible_moves[i].eva = minmax(deepth, color, !color);

                grid[tab_of_possible_moves[i].g_t + shift_in_x] = temp[0];
                grid[tab_of_possible_moves[i].g_t].emblem = '*';
                grid[tab_of_possible_moves[i].pos] = temp[1];
                break;
        }
    }

    //     todo weź wymyśl jak zrobić castle w sensie bo on zajmuje jedno miejsce a wszystko inne dwa
    tab_of_possible_moves.show();
    printf("\a");
    if (color) {

        return tab_of_possible_moves[min(tab_of_possible_moves)];
    } else {

        return tab_of_possible_moves[max(tab_of_possible_moves)];
    }
}

void board::cvc(int deep) {

    bool color = false;
    int sum = 0;
    std::string temp = "WHITE\tblack\n";
    if (list_of_moves.empty())list_of_moves.push_back(temp);
    std::vector<int> temp_moves;
    std::vector<mov> tab_of_possible_moves;

    while (1 < 2) {
        if (list_of_moves.back().back() == '\n') color = false;
        else if (list_of_moves.back().back() == '\t') color = true;
        else printf("error!");
        for (int i = 0; i < 64; i++) if (grid[i].emblem == 'k') grid[i].color ? (sum--) : (sum++);
        if (sum != 0) break;
        clear();

        this->show();

    }
}

double board::minmax(int deep, bool color_to_start, bool color_now) {
    int no_more_kings = 0;
    int oposite_king_position;
    if (deep == 0) return this->evaluate();
    if (color_now == BLACK) {
        for (int i = 0; i < 64; i++)
            if (grid[i].emblem == 'k')
                if (grid[i].color) no_more_kings--;
                else {
                    oposite_king_position = i;
                    no_more_kings++;
                }
    } else {
        for (int i = 0; i < 64; i++)
            if (grid[i].emblem == 'k') {
                if (grid[i].color) {
                    oposite_king_position = i;
                    no_more_kings--;
                } else no_more_kings++;
            }


    }
    switch (no_more_kings) {
        case -1:
            return -1069;
        case 1:
            return 1069;
            //case 0:
            //  break;
    }

    array temp_moves;
    dynamic_arr<mov> array_of_moves;
    //todo minmax jest pojebany i ty go źle napisałeś bo jesteś głupi

    for (int i = 0; i < 64; ++i) {
        if (grid[i].emblem != '*' && grid[i].color == color_now) {
            temp_moves = this->array_of_possible(i);
            for (int j = 0; j < temp_moves.size(); j++) {
                mov tp(i, temp_moves[j], 0);
                array_of_moves.push_back(tp);
            }
        }
    }

    int lil = array_of_moves.size();

    for (int i = 0; i < 64; ++i)
        if (grid[i].emblem == 'p' && grid[i].color == color_now) {
            temp_moves = stuff_with_lil_ones(color_now, i);
            for (int j = 0; j < temp_moves.size(); j++) {
                mov tp(i, temp_moves[j], 0);
                array_of_moves.push_back(tp);
            }
        }

    int casle = array_of_moves.size();
    temp_moves = castle(color_now);
    for (int j = 0; j < temp_moves.size(); j++) {
        mov tp(j, j, 0);
        array_of_moves.push_back(tp);

    }
    /// evaluation & stuff
    int color_dependence = 1;
    if (color_now == BLACK)color_dependence = -1;
    if (array_of_moves.empty()) {
        if (this->check(oposite_king_position)) return 100000 * color_dependence;
        return 0;
    }
    piece temp[2];
    double min_or_max;
    min_or_max = 1000006999 * -color_dependence;


    double min_max = 0.0;
    // reku dla

    if (color_now == WHITE) {
        for (int i = 0; i < lil; i++) {

            //if(grid[array_of_moves[i].g_t].emblem == 'k') return 1000;

            temp[0] = grid[array_of_moves[i].g_t];
            temp[1] = grid[array_of_moves[i].pos];

            grid[array_of_moves[i].g_t] = grid[array_of_moves[i].pos];

            grid[array_of_moves[i].g_t].is_moved = true;

            grid[array_of_moves[i].pos].emblem = '*';

            min_max = minmax(deep - 1, color_to_start, !color_now);

            if (min_max > min_or_max) min_or_max = min_max;

            grid[array_of_moves[i].g_t] = temp[0];

            grid[array_of_moves[i].pos] = temp[1];
            if (min_max > 200) return 1000000;
        }

        for (int i = lil; i < array_of_moves.size(); i++) {
            switch (array_of_moves[i].g_t) {
                case 100:
                    //      if(grid[array_of_moves[i].g_t].emblem == 'k') return 1000;
                    temp[0] = grid[array_of_moves[i].g_t]; //i+1
                    temp[1] = grid[array_of_moves[i].pos];

                    grid[array_of_moves[i].g_t] = new piece('n', color_now, true);
                    grid[array_of_moves[i].pos].emblem = '*';

                    min_max = minmax(deep - 1, color_to_start, !color_now);
                    if (min_max > min_or_max) min_or_max = min_max;

                    grid[array_of_moves[i].g_t] = temp[0];
                    grid[array_of_moves[i].pos] = temp[1];
                    if (min_max > 200) return 1000000;
                    break;
                case 101:
                    //    if(grid[array_of_moves[i].g_t].emblem == 'k') return 1000;
                    temp[0] = grid[array_of_moves[i].g_t];
                    temp[1] = grid[array_of_moves[i].pos];

                    grid[array_of_moves[i].g_t] = new piece('q', color_now, true);
                    grid[array_of_moves[i].pos].emblem = '*';

                    min_max = minmax(deep - 1, color_to_start, !color_now);
                    if (min_max > min_or_max) min_or_max = min_max;

                    grid[array_of_moves[i].g_t] = temp[0];
                    grid[array_of_moves[i].pos] = temp[1];
                    if (min_max > 200) return 1000000;
                    break;
                case 66:
                    if (color_now) {
                        grid[4].emblem = '*';
                        grid[5] = new piece('r', color_now, true);
                        grid[6] = new piece('k', color_now, true);
                        grid[7].emblem = '*';

                        min_max = minmax(deep - 1, color_to_start, !color_now);

                        if (min_max > min_or_max) min_or_max = min_max;

                        grid[4] = new piece('k', color_now, false);
                        grid[5].emblem = '*';
                        grid[6].emblem = '*';
                        grid[7] = new piece('r', color_now, false);


                    } else {
                        grid[60].emblem = '*';
                        grid[61] = new piece('r', color_now, true);
                        grid[62] = new piece('k', color_now, true);
                        grid[63].emblem = '*';

                        min_max = minmax(deep - 1, color_to_start, !color_now);
                        if (min_max > min_or_max) min_or_max = min_max;

                        grid[60] = new piece('k', color_now, false);
                        grid[61].emblem = '*';
                        grid[62].emblem = '*';
                        grid[63] = new piece('r', color_now, false);

                    }
                    break;
                case 666:
                    if (color_now) {
                        grid[0].emblem = '*';
                        grid[1].emblem = '*';
                        grid[2] = new piece('k', color_now, true);
                        grid[3] = new piece('r', color_now, true);
                        grid[4].emblem = '*';

                        min_max = minmax(deep - 1, color_to_start, !color_now);
                        if (min_max > min_or_max) min_or_max = min_max;

                        grid[0] = new piece('r', color_now, false);
                        grid[1].emblem = '*';
                        grid[2].emblem = '*';
                        grid[3].emblem = '*';
                        grid[4] = new piece('k', color_now, false);

                    } else {
                        grid[46].emblem = '*';
                        grid[47].emblem = '*';
                        grid[48] = new piece('k', color_now, true);
                        grid[49] = new piece('r', color_now, true);
                        grid[50].emblem = '*';

                        min_max = minmax(deep - 1, color_to_start, !color_now);
                        if (min_max > min_or_max) min_or_max = min_max;

                        grid[46] = new piece('r', color_now, false);
                        grid[47].emblem = '*';
                        grid[48].emblem = '*';
                        grid[49].emblem = '*';
                        grid[50] = new piece('k', color_now, false);
                    }
                    break;
                default:
                    int osem = -8;
                    if (color_now) osem = 8;

                    temp[0] = grid[array_of_moves[i].g_t + osem];
                    temp[1] = grid[array_of_moves[i].pos];

                    grid[array_of_moves[i].g_t] = grid[i];
                    grid[array_of_moves[i].g_t].is_moved = true;

                    grid[array_of_moves[i].pos].emblem = '*';
                    grid[array_of_moves[i].g_t + osem].emblem = '*';


                    min_max = minmax(deep - 1, color_to_start, !color_now);
                    if (min_max > min_or_max) min_or_max = min_max;


                    grid[array_of_moves[i].g_t + osem] = temp[0];
                    grid[array_of_moves[i].g_t].emblem = '*';
                    grid[array_of_moves[i].pos] = temp[1];
                    if (min_max > 200) return 1000000;
                    break;
            }


        }
    } else {
        for (int i = 0; i < lil; i++) {
            //if(grid[array_of_moves[i].g_t].emblem == 'k') return -1000;
            temp[0] = grid[array_of_moves[i].g_t];
            temp[1] = grid[array_of_moves[i].pos];

            grid[array_of_moves[i].g_t] = grid[array_of_moves[i].pos];

            grid[array_of_moves[i].g_t].is_moved = true;

            grid[array_of_moves[i].pos].emblem = '*';


            min_max = minmax(deep - 1, color_to_start, !color_now);
            if (min_max < min_or_max) min_or_max = min_max;


            grid[array_of_moves[i].g_t] = temp[0];

            grid[array_of_moves[i].pos] = temp[1];
            if (min_max < -200) return -1000000;
        }

        for (int i = lil; i < array_of_moves.size(); i++) {
            switch (array_of_moves[i].g_t) {
                case 100:
                    //      if(grid[array_of_moves[i].g_t].emblem == 'k') return -1000;
                    temp[0] = grid[array_of_moves[i].g_t]; //i+1
                    temp[1] = grid[array_of_moves[i].pos];

                    grid[array_of_moves[i].g_t] = new piece('n', color_now, true);
                    grid[array_of_moves[i].pos].emblem = '*';


                    min_max = minmax(deep - 1, color_to_start, !color_now);
                    if (min_max < min_or_max) min_or_max = min_max;


                    grid[array_of_moves[i].g_t] = temp[0];
                    grid[array_of_moves[i].pos] = temp[1];
                    if (min_max < -200) return -1000000;
                    break;
                case 101:
                    //    if(grid[array_of_moves[i].g_t].emblem == 'k') return -1000;
                    temp[0] = grid[array_of_moves[i].g_t];
                    temp[1] = grid[array_of_moves[i].pos];

                    grid[array_of_moves[i].g_t] = new piece('q', color_now, true);
                    grid[array_of_moves[i].pos].emblem = '*';


                    min_max = minmax(deep - 1, color_to_start, !color_now);
                    if (min_max < min_or_max) min_or_max = min_max;


                    grid[array_of_moves[i].g_t] = temp[0];
                    grid[array_of_moves[i].pos] = temp[1];
                    if (min_max < -200) return -1000000;
                    break;
                case 66:
                    if (color_now) {
                        grid[4].emblem = '*';
                        grid[5] = new piece('r', color_now, true);
                        grid[6] = new piece('k', color_now, true);
                        grid[7].emblem = '*';
                        min_max = minmax(deep - 1, color_to_start, !color_now);
                        if (min_max < min_or_max) min_or_max = min_max;
                        grid[4] = new piece('k', color_now, false);
                        grid[5].emblem = '*';
                        grid[6].emblem = '*';


                        grid[60].emblem = '*';
                        grid[63].emblem = '*';
                        min_max = minmax(deep - 1, color_to_start, !color_now);
                        if (min_max < min_or_max) min_or_max = min_max;
                        grid[60] = grid[60];
                        grid[60].is_moved = false;
                        grid[63] = grid[61];
                        grid[61].is_moved = false; // todo poprawspo
                        grid[61].emblem = '*';
                        grid[62].emblem = '*';

                    }
                    break;
                case 666:
                    if (color_now) {
                        grid[2] = grid[4];
                        grid[3] = grid[0];
                        grid[0].emblem = '*';           /// todo  like this one but restxd
                        grid[1].emblem = '*';
                        grid[4].emblem = '*';
                        min_max = minmax(deep - 1, color_to_start, !color_now);
                        if (min_max < min_or_max) min_or_max = min_max;
                        grid[0] = grid[3];
                        grid[0].is_moved = false;
                        grid[4] = grid[2];
                        grid[4].is_moved = false;

                        grid[1].emblem = '*';
                        grid[2].emblem = '*';
                        grid[3].emblem = '*';

                    } else {
                        grid[46].emblem = '*';
                        grid[47].emblem = '*';
                        grid[48] = new piece('k', color_now, true);
                        grid[49] = new piece('r', color_now, true);
                        grid[50].emblem = '*';
                        min_max = minmax(deep - 1, color_to_start, !color_now);
                        if (min_max < min_or_max) min_or_max = min_max;
                        grid[46] = new piece('r', color_now, false);
                        grid[47].emblem = '*';
                        grid[48].emblem = '*';
                        grid[49].emblem = '*';
                        grid[50] = new piece('k', color_now, false);
                    }
                    break;
                default:
                    int osem = -8;
                    if (color_now) osem = 8;

                    temp[0] = grid[array_of_moves[i].g_t + osem];
                    temp[1] = grid[array_of_moves[i].pos];

                    grid[array_of_moves[i].g_t] = grid[i];
                    grid[array_of_moves[i].g_t].is_moved = true;

                    grid[array_of_moves[i].pos].emblem = '*';
                    grid[array_of_moves[i].g_t + osem].emblem = '*';

                    min_max = minmax(deep - 1, color_to_start, !color_now);
                    if (min_max < min_or_max) min_or_max = min_max;

                    grid[array_of_moves[i].g_t + osem] = temp[0];
                    grid[array_of_moves[i].g_t].emblem = '*';
                    grid[array_of_moves[i].pos] = temp[1];
                    if (min_max < -200) return -1000000;
                    break;
            }


        }


    }
/*

*/

    return min_or_max; //i guess they never max huh?
    // u've got a boyfriend i bet he never kiss ya?
}

void board::admin_l(std::string temp) {
    std::ifstream myfile;
    myfile.open(temp, std::ios::in);
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

array board::castle(bool color) {
    array possible_moves;
    if (color) {
        if (grid[0].emblem == 'r' && grid[1].emblem == '*' && grid[2].emblem == '*' && grid[3].emblem == '*' &&
            grid[4].emblem == 'k')
            if (grid[0].is_moved == 0 && grid[4].is_moved == 0) {
                for (int i = 0; i < 64; i++) {
                    if (grid[i].color != color)
                        if (this->possible(i, 0) || this->possible(i, 1) ||
                            this->possible(i, 2) || this->possible(i, 3) ||
                            this->possible(i, 4))
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
                        if (this->possible(i, 56) || this->possible(i, 57) ||
                            this->possible(i, 58) || this->possible(i, 59) ||
                            this->possible(i, 60))
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
                        if (this->possible(i, 4) || this->possible(i, 5) ||
                            this->possible(i, 6) || this->possible(i, 7))
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
                        if (this->possible(i, 60) || this->possible(i, 61) ||
                            this->possible(i, 62) || this->possible(i, 63))
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

array board::stuff_with_lil_ones(bool color, int position) {
    array possible_moves;

    switch (position / 8) {
        case 1:
            if (!color && this->possible(position, position - 8)) {
                possible_moves.push_back(position);
                possible_moves.push_back(100);
                possible_moves.push_back(position);
                possible_moves.push_back(101);
            }
            break;
        case 3:
            if (!color && list_of_moves.size() > 3) {
                int i = 0;
                for (; i < list_of_moves.back().size(); i++) if (list_of_moves.back()[i] == '\t') break;
                i++;
                int hold21 = ctn(list_of_moves.back()[i + 2], list_of_moves.back()[i + 1]);
                int hold54 = ctn(list_of_moves.back()[i + 5], list_of_moves.back()[i + 4]);

                if (list_of_moves.back()[i] == 'p' && hold21 - hold54 == 16) {

                    if (hold54 == position - 1 && position % 8 != 0) {

                        possible_moves.push_back(position);
                        possible_moves.push_back(hold21 - 8);
                    }
                    if (hold54 == position + 1 && position % 8 != 7) {

                        possible_moves.push_back(position);
                        possible_moves.push_back(hold21 - 8);
                    }

                }
            }
            break;
        case 4:
            if (color && list_of_moves.size() > 3) {
                int i = 0;
                for (; i < list_of_moves.back().size(); i++) if (list_of_moves.back()[i] == '\t') break;
                i++;
                int hold21 = ctn(list_of_moves.back()[i + 2], list_of_moves.back()[i + 1]);
                int hold54 = ctn(list_of_moves.back()[i + 5], list_of_moves.back()[i + 4]);

                if (list_of_moves.back()[i] == 'p' && hold21 - hold54 == 16) {


                    if (hold54 == position - 1 && position % 8 != 0) {

                        possible_moves.push_back(position);
                        possible_moves.push_back(hold21 - 8);
                    }
                    if (hold54 == position + 1 && position % 8 != 7) {

                        possible_moves.push_back(position);
                        possible_moves.push_back(hold21 - 8);
                    }
                }
            }
            break;
        case 6:
            if (color && this->possible(position, position + 8)) {
                possible_moves.push_back(position);
                possible_moves.push_back(100);
                possible_moves.push_back(position);
                possible_moves.push_back(101);
            }
            break;


    }
    return possible_moves;
}

array board::array_of_possible(int position) {
#if 0
    array temp;
    if (grid[position].emblem == '*') {
        printf("error, it's not a pown \n");
        return temp;
    }
    int px = position / 8, py = position % 8;

/*
    temp = grid[position].pin(position, grid);


    if (!temp.empty()) {
        if (temp[0] == -1) temp.clear();
        return temp;
    }
*/

    switch (this->emblem) {
        case 'p':

            if (color) {   // czarne czyli \/

                if (grid[position + 8].emblem == '*') {
                    temp.push_back(position + 8);
                    if (!is_moved && grid[position + 16].emblem == '*') temp.push_back(position + 16);

                }

                if (py != 7 && grid[position + 9].emblem != '*' && grid[position + 9].color == !color)
                    temp.push_back(position + 9);
                if (py != 0 && grid[position + 7].emblem != '*' && grid[position + 7].color == !color)
                    temp.push_back(position + 7);



                break;
            } else {

                if (grid[position - 8].emblem == '*') {
                    temp.push_back(position - 8);
                    if (!is_moved && grid[position - 16].emblem == '*')
                        temp.push_back(position - 16);
                }

                if (py != 0 && grid[position - 9].emblem != '*' && grid[position - 9].color == !color)
                    temp.push_back(position - 9);
                if (py != 7 && grid[position - 7].emblem != '*' && grid[position - 7].color == !color)
                    temp.push_back(position - 7);

            }

            break;

        case 'n': {

            temp[0] = position - 15;
            temp[1] = position - 17;
            temp[2] = position - 6;
            temp[3] = position - 10;
            temp[4] = position + 15;
            temp[5] = position + 17;
            temp[6] = position + 6;
            temp[7] = position + 10;
            temp.size(8);


            switch (py) {
                case 0:
                    temp[1] = -101;
                    temp[3] = -101;
                    temp[4] = -101;
                    temp[6] = -101;
                    temp.rejects(4);
                    break;
                case 1:

                    temp[3] = -101;
                    temp[6] = -101;
                    temp.rejects(2);

                    break;
                case 6:

                    temp[2] = -101;
                    temp[7] = -101;

                    temp.rejects(2);

                    break;
                case 7:

                    temp[0] = -101;
                    temp[2] = -101;
                    temp[5] = -101;
                    temp[7] = -101;
                    temp.rejects(4);

                    break;
                default:
                    break;
            }

            temp.clr();

            switch (px) {
                case 0:
                    temp.erase(0, 4);

                    break;
                case 1:
                    temp.erase(0, 2);

                    break;
                case 6:

                    temp.erase(4, 6);


                    break;
                case 7:
                    temp.erase(4, 8);

                    break;
                default:
                    break;
            }

            temp.clr();

            for (int i = 0; i < temp.size(); i++) {
                if (grid[temp[i]].emblem != '*' && grid[temp[i]].color == color) temp.erase(i);
            }

            temp.clr();

            for (int i = 0; i < temp.size(); i++) {
                if (grid[position].check(temp[i], grid)) temp.erase(i);
            }
        }
            break;
        case 'k':

            temp[0] = position - 7;
            temp[1] = position - 8;
            temp[2] = position - 9;
            temp[3] = position - 1;
            temp[4] = position + 1;
            temp[5] = position + 7;
            temp[6] = position + 8;
            temp[7] = position + 9;
            temp.size(8);


            switch (px) {
                case 0:

                    temp[0] = -101;
                    temp[1] = -101;
                    temp[2] = -101;
                    temp.rejects(3);

                    break;
                case 7:

                    temp[5] = -101;
                    temp[6] = -101;
                    temp[7] = -101;
                    temp.rejects(3);

                    break;
                default:
                    break;
            }
            switch (py) {
                case 0:
                    temp.erase(2);
                    temp.erase(5);
                    temp.erase(3);

                    break;
                case 7:
                    temp.erase(4);
                    temp.erase(0);
                    temp.erase(7);
                    break;
                default:
                    break;
            }

            temp.clr();

            for (int i = 0; i < temp.size(); i++)
                if (grid[temp[i]].emblem != '*' && grid[temp[i]].color == color)temp.erase(i);

            temp.clr();

            for (int i = 0; i < temp.size(); i++)
                if (grid[position].check(temp[i], grid))temp.erase(i);


            break;
        case 'q': {
            int temp_x = px, temp_y = py;
            int i = 0;

            while (temp_x > 0 && 7 > temp_y)temp.push_back((--temp_x) * 8 + ++temp_y);

            temp_x = px;
            temp_y = py;

            for (; i < temp.

                    size();

                   i++)
                if (grid[temp[i]].emblem != '*') {
                    if (grid[temp[i]].color == color)
                        temp.erase(i, temp.size());
                    else
                        temp.
                                erase(i
                                      + 1, temp.

                                size()

                        );
                    break;

                }


            i = temp.size();

            while (
                    temp_x < 7 && 7 > temp_y
                    )
                temp.push_back((++temp_x) * 8 + ++temp_y);

            temp_x = px;
            temp_y = py;

            for (; i < temp.

                    size();

                   i++)
                if (grid[temp[i]].emblem != '*') {
                    if (grid[temp[i]].color == color)
                        temp.
                                erase(i, temp
                                .

                                        size()

                        );
                    else
                        temp.
                                erase(i
                                      + 1, temp.

                                size()

                        );
                    break;

                }

//y
            i = temp.size();
            while (temp_x < 7 && 0 < temp_y) temp.push_back((++temp_x) * 8 + --temp_y);


            temp_x = px;
            temp_y = py;
            for (; i < temp.

                    size();

                   i++)
                if (grid[temp[i]].emblem != '*') {
                    if (grid[temp[i]].color == color)
                        temp.
                                erase(i, temp
                                .

                                        size()

                        );
                    else
                        temp.
                                erase(i
                                      + 1, temp.

                                size()

                        );
                    break;

                }


            i = temp.size();
            while (temp_x > 0 && 0 < temp_y) temp.push_back((--temp_x) * 8 + --temp_y);


            for (; i < temp.

                    size();

                   i++)
                if (grid[temp[i]].emblem != '*') {
                    if (grid[temp[i]].color == color)
                        temp.
                                erase(i, temp
                                .

                                        size()

                        );
                    else
                        temp.
                                erase(i
                                      + 1, temp.

                                size()

                        );
                    break;

                }


//r
            i = temp.size();
            for (
                    int z = 1;
                    z <=
                    px;
                    z++)
                temp.
                        push_back(position
                                  - (z * 8));


            for (; i < temp.

                    size();

                   i++)
                if (grid[temp[i]].emblem != '*') {
                    if (grid[temp[i]].color == color)
                        temp.
                                erase(i, temp
                                .

                                        size()

                        );
                    else
                        temp.
                                erase(i
                                      + 1, temp.

                                size()

                        );
                    break;

                }


            i = temp.size();

            for (
                    int z = 1;
                    z < 8 -
                        px;
                    z++)
                temp.
                        push_back(position
                                  + (z * 8));


            for (; i < temp.

                    size();

                   i++)
                if (grid[temp[i]].emblem != '*') {
                    if (grid[temp[i]].color == color)
                        temp.
                                erase(i, temp
                                .

                                        size()

                        );
                    else
                        temp.
                                erase(i
                                      + 1, temp.

                                size()

                        );
                    break;

                }

//y
            i = temp.size();

            for (
                    int z = 1;
                    z <=
                    py;
                    z++)
                temp.
                        push_back(position
                                  - z);


            for (; i < temp.

                    size();

                   i++)
                if (grid[temp[i]].emblem != '*') {
                    if (grid[temp[i]].color == color)
                        temp.
                                erase(i, temp
                                .

                                        size()

                        );
                    else
                        temp.
                                erase(i
                                      + 1, temp.

                                size()

                        );
                    break;

                }


            i = temp.size();

            for (
                    int z = 1;
                    z < 8 -
                        py;
                    z++)
                temp.
                        push_back(position
                                  + z);


            for (; i < temp.

                    size();

                   i++)
                if (grid[temp[i]].emblem != '*') {
                    if (grid[temp[i]].color == color)
                        temp.
                                erase(i, temp
                                .

                                        size()

                        );
                    else
                        temp.
                                erase(i
                                      + 1, temp.

                                size()

                        );
                    break;

                }


        }
            break;
        case 'b': {
// x
            int temp_x = px, temp_y = py;
            int i = 0;

            while (temp_x > 0 && 7 > temp_y)temp.push_back((--temp_x) * 8 + ++temp_y);


            temp_x = px;
            temp_y = py;

            for (; i < temp.

                    size();

                   i++)
                if (grid[temp[i]].emblem != '*') {
                    if (grid[temp[i]].color == color)
                        temp.erase(i, temp.size());
                    else
                        temp.erase(i+ 1, temp.size());
                    break;

                }

            i = temp.size();

            while (temp_x < 7 && 7 > temp_y)
                temp.push_back((++temp_x) * 8 + ++temp_y);

            temp_x = px;
            temp_y = py;

            for (; i < temp.size();i++)
                if (grid[temp[i]].emblem != '*') {
                    if (grid[temp[i]].color == color)
                        temp.erase(i, temp.size()

                        );
                    else
                        temp.
                                erase(i
                                      + 1, temp.

                                size()

                        );
                    break;

                }

//y
            i = temp.size();
            while (temp_x < 7 && 0 < temp_y) temp.push_back((++temp_x) * 8 + --temp_y);


            temp_x = px;
            temp_y = py;
            for (; i < temp.

                    size();

                   i++)
                if (grid[temp[i]].emblem != '*') {
                    if (grid[temp[i]].color == color)
                        temp.
                                erase(i, temp
                                .

                                        size()

                        );
                    else
                        temp.
                                erase(i
                                      + 1, temp.

                                size()

                        );
                    break;

                }


            i = temp.size();
            while (temp_x > 0 && 0 < temp_y) temp.push_back((--temp_x) * 8 + --temp_y);


            for (; i < temp.

                    size();

                   i++)
                if (grid[temp[i]].emblem != '*') {
                    if (grid[temp[i]].color == color)
                        temp.
                                erase(i, temp.size()

                        );
                    else
                        temp.erase(i + 1, temp.size()

                        );
                    break;

                }

        }
            break;
        case 'r': {


            int i = 0;
//x
            for (
                    int z = 1;
                    z <=
                    px;
                    z++)
                temp.
                        push_back(position
                                  - (z * 8));


            for (; i < temp.

                    size();

                   i++)
                if (grid[temp[i]].emblem != '*') {
                    if (grid[temp[i]].color == color)
                        temp.
                                erase(i, temp
                                .

                                        size()

                        );
                    else
                        temp.
                                erase(i
                                      + 1, temp.

                                size()

                        );
                    break;

                }


            i = temp.size();

            for (
                    int z = 1;
                    z < 8 -
                        px;
                    z++)
                temp.
                        push_back(position
                                  + (z * 8));


            for (; i < temp.

                    size();

                   i++)
                if (grid[temp[i]].emblem != '*') {
                    if (grid[temp[i]].color == color)
                        temp.
                                erase(i, temp
                                .

                                        size()

                        );
                    else
                        temp.
                                erase(i
                                      + 1, temp.

                                size()

                        );
                    break;

                }

//y
            i = temp.size();

            for (
                    int z = 1;
                    z <=
                    py;
                    z++)
                temp.
                        push_back(position
                                  - z);


            for (; i < temp.

                    size();

                   i++)
                if (grid[temp[i]].emblem != '*') {
                    if (grid[temp[i]].color == color)
                        temp.
                                erase(i, temp
                                .

                                        size()

                        );
                    else
                        temp.
                                erase(i
                                      + 1, temp.

                                size()

                        );
                    break;

                }


            i = temp.size();

            for (
                    int z = 1;
                    z < 8 -
                        py;
                    z++)
                temp.
                        push_back(position
                                  + z);


            for (; i < temp.

                    size();

                   i++)
                if (grid[temp[i]].emblem != '*') {
                    if (grid[temp[i]].color == color)
                        temp.
                                erase(i, temp
                                .

                                        size()

                        );
                    else
                        temp.
                                erase(i
                                      + 1, temp.

                                size()

                        );
                    break;

                }


        }
            break;
        default:
            printf("well %d not a pon u dumbas \n", position);
            break;
    }
    temp.

            clr();

    return
            temp;
#else
    //ok the plan is that its 3 dimentional array and 1st lavel has 64 elemants seckond has 4 and the last is whatever

    array all_of_possible_moves;
    //
    int px = position / 8, py = position % 8;


    char emblem = grid[position].emblem;

    bool color = grid[position].color;

    bool is_moved = grid[position].is_moved;

    switch (emblem) {
        case 'p':
            if (color) {   // czarne czyli \/

                if (this->grid[position + 8].emblem == '*') {
                    all_of_possible_moves.push_back(position + 8);
                    if (!is_moved && this->grid[position + 16].emblem == '*')
                        all_of_possible_moves.push_back(position + 16);

                }

                if (py != 7 && this->grid[position + 9].emblem != '*' && this->grid[position + 9].color == !color)
                    all_of_possible_moves.push_back(position + 9);
                if (py != 0 && this->grid[position + 7].emblem != '*' && this->grid[position + 7].color == !color)
                    all_of_possible_moves.push_back(position + 7);


                break;
            } else {

                if (this->grid[position - 8].emblem == '*') {
                    all_of_possible_moves.push_back(position - 8);
                    if (!is_moved && this->grid[position - 16].emblem == '*')
                        all_of_possible_moves.push_back(position - 16);
                }

                if (py != 0 && this->grid[position - 9].emblem != '*' && this->grid[position - 9].color == !color)
                    all_of_possible_moves.push_back(position - 9);
                if (py != 7 && this->grid[position - 7].emblem != '*' && this->grid[position - 7].color == !color)
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

            all_of_possible_moves.clr();

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
                if (this->grid[all_of_possible_moves[i]].emblem != '*' &&
                    this->grid[all_of_possible_moves[i]].color == color)
                    all_of_possible_moves.erase(i);
            }

            all_of_possible_moves.clr();

            for (int i = 0; i < all_of_possible_moves.size(); i++) {
                if (this->check(all_of_possible_moves[i])) all_of_possible_moves.erase(i);
            }

        }
            break;
        case 'r': {

            dynamic_arr<array> before_processing(4);

            before_processing = this->full_board_of_moves_4_rook[position];


            for (int i = 0; i < before_processing.size(); i++) {
                for (int j = 0; j < before_processing[i].size(); j++) {


                    if (grid[before_processing[i][j]].emblem != '*') {
                        if (grid[before_processing[i][j]].color != color)
                            all_of_possible_moves.push_back(before_processing[i][j]);
                        break;
                    }
                    all_of_possible_moves.push_back(before_processing[i][j]);

                }
            }


        }

            break;
        case 'b': {
            dynamic_arr<array> before_processing;
            before_processing = this->full_board_of_moves_4_bishop[position];
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < before_processing[i].size(); j++) {
                    if (this->grid[before_processing[i][j]].emblem != '*') {
                        if (this->grid[before_processing[i][j]].color == color)break;
                        all_of_possible_moves.push_back(before_processing[i][j]);
                        break;
                    }
                    all_of_possible_moves.push_back(before_processing[i][j]);

                }
            }

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
                if (this->grid[all_of_possible_moves[i]].emblem != '*' &&
                    this->grid[all_of_possible_moves[i]].color == color)
                    all_of_possible_moves.erase(i);

            all_of_possible_moves.clr();

            for (int i = 0; i < all_of_possible_moves.size(); i++)
                if (this->check(all_of_possible_moves[i]))all_of_possible_moves.erase(i);


            break;

        case 'q': {
            dynamic_arr<array> before_processing;
            before_processing = this->full_board_of_moves_4_rook[position];

            for (int i = 0; i < before_processing.size(); i++) {
                for (int j = 0; j < before_processing[i].size(); j++) {
                    if (this->grid[before_processing[i][j]].emblem != '*') {
                        if (this->grid[before_processing[i][j]].color != color)
                            all_of_possible_moves.push_back(before_processing[i][j]);
                        break;
                    }
                    all_of_possible_moves.push_back(before_processing[i][j]);

                }
            }

            before_processing = this->full_board_of_moves_4_bishop[position];
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < before_processing[i].size(); j++) {
                    if (this->grid[before_processing[i][j]].emblem != '*') {
                        if (this->grid[before_processing[i][j]].color != color)
                            all_of_possible_moves.push_back(before_processing[i][j]);
                        break;
                    }
                    all_of_possible_moves.push_back(before_processing[i][j]);

                }
            }
        }
        break;
    }
    return all_of_possible_moves;
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
            int all_of_possible_moves[8] = {position - 17, position - 15, position - 10, position - 6, position + 6, position + 10,
                           position + 15, position + 17};
            return binary(go_to, all_of_possible_moves);
        }
            break;
        case 'k': {
            int all_of_possible_moves[8] = {position - 9, position - 8, position - 7, position - 1, position + 1, position + 7,
                           position + 8,
                           position + 9};
            return binary(go_to, all_of_possible_moves);
        }
            break;
        case 'q': {


            int b = px + py;
            ///         / <-this one
            if (b == gy + gx) {
                array all_of_possible_moves;


                if (gy < py) all_of_possible_moves = full_board_of_moves_4_bishop[position][2];
                else all_of_possible_moves = full_board_of_moves_4_bishop[position][0];


                for (int i = 0; i < all_of_possible_moves.size(); i++) {
                    if (grid[all_of_possible_moves[i]].emblem != '*')
                        if (grid[all_of_possible_moves[i]].color != color) return all_of_possible_moves[i] == go_to;
                        else return false;
                    if (all_of_possible_moves[i] == go_to) return true;
                }
            }

            /// \ <-this one
            b = py - px;
            if (b + gx == gy) {// lg to pd
                array all_of_possible_moves;


                /// tu idziemy do góry
                if (gy < py) all_of_possible_moves = full_board_of_moves_4_bishop[position][3];

                else all_of_possible_moves = full_board_of_moves_4_bishop[position][1];


                for (int i = 0; i < all_of_possible_moves.size(); i++) {
                    if (grid[all_of_possible_moves[i]].emblem != '*')
                        if (grid[all_of_possible_moves[i]].color != color) return all_of_possible_moves[i] == go_to;
                        else return false;
                    if (all_of_possible_moves[i] == go_to) return true;
                }

            }


            if (px == gx) {
                array all_of_possible_moves;
                if (py > gy) all_of_possible_moves = full_board_of_moves_4_rook[position][2];
                else all_of_possible_moves = full_board_of_moves_4_rook[position][0];


                for (int i = 0; i < all_of_possible_moves.size(); i++) {
                    if (grid[all_of_possible_moves[i]].emblem != '*')
                        if (grid[all_of_possible_moves[i]].color != color) return all_of_possible_moves[i] == go_to;
                        else return false;
                    if (all_of_possible_moves[i] == go_to) return true;
                }
            }
            if (py == gy) {

                array all_of_possible_moves;

                if (px > gx) all_of_possible_moves = full_board_of_moves_4_rook[position][3];
                else all_of_possible_moves = full_board_of_moves_4_rook[position][1];

                for (int i = 0; i < all_of_possible_moves.size(); i++) {
                    if (grid[all_of_possible_moves[i]].emblem != '*')
                        if (grid[all_of_possible_moves[i]].color != color) return all_of_possible_moves[i] == go_to;
                        else return false;
                    if (all_of_possible_moves[i] == go_to) return true;
                }
            }
        }

            break;
        case 'b': {
            int b = px + py;
            ///         / <-this one
            if (b == gy + gx) {
                array all_of_possible_moves;


                if (gy < py) all_of_possible_moves = full_board_of_moves_4_bishop[position][2];
                else all_of_possible_moves = full_board_of_moves_4_bishop[position][0];


                for (int i = 0; i < all_of_possible_moves.size(); i++) {
                    if (grid[all_of_possible_moves[i]].emblem != '*')
                        if (grid[all_of_possible_moves[i]].color != color) return all_of_possible_moves[i] == go_to;
                        else return false;
                    if (all_of_possible_moves[i] == go_to) return true;
                }
            }

            /// \ <-this one
            b = py - px;
            if (b + gx == gy) {// lg to pd
                array all_of_possible_moves;


                /// tu idziemy do góry
                if (gy < py) all_of_possible_moves = full_board_of_moves_4_bishop[position][3];

                else all_of_possible_moves = full_board_of_moves_4_bishop[position][1];


                for (int i = 0; i < all_of_possible_moves.size(); i++) {
                    if (grid[all_of_possible_moves[i]].emblem != '*')
                        if (grid[all_of_possible_moves[i]].color != color) return all_of_possible_moves[i] == go_to;
                        else return false;
                    if (all_of_possible_moves[i] == go_to) return true;
                }

            }
        }
            break;
        case 'r': {
            if (px == gx) {
                array all_of_possible_moves;
                if (py > gy) all_of_possible_moves = full_board_of_moves_4_rook[position][2];
                else all_of_possible_moves = full_board_of_moves_4_rook[position][0];


                for (int i = 0; i < all_of_possible_moves.size(); i++) {
                    if (grid[all_of_possible_moves[i]].emblem != '*')
                        if (grid[all_of_possible_moves[i]].color != color) return all_of_possible_moves[i] == go_to;
                        else return false;
                    if (all_of_possible_moves[i] == go_to) return true;
                }
            }
            if (py == gy) {

                array all_of_possible_moves;

                if (px > gx) all_of_possible_moves = full_board_of_moves_4_rook[position][3];
                else all_of_possible_moves = full_board_of_moves_4_rook[position][1];

                for (int i = 0; i < all_of_possible_moves.size(); i++) {
                    if (grid[all_of_possible_moves[i]].emblem != '*')
                        if (grid[all_of_possible_moves[i]].color != color) return all_of_possible_moves[i] == go_to;
                        else return false;
                    if (all_of_possible_moves[i] == go_to) return true;
                }
            }
        }
            break;


    }
    return false;


}

array board::pin(int position) {

    char emblem = grid[position].emblem;
    bool color = grid[position].color;

    array possible_moves;
    if (emblem == 'k') return possible_moves;

    int px = position / 8, py = position % 8;

    int king_x = 65, king_y = 65;

    for (int i = 0; i < 64; i++) {
        if (grid[i].emblem == 'k' && grid[i].color == color) {
            king_x = i / 8;
            king_y = i % 8;
            break;

        }

    }
    if (king_x == 65) return possible_moves;

    ///r
    int b = king_y - king_x;

    if (px == king_x) {
        if (py > king_y) {

            int i = king_y;
            for (; i < 7; i++) {

                if (grid[px * 8 + i].emblem != '*') {
                    if (i == py) {
                        i++;
                        while (i < 8) {
                            switch (grid[px * 8 + i].emblem) {
                                case '*':
                                    possible_moves.push_back(px * 8 + i);
                                    i++;
                                    break;

                                case 'r':
                                    if (grid[px * 8 + i].color == color) {
                                        possible_moves.clear();
                                        return possible_moves;
                                    } else possible_moves.push_back(px * 8 + i);

                                    for (i = possible_moves.size() - 1; i >= 0; i--)
                                        if (!this->possible(position, possible_moves[i]))
                                            possible_moves.erase(i);

                                    possible_moves.clr();
                                    if (possible_moves.size() == 0) possible_moves.push_back(-1);

                                    return possible_moves;
                                case 'q':
                                    if (grid[px * 8 + i].color == color) {
                                        possible_moves.clear();
                                        return possible_moves;
                                    } else possible_moves.push_back(px * 8 + i);

                                    for (i = possible_moves.size() - 1; i >= 0; i--)
                                        if (!this->possible(position, possible_moves[i]))
                                            possible_moves.erase(i);
                                    return possible_moves;
                                default:
                                    possible_moves.clear();
                                    return possible_moves;


                            }
                        }

                    } else possible_moves.clear();
                    return possible_moves;
                } else possible_moves.push_back(px * 8 + i);

            }
        } else {

            int i = king_y;
            i--;
            for (; i > 0; i--) {
                if (grid[king_x * 8 + i].emblem != '*') {
                    if (i == py) {

                        i--;
                        while (i >= 0) {
                            switch (grid[px * 8 + i].emblem) {
                                case '*':
                                    possible_moves.push_back(px * 8 + i);
                                    i--;
                                    break;
                                case 'r':
                                    if (grid[px * 8 + i].color == color) {
                                        possible_moves.clear();
                                        return possible_moves;
                                    } else possible_moves.push_back(px * 8 + i);

                                    for (i = possible_moves.size() - 1; i >= 0; i--)
                                        if (!this->possible(position, possible_moves[i]))
                                            possible_moves.erase(i);

                                    possible_moves.clr();
                                    if (possible_moves.size() == 0) possible_moves.push_back(-1);

                                    return possible_moves;
                                case 'q':
                                    if (grid[px * 8 + i].color == color) {
                                        possible_moves.clear();
                                        return possible_moves;
                                    } else possible_moves.push_back(px * 8 + i);

                                    for (i = possible_moves.size() - 1; i >= 0; i--)
                                        if (!this->possible(position, possible_moves[i]))
                                            possible_moves.erase(i);
                                    return possible_moves;
                                default:
                                    possible_moves.clear();
                                    return possible_moves;

                            }
                        }
                    } else possible_moves.clear();
                    return possible_moves;
                } else possible_moves.push_back(px * 8 + i);
            }
        }
    } else if (py == king_y) {
        if (px > king_x) {
            int i = king_x;
            while (i < 7) {
                i++;
                if (grid[i * 8 + py].emblem != '*') {
                    if (i == px) {
                        i++;
                        while (i < 8) {
                            switch (grid[i * 8 + py].emblem) {
                                case '*':
                                    possible_moves.push_back(i * 8 + py);
                                    i++;
                                case 'r':
                                    if (grid[px * 8 + i].color == color) {
                                        possible_moves.clear();
                                        return possible_moves;
                                    } else possible_moves.push_back(px * 8 + i);

                                    for (i = possible_moves.size() - 1; i >= 0; i--)
                                        if (!this->possible(position, possible_moves[i]))
                                            possible_moves.erase(i);

                                    possible_moves.clr();
                                    if (possible_moves.size() == 0) possible_moves.push_back(-1);

                                    return possible_moves;
                                case 'q':
                                    if (grid[px * 8 + i].color == color) {
                                        possible_moves.clear();
                                        return possible_moves;
                                    } else possible_moves.push_back(px * 8 + i);

                                    for (i = possible_moves.size() - 1; i >= 0; i--)
                                        if (!this->possible(position, possible_moves[i]))
                                            possible_moves.erase(i);
                                    return possible_moves;
                                default:
                                    possible_moves.clear();
                                    return possible_moves;
                            }
                        }
                    } else possible_moves.clear();
                    return possible_moves;
                } else possible_moves.push_back(i * 8 + py);
            }
        } else {
            int i = king_x;
            while (i >= 0) {
                i--;
                if (grid[i * 8 + py].emblem != '*') {
                    if (i == px) {
                        i--;
                        while (i >= 0) {
                            switch (grid[i * 8 + py].emblem) {
                                case '*':
                                    possible_moves.push_back(i * 8 + py);
                                    i--;
                                    break;
                                case 'r':
                                    if (grid[px * 8 + i].color == color) {
                                        possible_moves.clear();
                                        return possible_moves;
                                    } else possible_moves.push_back(px * 8 + i);

                                    for (i = possible_moves.size() - 1; i >= 0; i--)
                                        if (!this->possible(position, possible_moves[i]))
                                            possible_moves.erase(i);

                                    possible_moves.clr();
                                    if (possible_moves.size() == 0) possible_moves.push_back(-1);

                                    return possible_moves;
                                case 'q':
                                    if (grid[px * 8 + i].color == color) {
                                        possible_moves.clear();
                                        return possible_moves;
                                    } else possible_moves.push_back(px * 8 + i);

                                    for (i = possible_moves.size() - 1; i >= 0; i--)
                                        if (!this->possible(position, possible_moves[i]))
                                            possible_moves.erase(i);
                                    return possible_moves;
                                default:
                                    possible_moves.clear();
                                    return possible_moves;
                            }
                        }
                    } else possible_moves.clear();
                    return possible_moves;
                } else possible_moves.push_back(i * 8 + py);
            }
        }
    } else if (py == (px + b)) {
        if (py > king_y) {
            int nx = king_x, ny = king_y;
            while (nx > 0 && ny < 7) {
                nx--;
                ny++;

                if (grid[nx * 8 + ny].emblem != '*') {
                    if ((nx * 8 + ny) == (px * 8 + py)) {
                        nx = px - 1;
                        ny = py + 1;

                        while (nx > 0 && ny < 7) {
                            switch (grid[nx * 8 + ny].emblem) {
                                case '*':
                                    possible_moves.push_back(nx * 8 + ny);
                                    nx--;
                                    ny++;
                                    break;
                                case 'b':
                                    if (grid[nx * 8 + ny].color == color) {
                                        possible_moves.clear();
                                        return possible_moves;
                                    } else possible_moves.push_back(nx * 8 + ny);

                                    for (int i = possible_moves.size() - 1; i >= 0; i--)
                                        if (!this->possible(position, possible_moves[i]))
                                            possible_moves.erase(i);

                                    possible_moves.clr();
                                    if (possible_moves.size() == 0) possible_moves.push_back(-1);

                                    return possible_moves;
                                case 'q':
                                    if (grid[nx * 8 + ny].color == color) {
                                        possible_moves.clear();
                                        return possible_moves;
                                    } else possible_moves.push_back(nx * 8 + ny);

                                    for (int i = possible_moves.size() - 1; i >= 0; i--)
                                        if (!this->possible(position, possible_moves[i]))
                                            possible_moves.erase(i);
                                    return possible_moves;
                                default:
                                    possible_moves.clear();
                                    return possible_moves;
                            }
                        }
                    } else possible_moves.clear();
                    return possible_moves;
                } else possible_moves.push_back(nx * 8 + ny);
            }
        } else {
            int nx = king_x, ny = king_y;
            while (nx < 7 && ny > 0) {
                nx++;
                ny--;

                if (grid[nx * 8 + ny].emblem != '*') {
                    if ((nx * 8 + ny) == (px * 8 + py)) {
                        nx = px + 1;
                        ny = py - 1;
                        while (nx < 8 && ny >= 0) {
                            switch (grid[nx * 8 + ny].emblem) {
                                case '*':
                                    possible_moves.push_back(nx * 8 + ny);
                                    nx--;
                                    ny++;
                                    break;
                                case 'b':
                                    if (grid[nx * 8 + ny].color == color) {
                                        possible_moves.clear();
                                        return possible_moves;
                                    } else possible_moves.push_back(nx * 8 + ny);

                                    for (int i = possible_moves.size() - 1; i >= 0; i--)
                                        if (!this->possible(position, possible_moves[i]))
                                            possible_moves.erase(i);

                                    possible_moves.clr();
                                    if (possible_moves.size() == 0) possible_moves.push_back(-1);

                                    return possible_moves;
                                case 'q':
                                    if (grid[nx * 8 + ny].color == color) {
                                        possible_moves.clear();
                                        return possible_moves;
                                    } else possible_moves.push_back(nx * 8 + ny);

                                    for (int i = possible_moves.size() - 1; i >= 0; i--)
                                        if (!this->possible(position, possible_moves[i]))
                                            possible_moves.erase(i);
                                    return possible_moves;
                                default:
                                    possible_moves.clear();
                                    return possible_moves;
                            }
                        }
                    } else possible_moves.clear();
                    return possible_moves;
                } else possible_moves.push_back(nx * 8 + ny);
            }
        }
    } else if (py == (px - b)) {
        if (py < king_y) {
            int nx = king_x, ny = king_y;

            while (nx > 0 && ny > 0) {
                nx--;
                ny--;

                if (grid[nx * 8 + ny].emblem != '*') {
                    if ((nx * 8 + ny) == (px * 8 + py)) {
                        nx = px - 1;
                        ny = py - 1;

                        while (nx > 0 && ny < 7) {
                            switch (grid[nx * 8 + ny].emblem) {
                                case '*':
                                    possible_moves.push_back(nx * 8 + ny);
                                    nx--;
                                    ny--;
                                    break;
                                case 'b':
                                    if (grid[nx * 8 + ny].color == color) {
                                        possible_moves.clear();
                                        return possible_moves;
                                    } else possible_moves.push_back(nx * 8 + ny);

                                    for (int i = possible_moves.size() - 1; i >= 0; i--)
                                        if (!this->possible(position, possible_moves[i]))
                                            possible_moves.erase(i);

                                    possible_moves.clr();
                                    if (possible_moves.size() == 0) possible_moves.push_back(-1);

                                    return possible_moves;
                                case 'q':
                                    if (grid[nx * 8 + ny].color == color) {
                                        possible_moves.clear();
                                        return possible_moves;
                                    } else possible_moves.push_back(nx * 8 + ny);

                                    for (int i = possible_moves.size() - 1; i >= 0; i--)
                                        if (!this->possible(position, possible_moves[i]))
                                            possible_moves.erase(i);
                                    return possible_moves;
                                default:
                                    possible_moves.clear();
                                    return possible_moves;
                            }
                        }
                    } else possible_moves.clear();
                    return possible_moves;
                } else possible_moves.push_back(nx * 8 + ny);
            }
        } else {
            int nx = king_x, ny = king_y;

            while (nx < 7 && ny < 7) {
                nx++;
                ny++;

                if (grid[nx * 8 + ny].emblem != '*') {
                    if ((nx * 8 + ny) == (px * 8 + py)) {
                        nx = px + 1;
                        ny = py + 1;

                        while (nx < 7 && ny > 0) {
                            switch (grid[nx * 8 + ny].emblem) {
                                case '*':
                                    possible_moves.push_back(nx * 8 + ny);
                                    nx++;
                                    ny++;
                                    break;
                                case 'b':
                                    if (grid[nx * 8 + ny].color == color) {
                                        possible_moves.clear();
                                        return possible_moves;
                                    } else possible_moves.push_back(nx * 8 + ny);

                                    for (int i = possible_moves.size() - 1; i >= 0; i--)
                                        if (!this->possible(position, possible_moves[i]))
                                            possible_moves.erase(i);

                                    possible_moves.clr();
                                    if (possible_moves.size() == 0) possible_moves.push_back(-1);

                                    return possible_moves;
                                case 'q':
                                    if (grid[nx * 8 + ny].color == color) {
                                        possible_moves.clear();
                                        return possible_moves;
                                    } else possible_moves.push_back(nx * 8 + ny);

                                    for (int i = possible_moves.size() - 1; i >= 0; i--)
                                        if (!this->possible(position, possible_moves[i]))
                                            possible_moves.erase(i);
                                    return possible_moves;
                                default:
                                    possible_moves.clear();
                                    return possible_moves;
                            }
                        }
                    } else possible_moves.clear();
                    return possible_moves;
                } else possible_moves.push_back(nx * 8 + ny);
            }
        }
    }
    return possible_moves;
}

bool board::check(int position) {
#if 0
    int px = position / 8, py = position % 8;
   if (px < 0 || px > 7 || py < 0 || py > 7) return false;  // here
   int r_tab[14];

   ///4 bishup
   int b = py - px;


   int b_tab[13];
   int nx=px;
   int ny=py;
   while(1<2){
       if (nx < 0 || nx > 7 || ny < 0 || ny > 7) break;
       nx--;
       ny--;
   }
   int p[2]={nx, ny};
   int i=0;
   for (; nx + b == ny; i++) {
       b_tab[i] =  nx * 8+b + ny;
       nx++;
       ny++;
       if (nx > 7 || ny > 7) break;
   }
   nx=p[0];
   ny=p[1];

   for (; ny == nx-b ; i++) {
       b_tab[i] =  nx * 8+b + ny;
       nx++;
       ny++;
       if (nx < 0 ||  ny < 0 ) break;
   }// i guess;
   for (int j = 0; j < i; ++j) {
       if ((grid[b_tab[j]].emblem == 'b'||grid[b_tab[j]].emblem == 'q') && grid[b_tab[j]].color != color)
           if (grid[b_tab[j]].possible(b_tab[j], grid, position, true)) return true;
   }


///4 rook
int j=0;
   for (int i = 0; i < 8; i++) {

       if ((px*8 + i) != position){ r_tab[j] = px*8 + i;++j;}

   }

   for (int i = 0; i < 8; i++) {
       if ((i * 8 + py) != position){ r_tab[j] = i * 8 + py;++j;}
   }

   for (int i : r_tab) {
       if ((grid[i].emblem == 'r'|| grid[i].emblem == 'q') && grid[i].color != color)
           if (grid[i].possible(i, grid, position, true)) return true;
   }

   /// 4 horsey


   int temp[8] = {position - 17, position - 15, position - 10, position - 6, position + 6, position + 10,
                  position + 15, position + 17};

   for (int i = 0; i < 8; i++) {
       if (grid[temp[i]].emblem == 'n' && grid[temp[i]].color != color)
           if(grid[temp[i]].possible(temp[i],grid,position,true)) return true;


   }
   delete[] &temp;

/// paion

   if (color) {//+

       if (grid[position - 9].emblem == 'p' && grid[position - 9].color != color)
           if(grid[position - 9].possible(position - 9,grid,position,true)) return true;
       if (grid[position - 7].emblem == 'p' && grid[position - 7].color != color)
           if(grid[position - 7].possible(position - 7,grid,position,true)) return true;
   } else {//-

       if (grid[position + 9].emblem == 'p' && grid[position + 9].color != color)
           if(grid[position + 9].possible(position + 9,grid,position,true)) return true;
       if (grid[position + 7].emblem == 'p' && grid[position + 7].color != color)
           if(grid[position +7].possible(position +7 ,grid,position,true)) return true;
   }
   return false;
#else
    for (int i = 0; i < 64; i++)
        if (grid[i].emblem != '*' && grid[i].color != grid[position].color)
            if (this->possible(i, position)) return true;
    return false;
#endif
}

