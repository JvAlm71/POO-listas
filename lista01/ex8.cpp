#include <iostream>
#include <fstream>
#include <string>

std::string conteudo(std::string nome) {
    std::ifstream arq(nome);
    std::string linha, resultado;
    
    while (getline(arq, linha)) {
        resultado += linha;
    }
    
    arq.close();
    return resultado;
}

int main() {
    std::string texto = conteudo("arquivo.txt");
    std::cout << "\"" << texto << "\"" << std::endl;
    return 0;
}
