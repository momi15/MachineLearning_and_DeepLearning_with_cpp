#include <iostream>
#include <cstdlib>   // Per rand() e srand()
#include <ctime>     // Per time()
#include <cmath>     // Per abs()
using namespace std;
class neurone
{
public:
    void iniziallizzazione(bool stampa,float allenamento[][3]);
    float GetW1();
    float GetW2();
    float GetB();
    float sigmoid(float x);
    neurone();
    ~neurone();

private:
    void azzera();
    float numero();
    float cost(float w1, float w2,float b,float allenamento[][3]);
    float w1,w2,b,eps,rate,c;
    float dati[4][3];
    float lunghezza=4;
    int dimensione_dati;
};