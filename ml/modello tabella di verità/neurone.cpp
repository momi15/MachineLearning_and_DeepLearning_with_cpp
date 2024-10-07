//neurone.cpp

//file header
#include "neurone.hpp"
//funzione per generare un numero casuale
float neurone::numero()
{
    //cambio il seed con il tempo per avere dei valori il più casuali possibile
    srand(time(0));
    //restitutisco il valore in un formato float
    return static_cast<float>(rand()) / RAND_MAX;
}
//constructor 
neurone::neurone()
{
    //per evitare errori azzero le variabili 
    azzera();
}
//deconstructor
neurone::~neurone()
{
    //per liberare la memoria
    azzera();
}
//funzione per azzerare tutte le variabili
void neurone::azzera()
{
    w1=w2=b=eps=rate=c=0.0f;
    dimensione_dati=0;
}
//funzione costo
float neurone::cost(float w1, float w2,float b,float allenamento[][3]) 
{
    //variabile che sevirà per vedere quanto è veritiero il modello
    float risultato = 0.0f;
    //for per far scorrere l'array allenamento
    for (size_t i = 0; i < lunghezza; i++) {
        //si prendono i valori di entrata
        float x1 = allenamento[i][0];
        float x2 = allenamento[i][1];
        //si calcola y con la formula della retta e usando la funzione sigmoidea si ottengono valori da 0 a 1
        float y = sigmoid(x1 * w1 + x2 * w2+b);
        //per ridurre l'errore si calola la derivata di y
        float d = y - allenamento[i][2];
        /*si moltiplica la devivata per se stessa per 2 motivi il primo perchè così è sempre positivo il risultato 
          il secondo è perchè così se ci sono errori problemi etc... viene tutto raddoppiato volendo si può fare anche 
          per una terza d e fare il valore assoluto ma sarebbe inutile il doppio basta e avanza*/
        risultato += d * d;
    }
    //si divide per la lunghezza dell'allenamento per vedere la media
    return risultato / lunghezza;
}
//funzione per allenare il modello
void neurone::iniziallizzazione(bool stampa,float allenamento[][3])
{
    //si salvano i vari pesi con il bias con valori casuali
    w1 = numero();
    w2 = numero();
    b = numero();
    //di quanto aumento per trovare un valore "buono" in questo caso aumentiamo di 0.1
    eps = 1e-1; 
    //velocità di aprendimento in pratica quando calcoliamo la derivata di quanto si sposta  
    rate = 1e-1;
    //for che ripete la formula del costo faccendo un pò di esperimenti il valore migliore lo ottengo ripetendo la formula 1 milione di volte
    for (size_t i = 0; i < 1000 * 1000; ++i) {
        //salvo il risultato della funzione costo
        c = cost(w1, w2,b,allenamento);
        /*ora con la formula delle derivare che è (f(x+h)-f(x))/h per calcolare la derivata della funzione costo
          in modo da diminuire l'errore della funzione*/
        float Dcost1 = (cost(w1 + eps, w2,b,allenamento) - c) / eps;  //derivata peso 1
        float Dcost2 = (cost(w1, w2 + eps,b,allenamento) - c) / eps;  //derivata peso 2
        float db=(cost(w1,w2,b+eps,allenamento)-c)/eps;               // derivata bias
        //moltiplichiamo per la velocità di aprendimento perchè anche se usiamo la derivata è ancora tropo grande per andare verso 0
        w1 -= rate * Dcost1;
        w2 -= rate * Dcost2;
        b -= rate * db;
    }
        if(stampa) cout<<"w1= "<<w1<<" w2= "<<w2<<" b= "<<b<<" c= "<<c<<endl;
}
//qua si usa la formola 1/(1+e**-x) per fare in modo che sia limitato a dei valori da 0 a 1
float neurone::sigmoid(float x) {
    return 1.0f / (1 + expf(-x));
}
//funzione che restituisce il peso 1
float neurone::GetW1()
{
    return w1;
}
//funzione che restituisce il peso 2
float neurone::GetW2()
{
    return w2;
}
//funzione che restituisce il bias
float neurone::GetB()
{
    return b;
}