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

   
    friend Fracao operator+(const Fracao &a, const Fracao &b) {
        long long int numerador = a._numerador * b._denominador + b._numerador * a._denominador;
        long long int denominador = a._denominador * b._denominador;
        Fracao resultado(numerador, denominador);
        resultado.reduz();
        return resultado;
    }

   
    friend Fracao operator-(const Fracao &a, const Fracao &b) {
        long long int numerador = a._numerador * b._denominador - b._numerador * a._denominador;
        long long int denominador = a._denominador * b._denominador;
        Fracao resultado(numerador, denominador);
        resultado.reduz();
        return resultado;
    }

    
    friend Fracao operator*(const Fracao &a, const Fracao &b) {
        long long int numerador = a._numerador * b._numerador;
        long long int denominador = a._denominador * b._denominador;
        Fracao resultado(numerador, denominador);
        resultado.reduz();
        return resultado;
    }

    
    friend Fracao operator/(const Fracao &a, const Fracao &b) {
        long long int numerador = a._numerador * b._denominador;
        long long int denominador = a._denominador * b._numerador;
        Fracao resultado(numerador, denominador);
        resultado.reduz();
        return resultado;
    }

    
    operator double() const {
        return static_cast<double>(_numerador) / _denominador;
    }

    friend std::ostream& operator<<(std::ostream &out, const Fracao &f) {
        if (f._denominador == 1) {
            out << f._numerador;
        } else {
            out << f._numerador << "/" << f._denominador;
        }
        return out;
    }
};

int main() {
    Fracao f;
    std::cout << f << " " << double(f) << '\n';
    f = Fracao((long long int)1, (long long int)2);
    std::cout << f << " " << double(f) << '\n';
    f = f + Fracao((long long int)1, (long long int)1);
    std::cout << f << " " << double(f) << '\n';
    f = f + Fracao((long long int)1, (long long int)2);
    std::cout << f << " " << double(f) << '\n';
    f = f * Fracao((long long int)3, (long long int)2);
    std::cout << f << " " << double(f) << '\n';
    f = f / Fracao((long long int)3, (long long int)4);
    std::cout << f << " " << double(f) << '\n';
    f = f - Fracao((long long int)1, (long long int)6);
    std::cout << f << " " << double(f) << '\n';
    f = f * Fracao((long long int)0, (long long int)999999999999);
    std::cout << f << " " << double(f) << '\n';

    return 0;
}
