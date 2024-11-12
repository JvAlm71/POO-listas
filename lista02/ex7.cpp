#include <stdio.h>
#include <iostream>

// Classe BigInt
class BigInt {
private:
    long long int value;
public:
    BigInt(long long int val = 0) : value(val) {}

    BigInt operator+(const BigInt& other) const {
        return BigInt(value + other.value);
    }

    BigInt operator-(const BigInt& other) const {
        return BigInt(value - other.value);
    }

    BigInt operator*(const BigInt& other) const {
        return BigInt(value * other.value);
    }

    BigInt operator/(const BigInt& other) const {
        return BigInt(value / other.value);
    }

    bool operator==(const BigInt& other) const {
        return value == other.value;
    }

    long long int getValue() const {
        return value;
    }

    // Função para calcular o MDC (Máximo Divisor Comum)
    static long long int gcd(long long int a, long long int b) {
        while (b != 0) {
            long long int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }

    friend std::ostream& operator<<(std::ostream& out, const BigInt& num) {
        out << num.value;
        return out;
    }
};

// Classe Fracao
class Fracao {
private:
    BigInt _numerador;
    BigInt _denominador;

public:
    // Construtor com validação do denominador
    Fracao(BigInt numerador = 0, BigInt denominador = 1) : _numerador(numerador), _denominador(denominador) {
        if (_denominador == BigInt(0)) {
            std::cerr << "Erro: o denominador não pode ser zero" << std::endl;
            _denominador = BigInt(1);
        }
        simplify();
    }

    // Operadores friend de adição, subtração, multiplicação e divisão
    friend Fracao operator+(const Fracao& a, const Fracao& b) {
        BigInt num = a._numerador * b._denominador + b._numerador * a._denominador;
        BigInt den = a._denominador * b._denominador;
        return Fracao::simplifyFraction(num, den);
    }

    friend Fracao operator-(const Fracao& a, const Fracao& b) {
        BigInt num = a._numerador * b._denominador - b._numerador * a._denominador;
        BigInt den = a._denominador * b._denominador;
        return Fracao::simplifyFraction(num, den);
    }

    friend Fracao operator*(const Fracao& a, const Fracao& b) {
        BigInt num = a._numerador * b._numerador;
        BigInt den = a._denominador * b._denominador;
        return Fracao::simplifyFraction(num, den);
    }

    friend Fracao operator/(const Fracao& a, const Fracao& b) {
        BigInt num = a._numerador * b._denominador;
        BigInt den = a._denominador * b._numerador;
        return Fracao::simplifyFraction(num, den);
    }

    // Operador de saída
    friend std::ostream& operator<<(std::ostream& out, const Fracao& f) {
        out << f._numerador << "/" << f._denominador;
        return out;
    }

private:
    // Função para simplificar a fração (privada e estática)
    static Fracao simplifyFraction(BigInt num, BigInt den) {
        long long int gcdValue = BigInt::gcd(num.getValue(), den.getValue());
        num = BigInt(num.getValue() / gcdValue);
        den = BigInt(den.getValue() / gcdValue);
        if (den.getValue() < 0) {  // Manter o denominador positivo
            num = BigInt(-num.getValue());
            den = BigInt(-den.getValue());
        }
        return Fracao(num, den);
    }

    // Simplificação inicial do construtor
    void simplify() {
        long long int gcdValue = BigInt::gcd(_numerador.getValue(), _denominador.getValue());
        _numerador = BigInt(_numerador.getValue() / gcdValue);
        _denominador = BigInt(_denominador.getValue() / gcdValue);
        if (_denominador.getValue() < 0) {  // Manter o denominador positivo
            _numerador = BigInt(-_numerador.getValue());
            _denominador = BigInt(-_denominador.getValue());
        }
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
    
    f = f * Fracao(BigInt(0), BigInt(999999999999999999));
    std::cout << f << std::endl;
    
    return 0;
}
