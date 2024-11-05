#include <iostream>
#include <iomanip>
#include <stdio.h>

class Fracao {
private:
    long long int _numerador;
    long long int _denominador;

    void reduz() {
        long long int a = _numerador;
        long long int b = _denominador;

        while (b != 0) {
            long long int temp = b;
            b = a % b;
            a = temp;
        }

        long long int divisor = (a != 0) ? a : 1;

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
        if (_denominador == 0) {
            _denominador = 1;
        }
        reduz();
    }

    Fracao(double x, double eps = 1e-9) {
        long long int numerador = static_cast<long long int>(x / eps);
        long long int denominador = static_cast<long long int>(1.0 / eps);
        _numerador = numerador;
        _denominador = denominador;
        reduz();
    }

    operator double() const {
        return static_cast<double>(_numerador) / _denominador;
    }

    friend Fracao operator+(const Fracao &a, const Fracao &b) {
        long long int numerador = a._numerador * b._denominador + b._numerador * a._denominador;
        long long int denominador = a._denominador * b._denominador;
        return Fracao(numerador, denominador);
    }

    friend Fracao operator-(const Fracao &a, const Fracao &b) {
        long long int numerador = a._numerador * b._denominador - b._numerador * a._denominador;
        long long int denominador = a._denominador * b._denominador;
        return Fracao(numerador, denominador);
    }

    friend Fracao operator*(const Fracao &a, const Fracao &b) {
        long long int numerador = a._numerador * b._numerador;
        long long int denominador = a._denominador * b._denominador;
        return Fracao(numerador, denominador);
    }

    friend Fracao operator/(const Fracao &a, const Fracao &b) {
        long long int numerador = a._numerador * b._denominador;
        long long int denominador = a._denominador * b._numerador;
        return Fracao(numerador, denominador);
    }

    friend std::ostream& operator<<(std::ostream &out, const Fracao &f) {
        if (f._numerador == 0) {
            out << "0";
        } else if (f._denominador == 1) {
            out << f._numerador;
        } else {
            out << f._numerador << "/" << f._denominador;
        }
        return out;
    }
};

int main() {
    
    Fracao f(0LL);
    std::cout << f << " " << double(f) << std::endl;
    f = f + Fracao(1LL, 2LL);
    std::cout << f << " " << double(f) << std::endl;
    f = f + Fracao(1LL, 2LL);
    std::cout << f << " " << double(f) << std::endl;
    f = f * Fracao(3LL, 2LL);
    std::cout << f << " " << double(f) << std::endl;
    f = f / Fracao(3LL, 4LL);
    std::cout << f << " " << double(f) << std::endl;
    f = f - Fracao(1LL, 6LL);
    std::cout << f << " " << double(f) << std::endl;
    f = f * Fracao(0LL, 99999999999999LL);
    std::cout << f << " " << double(f) << std::endl;
    return 0;
}