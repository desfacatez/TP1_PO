#ifndef CARTAOCREDITO_H
#define CARTAOCREDITO_H

#include <string>
#include <vector>
using namespace std;


struct ParcelaFatura {
    string descricao;
    double valorTotal;
    int    totalParcelas;
    int    parcelaAtual;
    double valorParcela;
};

class CartaoCredito {
private:
    double limite;
    double limiteDisponivel;
    bool   bloqueado;
    double faturaAtual;
    vector<ParcelaFatura> compras;

public:

    CartaoCredito(double limite = 0.0);

    double getLimite()                        const;
    double getLimiteDisponivel()              const;
    bool   isBloqueado()                      const;
    double getFaturaAtual()                   const;
    const vector<ParcelaFatura>& getCompras() const;

    void setLimite(double l);

    void bloquear()    { bloqueado = true; }

    void desbloquear() { bloqueado = false; }

    bool realizarCompraParcelada(const string& descricao,
                                 double valorTotal, int numParcelas);

    void exibirFatura() const;

    double pagarFatura();
};

#endif // CARTAOCREDITO_H
