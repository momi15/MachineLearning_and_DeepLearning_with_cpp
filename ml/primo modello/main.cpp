#include "main.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <random>
#include <cassert>

using namespace std;

int allenamento[][2] = {
    {1, 1},
    {2, 2},
    {3, 4},
    {4, 8},
    {5, 16},
};

int lunghezza_allenamento = (sizeof(allenamento) / sizeof(allenamento[0]));

float numero() {
    static random_device rd;
    static mt19937 gen(rd());
    static uniform_real_distribution<> dis(0.0, 1.0);
    return dis(gen);
}

float cost(float w, float b) {
    float risultato = 0.0f;
    for (size_t i = 0; i < lunghezza_allenamento; i++) {
        float x = allenamento[i][0];
        float y = x * w + b;
        float d = y - allenamento[i][1];
        risultato += d * d;
    }
    return risultato / lunghezza_allenamento;
}

int arrotonda(float numero) {
    return static_cast<int>(numero + 0.5f);
}


int main() {
    srand(static_cast<unsigned int>(time(0)));

    float w = numero();
    float b = numero();
    float c = cost(w, b);
    const float eps = 1e-3;
    const float rate = 1e-2;

    for (size_t i = 0; i < 100000; ++i) {
        float Dcost = (cost(w + eps, b) - cost(w, b)) / eps;
        float bd = (cost(w, b + eps) - cost(w, b)) / eps;
        w -= rate * Dcost;
        b -= rate * bd;

        c = cost(w, b);
        if (c < 0.02) {
            break;
        }

        cout << w << " " << b << " " << fixed << setprecision(11) << c << endl;
    }

    return 0;
}
