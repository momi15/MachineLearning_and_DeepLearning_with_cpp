#include "main.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <random>
#include <cassert>

using namespace std;

int allenamento[][2] = {
    {1, 2},
    {2, 4},
    {3, 6},
    {4, 8},
    {5, 10},
    {6, 12},
    {7, 14},
    {8, 16},
    {9, 18},
    {10, 20},
};

int lunghezza_allenamento = (sizeof(allenamento) / sizeof(allenamento[0]));

float numero(float max,float min) {
    return static_cast<double>(rand())/RAND_MAX*(max-min)+min;
}

float cost(float w) {
    float risultato = 0.0f;
    for (size_t i = 0; i < lunghezza_allenamento; i++) {
        float x = allenamento[i][0];
        float y = x * w;
        float d = y - allenamento[i][1];
        risultato += d * d;
    }
    return risultato / lunghezza_allenamento;
}

int arrotonda(float numero) {
    return static_cast<int>(numero + 0.5f);
}

float dcost(float w){
    float risultato=0;
    for(size_t i=0;i<lunghezza_allenamento;++i){
        float x=allenamento[i][0],y=allenamento[i][1];
        risultato+=2*(x*w-y)*x;
    }
    risultato/=lunghezza_allenamento;
    return risultato;
}
int main() {
    srand(time(0));

    float w = numero(10,0);
//    float b = numero(-1,1);
    float c = cost(w);
    const float eps = 1e-8;
    const float rate = 1e-5;

    for (size_t i = 0; i <1000; ++i) {
        float Dcost = (cost(w + eps) - cost(w)) / eps;
//        float bd = (cost(w, b + eps) - cost(w, b)) / eps;
        w -= rate * Dcost;
//        b -= rate * bd;

        c = cost(w);
    }
        cout <<fixed << setprecision(11)<<"W = "<< w <<endl<<"C = "<< c << endl;
    w=numero(10,0);
    for(size_t j=0;j<1000;++j){
        c=cost(w);
        float gcost=dcost(w);
        w-=rate*gcost;
    }
        cout <<fixed << setprecision(11)<<"W = "<< w <<endl<<"C = "<< c << endl;
    return 0;
}
