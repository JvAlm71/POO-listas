#include<stdio.h>
#include<iostream>

int soma(double a, double b){
    return a + b;
};

int main(){
    std::cout << soma(1, 2.5) << std::endl;
    return 0;
}
