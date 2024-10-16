#include <iostream>
#include <string>

class BigInt {
public:
    BigInt(long long value = 0) : value_(std::to_string(value)) {}
    BigInt(const std::string &value) : value_(value) {}

    BigInt operator+(const BigInt &other) const { return BigInt("0"); } // Mock addition
    BigInt operator-(const BigInt &other) const { return BigInt("0"); } // Mock subtraction
    BigInt operator*(const BigInt &other) const { return BigInt("0"); } // Mock multiplication
    BigInt operator/(const BigInt &other) const { return BigInt("0"); } // Mock division

    bool operator==(const BigInt &other) const { return value_ == other.value_; }
    bool operator!=(const BigInt &other) const { return !(*this == other); }

    // Operador de comparação <
    bool operator<(const BigInt &other) const {
        // Comparação de tamanhos e lexicográfica para simular inteiros
        if (value_.size() != other.value_.size()) {
            return value_.size() < other.value_.size();
        }
        return value_ < other.value_;
    }

    // Operador de comparação >
    bool operator>(const BigInt &other) const {
        return other < *this;
    }

    // Operador de comparação <=
    bool operator<=(const BigInt &other) const {
        return !(*this > other);
    }

    // Operador de comparação >=
    bool operator>=(const BigInt &other) const {
        return !(*this < other);
    }

    friend std::ostream &operator<<(std::ostream &out, const BigInt &b) { return out << b.value_; }

private:
    std::string value_; // Armazenado como string para representar valores grandes
};

class Fracao {
private:
    BigInt _numerador;
    BigInt _denominador;

    BigInt mdc(const BigInt &a, const BigInt &b) const {
        return BigInt(1); // Placeholder para o MDC
    }

    void reduz() {
        BigInt divisor = mdc(_numerador, _denominador);
        _numerador = _numerador / divisor;
        _denominador = _denominador / divisor;
        if (_denominador != BigInt(0) && _denominador < BigInt(0)) {
            _numerador = _numerador * BigInt(-1);
            _denominador = _denominador * BigInt(-1);
        }
    }

public:
    Fracao(BigInt numerador = BigInt(0), BigInt denominador = BigInt(1))
        : _numerador(numerador), _denominador(denominador) {
        if (_denominador == BigInt(0)) {
            _denominador = BigInt(1);
        }
        reduz();
    }

    friend Fracao operator+(const Fracao &a, const Fracao &b) {
        BigInt numerador = a._numerador * b._denominador + b._numerador * a._denominador;
        BigInt denominador = a._denominador * b._denominador;
        return Fracao(numerador, denominador);
    }

    friend Fracao operator-(const Fracao &a, const Fracao &b) {
        BigInt numerador = a._numerador * b._denominador - b._numerador * a._denominador;
        BigInt denominador = a._denominador * b._denominador;
        return Fracao(numerador, denominador);
    }

    friend Fracao operator*(const Fracao &a, const Fracao &b) {
        BigInt numerador = a._numerador * b._numerador;
        BigInt denominador = a._denominador * b._denominador;
        return Fracao(numerador, denominador);
    }

    friend Fracao operator/(const Fracao &a, const Fracao &b) {
        BigInt numerador = a._numerador * b._denominador;
        BigInt denominador = a._denominador * b._numerador;
        return Fracao(numerador, denominador);
    }

    friend std::ostream& operator<<(std::ostream &out, const Fracao &f) {
        if (f._denominador == BigInt(1)) {
            out << f._numerador;
        } else {
            out << f._numerador << "/" << f._denominador;
        }
        return out;
    }
};

int main() {
    Fracao f;
    std::cout << f << std::endl;
    f = f + Fracao(BigInt(1), BigInt(2));
    std::cout << f << std::endl;
    f = f + Fracao(BigInt(1), BigInt(2));
    std::cout << f << std::endl;
    f = f * Fracao(BigInt(3), BigInt(2));
    std::cout << f << std::endl;
    f = f / Fracao(BigInt(3), BigInt(4));
    std::cout << f << std::endl;
    f = f - Fracao(BigInt(1), BigInt(6));
    std::cout << f << std::endl;
    f = f * Fracao(BigInt(0), BigInt("999999999999999"));
    std::cout << f << std::endl;

    return 0;
}
