#include <iostream>

//Basicamente esse código representa um calculo utilizando uma 
//propriedade da aritmética modular, que é a potência modular.
//A potência modular é uma operação que calcula a potência de um número
int potenciaModular(int base, int expoente, int mod) {
    int resultado = 1;
    base = base % mod;

    // Executa enquanto o expoente for maior que zero
    while (expoente > 0) {
        // Se o expoente for ímpar, multiplicamos o resultado pela base
        if (expoente % 2 != 0) {
            resultado = (resultado * base) % mod;
        }
        // Reduzimos o expoente pela metade
        expoente /= 2;
        // Elevamos a base ao quadrado e aplicamos o módulo
        base = (base * base) % mod;
    }
    return resultado;
}

int main() {
    int base, expoente, modulo;

    // Exemplo de cálculo da potência modular
    base = 2;
    expoente = 10;
    modulo = 100;
    
    int resultado = potenciaModular(base, expoente, modulo);
    
    std::cout << resultado << std::endl;

    return 0;
}
