#include <stdio.h>
#include <iostream>

class BigInt {
private:
    long long int value;
public:
    // Constructor from long long int
    BigInt(long long int val = 0) : value(val) {}

    // Overloaded operators
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

    // Equality operator
    bool operator==(const BigInt& other) const {
        return value == other.value;
    }

    // Getter for value
    long long int getValue() const {
        return value;
    }

    // Output operator
    friend std::ostream& operator<<(std::ostream& os, const BigInt& bi) {
        os << bi.value;
        return os;
    }
};

class Fracao {
private:
    BigInt numerador;
    BigInt denominador;

public:
    // Constructor with default values
    Fracao(BigInt numerador = 0, BigInt denominador = 1) : numerador(numerador), denominador(denominador) {}

    // Friend functions for arithmetic operations
    friend Fracao operator+(const Fracao& a, const Fracao& b);
    friend Fracao operator-(const Fracao& a, const Fracao& b);
    friend Fracao operator*(const Fracao& a, const Fracao& b);
    friend Fracao operator/(const Fracao& a, const Fracao& b);

    // Friend function for output
    friend std::ostream& operator<<(std::ostream &out, const Fracao &a);
};

// Implementations of friend functions
Fracao operator+(const Fracao& a, const Fracao& b) {
    BigInt new_numerador = a.numerador * b.denominador + b.numerador * a.denominador;
    BigInt new_denominador = a.denominador * b.denominador;
    return Fracao(new_numerador, new_denominador);
}

Fracao operator-(const Fracao& a, const Fracao& b) {
    BigInt new_numerador = a.numerador * b.denominador - b.numerador * a.denominador;
    BigInt new_denominador = a.denominador * b.denominador;
    return Fracao(new_numerador, new_denominador);
}

Fracao operator*(const Fracao& a, const Fracao& b) {
    BigInt new_numerador = a.numerador * b.numerador;
    BigInt new_denominador = a.denominador * b.denominador;
    return Fracao(new_numerador, new_denominador);
}

Fracao operator/(const Fracao& a, const Fracao& b) {
    BigInt new_numerador = a.numerador * b.denominador;
    BigInt new_denominador = a.denominador * b.numerador;
    return Fracao(new_numerador, new_denominador);
}

std::ostream& operator<<(std::ostream &out, const Fracao &a) {
    out << a.numerador << '/' << a.denominador;
    return out;
}

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
