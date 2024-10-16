#include <iostream>
#include <random>
#include <math.h>

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
            resultado[1] = (-_b + sqrt(delta)) / (2.0 * _a);
            resultado[2] = (-_b - sqrt(delta)) / (2.0 * _a);
        }

        return resultado;
    }

    double operator()(double x) {
        return _a * x * x + _b * x + _c;
    }
};

int main() {
    double* v;
    
    Polinomio2 p1(1, 1, 1);
    v = p1.raizes();
    for (int i = 0; i <= v[0]; i++) std::cout << v[i] << " ";
    std::cout << '\n' << p1(2) << '\n';
    
    Polinomio2 p2(1, 2, 1);
    v = p2.raizes();
    for (int i = 0; i <= v[0]; i++) std::cout << v[i] << " ";
    std::cout << '\n' << p2(2) << '\n';
    
    Polinomio2 p3(1, -3, 2);
    v = p3.raizes();
    for (int i = 0; i <= v[0]; i++) std::cout << v[i] << " ";
    std::cout << '\n' << p3(2) << '\n';

    return 0;
}
