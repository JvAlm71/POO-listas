#include <iostream>
#include <fstream>
#include <string>

class Arquivo {
private:
    std::ifstream conteudo;

public:
    // Construtor que abre o arquivo
    Arquivo(const std::string& arquivo) {
        conteudo.open(arquivo);
        if (!conteudo) {
            std::cerr << "Erro ao abrir o arquivo: " << arquivo << std::endl;
        }
    }

    // Método que lê a próxima linha
    std::string proxima_linha() {
        if (!conteudo.is_open()) {
            return "."; // Retorna '.' se o arquivo não pôde ser aberto
        }
        std::string linha;
        if (std::getline(conteudo, linha)) {
            return linha;
        } else {
            return "."; // Retorna '.' se não houver mais linhas
        }
    }

    // Destrutor que fecha o arquivo
    ~Arquivo() {
        if (conteudo.is_open()) {
            conteudo.close();
        }
    }
};

int main() {
    Arquivo a("arquivo.txt");
    std::cout << a.proxima_linha() << std::endl;
    std::cout << a.proxima_linha() << std::endl;
    return 0;
}
