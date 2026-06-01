#include "banco.h"
#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;

void Banco::cadastrarCliente() {
    cout << "\n----- CADASTRAR CLIENTE -----\n";

    string nome, dataNasc, trabalho, login, senha, tipoConta;
    double remuneracao = 0.0, taxaRendimento = 0.0, saldoInicial = 0.0;

    cout << "Nome                        : ";
    getline(cin, nome);

    cout << "Data de Nascimento (DD/MM/AAAA): ";
    getline(cin, dataNasc);

    cout << "Trabalho/Profissao          : ";
    getline(cin, trabalho);

    cout << "Remuneracao mensal (R$)     : ";
    cin >> remuneracao;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    do {
        cout << "Tipo de conta (corrente / poupanca): ";
        getline(cin, tipoConta);
        if (tipoConta != "corrente" && tipoConta != "poupanca") {
            cout << "[ERRO] Digite exatamente 'corrente' ou 'poupanca'.\n";
        }
    } while (tipoConta != "corrente" && tipoConta != "poupanca");

    if (tipoConta == "poupanca") {
        taxaRendimento = 0.5 + (remuneracao / 10000.0);
        if (taxaRendimento > 2.0) taxaRendimento = 2.0;
        cout << "[INFO] Taxa de rendimento calculada automaticamente: "
             << fixed << setprecision(2) << taxaRendimento << "% ao mes\n";
    }

    cout << "Saldo inicial (R$)          : ";
    cin >> saldoInicial;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Login                       : ";
    getline(cin, login);

    if (buscarClientePorLogin(login) != nullptr) {
        cout << "[ERRO] Login '" << login << "' ja esta em uso. Cadastro cancelado.\n";
        return;
    }

    cout << "Senha                       : ";
    getline(cin, senha);

    clientes.emplace_back(nome, dataNasc, trabalho, remuneracao,
                          tipoConta, taxaRendimento, saldoInicial, login, senha);
    mapaClientes[login] = static_cast<int>(clientes.size()) - 1;

    cout << "[OK] Cliente '" << nome << "' cadastrado com sucesso!\n";
}


void Banco::cadastrarGerente() {
    cout << "\n----- CADASTRAR GERENTE -----\n";

    string nome, trabalho, login, senha;

    cout << "Nome         : ";
    getline(cin, nome);

    cout << "Trabalho/Cargo: ";
    getline(cin, trabalho);

    cout << "Login        : ";
    getline(cin, login);

    if (mapaGerentes.find(login) != mapaGerentes.end()) {
        cout << "[ERRO] Login '" << login << "' ja esta em uso. Cadastro cancelado.\n";
        return;
    }

    cout << "Senha        : ";
    getline(cin, senha);

    gerentes.emplace_back(nome, trabalho, login, senha);
    mapaGerentes[login] = static_cast<int>(gerentes.size()) - 1;

    cout << "[OK] Gerente '" << nome << "' cadastrado com sucesso!\n";
}

void Banco::associarGerenteCliente() {
    cout << "\n----- ASSOCIAR GERENTE A CLIENTE -----\n";

    if (gerentes.empty()) {
        cout << "[AVISO] Nenhum gerente cadastrado.\n";
        return;
    }
    if (clientes.empty()) {
        cout << "[AVISO] Nenhum cliente cadastrado.\n";
        return;
    }

    string nomeGerente, nomeCliente;

    cout << "Nome do gerente : ";
    getline(cin, nomeGerente);

    Gerente* g = buscarGerentePorNome(nomeGerente);
    if (!g) {
        cout << "[ERRO] Gerente nao encontrado.\n";
        return;
    }
    cout << "[INFO] Gerente encontrado: " << g->getNome() << "\n";

    cout << "Nome do cliente : ";
    getline(cin, nomeCliente);

    Cliente* c = buscarClientePorNome(nomeCliente);
    if (!c) {
        cout << "[ERRO] Cliente nao encontrado.\n";
        return;
    }
    cout << "[INFO] Cliente encontrado: " << c->getNome() << "\n";

    if (g->clienteJaVinculado(c->getLogin())) {
        cout << "[AVISO] '" << c->getNome()
             << "' ja esta vinculado ao gerente '" << g->getNome() << "'.\n";
        return;
    }

    g->setCliente(c);
    cout << "[OK] Cliente '" << c->getNome()
         << "' vinculado ao gerente '" << g->getNome() << "'.\n";
}
