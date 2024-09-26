#include <iostream>
#include <iomanip>

void calcularTroco(double valorCompra, double valorPago) {
    int cedulasMoedas[] = {20000, 10000, 5000, 2000, 1000, 500, 200, 100, 50, 25, 10, 5, 1};
    std::string nomes[] = {
        "R$ 200.00", "R$ 100.00", "R$ 50.00", "R$ 20.00", "R$ 10.00", "R$ 5.00", 
        "R$ 2.00", "R$ 1.00", "R$ 0.50", "R$ 0.25", "R$ 0.10", "R$ 0.05", "R$ 0.01"
    };

    // calculo do troco em centavos para evitar problemas de precisão com números de ponto flutuante
    int trocoCentavos = (valorPago - valorCompra) * 100 + 0.5; // +0.5 para arredondar corretamente

    std::cout << "Troco: R$ " << std::fixed << std::setprecision(2) << (trocoCentavos / 100.0) << std::endl;

    // calcula a quantidade de cada cédula/moeda necessária
    for (int i = 0; i < 13; ++i) {
        int quantidade = trocoCentavos / cedulasMoedas[i];
        std::cout << quantidade << " de " << nomes[i] << std::endl;
        trocoCentavos %= cedulasMoedas[i]; // Atualiza o troco restante
    }
}

int main() {
    double valorCompra, valorPago;
    
    std::cin >> valorCompra >> valorPago;

    // chama a função 
    calcularTroco(valorCompra, valorPago);

    return 0;
}
