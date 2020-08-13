//
// Created by piotr on 23.07.2020.
//

#ifndef CHESS_MOV_H
#define CHESS_MOV_H


struct mov {
    int pos;
    int g_t;
    double eva;

    mov() {
        pos = 0;
        g_t = 0;
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
        this->pos = a.pos;
        this->g_t = a.g_t;
        this->eva = a.eva;
        return *this;
    }

    void show() {
        printf("from: %c%d\tto: %c%d\twith: %f\n", (char) pos % 8 + 97, ((pos / 8) - 8) * (-1), (char) g_t % 8 + 97,
               ((g_t / 8) - 8) * (-1), eva);
    }
};

class array {
    const int max_siz = 30;
    int siz;
    int rej;
    int tab[30];
public:
    array() {
        siz = 0;
        rej = 0;
        for (int i = 0; i < 30; i++)tab[i] = -101;
    }


    int size() { return this->siz; }

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

    array &operator=(array a) {
        if (this != &a) {
            this->siz = a.siz;
            this->rej = a.rej;
            for (int i = 0; i < a.siz; i++) this->tab[i] = a.tab[i];
        } else printf("bnsdfhasdf");
        return *this;
    }


    array(const array &other) {

        siz = other.siz;
        rej = other.rej;
        for (int i = 0; i < other.siz; i++) {
            tab[i] = other.tab[i];
        }

    }

    void erase(int del) {
        if (tab[del !=-101]) {
            tab[del] = -101;
            rej++;
        }
    }

    void erase(int del, int del_to) {

        for (int i = del; i < del_to; i++) {
            if (tab[i] != -101) {
                tab[i] = -101;
                rej++;
            }
        }
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
          rej =0;
        for (int &i : tab)i = -101;


    }

    void show() {
        for (int i = 0; i < 30; i++)printf("%d ", tab[i]);
        printf("\nsiz: %d\trejects: %d\n", siz, rej);
    }

};


template<class T>
class dynamic_arr {
    int siz;
    int max_siz;
    const int inkrement = 80;
    T *tab;
public:

    dynamic_arr() {
        siz = 0;
        max_siz = 80;
        tab = new T[80];
    }

    dynamic_arr(int size, int max_size) {
        siz = size;
        this->max_siz = max_size;
        tab = new T[max_size];
    }

    dynamic_arr(int size) {
        siz = size;
        max_siz = size;
        tab = new T[size];
    }

    ~dynamic_arr() {
        delete[] tab;
        tab = nullptr;

    }


    T &operator[](int pos) {
        if (pos > siz) {


            printf("lelelele");

        }
        return tab[pos];


    }

    dynamic_arr &operator=(dynamic_arr &a) {
        tab = new T[a.siz];
        this->siz = a.siz;
        for (int i = 0; i < a.siz; i++)this->tab[i] = a.tab[i];
        return *this;
    }

    int size() { return this->siz; }

    void size(int siz) { this->siz = siz; }

    void clear() {
        delete[]tab;
        this->max_siz = 80;
        this->siz = 0;
        this->tab = new T[80];
    }

    bool empty() { return siz == 0; }


    void push_back(mov a) {
        if (siz >= max_siz) {
            dynamic_arr<T> tp(siz);
            for (int i = 0; i < siz; i++) tp[i] = this->tab[i];
            delete[] tab;
            max_siz = siz + inkrement;
            tab = new T[max_siz];
            for (int i = 0; i < siz; i++) tab[i] = tp[i];
            delete[] tp.tab;
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
