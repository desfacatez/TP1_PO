#ifndef CLIENTE_H
#define CLIENTE_H
#include "Pessoa.h"
#include "Transacao.h"
#include <vector>

class Cliente : public Pessoa {
private:
    string dataNascimento;              
    double remuneracao;                 
    string tipoConta;                   
    double taxaDeRendimento;              
    double saldo;                       
    vector<Transacao> transacoes; 
    
public:
    Cliente();

    Cliente(const string& nome, const string& dataNasc,
            const string& trabalho, double remuneracao,
            const string& tipoConta, double taxaDeRendimento,
            double saldo, const string& login, const string& senha);

    string getDataNascimento() const;
    double getRemuneracao() const;
    string getTipoConta() const;
    double getRendimento() const;
    double getSaldo() const;
    const vector<Transacao>& getExtrato() const;
   

    void setDataNascimento(const string& d);
    void setRemuneracao(double r);
    void setTipoConta(const string& t);
    void setRendimento(double t);
    void setSaldo(double s);
    void SetTransacao(const Transacao& t);
    
    void aplicarRendimento();
    void criarCartao();
    void exibirDados() const override; 
    
};
#endif // CLIENTE_H
