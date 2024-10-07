#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;
// sigmoid function
float sigmoid(float x) {
    return 1.0f / (1 + expf(-x));
}
typedef float semplice[3];
// OR training data
semplice allenamento_or[] = {
    {0,0,0},
    {0,1,1},
    {1,0,1},
    {1,1,1},
};

// AND training data
semplice allenamento_and[]= {
    {0,0,0},
    {0,1,0},
    {1,0,0},
    {1,1,1},
};
// NAND
semplice allenamento_nand[] = {
    {0,0,1},
    {0,1,1},
    {1,0,1},
    {1,1,0},
};

size_t lunghezza=4;

semplice *allenamento=allenamento_and;

float numero() {
    return static_cast<float>(rand()) / RAND_MAX;
}

float cost(float w1, float w2,float b) {
    float risultato = 0.0f;
    for (size_t i = 0; i < lunghezza; i++) {
        float x1 = allenamento[i][0];
        float x2 = allenamento[i][1];
        float y = sigmoid(x1 * w1 + x2 * w2+b);
        float d = y - allenamento[i][2];
        risultato += d * d;
    }
    return risultato / lunghezza;
}

int main() {
    srand(time(0));
    float w1 = numero();
    float w2 = numero();
    float b = numero();
    float eps = 1e-1;  // Small epsilon for numerical derivative
    float rate = 1e-1;
    float c = cost(w1, w2,b);

    for(int i=0;i<2;++i){
        for(int j=0;j<2;++j){
            cout<<i<<"|"<<j<<"="<<sigmoid(i*w1+j*w2+b)<<endl;
        }
    }
    return 0;
}
