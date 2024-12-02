#include <iostream>
#include <cmath>
#include <cstdlib>
#include <iomanip>
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
void gcost(float w1,float w2,float b,float *dw1,float *dw2,float *db){
    // dw1=0;
    // dw2=0;
    // db=0;
    for(size_t i=0;i<lunghezza;++i){
        float xi=allenamento[i][0],yi=allenamento[i][1],zi=allenamento[i][2];
        float ai=sigmoid(xi*w1+yi*w2+b);
        *dw1+=2*(ai-zi)*ai*(1-ai)*xi;
        *dw1+=2*(ai-zi)*ai*(1-ai)*yi;
        *db+=2*(ai-zi)*ai*(1-ai);
    }
    *dw1/=lunghezza;
    *dw2/=lunghezza;
    *db/=lunghezza;
}
int main() {
    srand(time(0));
    float w1 = numero(),w2 = numero(),b = numero();
    float dw1 = 0,dw2 = 0,db = 0;

    float eps = 1e-5;  // Small epsilon for numerical derivative
    float rate = 1e-5;
    cout<<"C="<<cost(w1, w2,b)<<endl;
    for(size_t i=0;i<100000*1000;++i){
        gcost(w1,w2,b,&dw1,&dw2,&db);
        w1-=rate*dw1;
        w2-=rate*dw2;
        b-=rate*db;
        if(i%1000==0)
        cout<<"C="<<cost(w1, w2,b)<<endl;
    }
    for(int i=0;i<2;++i){
        for(int j=0;j<2;++j){
            cout<<i<<" & "<<j<<"="<<fixed<<setprecision(9)<<sigmoid(i*w1+j*w2+b)<<endl;
        }
    }
    return 0;
}
