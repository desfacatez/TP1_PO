#include "cartaoCredito.h"
#include <iostream>
#include <iomanip>
using namespace std;

CartaoCredito::CartaoCredito(double limite)
    : limite(limite), limiteDisponivel(limite), bloqueado(false), faturaAtual(0.0) {}

double CartaoCredito::getLimite()                        const { return limite; }
double CartaoCredito::getLimiteDisponivel()              const { return limiteDisponivel; }
bool   CartaoCredito::isBloqueado()                      const { return bloqueado; }
double CartaoCredito::getFaturaAtual()                   const { return faturaAtual; }
const vector<ParcelaFatura>& CartaoCredito::getCompras() const { return compras; }    

void CartaoCredito::setLimite(double l) {
    double valorUsado = limite - limiteDisponivel;
    limite = l;
    limiteDisponivel = (l > valorUsado) ? (l - valorUsado) : 0.0;
}

void CartaoCredito::bloquear()    { bloqueado = true; }

void CartaoCredito::desbloquear() { bloqueado = false; }


bool CartaoCredito::realizarCompraParcelada(const string& descricao, double valorTotal, int numParcelas) {
    if (bloqueado) {
        cout << "[ERRO] Cartao bloqueado. Desbloqueie antes de realizar compras.\n";
        return false;
    }
    if (numParcelas <= 0) numParcelas = 1;

    if (valorTotal > limiteDisponivel) {
        cout << "[ERRO] Limite insuficiente. Disponivel: R$ "
             << fixed << setprecision(2) << limiteDisponivel << "\n";
        return false;
    }

    ParcelaFatura compra;
    compra.descricao     = descricao;
    compra.valorTotal    = valorTotal;
    compra.totalParcelas = numParcelas;
    compra.parcelaAtual  = 1;
    compra.valorParcela  = valorTotal / numParcelas;
    compras.push_back(compra);
    limiteDisponivel -= valorTotal;
    faturaAtual      += compra.valorParcela;

    return true;
}

void CartaoCredito::exibirFatura() const {
    cout << "\n====== FATURA DO CARTAO DE CREDITO ======\n";
    cout << "Limite total     : R$ " << fixed << setprecision(2) << limite << "\n";
    cout << "Limite disponivel: R$ " << limiteDisponivel << "\n";
    cout << "Status           : " << (bloqueado ? "BLOQUEADO" : "ATIVO") << "\n";
    cout << "-----------------------------------------\n";

    if (compras.empty()) {
        cout << "  Nenhuma compra registrada.\n";
    } else {
        for (const auto& c : compras) {
            cout << "  " << c.descricao
                 << " | Total: R$ " << fixed << setprecision(2) << c.valorTotal
                 << " | Parcela " << c.parcelaAtual << "/" << c.totalParcelas
                 << " (R$ " << c.valorParcela << ")\n";
        }
    }

    cout << "-----------------------------------------\n";
    cout << "TOTAL FATURA ATUAL: R$ " << fixed << setprecision(2) << faturaAtual << "\n";
    cout << "=========================================\n";
}

double CartaoCredito::pagarFatura() {
    double valorDebitar = faturaAtual;

    vector<ParcelaFatura> comprasRestantes;
    for (auto& c : compras) {
        c.parcelaAtual++;
        if (c.parcelaAtual <= c.totalParcelas) {
            comprasRestantes.push_back(c);
        }
    }
    compras = comprasRestantes;

    faturaAtual = 0.0;
    for (const auto& c : compras) {
        faturaAtual += c.valorParcela;
    }

    limiteDisponivel += valorDebitar;
    if (limiteDisponivel > limite) limiteDisponivel = limite;

    return valorDebitar;
}
