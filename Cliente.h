#ifndef     CLIENTE_H
#define     CLIENTE_H
#include "Pessoa.h"
#include "Transacao.h"
#include <vector>

class Cliente : public Pessoa {
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

    string getDataNascimento()            const { return dataNascimento; }
    double getRemuneracao()               const { return remuneracao; }
    string getTipoConta()                 const { return tipoConta; }
    double getRendimento()                const { return taxaDeRendimento; }
    double getSaldo()                     const { return saldo; }
    const vector<Transacao>& getExtrato() const { return transacoes; }
   

    void setDataNascimento(const string& d) { dataNascimento = d; }
    void setRemuneracao(double r)           { remuneracao = r; }
    void setTipoConta(const string& t)      { tipoConta = t; }
    void setRendimento(double t)            { taxaDeRendimento = t; }
    void setSaldo(double s)                 { saldo = s; }

    void SetTransacao(const Transacao& t) { transacoes.push_back(t); }

    void aplicarRendimento();

    void exibirDados() const override; 
    
};
#endif // CLIENTE_H