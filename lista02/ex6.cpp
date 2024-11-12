#include <iostream>
#include <string>
#include <iomanip>

const int BASE = 1000000000; // Base 10^9
const int BASE_DIGITOS = 9;  // Dígitos por parte

class BigInt {
private:
    int* partes;
    int npartes;
    bool positivo;

public:
    // Construtor a partir de string
    BigInt(std::string numero) {
        positivo = true;
        if (numero.empty()) {
            npartes = 1;
            partes = new int[1];
            partes[0] = 0;
            return;
        }

        if (numero[0] == '-') {
            positivo = false;
            numero = numero.substr(1);
        }

        // Remover zeros à esquerda
        while (numero.size() > 1 && numero[0] == '0') {
            numero.erase(0, 1);
        }

        int len = numero.length();
        npartes = (len + BASE_DIGITOS - 1) / BASE_DIGITOS;
        partes = new int[npartes];

        int indice = 0;
        for (int i = len; i > 0; i -= BASE_DIGITOS) {
            int inicio = std::max(0, i - BASE_DIGITOS);
            int tamanho = i - inicio;
            partes[indice++] = std::stoi(numero.substr(inicio, tamanho));
        }
    }

    // Construtor a partir de int
    BigInt(int num, bool eh_num = true) {
        if (eh_num) {
            positivo = num >= 0;
            num = std::abs(num);

            if (num == 0) {
                npartes = 1;
                partes = new int[1];
                partes[0] = 0;
            } else {
                npartes = 0;
                int temp = num;
                while (temp > 0) {
                    temp /= BASE;
                    npartes++;
                }

                partes = new int[npartes];
                int indice = 0;
                while (num > 0) {
                    partes[indice++] = num % BASE;
                    num /= BASE;
                }
            }
        } else {
            npartes = num;
            positivo = true;
            partes = new int[npartes];
            for (int i = 0; i < npartes; i++) {
                partes[i] = 0;
            }
        }
    }

    // Construtor padrão
    BigInt() {
        positivo = true;
        npartes = 1;
        partes = new int[1];
        partes[0] = 0;
    }

    // Construtor de movimento
    BigInt(BigInt&& b) : partes(b.partes), npartes(b.npartes), positivo(b.positivo) {
        b.partes = nullptr;
        b.npartes = 0;
    }

    // Construtor de cópia
    BigInt(const BigInt& b) : npartes(b.npartes), positivo(b.positivo) {
        partes = new int[npartes];
        for (int i = 0; i < npartes; i++) {
            partes[i] = b.partes[i];
        }
    }

    // Destrutor
    ~BigInt() {
        delete[] partes;
    }

    // Método isPositivo()
    bool isPositivo() const {
        return positivo;
    }

    // Operador de atribuição
    BigInt& operator=(const BigInt& b) {
        if (this != &b) {
            delete[] partes;
            npartes = b.npartes;
            positivo = b.positivo;
            partes = new int[npartes];
            for (int i = 0; i < npartes; i++) {
                partes[i] = b.partes[i];
            }
        }
        return *this;
    }

    // Método abs()
    BigInt abs() const {
        BigInt resultado(*this);
        resultado.positivo = true;
        return resultado;
    }

    // Operador ==
    friend bool operator==(const BigInt& a, const BigInt& b) {
        if (a.positivo != b.positivo) return false;
        if (a.npartes != b.npartes) return false;
        for (int i = 0; i < a.npartes; i++) {
            if (a.partes[i] != b.partes[i]) return false;
        }
        return true;
    }

    // Operador >
    friend bool operator>(const BigInt& a, const BigInt& b) {
        if (a.positivo != b.positivo)
            return a.positivo;

        if (a.npartes != b.npartes)
            return a.npartes > b.npartes ? a.positivo : !a.positivo;

        for (int i = a.npartes - 1; i >= 0; i--) {
            if (a.partes[i] != b.partes[i])
                return a.partes[i] > b.partes[i] ? a.positivo : !a.positivo;
        }
        return false;
    }

