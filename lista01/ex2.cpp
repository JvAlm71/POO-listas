#include<iostream>
#include<stdio.h>

int main(){
    int numbalas;
    double precobalas;
    int numchoco;
    double precochoco;
    std::cin >> numbalas >> precobalas >> numchoco >> precochoco;
    double total = numbalas*precobalas + numchoco*precochoco;

    printf("%.1f\n", total);
}