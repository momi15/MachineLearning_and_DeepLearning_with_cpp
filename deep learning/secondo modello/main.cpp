#include "main.hpp"
int main(){
    srand(0);
    size_t arch[]={2,2,1};
    NN nn=nn_alloc(arch,ARRAY_LEN(arch));
    NN b=nn_alloc(arch,ARRAY_LEN(arch));
    nn_fill(nn,-1,1);
    double td_xor[]={
        0,0,0,
        0,1,1,
        1,0,1,
        1,1,0,
    };
    double td_or[]={
        0,0,0,
        0,1,1,
        1,0,1,
        1,1,1,
    };
    size_t stride=3;
    size_t n=sizeof(td_xor)/sizeof(td_xor[0])/stride;

    Mat ti ={
        .rows=n,
        .cols=2,
        .stride=stride,
        .es=td_xor,
    };
    Mat to={
        .rows=n,
        .cols=1,
        .stride=stride,
        .es=td_xor+2,
    };
    mat_copy(NN_INPUT(nn),mat_row(ti,1));
    NN_forward(nn);
    double eps=2e-2,rate=2e-2;
        std::cout<<std::endl<<nn_cost(nn,ti,to)<<std::endl;
    for(size_t i=0;i<1000*1000;++i){
        double c=nn_cost(nn,ti,to);
        nn_finite_diff(nn,b,eps,ti,to);
        nn_learn(nn,b,rate);
    }
        std::cout<<std::endl<<nn_cost(nn,ti,to)<<std::endl;
    for(size_t i=0;i<2;++i){
        for(size_t j=0;j<2;++j){
            MAT_AT(NN_INPUT(nn),0,0)=i;
            MAT_AT(NN_INPUT(nn),0,1)=j;
            NN_forward(nn);
            double y=*NN_OUTPUT(nn).es;
            std::cout<<std::endl<<i<<j<<"="<<y<<std::endl;
        }
    }
    NN_PRINT(nn);
    nn_libera(nn);
    return 0;
}