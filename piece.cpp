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


piece &piece::operator=(piece *a) {
    emblem = a->emblem;
    is_moved = a->is_moved;
    color = a->color;


    return *this;
}

arr piece::possible(int position, piece *grid) {
    arr temp;
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

bool binary(int check, arr tab) {
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

bool piece::possible(int position, piece *grid, int go_to, bool pin) {

    int px = position / 8, py = position % 8, gx = go_to / 8, gy = go_to % 8;

    if (pin) {
        /*
        arr row = grid[position].pin(position, grid);
        if (row.size() != 0) {
            if (row[0] == -1) return false;
            return binary(go_to, row);
        }
 */
    }


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
            int temp[8] = {position - 17, position - 15, position - 10, position - 6, position + 6, position + 10,
                           position + 15, position + 17};
            return binary(go_to, temp);
        }
            break;
        case 'k': {
            int temp[8] = {position - 9, position - 8, position - 7, position - 1, position + 1, position + 7,
                           position + 8,
                           position + 9};
            return binary(go_to, temp);
        }
            break;
        case 'q': {

/// ok nowy plan
            int b = px + py;
            ///         / <-this one
            if (b == gy + gx) {
                arr temp;
                int temp_x = px, temp_y = py;

                if (gy < py) while (temp_x < 7 && 0 < temp_y) temp.push_back((++temp_x) * 8 + --temp_y);
                else while (temp_x > 0 && 7 > temp_y)temp.push_back((--temp_x) * 8 + ++temp_y);


                for (int i = 0; i < temp.size(); i++) {
                    if (grid[temp[i]].emblem != '*')
                        if (grid[temp[i]].color != color) return temp[i] == go_to;
                        else return false;
                    if (temp[i] == go_to) return true;
                }
            }

            /// \ <-this one
            b = py - px;
            if (b + gx == gy) {// lg to pd
                arr temp;

                int temp_x = px, temp_y = py;
                /// tu idziemy do góry
                if (gy < py) while (temp_x > 0 && 0 < temp_y) temp.push_back((--temp_x) * 8 + --temp_y);
                else while (temp_x < 7 && 7 > temp_y) temp.push_back((++temp_x) * 8 + ++temp_y);


                for (int i = 0; i < temp.size(); i++) {
                    if (grid[temp[i]].emblem != '*')
                        if (grid[temp[i]].color != color) return temp[i] == go_to;
                        else return false;
                    if (temp[i] == go_to) return true;
                }

            }


            if (px == gx) {
                arr temp;
                if (py > gy) for (int z = py - 1; z >= 0; z--) temp.push_back(px * 8 + z);
                else for (int z = py + 1; z < 8; z++) temp.push_back(px * 8 + z);


                for (int i = 0; i < temp.size(); i++) {
                    if (grid[temp[i]].emblem != '*')
                        if (grid[temp[i]].color != color) return temp[i] == go_to;
                        else return false;
                    if (temp[i] == go_to) return true;
                }
            }
            if (py == gy) {

                arr temp;

                if (px > gx) for (int z = px - 1; z >= 0; z--) temp.push_back(z * 8 + py);
                else for (int z = px + 1; z < 8; z++) temp.push_back(z * 8 + py);

                for (int i = 0; i < temp.size(); i++) {
                    if (grid[temp[i]].emblem != '*')
                        if (grid[temp[i]].color != color) return temp[i] == go_to;
                        else return false;
                    if (temp[i] == go_to) return true;
                }
            }
        }

            break;
        case 'b': {
            int b = px + py;
            ///         / <-this one
            if (b == gy + gx) {
                arr temp;
                int temp_x = px, temp_y = py;

                if (gy < py) while (temp_x < 7 && 0 < temp_y) temp.push_back((++temp_x) * 8 + --temp_y);
                else while (temp_x > 0 && 7 > temp_y)temp.push_back((--temp_x) * 8 + ++temp_y);


                for (int i = 0; i < temp.size(); i++) {
                    if (grid[temp[i]].emblem != '*')
                        if (grid[temp[i]].color != color) return temp[i] == go_to;
                        else return false;
                    if (temp[i] == go_to) return true;
                }
            }

            /// \ <-this one
            b = py - px;
            if (b + gx == gy) {// lg to pd
                arr temp;

                int temp_x = px, temp_y = py;
                /// tu idziemy do góry
                if (gy < py) while (temp_x > 0 && 0 < temp_y) temp.push_back((--temp_x) * 8 + --temp_y);
                else while (temp_x < 7 && 7 > temp_y) temp.push_back((++temp_x) * 8 + ++temp_y);


                for (int i = 0; i < temp.size(); i++) {
                    if (grid[temp[i]].emblem != '*')
                        if (grid[temp[i]].color != color) return temp[i] == go_to;
                        else return false;
                    if (temp[i] == go_to) return true;
                }

            }
        }
            break;
        case 'r': {
            if (px == gx) {

                arr temp;

                if (py > gy) for (int z = py - 1; z >= 0; z--) temp.push_back(px * 8 + z);
                else for (int z = py + 1; z < 8; z++) temp.push_back(px * 8 + z);


                for (int i = 0; i < temp.size(); i++) {
                    if (grid[temp[i]].emblem != '*')
                        if (grid[temp[i]].color != color) return temp[i] == go_to;
                        else return false;
                    if (temp[i] == go_to) return true;
                }
            }
            if (py == gy) {

                arr temp;

                if (px > gx) for (int z = px - 1; z >= 0; z--) temp.push_back(z * 8 + py);
                else for (int z = px + 1; z < 8; z++) temp.push_back(z * 8 + py);

                for (int i = 0; i < temp.size(); i++) {
                    if (grid[temp[i]].emblem != '*')
                        if (grid[temp[i]].color != color) return temp[i] == go_to;
                        else return false;
                    if (temp[i] == go_to) return true;
                }

            }

        }
            break;


    }
    return false;


}    //todo test it ;znaczy zwal to na elizę
#if 1
arr piece::pin(int position, piece *grid) { // todo weż sparawadz czy dobrze kolorki figur przeciwnego teamu zrobiłeś

    arr possible_moves;
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
                                        if (!grid[position].possible(position, grid, possible_moves[i], false))
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
                                        if (!grid[position].possible(position, grid, possible_moves[i], false))
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
                                        if (!grid[position].possible(position, grid, possible_moves[i], false))
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
                                        if (!grid[position].possible(position, grid, possible_moves[i], false))
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
                                        if (!grid[position].possible(position, grid, possible_moves[i], false))
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
                                        if (!grid[position].possible(position, grid, possible_moves[i], false))
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
                                        if (!grid[position].possible(position, grid, possible_moves[i], false))
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
                                        if (!grid[position].possible(position, grid, possible_moves[i], false))
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
                                        if (!grid[position].possible(position, grid, possible_moves[i], false))
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
                                        if (!grid[position].possible(position, grid, possible_moves[i], false))
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
                                        if (!grid[position].possible(position, grid, possible_moves[i], false))
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
                                        if (!grid[position].possible(position, grid, possible_moves[i], false))
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
                                        if (!grid[position].possible(position, grid, possible_moves[i], false))
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
                                        if (!grid[position].possible(position, grid, possible_moves[i], false))
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
                                        if (!grid[position].possible(position, grid, possible_moves[i], false))
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
                                        if (!grid[position].possible(position, grid, possible_moves[i], false))
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
#else
arr piece::pin(int position, piece *grid){
    arr possible_moves;
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
    if(px==king_x){
        if(py==king_y)

    }else{




    }




}
#endif
bool piece::check(int position, piece *grid) { // to da się zrobić lepiej
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
        if (grid[i].emblem != '*' && grid[i].color != color)
            if (grid[i].possible(i, grid, position, true)) return true;
    return false;
#endif

}

