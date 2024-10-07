//neurone.cpp
#include "neurone.hpp"

float neurone::numero()
{
    srand(time(0));
    return static_cast<float>(rand()) / RAND_MAX;
}

neurone::neurone()
{
    azzera();
}

neurone::~neurone()
{
    azzera();
}

void neurone::azzera()
{
    w1=w2=b=eps=rate=c=0.0f;
    dimensione_dati=0;
}

float neurone::cost(float w1, float w2,float b,float allenamento[][3]) 
{
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

void neurone::iniziallizzazione(bool stampa,float allenamento[][3])
{
    w1 = numero();
    w2 = numero();
    b = numero();
    eps = 1e-1;  // Small epsilon for numerical derivative
    rate = 1e-1;
    for (size_t i = 0; i < 1000 * 1000; ++i) {
        c = cost(w1, w2,b,allenamento);
        float Dcost1 = (cost(w1 + eps, w2,b,allenamento) - c) / eps;
        float Dcost2 = (cost(w1, w2 + eps,b,allenamento) - c) / eps;
        float db=(cost(w1,w2,b+eps,allenamento)-c)/eps;
        w1 -= rate * Dcost1;
        w2 -= rate * Dcost2;
        b -= rate * db;
    }
        if(stampa)
        cout<<"w1= "<<w1<<" w2= "<<w2<<" b= "<<b<<" c= "<<c<<endl;
}
float neurone::sigmoid(float x) {
    return 1.0f / (1 + expf(-x));
}

float neurone::GetW1()
{
    return w1;
}
float neurone::GetW2()
{
    return w2;
}
float neurone::GetB()
{
    return b;
}