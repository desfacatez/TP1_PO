#include "pessoa.h"
#include <cstring>
#include <iostream>
#include <iomanip>

using namespace std;

Pessoa::Pessoa(const string& nome, const string& trabalho, const string& login, const string& senha) : nome(nome), trabalho(trabalho), login(login), senha(senha) {}

void Pessoa::definirNome(const string& nome){
    this->nome = nome;
}

void Pessoa::definirTrabalho(const string& trabalho){
    this->trabalho = trabalho;
}

void Pessoa::definirLogin(const string& login){
    this->login = login;
}

void Pessoa::definirSenha(const string& senha){
    this->senha = senha;
}

void Pessoa::exibirDados() const {
    string divisoria = "==================================================";
    string divisoria2 = "----------------------\n\n";
    string mensagem = "Listagem do(a) Cliente " + nome;

    // Centralização da mensagem com base no tamanho das divisórias
    int largura = divisoria.length();
    int centralizacao = (largura + mensagem.length()) / 2;
    
    // setw vai garantir a centralização da mensagem e preencher sua direita com espaçamentos
    cout << divisoria << "\n"
    << setw(centralizacao) << mensagem << "\n"
    << divisoria << "\n";

    cout << "Trabalho: " << trabalho << "\n";
    cout << "Login:    " << login << "\n";
    cout << "Senha:    " << senha << "\n";

}