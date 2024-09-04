#include<stdio.h>
#include<iostream>


int main(){
    int n;
    std::cin >> n;

    for(int i = 1 ; i <= n; i++){
        if(i%3 == 0 && i%5 == 0 && i%7 == 0 & i%11 == 0 && i%17 == 0 ){
            std::cout << i << std::endl;
    }

    }
};

