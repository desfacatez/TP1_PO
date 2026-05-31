#include "cliente.h"
#include "transacao.h"
#include "cartaoCredito.h"
#include <iostream>
#include <iomanip>

using namespace std;

Cliente::Cliente(const string& nome, const string& dataNasc,
                 const string& trabalho, double remuneracao,
                 const string& tipoConta, double taxaDeRendimento,
                 double saldo, const string& login, const string& senha)
                 :Pessoa(nome, trabalho, login, senha), dataNascimento(dataNasc),
                 remuneracao(remuneracao), tipoConta(tipoConta),
                 taxaRendimento(taxaRendimento), saldo(saldo) {
                    // Padronização da string tipoConta
                    if(tipoConta == "poupanca" || tipoConta == "poupança" || tipoConta == "Poupanca" || tipoConta == "Poupança"){
                        this->tipoConta = "Poupança";
                    } else {
                        this->tipoConta = "Corrente";
                    }
                 }

string Cliente::getDataNascimento() const { return dataNascimento; }
double Cliente::getRemuneracao() const { return remuneracao; }
string Cliente::getTipoConta() const { return tipoConta; }
double Cliente::getRendimento() const { return taxaRendimento; }
double Cliente::getSaldo() const { return saldo; }
const vector<Transacao*>& Cliente::getExtrato() const { return transacoes; }
CartaoCredito* Cliente::getCartao()      const { return cartao.get(); }

void Cliente::setDataNascimento(const string& data) { dataNascimento = data; }
void Cliente::setRemuneracao(double remuneracao) { this->remuneracao = remuneracao; }
void Cliente::setTipoConta(const string& tipoConta) { this->tipoConta = tipoConta; }
void Cliente::setRendimento(double rendimento) { taxaRendimento = rendimento; }
void Cliente::setSaldo(double saldo) { this->saldo = saldo; }
void Cliente::SetTransacao(Transacao* t) { transacoes.push_back(t); }

void Cliente::exibirDados() const {

    // Chama o cabeçalho global em Pessoa (para Cliente)
    Pessoa::exibirDados();

    // Exibe dados adicionais
    cout << "Data de Nascimento:     " << dataNascimento << "\n";
    cout << "Remuneracão:     R$ " << fixed << setprecision(2) << remuneracao << "\n";
    cout << "Tipo de Conta:     " << tipoConta << "\n";

    if (tipoConta == "poupanca" || tipoConta == "poupança") {
        cout << "Taxa Rendimento:     " << taxaRendimento << "% ao mês\n";
    }

    cout << "Saldo Atual:     R$" << fixed << setprecision(2) << saldo << "\n";
    cout << "Transações:     " << transacoes.size() << " efetuada(s)\n";
    /*cout << "Cartao Credito  : " << (cartao ? "Sim" : "Nao") << "\n";


    if (cartao) {
        cout << "  Limite        : R$ " << fixed << setprecision(2) << cartao->getLimite() << "\n";
        cout << "  Disponivel    : R$ " << cartao->getLimiteDisponivel() << "\n";
        cout << "  Status        : " << (cartao->isBloqueado() ? "BLOQUEADO" : "ATIVO") << "\n";
        cout << "  Fatura atual  : R$ " << cartao->getFaturaAtual() << "\n";
    }

    cout << "Transacoes      : " << transacoes.size() << " registrada(s)\n";
    cout << "==================================\n";

    cout << Pessoa::divisoria << "\n\n";
    
}

void Cliente::aplicarRendimento() {
    if (tipoConta == "Poupança" && taxaRendimento > 0.0){
        double rendimento = saldo * (taxaRendimento / 100.0);
        saldo += rendimento;

        cout << "Rendimento de R$" << fixed << setprecision(2)
             << rendimento << " aplicado ao saldo de " << getNome();
        
        cout << "(Novo saldo de: R$" << saldo << ").\n";

    } else {
        cout << "Erro. Conta corrente não possui rendimento.\n";
    }
}
bool Cliente::temCartao() const { return cartao != nullptr; }

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
