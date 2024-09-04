#include<stdio.h>
#include<iostream>

int seq(int n, int k,int *ini){

    if (n < k) {
        return ini[n];
    } else {
        int nesimo = 0;
        for (int i = n - k; i < n; ++i) {
            int termo = seq(i, k, ini); 
            nesimo += termo * termo; 
        }
     return nesimo; 
    }
};

int main(){
    int ini[] ={1,-2,1};
    int n = 3;
    int k = 3;

    int resultado = seq(n, k, ini);
    std::cout << resultado << std::endl;

return 0;
};