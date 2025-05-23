#include <iostream>
#include <string>

// Função para remover todas as ocorrências de um caractere 'c' da string 'texto'
std::string retira(std::string texto, char c) {
    std::string resultado;
    
    // Itera sobre todos os caracteres da string
    for (char t : texto) {
        if (t != c) {
            resultado += t;  
        }
    }
    
    return resultado;
}

int main() {
    std::cout << retira("Testes", 'e') << std::endl;  
    std::cout << retira("Testes", 'X') << std::endl;  
    
    return 0;
}
