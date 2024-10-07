#pragma once
#define NN_IMPLEMENTAZION
#include <nn.hpp>
struct Xor
{
    Mat a0;
    Mat w1,b1,a1;
    Mat w2,b2,a2;
    Mat w3,b3,a3;
};
void forward_xor(Xor m);
Xor xor_alloc();
void learn(Xor m,Xor g,float rate);
float cost(Xor m,Mat ti,Mat to);
void pulisci(Xor m);
void Forward_xor_calcolo(Mat Risultato,Mat stratoAtecedente,Mat peso,Mat b);
void calcoloFinite_diff(Xor m,size_t i,size_t j,Mat pesoMat1,Mat pesoMat2,float eps,Mat ti,Mat to,float &saved,float c);
void finite_diff(Xor m,Xor g,float eps,Mat ti,Mat to);