#include <iostream>
#include <string>
#include <iomanip>

const int BASE = 1000000000; // Base 10^9
const int BASE_DIGITOS = 9;  // Dígitos por parte

class BigInt {
private:
    int* _partes;
    int _npartes;
    bool _positivo;

public:
    // Construtor a partir de string
    BigInt(std::string numero) {
        _positivo = true;
        if (numero.empty()) {
            _npartes = 1;
            _partes = new int[1];
            _partes[0] = 0;
            return;
        }

        if (numero[0] == '-') {
            _positivo = false;
            numero = numero.substr(1);
        }

        // Remover zeros à esquerda
        while (numero.size() > 1 && numero[0] == '0') {
            numero.erase(0, 1);
        }

        int len = numero.length();
        _npartes = (len + BASE_DIGITOS - 1) / BASE_DIGITOS;
        _partes = new int[_npartes];

        int indice = 0;
        for (int i = len; i > 0; i -= BASE_DIGITOS) {
            int inicio = std::max(0, i - BASE_DIGITOS);
            int tamanho = i - inicio;
            _partes[indice++] = std::stoi(numero.substr(inicio, tamanho));
        }
    }

    // Construtor a partir de int
    BigInt(int num, bool eh_num = true) {
        if (eh_num) {
            _positivo = num >= 0;
            num = std::abs(num);

            if (num == 0) {
                _npartes = 1;
                _partes = new int[1];
                _partes[0] = 0;
            } else {
                _npartes = 0;
                int temp = num;
                while (temp > 0) {
                    temp /= BASE;
                    _npartes++;
                }

                _partes = new int[_npartes];
                int indice = 0;
                while (num > 0) {
                    _partes[indice++] = num % BASE;
                    num /= BASE;
                }
            }
        } else {
            _npartes = num;
            _positivo = true;
            _partes = new int[_npartes];
            for (int i = 0; i < _npartes; i++) {
                _partes[i] = 0;
            }
        }
    }

    // Construtor padrão
    BigInt() {
        _positivo = true;
        _npartes = 1;
        _partes = new int[1];
        _partes[0] = 0;
    }

    // Construtor de movimento
    BigInt(BigInt&& b) : _partes(b._partes), _npartes(b._npartes), _positivo(b._positivo) {
        b._partes = nullptr;
        b._npartes = 0;
    }

    // Construtor de cópia
    BigInt(const BigInt& b) : _npartes(b._npartes), _positivo(b._positivo) {
        _partes = new int[_npartes];
        for (int i = 0; i < _npartes; i++) {
            _partes[i] = b._partes[i];
        }
    }

    // Destrutor
    ~BigInt() {
        delete[] _partes;
    }

    // Método isPositivo()
    bool isPositivo() const {
        return _positivo;
    }

    // Operador de atribuição
    BigInt& operator=(const BigInt& b) {
        if (this != &b) {
            delete[] _partes;
            _npartes = b._npartes;
            _positivo = b._positivo;
            _partes = new int[_npartes];
            for (int i = 0; i < _npartes; i++) {
                _partes[i] = b._partes[i];
            }
        }
        return *this;
    }

    // Método abs()
    BigInt abs() const {
        BigInt resultado(*this);
        resultado._positivo = true;
        return resultado;
    }

    // Operador ==
    friend bool operator==(const BigInt& a, const BigInt& b) {
        if (a._positivo != b._positivo) return false;
        if (a._npartes != b._npartes) return false;
        for (int i = 0; i < a._npartes; i++) {
            if (a._partes[i] != b._partes[i]) return false;
        }
        return true;
    }

    // Operador >
    friend bool operator>(const BigInt& a, const BigInt& b) {
        if (a._positivo != b._positivo)
            return a._positivo;

        if (a._npartes != b._npartes)
            return a._npartes > b._npartes ? a._positivo : !a._positivo;

        for (int i = a._npartes - 1; i >= 0; i--) {
            if (a._partes[i] != b._partes[i])
                return a._partes[i] > b._partes[i] ? a._positivo : !a._positivo;
        }
        return false;
    }

    // Operador +
    friend BigInt operator+(const BigInt& a, const BigInt& b) {
        if (a._positivo == b._positivo) {
            BigInt resultado;
            resultado._positivo = a._positivo;
            int maxPartes = std::max(a._npartes, b._npartes) + 1;
            resultado._partes = new int[maxPartes];
            for (int i = 0; i < maxPartes; i++) {
                resultado._partes[i] = 0;
            }
            resultado._npartes = maxPartes;

            int carry = 0;
            for (int i = 0; i < maxPartes - 1; i++) {
                long long soma = carry;
                if (i < a._npartes) soma += a._partes[i];
                if (i < b._npartes) soma += b._partes[i];
                if (soma >= BASE) {
                    carry = 1;
                    soma -= BASE;
                } else {
                    carry = 0;
                }
                resultado._partes[i] = soma;
            }
            if (carry == 0) {
                resultado._npartes--;
            } else {
                resultado._partes[maxPartes - 1] = carry;
            }
            return resultado;
        } else if (a._positivo && !b._positivo) {
            return a - b.abs();
        } else {
            return b - a.abs();
        }
    }

