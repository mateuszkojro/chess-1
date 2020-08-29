#include <iostream>
#ifdef _WIN32
 #include <conio.h>
#endif
#include <time.h>
#include <fstream>
#include "piece.h"
#include "board.h"


int main() {
    srand(time(NULL));

    board cghe;
    cghe.cvc(WHITE,500,30000,"dane.txt",true,4);




//TODO  dać Elizie porzetesować szachwnice i najlepiej jeszcze komuś
// Todo chech

//todo zfinalizuj warunki
    printf("xd");
    return 0;
}