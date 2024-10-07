//main.cpp

#include "main.hpp"
#include "neurone.hpp"

//xor= (x|y) & !(x&y)
neurone NeuroneAND,NeuroneOR,NeuroneNAND;
// OR
float allenamento_or[][3]= {
    {0,0,0},
    {0,1,1},
    {1,0,1},
    {1,1,1},
};

// AND
float allenamento_and[][3]= {
    {0,0,0},
    {0,1,0},
    {1,0,0},
    {1,1,1},
};
// NAND
float allenamento_nand[][3]= {
    {0,0,1},
    {0,1,1},
    {1,0,1},
    {1,1,0},
};

int main() {
    NeuroneAND.iniziallizzazione(false,allenamento_and);
    NeuroneOR.iniziallizzazione(false,allenamento_or);
    NeuroneNAND.iniziallizzazione(false,allenamento_nand);
    float w1_AND=NeuroneAND.GetW1(),w2_AND=NeuroneAND.GetW2(),b_AND=NeuroneAND.GetB();
    float w1_OR=NeuroneOR.GetW1(),w2_OR=NeuroneOR.GetW2(),b_OR=NeuroneOR.GetB();
    float w1_NAND=NeuroneNAND.GetW1(),w2_NAND=NeuroneNAND.GetW2(),b_NAND=NeuroneNAND.GetB();
    for(int i=0;i<2;++i){
        for(int j=0;j<2;++j){
            float risultatoOR=NeuroneOR.sigmoid(i*w1_OR+j*w2_OR+b_OR);
            float risultatoNAND=NeuroneNAND.sigmoid(i*w1_NAND+j*w2_NAND+b_NAND);
            float risultatoAND=NeuroneAND.sigmoid(i*w1_AND+j*w2_AND+b_AND);
            float risultatoXOR=NeuroneOR.sigmoid(risultatoOR*w1_AND+risultatoNAND*w2_AND+b_AND);
            cout<<i<<" XOR "<<j<<" = "<<risultatoXOR<<endl;
        }
    }
    return 0;
}