    // Operador -
    friend BigInt operator-(const BigInt& a, const BigInt& b) {
        if (a._positivo == b._positivo) {
            if (a.abs() >= b.abs()) {
                BigInt resultado;
                resultado._positivo = a._positivo;
                resultado._npartes = a._npartes;
                resultado._partes = new int[resultado._npartes];
                for (int i = 0; i < resultado._npartes; i++) {
                    resultado._partes[i] = 0;
                }

                int carry = 0;
                for (int i = 0; i < a._npartes; i++) {
                    long long sub = a._partes[i] - carry - (i < b._npartes ? b._partes[i] : 0);
                    if (sub < 0) {
                        sub += BASE;
                        carry = 1;
                    } else {
                        carry = 0;
                    }
                    resultado._partes[i] = sub;
                }

                while (resultado._npartes > 1 && resultado._partes[resultado._npartes - 1] == 0) {
                    resultado._npartes--;
                }
                return resultado;
            } else {
                BigInt resultado = b - a;
                resultado._positivo = !a._positivo;
                return resultado;
            }
        } else if (a._positivo && !b._positivo) {
            return a + b.abs();
        } else {
            BigInt resultado = a.abs() + b;
            resultado._positivo = false;
            return resultado;
        }
    }

    // Operador unário -
    BigInt operator-() const {
        BigInt resultado(*this);
        if (resultado != BigInt(0)) {
            resultado._positivo = !resultado._positivo;
        }
        return resultado;
    }

    // Operador *
    friend BigInt operator*(const BigInt& a, const BigInt& b) {
        BigInt resultado;
        resultado._positivo = (a._positivo == b._positivo);
        resultado._npartes = a._npartes + b._npartes;
        resultado._partes = new int[resultado._npartes];
        for (int i = 0; i < resultado._npartes; i++) {
            resultado._partes[i] = 0;
        }

        for (int i = 0; i < a._npartes; i++) {
            long long carry = 0;
            for (int j = 0; j < b._npartes || carry != 0; j++) {
                long long atual = resultado._partes[i + j] + carry +
                    (long long)a._partes[i] * (j < b._npartes ? b._partes[j] : 0);
                resultado._partes[i + j] = atual % BASE;
                carry = atual / BASE;
            }
        }

        while (resultado._npartes > 1 && resultado._partes[resultado._npartes - 1] == 0) {
            resultado._npartes--;
        }
        return resultado;
    }

    // Operador /(int)
    BigInt operator/(int b) const {
        BigInt resultado;
        resultado._positivo = (_positivo == (b >= 0));
        int divisor = std::abs(b);

        resultado._npartes = _npartes;
        resultado._partes = new int[resultado._npartes];
        for (int i = 0; i < resultado._npartes; i++) {
            resultado._partes[i] = 0;
        }

        long long resto = 0;
        for (int i = _npartes - 1; i >= 0; i--) {
            long long atual = _partes[i] + resto * BASE;
            resultado._partes[i] = atual / divisor;
            resto = atual % divisor;
        }

        while (resultado._npartes > 1 && resultado._partes[resultado._npartes - 1] == 0) {
            resultado._npartes--;
        }
        return resultado;
    }

    // Operador <<
    friend std::ostream& operator<<(std::ostream &out, const BigInt &a) {
        if (!a._positivo && !(a._npartes == 1 && a._partes[0] == 0)) {
            out << '-';
        }
        out << a._partes[a._npartes - 1];
        for (int i = a._npartes - 2; i >= 0; i--) {
            out << std::setw(BASE_DIGITOS) << std::setfill('0') << a._partes[i];
        }
        return out;
    }

    // Comparação adicional necessária
    friend bool operator!=(const BigInt& a, const BigInt& b) {
        return !(a == b);
    }

    friend bool operator<(const BigInt& a, const BigInt& b) {
        return !(a > b || a == b);
    }

    friend bool operator>=(const BigInt& a, const BigInt& b) {
        return (a > b || a == b);
    }

    friend bool operator<=(const BigInt& a, const BigInt& b) {
        return !(a > b);
    }
};

class Fracao {
private:
    BigInt numerador;
    BigInt denominador;

public:
    // Construtor padrão
    Fracao(BigInt num = 0, BigInt den = 1) : numerador(num), denominador(den) {
        // Não simplificar
    }

    // Operador +
    friend Fracao operator+(const Fracao& a, const Fracao& b) {
        BigInt num = a.numerador * b.denominador + b.numerador * a.denominador;
        BigInt den = a.denominador * b.denominador;
        return Fracao(num, den);
    }

    // Operador -
    friend Fracao operator-(const Fracao& a, const Fracao& b) {
        BigInt num = a.numerador * b.denominador - b.numerador * a.denominador;
        BigInt den = a.denominador * b.denominador;
        return Fracao(num, den);
    }

    // Operador *
    friend Fracao operator*(const Fracao& a, const Fracao& b) {
        BigInt num = a.numerador * b.numerador;
        BigInt den = a.denominador * b.denominador;
        return Fracao(num, den);
    }

    // Operador /
    friend Fracao operator/(const Fracao& a, const Fracao& b) {
        BigInt num = a.numerador * b.denominador;
        BigInt den = a.denominador * b.numerador;
        return Fracao(num, den);
    }

    // Operador <<
    friend std::ostream& operator<<(std::ostream &out, const Fracao &f) {
        out << f.numerador << "/" << f.denominador;
        return out;
    }
};

// Função principal com o exemplo fornecido
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
    f = f * Fracao(BigInt(0), BigInt("999999999999999999"));
    std::cout << f << std::endl;

    return 0;
}
