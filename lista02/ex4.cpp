#include <iostream>
#include <random>
#include <math.h>
#include <stdio.h>

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
        static double resultado[3];
        double delta = _b * _b - 4 * _a * _c;

        if (delta < 0) {
            resultado[0] = 0; // Nenhuma raiz real
        } else if (delta == 0) {
            resultado[0] = 1; 
            resultado[1] = -_b / (2.0 * _a);
        } else {
            resultado[0] = 2; 
            resultado[1] = (-_b - sqrt(delta)) / (2.0 * _a);
            resultado[2] = (-_b + sqrt(delta)) / (2.0 * _a);
        }

        return resultado;
    }

    double operator()(double x) {
        return _a * x * x + _b * x + _c;
    }
};

int main() {
    Polinomio2 p(189, 5962, 1928);
    double *v = p.raizes();
    for(int i=0; i<=v[0]; i++) std::cout << v[i] << " " ;
    std::cout << p(2) << std::endl;
    return 0;
}