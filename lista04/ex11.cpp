#include <iostream>
#include <string>

class Pessoa {
public:
    Pessoa(const std::string& dados) {
        // Localiza a posição do nome
        size_t pos = dados.find(" tem ");
        nome = dados.substr(0, pos);  // Extrai o nome

        // Localiza a posição da idade
        size_t pos_idade = dados.find(" anos e mora em ");
        idade = dados.substr(pos + 5, pos_idade - (pos + 5));  // Extrai a idade

        // Localiza a posição da cidade
        size_t pos_cidade = dados.find("mora em ") + 8;
        size_t pos_uf = dados.find("-", pos_cidade);
        cidade = dados.substr(pos_cidade, pos_uf - pos_cidade);  // Extrai a cidade

        // Localiza a posição do UF
        uf = dados.substr(pos_uf + 1, dados.find(",", pos_uf) - pos_uf - 1);  // Extrai o UF

        // Localiza a posição do país
        size_t pos_pais = dados.find(",", pos_uf) + 2;
        pais = dados.substr(pos_pais);  // Extrai o país
    }

    friend std::ostream& operator<<(std::ostream& os, const Pessoa& p) {
        os << p.nome << std::endl;
        os << p.idade << std::endl;
        os << p.cidade << std::endl;
        os << p.uf << std::endl;
        os << p.pais << std::endl;
        return os;
    }

private:
    std::string nome, idade, cidade, uf, pais;
};

int main() {
    // Passando a string que contém as informações
    std::cout << Pessoa("André Smaira tem 34 anos e mora em São Carlos-SP, Brasil");
    return 0;
}
