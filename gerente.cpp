#include "gerente.h"
#include "cliente.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

Gerente::Gerente(const string& nome, const string& trabalho,
                 const string& login, const string& senha)
                 :Pessoa(nome, trabalho, login, senha) {}

void Gerente::setCliente(Cliente* novoCliente) {
    if (!novoCliente) return;

    // Varre o vetor clientes do comeco ao fim procurando por um login identico
    // Se o encontrar, 'it' guarda a posicao do cliente repetido
    auto it = find_if(clientes.begin(), clientes.end(),
        [&](const Cliente* existente) {
            return existente->getLogin() == novoCliente->getLogin();
        });
    
    // Se a varredura nao identificou um login identico ao do novoCliente, guarda seu ponteiro no vetor
    if (it == clientes.end()) {
        clientes.push_back(novoCliente);
    }
}

// Funcao que varre o vetor clientes de Gerente ppra identificar se o cliente atual existe no sistema
bool Gerente::clienteVinculado(const string& login) const {
    for (const Cliente* cliente : clientes) {
        // se o login do cliente atual for igual ao login que estamos olhando, retorna true
        if (cliente->getLogin() == login) {
            return true;
        }
    }
    // Retorna false pois o cliente nao ta vinculado ao gerente
    return false;
}

void Gerente::exibirDados() const {

    // Chama o cabeçalho global em Pessoa (para Gerente) 
    Pessoa::exibirDados();
    cout << "Clientes vinculados (" << clientes.size() << "):\n";

    if (!clientes.empty()){
        for (const auto* cliente : clientes) {
            cout << "  - " << left << setw(25) << cliente->getNome()
                 << " [" << cliente->getLogin() << "]"
                 << " | " << setw(10) << cliente->getTipoConta()
                 << " | Saldo: R$"
                 << fixed << setprecision(2) << cliente->getSaldo() << "\n";
        }
    } else {
        cout << "(Erro. Nenhum cliente vinculado.)\n";
    }
    cout << Pessoa::divisoria << "\n\n";
}