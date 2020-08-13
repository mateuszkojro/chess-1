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
    cghe.admin();
    cghe.pvc(3,WHITE);


    std::cout<<">>>>>>>>>"<< compare::counter <<"<<<<<<<";


//TODO  dać Elizie porzetesować szachwnice i najlepiej jeszcze komuś
// Todo chech

//todo zfinalizuj warunki
    printf("xd");
    return 0;
}