#include <iostream>
#include <cmath>

class Fracao {
private:
    long long int _numerador;
    long long int _denominador;


    long long int _mdc(long long int a, long long int b) {
        return b == 0 ? a : _mdc(b, a % b);
    }

    void reduz() {
        long long int divisor = _mdc(_numerador, _denominador);
        _numerador /= divisor;
        _denominador /= divisor;
        if (_denominador < 0) {
            _numerador = -_numerador;
            _denominador = -_denominador;
        }
    }

public:
    Fracao(long long int numerador = 0, long long int denominador = 1)
        : _numerador(numerador), _denominador(denominador) {
        if (_denominador == 0) _denominador = 1; // Evita divisão por zero
        reduz();
    }

    Fracao(double x, double eps = 1e-9) {
        long long int numerador = (long long int)(x / eps);
        long long int denominador = (long long int)(1.0 / eps);
        _numerador = numerador;
        _denominador = denominador;
        reduz();
    }

   
operator double() const {
    return static_cast<double>(_numerador) / _denominador;
}
};
