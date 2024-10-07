#include <iostream>
using namespace std;
    bool prova(int x) {
        if(x<0)return false;
        std::string a=std::to_string(x),b;
        for(int i=a.size();i>=0;--i){
            b.push_back(a[i]);
            cout<<b<<endl;
        }
        cout<<b;
        return a==b;
    }

int main(){
    string a="ciao";
    cout<<prova(222);
    return 0;
}