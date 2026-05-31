#ifndef GERENTE_H
#define GERENTE_H

#include "pessoa.h"
#include <vector>
using namespace std;

class Cliente;

class Gerente : public Pessoa {
private:
    vector<Cliente*> clientes;

public:

    Gerente() = default;

    Gerente(const string& nome, const string& trabalho,
            const string& login, const string& senha);

    void setCliente(Cliente* novoCliente);
    const vector<Cliente*>& getClientes() const { return clientes; }
    bool clienteVinculado(const string& login) const;

    void exibirDados() const override;
};

#endif // GERENTE_H