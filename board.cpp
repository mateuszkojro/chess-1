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


#define black true
#define white false
#define ABS(N) ((N<0)?(-N):(N))

int ctn(char x, char y) {
    return ((static_cast<int>(x) - 56) * (-8)) + (static_cast<int>(y) - 97);
}


int max(dynamic_arr row) {
    int k = 0;
    for (int i = 1; i < row.size(); ++i) {
        if (row[i].eva > row[k].eva) k = i;
    }
    return k;
}

int min(dynamic_arr row) {
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
                                    if (grid[i].possible(i, grid, 0, true) || grid[i].possible(i, grid, 1, true) ||
                                        grid[i].possible(i, grid, 2, true) || grid[i].possible(i, grid, 3, true) ||
                                        grid[i].possible(i, grid, 4, true))
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
                                    if (grid[i].possible(i, grid, 56, true) || grid[i].possible(i, grid, 57, true) ||
                                        grid[i].possible(i, grid, 58, true) || grid[i].possible(i, grid, 59, true) ||
                                        grid[i].possible(i, grid, 60, true))
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
                                    if (grid[i].possible(i, grid, 4, true) || grid[i].possible(i, grid, 5, true) ||
                                        grid[i].possible(i, grid, 6, true) || grid[i].possible(i, grid, 7, true))
                                        break;
                                if (i == 63) {
                                    grid[7] = new piece();
                                    grid[4] = new piece();
                                    grid[5] = new piece('r', color, true);
                                    grid[6] = new piece('k', color, true);

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
                                    if (grid[i].possible(i, grid, 60, true) || grid[i].possible(i, grid, 61, true) ||
                                        grid[i].possible(i, grid, 62, true) || grid[i].possible(i, grid, 63, true))
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
                if (!grid[position].possible(position, grid, go_to, true)) { // todo tutaj daj bicie w przelocie



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
            case 'b': {

                arr legal;
                legal = grid[ctn(temp[2], temp[1])].pin(ctn(temp[2], temp[1]), grid);
                for (int i = 0; i < legal.size(); i++) {

                    printf("%c%d  ", (char) legal[i] % 8 + 97, ((legal[i] / 8) - 8) * (-1));

                }
                printf(" >%d<\n", legal.size());

                do_it = false;
            }
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
                    printf("%d ", (grid[ctn(temp[2], temp[1])].possible(
                            ctn(temp[2], temp[1]), grid,
                            ctn(temp[4], temp[3]), true)));
                else {
                    arr legal = grid[ctn(temp[2], temp[1])].possible(ctn(temp[2], temp[1]), grid);
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
        if (list_of_moves.back().back() == '\n') color = black;
        else if (list_of_moves.back().back() == '\t') color = white;
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

        b_moves += castle(black).size();
        w_moves += castle(white).size();

        switch (grid[i].emblem) {
            case 'k':
                if (grid[i].color) {
                    b_tab[0]++;
                    b_moves += grid[i].possible(i, grid).size();
                } else {
                    w_tab[0]++;
                    w_moves += grid[i].possible(i, grid).size();
                }
                break;
            case 'q':
                if (grid[i].color) {
                    b_tab[1]++;
                    b_moves += grid[i].possible(i, grid).size();
                } else {
                    w_tab[1]++;
                    w_moves += grid[i].possible(i, grid).size();
                }
                break;
            case 'r':
                if (grid[i].color) {
                    b_tab[2]++;
                    b_moves += grid[i].possible(i, grid).size();
                } else {
                    w_tab[2]++;
                    w_moves += grid[i].possible(i, grid).size();
                }
                break;
            case 'b':
                if (grid[i].color) {
                    b_tab[3]++;
                    b_moves += grid[i].possible(i, grid).size();
                } else {
                    w_tab[3]++;
                    w_moves += grid[i].possible(i, grid).size();
                }
                break;
            case 'n':
                if (grid[i].color) {
                    b_tab[4]++;
                    b_moves += grid[i].possible(i, grid).size();
                } else {
                    w_tab[4]++;
                    w_moves += grid[i].possible(i, grid).size();
                }
                break;
            case 'p':
                if (grid[i].color) {
                    b_tab[5]++;
                    b_moves += grid[i].possible(i, grid).size();
                } else {
                    w_tab[5]++;
                    w_moves += grid[i].possible(i, grid).size();
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
    dynamic_arr tab_of_possible_moves;
    arr temp_moves;
    for (int i = 0; i < 64; ++i) {
        if (grid[i].emblem != '*' && grid[i].color == color) {
            temp_moves = grid[i].possible(i, grid);
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
    std::string temp = "white\tblack\n";
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
    if (color_now == black) {
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

    arr temp_moves;
    dynamic_arr array_of_moves;
    //todo minmax jest pojebany i ty go źle napisałeś bo jesteś głupi

    for (int i = 0; i < 64; ++i) {
        if (grid[i].emblem != '*' && grid[i].color == color_now) {
            temp_moves = grid[i].possible(i, grid);
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
    if (color_now == black)color_dependence = -1;
    if (array_of_moves.empty()) {
        if (grid[oposite_king_position].check(oposite_king_position, grid)) return 100000 * color_dependence;
        return 0;
    }
    piece temp[2];
    double min_or_max;
    min_or_max = 1000006999 * -color_dependence;


    double min_max = 0.0;
    // reku dla

    if (color_now == white) {
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
            if (min_max>200) return 1000000;
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
                    if (min_max>200) return 1000000;
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
                    if (min_max>200) return 1000000;
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
                    if (min_max>200) return 1000000;
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

arr board::castle(bool color) {
    arr possible_moves;
    if (color) {
        if (grid[0].emblem == 'r' && grid[1].emblem == '*' && grid[2].emblem == '*' && grid[3].emblem == '*' &&
            grid[4].emblem == 'k')
            if (grid[0].is_moved == 0 && grid[4].is_moved == 0) {
                for (int i = 0; i < 64; i++) {
                    if (grid[i].color != color)
                        if (grid[i].possible(i, grid, 0, true) || grid[i].possible(i, grid, 1, true) ||
                            grid[i].possible(i, grid, 2, true) || grid[i].possible(i, grid, 3, true) ||
                            grid[i].possible(i, grid, 4, true))
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
                        if (grid[i].possible(i, grid, 56, true) || grid[i].possible(i, grid, 57, true) ||
                            grid[i].possible(i, grid, 58, true) || grid[i].possible(i, grid, 59, true) ||
                            grid[i].possible(i, grid, 60, true))
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
                        if (grid[i].possible(i, grid, 4, true) || grid[i].possible(i, grid, 5, true) ||
                            grid[i].possible(i, grid, 6, true) || grid[i].possible(i, grid, 7, true))
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
                        if (grid[i].possible(i, grid, 60, true) || grid[i].possible(i, grid, 61, true) ||
                            grid[i].possible(i, grid, 62, true) || grid[i].possible(i, grid, 63, true))
                            break;
                    if (i == 63) {
                        possible_moves.push_back(66);
                    }
                }
            }
    }
    /// ok więć to jest tak weź to i wklaej do bool possible  i to będzie lepszze tam
    /// na na na pierdolić
    return possible_moves;

}

arr board::stuff_with_lil_ones(bool color, int position) {
    arr possible_moves;

    switch (position / 8) {
        case 1:
            if (!color && grid[position].possible(position, grid, position - 8)) {
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
            if (color && grid[position].possible(position, grid, position + 8)) {
                possible_moves.push_back(position);
                possible_moves.push_back(100);
                possible_moves.push_back(position);
                possible_moves.push_back(101);
            }
            break;


    }
    return possible_moves;
}