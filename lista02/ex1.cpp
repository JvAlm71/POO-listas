#include <iostream>

class Televisao {
private:
    bool ligada;
    int canal;

public:
    // construtor com valores padrao para ligada e canal
    Televisao(bool ligada = false, int canal = 1) {
        this->ligada = ligada;
        this->canal = canal;
    }

    
    void liga() {
        ligada = true;
    }


    void desliga() {
        ligada = false;
    }

    // aumenta o canal em 1
    void canal_cima() {
        if (ligada) {
            canal++;
        }
    }

    // diminui o canal em 1
    void canal_baixo() {
        if (ligada) {
            canal--;
        }
    }

    // sobrecarga do operador para a saída no formato (estado, canal)
    friend std::ostream& operator<<(std::ostream &out, const Televisao &tv) {
        out << "(" << (tv.ligada ? "ligada" : "desligada") << ", " << tv.canal << ")";
        return out;
    }
};

int main() {
    Televisao tv;
    std::cout << tv << std::endl;
    tv.canal_cima();
    std::cout << tv << std::endl;
    tv.canal_baixo();
    std::cout << tv << std::endl;
    tv.liga();
    std::cout << tv << std::endl;
    tv.canal_cima();
    std::cout << tv << std::endl;
    tv.canal_baixo();
    std::cout << tv << std::endl;
    tv.desliga();
    std::cout << tv << std::endl;
    tv.canal_cima();
    std::cout << tv << std::endl;

    return 0;
}