    // Operador +
    friend BigInt operator+(const BigInt& a, const BigInt& b) {
        if (a.positivo == b.positivo) {
            BigInt resultado;
            resultado.positivo = a.positivo;
            int maxPartes = std::max(a.npartes, b.npartes) + 1;
            resultado.partes = new int[maxPartes];
            for (int i = 0; i < maxPartes; i++) {
                resultado.partes[i] = 0;
            }
            resultado.npartes = maxPartes;

            int carry = 0;
            for (int i = 0; i < maxPartes - 1; i++) {
                long long soma = carry;
                if (i < a.npartes) soma += a.partes[i];
                if (i < b.npartes) soma += b.partes[i];
                if (soma >= BASE) {
                    carry = 1;
                    soma -= BASE;
                } else {
                    carry = 0;
                }
                resultado.partes[i] = soma;
            }
            if (carry == 0) {
                resultado.npartes--;
            } else {
                resultado.partes[maxPartes - 1] = carry;
            }
            return resultado;
        } else if (a.positivo && !b.positivo) {
            return a - b.abs();
        } else {
            return b - a.abs();
        }
    }

    // Operador -
    friend BigInt operator-(const BigInt& a, const BigInt& b) {
        if (a.positivo == b.positivo) {
            if (a.abs() >= b.abs()) {
                BigInt resultado;
                resultado.positivo = a.positivo;
                resultado.npartes = a.npartes;
                resultado.partes = new int[resultado.npartes];
                for (int i = 0; i < resultado.npartes; i++) {
                    resultado.partes[i] = 0;
                }

                int carry = 0;
                for (int i = 0; i < a.npartes; i++) {
                    long long sub = a.partes[i] - carry - (i < b.npartes ? b.partes[i] : 0);
                    if (sub < 0) {
                        sub += BASE;
                        carry = 1;
                    } else {
                        carry = 0;
                    }
                    resultado.partes[i] = sub;
                }

                while (resultado.npartes > 1 && resultado.partes[resultado.npartes - 1] == 0) {
                    resultado.npartes--;
                }
                return resultado;
            } else {
                BigInt resultado = b - a;
                resultado.positivo = !a.positivo;
                return resultado;
            }
        } else if (a.positivo && !b.positivo) {
            return a + b.abs();
        } else {
            BigInt resultado = a.abs() + b;
            resultado.positivo = false;
            return resultado;
        }
    }

    // Operador unário -
    BigInt operator-() const {
        BigInt resultado(*this);
        if (resultado != BigInt(0)) {
            resultado.positivo = !resultado.positivo;
        }
        return resultado;
    }

    // Operador *
    friend BigInt operator*(const BigInt& a, const BigInt& b) {
        BigInt resultado;
        resultado.positivo = (a.positivo == b.positivo);
        resultado.npartes = a.npartes + b.npartes;
        resultado.partes = new int[resultado.npartes];
        for (int i = 0; i < resultado.npartes; i++) {
            resultado.partes[i] = 0;
        }

        for (int i = 0; i < a.npartes; i++) {
            long long carry = 0;
            for (int j = 0; j < b.npartes || carry != 0; j++) {
                long long atual = resultado.partes[i + j] + carry +
                    (long long)a.partes[i] * (j < b.npartes ? b.partes[j] : 0);
                resultado.partes[i + j] = atual % BASE;
                carry = atual / BASE;
            }
        }

        while (resultado.npartes > 1 && resultado.partes[resultado.npartes - 1] == 0) {
            resultado.npartes--;
        }
        return resultado;
    }

    // Operador /(int)
    BigInt operator/(int b) const {
        BigInt resultado;
        resultado.positivo = (positivo == (b >= 0));
        int divisor = std::abs(b);

        resultado.npartes = npartes;
        resultado.partes = new int[resultado.npartes];
        for (int i = 0; i < resultado.npartes; i++) {
            resultado.partes[i] = 0;
        }

        long long resto = 0;
        for (int i = npartes - 1; i >= 0; i--) {
            long long atual = partes[i] + resto * BASE;
            resultado.partes[i] = atual / divisor;
            resto = atual % divisor;
        }

        while (resultado.npartes > 1 && resultado.partes[resultado.npartes - 1] == 0) {
            resultado.npartes--;
        }
        return resultado;
    }

    // Operador <<
    friend std::ostream& operator<<(std::ostream &out, const BigInt &a) {
        if (!a.positivo && !(a.npartes == 1 && a.partes[0] == 0)) {
            out << '-';
        }
        out << a.partes[a.npartes - 1];
        for (int i = a.npartes - 2; i >= 0; i--) {
            out << std::setw(BASE_DIGITOS) << std::setfill('0') << a.partes[i];
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
