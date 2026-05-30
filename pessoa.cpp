#include "pessoa.h"
#include <string>
#include <iostream>
using namespace std;

Pessoa::Pessoa(const string& nome, const string& trabalho,
               const string& login, const string& senha) 
               : nome(nome), trabalho(trabalho), login(login), senha(senha) {}

string Pessoa:: getNome()     const { return nome; }
string Pessoa:: getTrabalho() const { return trabalho; }
string Pessoa:: getLogin()    const { return login; }
string Pessoa:: getSenha()    const { return senha; }


void Pessoa:: setNome(const string& nome)         { this->nome = nome; }
void Pessoa:: setTrabalho(const string& trabalho) { this->trabalho = trabalho; }
void Pessoa:: setLogin(const string& login)       { this->login = login; }
void Pessoa:: setSenha(const string& senha)       { this->senha = senha; }

void Pessoa::exibirDados() const {
    cout << "Nome: " << nome << endl;
    cout << "Trabalho: " << trabalho << endl;
    cout << "Login: " << login << endl;
    cout << "Senha: " << senha << endl;
}