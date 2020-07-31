//
// Created by piotr on 23.07.2020.
//

#ifndef CHESS_MOV_H
#define CHESS_MOV_H



struct mov {
    int pos;
    int g_t;
    double eva;
mov(){
    pos=0;
    g_t=0;
    eva = 0.0;
}
    mov(int pos, int g_t, double eva) {
        this->pos = pos;
        this->g_t = g_t;
        this->eva = eva;
    }

    mov(int pos, int g_t) {
        this->pos = pos;
        this->g_t = g_t;
        this->eva = 0;

    }
    mov &operator=(mov a) {
        this->pos=a.pos;
        this->g_t=a.g_t;
        this->eva=a.eva;
        return *this;
    }
    void show() { printf("from: %c%d\tto: %c%d\twith: %f\n",(char) pos % 8 + 97, ((pos / 8) - 8) * (-1), (char) g_t % 8 + 97, ((g_t / 8) - 8) * (-1), eva); }
};

class arr {
    const int max_siz = 30;
    int siz;
    int rej;
    int tab[30];
public:
    arr() {
        siz = 0;
        rej = 0;
        for (int i = 0; i < 30; i++)tab[i] = -101;
    }


    int size() { return siz; }

    void size(int siz) { this->siz = siz; }

    int rejects() { return rej; }

    void rejects(int rejects) { this->rej += rejects; }

    void push_back(int ad) {

        tab[siz] = ad;
        siz++;

    }

    int &operator[](int pos) {

        return tab[pos];
    }

    arr &operator=(arr a) {

        this->siz = a.siz;
        this->rej = a.rej;
        for (int i = 0; i < a.siz; i++)this->tab[i] = a.tab[i];
    return *this;
    }

    void erase(int del) {
        tab[del] = -101;
        rej++;
    }

    void erase(int del, int del_to) {


        for (int i = del; i < del_to; i++)tab[i] = -101;
        rej += del_to - del;
    }

    bool empty() { return siz == 0; }

    void clr() {
        if (rej == 0) return;
        int i = 0;
        int j = siz;

        for (; i < j; i++) {
            if (tab[i] == -101)
                for (; j > i; j--) {
                    if (tab[j] != -101) {
                        tab[i] = tab[j];
                        tab[j] = -101;
                        break;
                    }
                }
        }
        siz -= rej;
        rej = 0;
    }

    void clear() {
        siz = 0;
        for (int &i : tab)i = -101;


    }

    void show() {
        for (int i = 0; i < 30; i++)printf("%d ", tab[i]);
        printf("\nsiz: %d\trejects: %d\n", siz, rej);
    }

};
class dynamic_arr{
    int siz;
    int max_siz;
    const int inkrement=80;
    mov *tab;
public:
    dynamic_arr(){
        siz=0;
        max_siz = 80;
        tab = new mov[80];
    }
    dynamic_arr(int size, int max_size){
        siz=size;
        this->max_siz = max_size;
        tab = new mov[max_size];
    }
    dynamic_arr(int size){
        siz=size;
        max_siz = size;
        tab = new mov[size];
    }
    ~dynamic_arr(){
        delete[] tab;

    }
    mov &operator[](int pos) {

        return tab[pos];
    }

    dynamic_arr &operator=(dynamic_arr  a) {
        this->siz = a.siz;
        for (int i = 0; i < a.siz; i++)this->tab[i] = a.tab[i];
        return *this;
    }
    int size(){return this->siz;}
    bool empty(){return siz==0;}
    void push_back(mov a){
        if(siz==max_siz) {
            dynamic_arr tp(siz);
            for(int i=0;i<siz;i++) tp[i]=this->tab[i];
            delete [] tab;
            max_siz = siz + inkrement;
            tab = new mov[max_siz];
            for(int i=0;i<siz;i++) tab[i]=tp[i];

        }
        tab[siz] = a;
        siz++;

    }

    void show() {
        for (int i = 0; i < siz; i++)tab[i].show();
        printf("\tsiz: %d\n", siz);
    }
};
#endif //CHESS_MOV_H
