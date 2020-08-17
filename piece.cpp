//
// Created by piotr on 28.06.2020.
//
#ifdef _WIN32



#endif


#include "piece.h"



piece &piece::operator=(piece *a) {
    emblem = a->emblem;
    is_moved = a->is_moved;
    color = a->color;


    return *this;
}






