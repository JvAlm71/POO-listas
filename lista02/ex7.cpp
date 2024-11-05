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
    BigInt _numerador;
    BigInt _denominador;

public:
    // Constructor with default values
    Fracao(BigInt _numerador = 0, BigInt _denominador = 1) : _numerador(_numerador), _denominador(_denominador) {}

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
    BigInt new_numerador = a._numerador * b._denominador + b._numerador * a._denominador;
    BigInt new_denominador = a._denominador * b._denominador;
    return Fracao(new_numerador, new_denominador);
}

Fracao operator-(const Fracao& a, const Fracao& b) {
    BigInt new_numerador = a._numerador * b._denominador - b._numerador * a._denominador;
    BigInt new_denominador = a._denominador * b._denominador;
    return Fracao(new_numerador, new_denominador);
}

Fracao operator*(const Fracao& a, const Fracao& b) {
    BigInt new_numerador = a._numerador * b._numerador;
    BigInt new_denominador = a._denominador * b._denominador;
    return Fracao(new_numerador, new_denominador);
}

Fracao operator/(const Fracao& a, const Fracao& b) {
    BigInt new_numerador = a._numerador * b._denominador;
    BigInt new_denominador = a._denominador * b._numerador;
    return Fracao(new_numerador, new_denominador);
}

std::ostream& operator<<(std::ostream &out, const Fracao &a) {
    out << a._numerador << '/' << a._denominador;
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
