#include "Cliente.h"
#include "Transacao.h"
#include <iostream>
#include <iomanip>
using namespace std;


Cliente::Cliente(const string& nome, const string& dataNasc,
                 const string& trabalho, double remuneracao,
                 const string& tipoConta, double taxaDeRendimento,
                 double saldo, const string& login, const string& senha)
                 :Pessoa(nome, trabalho, login, senha), dataNascimento(dataNasc),
                  remuneracao(remuneracao), tipoConta(tipoConta), taxaDeRendimento(taxaDeRendimento), saldo(saldo) {}

string Cliente::getDataNascimento()            const { return dataNascimento; }
double Cliente::getRemuneracao()               const { return remuneracao; }
string Cliente::getTipoConta()                 const { return tipoConta; }
double Cliente::getRendimento()                const { return taxaDeRendimento; }
double Cliente::getSaldo()                     const { return saldo; }
const vector<Transacao>& Cliente::getExtrato() const { return transacoes; }

void Cliente::setDataNascimento(const string& d) { dataNascimento = d; }
void Cliente::setRemuneracao(double r)           { remuneracao = r; }
void Cliente::setTipoConta(const string& t)      { tipoConta = t; }
void Cliente::setRendimento(double t)            { taxaDeRendimento = t; }
void Cliente::setSaldo(double s)                 { saldo = s; }
void Cliente::SetTransacao(const Transacao& t) { transacoes.push_back(t); }

void Cliente::exibirDados() const {
    cout << "\n======== DADOS DO CLIENTE ========\n";
    cout << "Nome            : " << nome << "\n";
    cout << "Data Nascimento : " << dataNascimento << "\n";
    cout << "Trabalho        : " << trabalho << "\n";
    cout << "Remuneracao     : R$ " << fixed << setprecision(2) << remuneracao << "\n";
    cout << "Login           : " << login << "\n";
    cout << "Tipo de Conta   : " << tipoConta << "\n";

    if (tipoConta == "poupanca") {
        cout << "Taxa Rendimento : " << taxaDeRendimento << "% ao mes\n";
    }

    cout << "Saldo Atual     : R$ " << fixed << setprecision(2) << saldo << "\n";
    /*cout << "Cartao Credito  : " << (cartao ? "Sim" : "Nao") << "\n";


    if (cartao) {
        cout << "  Limite        : R$ " << fixed << setprecision(2) << cartao->getLimite() << "\n";
        cout << "  Disponivel    : R$ " << cartao->getLimiteDisponivel() << "\n";
        cout << "  Status        : " << (cartao->isBloqueado() ? "BLOQUEADO" : "ATIVO") << "\n";
        cout << "  Fatura atual  : R$ " << cartao->getFaturaAtual() << "\n";
    }

    cout << "Transacoes      : " << transacoes.size() << " registrada(s)\n";
    cout << "==================================\n";
    */
}

void Cliente::aplicarRendimento() {
    if (tipoConta == "poupanca" && taxaDeRendimento > 0.0) {
        double rendimento = saldo * (taxaDeRendimento / 100.0);
        saldo += rendimento;
        cout << "[INFO] Rendimento de R$ " << fixed << setprecision(2)
             << rendimento << " aplicado ao saldo de " << nome
             << " (novo saldo: R$ " << saldo << ").\n";
    } else {
        cout << "[AVISO] Conta corrente nao possui rendimento.\n";
    }
}
/*
void Cliente::criarCartao() {
    if (cartao) {
        cout << "[AVISO] O cliente ja possui cartao de credito.\n";
        return;
    }
    double limiteCalculado = remuneracao * 3.0;
    cartao = make_unique<CartaoCredito>(limiteCalculado);
    cout << "[OK] Cartao criado com limite de R$ "
         << fixed << setprecision(2) << limiteCalculado << ".\n";
}
*/         
