#include <iostream>
#ifdef _WIN32
 #include <conio.h>
#endif
#include <time.h>
#include "piece.h"
#include "board.h"


int main() {


    srand(time(NULL));
#if 0
    std::string grid_background = "8..###...###...###...###...###...###...###...###...###...###...###...###7##...###...###...###...###...###...###...###...###...###...###...###...6..###...###...###...###...###...###...###...###...###...###...###...###5##...###...###...###...###...###...###...###...###...###...###...###...4..###...###...###...###...###...###...###...###...###...###...###...###3##...###...###...###...###...###...###...###...###...###...###...###...2..###...###...###...###...###...###...###...###...###...###...###...###1##...###...###...###...###...###...###...###...##a..b##c..d##e..f##g..h";
    for(char i:grid_background)
    switch(i){
        case '#':
            std::cout<<'.';
            break;
        case '.':
            std::cout<<' ';
            break;
        default:
            std::cout<<i;

    }
#endif

    board cghe;
    printf("ty penisie");
 //    cghe.admin_l("test.txt");
       cghe.admin();
std::cout<<">>>>>>>>>"<< compare::counter <<"<<<<<<<";


//TODO  dać Elizie porzetesować szachwnice i najlepiej jeszcze komuś
// Todo chech

//todo zfinalizuj warunki
    printf("xd");
    return 0;
}