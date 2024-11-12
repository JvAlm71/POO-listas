#include <iostream>
#include <string> 

class C {
private:
    double _real;
    double _imag;

public:
    C(double r = 0.0, double i = 0.0) : _real(r), _imag(i) {}

    double getReal() const { return _real; }
    double getImag() const { return _imag; }

    void setReal(double r) { _real = r; }
    void setImag(double i) { _imag = i; }

    virtual void print(std::ostream &out) const {
        out << _real << " + " << _imag << "i";
    }

    friend std::ostream &operator<<(std::ostream &out, const C &c) {
        c.print(out);
        return out;
    }
};

class R : public C {
public:
    R(double r = 0.0) : C(r, 0.0) {}

    void print(std::ostream &out) const override {
        out << getReal();
    }
};

class Q : public R {
private:
    int _numerador;
    int _denominador;

    int gcd(int a, int b) {
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }

    void reduz() {
        int divisor = gcd(_numerador, _denominador);
        _numerador /= divisor;
        _denominador /= divisor;
        if (_denominador < 0) {
            _numerador = -_numerador;
            _denominador = -_denominador;
        }
    }

public:
    Q(int num = 0, int den = 1) : R(static_cast<double>(num) / den), _numerador(num), _denominador(den) {
        if (den == 0) {
            std::cerr << "Erro: Denominador não pode ser zero" << std::endl;
            _numerador = 0;
            _denominador = 1;
        } else {
            reduz();
        }
    }

    int getNumerador() const { return _numerador; }
    int getDenominador() const { return _denominador; }

    void print(std::ostream &out) const override {
        out << _numerador << "/" << _denominador;
    }
};

class Z : public Q {
public:
    Z(int num = 0) : Q(num, 1) {}

    void print(std::ostream &out) const override {
        out << "+" << getNumerador();
    }
};

class N : public Z {
public:
    N(int num = 0) : Z(num) {
        if (num < 0) {
            std::cerr << "Erro: Número natural não pode ser negativo" << std::endl;
            setReal(0);
        }
    }
};

int main() {
    const int numObjetos = 5;
    C* objetos[numObjetos];
    objetos[0] = new C(3.5, 2.1);
    objetos[1] = new R(5.0);
    objetos[2] = new Q(1, 3);
    objetos[3] = new Z(10);
    objetos[4] = new N(10);

    for (int i = 0; i < numObjetos; ++i)
        std::cout << *objetos[i] << std::endl;

    for (int i = 0; i < numObjetos; ++i)
        delete objetos[i];

    return 0;
}


//ANALISAR FORMATAÇÃO...