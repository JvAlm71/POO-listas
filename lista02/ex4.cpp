#include <iostream>
#include <random>
#include <math.h>
#include <stdio.h> // para printf

class Polinomio2 {
private:
    int _a, _b, _c;

public:
    Polinomio2(int a = 0, int b = 0, int c = 0) : _a(a), _b(b), _c(c) {
        if (_a == 0) {
            _a = 1;
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dist(0, 9);
            _b = dist(gen);
            _c = dist(gen);
        }
    }

    double* raizes() {
        double* resultado = new double[3];
        double delta = _b * _b - 4 * _a * _c;

        if (delta < 0) {
            resultado[0] = 0; // Sem raízes reais
        } else if (delta == 0) {
            resultado[0] = 1; // Uma raiz real
            resultado[1] = -_b / (2.0 * _a);
        } else {
            resultado[0] = 2; // Duas raízes reais
            double raiz1 = (-_b + sqrt(delta)) / (2.0 * _a);
            double raiz2 = (-_b - sqrt(delta)) / (2.0 * _a);
            if (raiz1 < raiz2) {
                resultado[1] = raiz1;
                resultado[2] = raiz2;
            } else {
                resultado[1] = raiz2;
                resultado[2] = raiz1;
            }
        }

        return resultado;
    }

    double operator()(double x) {
        return _a * x * x + _b * x + _c;
    }
};

int main() {
    double* v;
    
    Polinomio2 p1(-1454, 5891, 44);
    v = p1.raizes();
    printf("%.1f ", v[0]); // Primeira saída sem decimais, apenas o número de raízes
    for (int i = 1; i <= v[0]; i++) {
        printf("%.15f ", v[i]); // Usando 15 casas decimais para as raízes
    }
    printf("%.0f\n", p1(2)); // Valor do polinômio para x = 2, sem casas decimais

    return 0;
}
