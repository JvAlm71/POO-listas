#include <iostream>
//Basicamente esse código representa um calculo utilizando uma 
//propriedade da aritmética modular, que é a potência modular.
//A potência modular é uma operação que calcula a potência de um número
int pow(int b, int e, int m) {
    int resultado = 1;
    b = b % m;
    //Basicamente abaixo estaremos usando uma propriedade matemática
    while (e > 0) {
        if (e % 2 == 1) {
            resultado = (resultado * b) % m;
        }
        e = e / 2;
        b = (b * b) % m;
    }
    return resultado; 
}

int main() {
    int base, exp, mod;
    int resultado = pow(2, 10, 100);
    
    std::cout << resultado << std::endl;

    return 0;
;}

