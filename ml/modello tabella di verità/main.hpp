//main.hpp
#ifndef MAIN_HPP
#define MAIN_HPP
//libererie e file header
#include <iostream> 
#include <cstdlib>
#include <ctime>
#include <cmath> 
#include <vector>
#include "neurone.hpp"

//funzioni
float sigmoid(float x);

std::vector<float> CalcoloDigitale(int numero[], const std::vector<std::vector<int>>& variabili, float allenamento[][3], neurone& tipo, int numero_bit);

std::vector<float> CalcoloDigitaleConRisultati(int numero[], const std::vector<std::vector<int>>& variabili, float allenamento[][3], neurone& tipo, const std::vector<float>& risultato1, const std::vector<float>& risultato2, bool piuRisultati, int numero_bit);

std::vector<float> CalcoloDigitaleXOR(int numero[], const std::vector<std::vector<int>>& variabili, int numero_bit);

std::vector<float> CalcoloDigitaleXOR(int numero[], const std::vector<std::vector<int>>& variabili, const std::vector<float>& risultato1, const std::vector<float>& risultato2, bool piuRisultati, int numero_bit);

void gestione_risposte(std::vector<std::vector<float>>& risultati, int numero[], const std::vector<std::vector<int>>& variabili, float allenamento[][3], neurone& tipo, std::vector<float>& supRisultati, int numero_bit, int numero_variabili);

#endif // MAIN_HPP
