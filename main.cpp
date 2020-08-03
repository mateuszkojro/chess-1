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
 /*   printf("ty penisie");
    for (int i = 0; i < 64; i++) {
     for(int j =0;j<4;j++) {
      for(int k=0;k<cghe.full_board_of_moves_4_rook[i][j].size();k++) {
       printf("%d ",   cghe.full_board_of_moves_4_rook[i][j][k]);

      }
      printf("\t");
     }
        printf("\n");
    }*/
    //    cghe.admin_l("test.txt");
       cghe.admin();

std::cout<<">>>>>>>>>"<< compare::counter <<"<<<<<<<";


//TODO  dać Elizie porzetesować szachwnice i najlepiej jeszcze komuś
// Todo chech

//todo zfinalizuj warunki
    printf("xd");
    return 0;
}