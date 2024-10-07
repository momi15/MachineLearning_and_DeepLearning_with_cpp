#include "main.hpp"
float cost(Xor m,Mat ti,Mat to){
    controllo(ti.rows==to.rows,"controllo righe nella funzione costo");
    controllo(to.cols==m.a3.cols,"controllo colonne nelle funzione costo");
    size_t n=ti.rows;
    float c=0;
    for(size_t i=0;i<n;++i){
        Mat x = mat_row(ti,i);
        Mat y = mat_row(to,i);
        mat_copy(m.a0,mat_row(ti,i));
        forward_xor(m);
        size_t q=to.cols;
        for(size_t j=0;j<q;++j){
            float d = MAT_AT(m.a3,0,j)-MAT_AT(y,0,j);
            c+=d*d;
        }
    }
    return c/n;
}
Xor xor_alloc(){
    Xor XOR;
    //primo strato
    XOR.w1 = mat_alloc(2,3);
    XOR.b1 = mat_alloc(1,3);
    XOR.a1 = mat_alloc(1,3);
    //secondo strato
    XOR.w2 = mat_alloc(3,1);
    XOR.b2 = mat_alloc(1,1);
    XOR.a2 = mat_alloc(1,1);
    //terzo strato
    XOR.w3 = mat_alloc(1,1);
    XOR.b3 = mat_alloc(1,1);
    XOR.a3 = mat_alloc(1,1);
    //risultato prima moltiplicazione
    XOR.a0 = mat_alloc(1,2);
    //si riempono con dati randomici da 0 a 1
    mat_fill(XOR.w1,-1,1);
    mat_fill(XOR.b1,-1,1);

    mat_fill(XOR.w2,-1,1);
    mat_fill(XOR.b2,-1,1);

    mat_fill(XOR.w3,-1,1);
    mat_fill(XOR.b3,-1,1);
    return XOR;
    }
