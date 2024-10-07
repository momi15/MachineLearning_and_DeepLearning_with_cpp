//neurone.hpp
//libererie e file header
#include <iostream>
#include <cstdlib>  
#include <ctime>    
#include <cmath>    
using namespace std;
//definisco la classe neurone
class neurone
{
public:
    //funzioni publiche
    void iniziallizzazione(bool stampa,float allenamento[][3]);
    float GetW1();
    float GetW2();
    float GetB();
    float sigmoid(float x);
    //constructor destructor
    neurone();
    ~neurone();
private:
    //funzioni private
    void azzera();
    float numero();
    float cost(float w1, float w2,float b,float allenamento[][3]);
    //variabili private
    float w1,w2,b,eps,rate,c;
    float dati[4][3];
    float lunghezza=4;
    int dimensione_dati;
};