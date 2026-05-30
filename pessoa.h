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

    //Construtor 
    Pessoa() = default;
    // Construtor com parâmetros
    Pessoa(const string& nome, const string& trabalho, const string& login, const string& senha);
    // Destrutor
    virtual ~Pessoa() = default;

    // Getters
    string definirNome() const { return nome; }
    string definirTrabalho() const { return trabalho; }
    string definirLogin() const { return login; }
    string definirSenha() const { return senha; }

    // Setters
    void definirNome(const string& nome);
    void definirTrabalho(const string& trabalho);
    void definirLogin(const string& login);
    void definirSenha(const string& senha);

    // Exibir Dados Global
    virtual void exibirDados() const;
};

#endif // PESSOA_H