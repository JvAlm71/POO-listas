#include <iostream>
#include <iomanip>
#include <string>
#include <cstdio>

class BigInt {
private:
    int* partes;    // Vetor com cada uma das partes do número
    int _npartes;   // Número de elementos no vetor partes
    bool positivo;  // Sinal do número

    // Função auxiliar para inicializar as partes
    void inicializarPartes(const std::string& numero) {
        int tamanho = numero.size();
        _npartes = (tamanho + 8) / 9; // Cada parte terá no máximo 9 dígitos
        partes = new int[_npartes]();

        int indiceParte = _npartes - 1;
        for (int i = tamanho; i > 0; i -= 9) {
            int inicio = (i >= 9) ? i - 9 : 0;
            int tamanhoParte = (i >= 9) ? 9 : i;
            partes[indiceParte--] = std::stoi(numero.substr(inicio, tamanhoParte));
        }
    }

public:
    // Construtor a partir de string
    BigInt(const std::string& numero) {
        if (numero.empty()) throw std::invalid_argument("O número não pode ser vazio.");
        positivo = (numero[0] != '-');
        std::string numStr = (numero[0] == '-' || numero[0] == '+') ? numero.substr(1) : numero;
        inicializarPartes(numStr);
    }

    // Construtor a partir de int
    BigInt(int num = 0, bool eh_num = true) {
        positivo = (num >= 0);
        num = std::abs(num);
        _npartes = 1;
        partes = new int[1]{num};
    }

    // Construtor padrão
    BigInt() : _npartes(1), positivo(true) {
        partes = new int[1]{0};
    }

    // Construtor de movimento
    BigInt(BigInt&& b) noexcept : partes(b.partes), _npartes(b._npartes), positivo(b.positivo) {
        b.partes = nullptr;
        b._npartes = 0;
    }

    // Destrutor
    ~BigInt() {
        delete[] partes;
    }

    // Retorna true se o número for positivo ou zero
    bool positivo() const {
        return positivo;
    }

    // Operador de atribuição
    BigInt& operator=(const BigInt& b) {
        if (this != &b) {
            delete[] partes;
            _npartes = b._npartes;
            positivo = b.positivo;
            partes = new int[_npartes];
            for (int i = 0; i < _npartes; ++i) {
                partes[i] = b.partes[i];
            }
        }
        return *this;
    }

    // Retorna o módulo (valor absoluto)
    BigInt abs() const {
        BigInt result = *this;
        result.positivo = true;
        return result;
    }

    // Operador de igualdade
    friend bool operator==(const BigInt& a, const BigInt& b) {
        if (a.positivo != b.positivo || a._npartes != b._npartes) return false;
        for (int i = 0; i < a._npartes; ++i) {
            if (a.partes[i] != b.partes[i]) return false;
        }
        return true;
    }

    // Operador de maior que
    friend bool operator>(const BigInt& a, const BigInt& b) {
        if (a.positivo != b.positivo) return a.positivo;
        if (a._npartes != b._npartes) return (a._npartes > b._npartes) == a.positivo;
        for (int i = 0; i < a._npartes; ++i) {
            if (a.partes[i] != b.partes[i]) {
                return (a.partes[i] > b.partes[i]) == a.positivo;
            }
        }
        return false;
    }

    // Operador de soma
    friend BigInt operator+(const BigInt& a, const BigInt& b) {
        // Implementação simplificada: Lógica completa precisa lidar com o transporte (carry)
        return BigInt();
    }

    // Operador de subtração
    friend BigInt operator-(const BigInt& a, const BigInt& b) {
        // Implementação simplificada
        return BigInt();
    }

    // Operador de negação (sinal oposto)
    BigInt operator-() const {
        BigInt result = *this;
        result.positivo = !positivo;
        return result;
    }

    // Operador de multiplicação
    friend BigInt operator*(const BigInt& a, const BigInt& b) {
        // Implementação simplificada
        return BigInt();
    }

    // Operador de divisão
    friend BigInt operator/(const BigInt& a, const BigInt& b) {
        // Implementação simplificada
        return BigInt();
    }

    // Impressão
    friend std::ostream& operator<<(std::ostream& out, const BigInt& num) {
        if (!num.positivo) out << "-";
        out << num.partes[0]; // Imprime a primeira parte sem zeros à esquerda
        for (int i = 1; i < num._npartes; ++i) {
            out << std::setw(9) << std::setfill('0') << num.partes[i];
        }
        return out;
    }
};
