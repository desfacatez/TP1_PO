#include "pessoa.h"
#include <cstring>
#include <iostream>
#include <iomanip>

using namespace std;

// Inicializa strings para uso
const string Pessoa::divisoria = "==================================================";
const string Pessoa::divisoria2 = "----------------------\n\n";

Pessoa::Pessoa(const string& nome, const string& trabalho,
               const string& login, const string& senha)
             : nome(nome), trabalho(trabalho), login(login), senha(senha) {}

void Pessoa::setNome(const string& nome){ this->nome = nome; }
void Pessoa::setTrabalho(const string& trabalho){ this->trabalho = trabalho; }
void Pessoa::setLogin(const string& login) { this->login = login; }
void Pessoa::setSenha(const string& senha){ this->senha = senha; }

void Pessoa::exibirDados() const {
    
    string mensagem = "Listagem do(a) " + trabalho + " " + nome;

    // Centralização da mensagem com base no tamanho das divisorias
    int centralizacao = (divisoria.length() + mensagem.length()) / 2;
    
    // setw vai garantir a centralizacao da mensagem e preencher sua direita com espacamentos
    cout << divisoria << "\n"
    << setw(centralizacao) << mensagem << "\n"
    << divisoria << "\n";

    cout << "Login:     " << login << "\n";
    cout << "Senha:     " << senha << "\n";

}