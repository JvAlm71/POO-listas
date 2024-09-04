#include<stdio.h>
#include<iostream>
#include<math.h>
#include<iomanip>


int main (){
    double x1 , x2 , y1 , y2 , distancia;
    std::cin >> x1 >> y1;
    std::cin >> x2 >> y2;
    distancia = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
    std::cout << std::fixed << std::setprecision(4) << distancia << std::endl;
    return 0;
}