void Forward_xor_calcolo(Mat Risultato,Mat stratoAtecedente,Mat peso,Mat b){
    mat_dot(Risultato,stratoAtecedente,peso);
    mat_sum(Risultato,b);
    mat_sigmoid(Risultato);
}
void forward_xor(Xor m){
    Forward_xor_calcolo(m.a1,m.a0,m.w1,m.b1);

    Forward_xor_calcolo(m.a2,m.a1,m.w2,m.b2);

    Forward_xor_calcolo(m.a3,m.a2,m.w3,m.b3);
}
void calcoloFinite_diff(Xor m,size_t i,size_t j,Mat pesoMat1,Mat pesoMat2,float eps,Mat ti,Mat to,float &saved,float c){
    saved=MAT_AT(pesoMat1,i,j);
    MAT_AT(pesoMat1,i,j)+=eps;
    MAT_AT(pesoMat2,i,j)=(cost(m,ti,to)-c)/eps;
    MAT_AT(pesoMat1,i,j) = saved;
}
void finite_diff(Xor m,Xor g,float eps,Mat ti,Mat to){
    float saved,c=cost(m,ti,to);
    for(size_t i=0;i<m.w1.rows;++i){
        for(size_t j=0;j<m.w1.cols;++j){
            calcoloFinite_diff(m,i,j,m.w1,g.w1,eps,ti,to,saved,c);
        }
    }

    for(size_t i=0;i<m.b1.rows;++i){
        for(size_t j=0;j<m.b1.cols;++j){
            calcoloFinite_diff(m,i,j,m.b1,g.b1,eps,ti,to,saved,c);
        }
    }

    for(size_t i=0;i<m.w2.rows;++i){
        for(size_t j=0;j<m.w2.cols;++j){
            calcoloFinite_diff(m,i,j,m.w2,g.w2,eps,ti,to,saved,c);
        }
    }

    for(size_t i=0;i<m.b2.rows;++i){
        for(size_t j=0;j<m.b2.cols;++j){
            calcoloFinite_diff(m,i,j,m.b2,g.b2,eps,ti,to,saved,c);
        }
    }

    for(size_t i=0;i<m.w3.rows;++i){
        for(size_t j=0;j<m.w3.cols;++j){
            calcoloFinite_diff(m,i,j,m.w3,g.w3,eps,ti,to,saved,c);
        }
    }

    for(size_t i=0;i<m.b3.rows;++i){
        for(size_t j=0;j<m.b3.cols;++j){
            calcoloFinite_diff(m,i,j,m.b3,g.b3,eps,ti,to,saved,c);
        }
    }
}
void learn(Xor m,Xor g,float rate){

    for(size_t i=0;i<m.w1.rows;++i){
        for(size_t j=0;j<m.w1.cols;++j){
            MAT_AT(m.w1,i,j)-=rate*MAT_AT(g.w1,i,j);
        }
    }

    for(size_t i=0;i<m.b1.rows;++i){
        for(size_t j=0;j<m.b1.cols;++j){
            MAT_AT(m.b1,i,j)-=rate*MAT_AT(g.b1,i,j);
        }
    }

    for(size_t i=0;i<m.w2.rows;++i){
        for(size_t j=0;j<m.w2.cols;++j){
            MAT_AT(m.w2,i,j)-=rate*MAT_AT(g.w2,i,j);
        }
    }

    for(size_t i=0;i<m.b2.rows;++i){
        for(size_t j=0;j<m.b2.cols;++j){
            MAT_AT(m.b2,i,j)-=rate*MAT_AT(g.b2,i,j);
        }
    }

    for(size_t i=0;i<m.w3.rows;++i){
        for(size_t j=0;j<m.w3.cols;++j){
            MAT_AT(m.w3,i,j)-=rate*MAT_AT(g.w3,i,j);
        }
    }

    for(size_t i=0;i<m.b3.rows;++i){
        for(size_t j=0;j<m.b3.cols;++j){
            MAT_AT(m.b3,i,j)-=rate*MAT_AT(g.b3,i,j);
        }
    }
}
void pulisci(Xor m){
    mat_clear(m.a0);
    mat_clear(m.w1);
    mat_clear(m.b1);
    mat_clear(m.a1);
    mat_clear(m.w2);
    mat_clear(m.b2);
    mat_clear(m.a2);
    mat_clear(m.w3);
    mat_clear(m.b3);
    mat_clear(m.a3);
}
int main(){
    srand(time(0));
    float td[]={
        0,0,0,
        0,1,1,
        1,0,1,
        1,1,0,
    };
    size_t stride=3;
    size_t n=sizeof(td)/sizeof(td[0])/stride;
    Mat ti ={
        .rows=n,
        .cols=2,
        .stride=stride,
        .es=td,
    };
    Mat to={
        .rows=n,
        .cols=1,
        .stride=stride,
        .es=td+2,
    };
    MAT_PRINT(ti);
    MAT_PRINT(to);
    Xor m=xor_alloc(),g=xor_alloc();
    std::cout<<std::endl<<cost(m,ti,to);
    float eps=1e-1,rate=1e-1;
    for(size_t i=0;i<200*200;++i){
        finite_diff(m,g,eps,ti,to);
        learn(m,g,rate);
//        std::cout<<std::endl<<i<<"  "<<cost(m,ti,to)<<std::endl;
    }
    std::cout<<std::endl<<cost(m,ti,to)<<std::endl;
    for(size_t i=0;i<2;++i){
        for(size_t j=0;j<2;++j){
            MAT_AT(m.a0,0,0)=i;
            MAT_AT(m.a0,0,1)=j;
            forward_xor(m);
            float y=*m.a3.es;
            std::cout<<std::endl<<i<<j<<"="<<y<<std::endl;
        }
    }
    MAT_PRINT(m.a2);
    MAT_PRINT(m.a3);
    std::cout<<std::endl<<m.a3.cols;
    //svuota le matrici  
    pulisci(m);
    pulisci(g);
   return 0;
}