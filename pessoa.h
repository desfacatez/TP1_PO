#ifndef PESSOA_H
#define PESSOA_H

#include <string>
using namespace std;

class Pessoa{

public:
    string nome;
    string trabalho;

protected:
    string login;
    string senha;

public:
    //Construtor 
    Pessoa() = default;

    Pessoa(const string& nome, const string& trabalho,
           const string& login, const string& senha);

    //Destrutor
    virtual ~Pessoa() = default;

    string getNome()     const;
    string getTrabalho() const;
    string getLogin()    const;
    string getSenha()    const;

    void setNome(const string& nome);
    void setTrabalho(const string& trabalho);
    void setLogin(const string& login);
    void setSenha(const string& senha);

    virtual void exibirDados() const = 0;
};

#endif // PESSOA_H