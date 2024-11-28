#include "main.hpp"
int main(){
    srand(0);
    size_t arch[]={2,2,1};
    NN nn=nn_alloc(arch,ARRAY_LEN(arch));
    NN b=nn_alloc(arch,ARRAY_LEN(arch));
    NN derivataCost=nn_alloc(arch,ARRAY_LEN(arch));
    nn_fill(nn,-0.5,0.5);
    nn_fill(b,-0.5,0.5);
    nn_fill(derivataCost,-0.5,0.5);
    std::vector<double> td_xor{
        0,0,0,
        0,1,1,
        1,0,1,
        1,1,0,
    };
    std::vector<double> td_or{
        0,0,0,
        0,1,1,
        1,0,1,
        1,1,1,
    };
    size_t stride=3;
    std::vector<double>td=td_or;
    size_t n=td.size()/stride;

    Mat ti ={
        .rows=n,
        .cols=2,
        .stride=stride,
        .es=td.data(),
    };
    Mat to={
        .rows=n,
        .cols=1,
        .stride=stride,
        .es=td.data()+2,
    };
    mat_copy(NN_INPUT(nn),mat_row(ti,1));
    NN_forward(nn);
    double eps=1e-2,rate=1e-6;
    std::cout<<std::endl<<nn_cost(nn,ti,to)<<std::endl;
    for(size_t i=0;i<20;++i){
        double c=nn_cost(nn,ti,to);
//        nn_finite_diff(nn,b,eps,ti,to);
        NN_Dcost(derivataCost,ti,to);
        nn_learn(nn,derivataCost,rate);
//       nn_adam(nn,derivataCost,rate);
//       if(i%1000)
        std::cout<<std::endl<<nn_cost(nn,ti,to)<<std::endl;
    }
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
    return 0;
}