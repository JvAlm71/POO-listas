#include <iostream>
#include <fstream>
#include <string>

class Arquivo {
private:
    std::ifstream _conteudo;

public:
   
    Arquivo(const std::string& arquivo) {
        _conteudo.open(arquivo);
        if (!_conteudo) {
            std::cerr << "Erro ao abrir o arquivo: " << arquivo << std::endl;
        }
    }

    std::string proxima_linha() {
        if (!_conteudo.is_open()) {
            return "."; 
        }
        std::string linha;
        if (std::getline(_conteudo, linha)) {
            return linha;
        } else {
            return "."; 
        }
    }

   
    ~Arquivo() {
        if (_conteudo.is_open()) {
            _conteudo.close();
        }
    }
};

int main() {
    Arquivo a("arquivo.txt");
    std::cout << a.proxima_linha() << std::endl;
    std::cout << a.proxima_linha() << std::endl;
    return 0;
}
