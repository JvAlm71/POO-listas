#include <iostream>

int calcularSequencia(int n, int k, int *inicial) {

    // Se n for menor que k, retorna o valor direto do vetor inicial
    if (n < k) {
        return inicial[n];
    } else {
        int somaQuadrados = 0;

        // Itera sobre os últimos k elementos e soma o quadrado de cada termo
        for (int i = n - k; i < n; ++i) {
            int valor = calcularSequencia(i, k, inicial);
            somaQuadrados += valor * valor;
        }

        // Retorna a soma dos quadrados
        return somaQuadrados;
    }
}

int main() {
    // Vetor com os valores iniciais
    int termosIniciais[] = {1, -2, 1};

    // Definindo os valores de n e k
    int n = 3;
    int k = 3;

    // Calcula o n-ésimo termo da sequência
    int resultado = calcularSequencia(n, k, termosIniciais);

    // Exibe o resultado final
    std::cout << resultado << std::endl;

    return 0;
}
