#ifndef CLIENTE_H
#define CLIENTE_H

#include "pessoa.h"
#include "Transacao.h"
#include "CartaoCredito.h"
#include <vector>
#include <string>

class Transacao;

class Cliente : public Pessoa {
private:
    string dataNascimento;              
    double remuneracao;                 
    string tipoConta;                   
    double taxaDeRendimento;              
    double saldo;                       
    vector<Transacao*> transacoes; 
    
public:
    Cliente() = default;

    Cliente(const string& nome, const string& dataNasc,
            const string& trabalho, double remuneracao,
            const string& tipoConta, double taxaDeRendimento,
            double saldo, const string& login, const string& senha);

    // Getters
    string getDataNascimento() const;
    double getRemuneracao() const;
    string getTipoConta() const;
    double getRendimento() const;
    double getSaldo() const;
    const vector<Transacao*>& getExtrato() const;
   
    // Setters
    void setDataNascimento(const string& d);
    void setRemuneracao(double r);
    void setTipoConta(const string& t);
    void setRendimento(double t);
    void setSaldo(double s);
    void setTransacao(Transacao* t);
    
    void aplicarRendimento();
    bool temCartao() const;
    void criarCartao();
    void exibirDados() const override; 
    
};
#endif // CLIENTE_H
