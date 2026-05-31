#ifndef PESSOA_H
#define PESSOA_H

#include <string>
#include <iostream>
using namespace std;

class Pessoa {

protected:
    string nome;
    string trabalho;
    string login;
    string senha;

public:

    // Constantes de divisorias para uso global
    static const string divisoria;
    static const string divisoria2;

    // Construtor 
    Pessoa() = default;
    // Construtor com parametros
    Pessoa(const string& nome, const string& trabalho,
           const string& login, const string& senha);
    // Destrutor
    virtual ~Pessoa() = default;

    // Getters
    string getNome() const { return nome; }
    string getTrabalho() const { return trabalho; }
    string getLogin() const { return login; }
    string getSenha() const { return senha; }

    // Setters
    void setNome(const string& nome);
    void setTrabalho(const string& trabalho);
    void setLogin(const string& login);
    void setSenha(const string& senha);

    // Exibir Dados Global
    virtual void exibirDados() const;

};

#endif // PESSOA_H