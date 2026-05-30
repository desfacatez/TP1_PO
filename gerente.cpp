#include "Gerente.h"
#include "Cliente.h"
#include <iostream>
#include <iomanip>
using namespace std;

Gerente::Gerente(const string& nome, const string& trabalho,
                 const string& login, const string& senha)
                : Pessoa(nome, trabalho, login, senha) {}

void Gerente::setCliente(Cliente* c) {
    if (!c) return;

    auto it = find_if(clientes.begin(), clientes.end(),
        [&](const Cliente* existente) {
            return existente->getLogin() == c->getLogin();
        });

    if (it == clientes.end()) {
        clientes.push_back(c);
    }
}

bool Gerente::clienteJaVinculado(const string& login) const {
    for (const Cliente* c : clientes) {
        if (c->getLogin() == login) {
            return true;
        }
    }
    return false;
}

void Gerente::exibirDados() const {
    Pessoa::exibirDados();
    cout << "Clientes vinculados (" << clientes.size() << "):\n";

    if (clientes.empty()) {
        cout << "  (nenhum cliente vinculado)\n";
    } else {
        for (const auto* c : clientes) {
            cout << "  - " << left << setw(25) << c->getNome()
                 << " [" << c->getLogin() << "]"
                 << " | " << setw(10) << c->getTipoConta()
                 << " | Saldo: R$ "
                 << fixed << setprecision(2) << c->getSaldo() << "\n";
        }
    }
    cout << "==================================\n";
}