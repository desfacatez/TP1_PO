#include "banco.h"
#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;

void Banco::criarTransacao() {
    cout << "\n----- CRIAR TRANSACAO -----\n";

    if (clientes.empty()) {
        cout << "[AVISO] Nenhum cliente cadastrado.\n";
        return;
    }

    string tipo, loginOrigem, loginDestino;
    double valor = 0.0;

    do {
        cout << "Tipo (deposito / saque / transferencia): ";
        getline(cin, tipo);
        if (tipo != "deposito" && tipo != "saque" && tipo != "transferencia") {
            cout << "[ERRO] Tipo invalido. Use exatamente: deposito, saque ou transferencia.\n";
        }
    } while (tipo != "deposito" && tipo != "saque" && tipo != "transferencia");

    cout << "Valor (R$): ";
    cin >> valor;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (valor <= 0.0) {
        cout << "[ERRO] O valor deve ser positivo.\n";
        return;
    }

    string data, horario;
    obterDataHoraAtual(data, horario);

    Transacao t(tipo, valor, data, horario);

    if (tipo == "deposito") {
        cout << "Login do cliente destino: ";
        getline(cin, loginDestino);

        Cliente* dest = buscarClientePorLogin(loginDestino);
        if (!dest) { cout << "[ERRO] Cliente nao encontrado.\n"; return; }

        dest->setSaldo(dest->getSaldo() + valor);
        t.setCliente(dest);
        dest->setTransacao(t);

        cout << "[OK] Deposito de R$ " << fixed << setprecision(2) << valor
             << " realizado para " << dest->getNome()
             << ". Novo saldo: R$ " << dest->getSaldo() << "\n";

    } else if (tipo == "saque") {
        cout << "Login do cliente: ";
        getline(cin, loginOrigem);

        Cliente* orig = buscarClientePorLogin(loginOrigem);
        if (!orig) { cout << "[ERRO] Cliente nao encontrado.\n"; return; }

        if (orig->getSaldo() < valor) {
            cout << "[ERRO] Saldo insuficiente. Saldo atual: R$ "
                 << fixed << setprecision(2) << orig->getSaldo() << "\n";
            return;
        }

        orig->setSaldo(orig->getSaldo() - valor);
        t.setCliente(orig);
        orig->setTransacao(t);

        cout << "[OK] Saque de R$ " << fixed << setprecision(2) << valor
             << " realizado. Saldo restante: R$ " << orig->getSaldo() << "\n";

    } else {
        cout << "Login do cliente de ORIGEM : ";
        getline(cin, loginOrigem);

        cout << "Login do cliente de DESTINO: ";
        getline(cin, loginDestino);

        if (loginOrigem == loginDestino) {
            cout << "[ERRO] Origem e destino nao podem ser o mesmo cliente.\n";
            return;
        }

        Cliente* orig = buscarClientePorLogin(loginOrigem);
        Cliente* dest = buscarClientePorLogin(loginDestino);

        if (!orig) { cout << "[ERRO] Cliente de origem nao encontrado.\n"; return; }
        if (!dest) { cout << "[ERRO] Cliente de destino nao encontrado.\n"; return; }

        if (orig->getSaldo() < valor) {
            cout << "[ERRO] Saldo insuficiente. Saldo atual de " << orig->getNome()
                 << ": R$ " << fixed << setprecision(2) << orig->getSaldo() << "\n";
            return;
        }

        orig->setSaldo(orig->getSaldo() - valor);
        dest->setSaldo(dest->getSaldo() + valor);

        t.setCliente(orig);
        t.setCliente(dest);
        orig->setTransacao(t);
        dest->setTransacao(t);

        cout << "[OK] Transferencia de R$ " << fixed << setprecision(2) << valor
             << " de " << orig->getNome() << " para " << dest->getNome() << " realizada.\n";
        cout << "     Saldo " << orig->getNome() << ": R$ " << orig->getSaldo() << "\n";
        cout << "     Saldo " << dest->getNome() << ": R$ " << dest->getSaldo() << "\n";
    }
}

void Banco::exibirExtrato() {
    cout << "\n----- EXTRATO DO CLIENTE -----\n";

    if (clientes.empty()) {
        cout << "[AVISO] Nenhum cliente cadastrado.\n";
        return;
    }

    cout << "Nome do cliente: ";
    string nome;
    getline(cin, nome);

    Cliente* c = buscarClientePorNome(nome);
    if (!c) {
        cout << "[ERRO] Cliente nao encontrado.\n";
        return;
    }

    cout << "\n===== EXTRATO DE " << c->getNome() << " =====\n";
    cout << "Tipo de conta: " << c->getTipoConta() << "\n";
    cout << "Saldo atual  : R$ " << fixed << setprecision(2) << c->getSaldo() << "\n\n";

    const auto& extrato = c->getExtrato();
    if (extrato.empty()) {
        cout << "  Nenhuma transacao registrada.\n";
    } else {
        cout << "  Total de transacoes: " << extrato.size() << "\n\n";
        int num = 1;
        for (const auto& t : extrato) {
            cout << "  [" << num++ << "] ";
            t.exibirTransacao();
        }
    }
    cout << "==============================\n";
}

void Banco::aplicarRendimentoTodos() {
    cout << "\n----- APLICAR RENDIMENTO DA POUPANCA -----\n";

    if (clientes.empty()) {
        cout << "[AVISO] Nenhum cliente cadastrado.\n";
        return;
    }

    int contPoupanca = 0;
    for (auto& c : clientes) {
        if (c.getTipoConta() == "poupanca") {
            c.aplicarRendimento();
            contPoupanca++;
        }
    }

    if (contPoupanca == 0) {
        cout << "[INFO] Nenhum cliente possui conta poupanca.\n";
    } else {
        cout << "[OK] Rendimento aplicado a " << contPoupanca << " conta(s) poupanca.\n";
    }
}

void Banco::listarClientes() {
    cout << "\n----- LISTAR CLIENTES -----\n";

    if (clientes.empty()) {
        cout << "[AVISO] Nenhum cliente cadastrado.\n";
        return;
    }

    cout << "Nome do cliente (ENTER para listar todos): ";
    string nome;
    getline(cin, nome);

    if (nome.empty()) {
        cout << "\nTotal de clientes: " << clientes.size() << "\n\n";
        cout << left << setw(15) << "Login"
             << setw(25) << "Nome"
             << setw(12) << "Conta"
             << "Saldo\n";
        cout << string(60, '-') << "\n";
        for (const auto& c : clientes) {
            cout << left << setw(15) << c.getLogin()
                 << setw(25) << c.getNome()
                 << setw(12) << c.getTipoConta()
                 << "R$ " << fixed << setprecision(2) << c.getSaldo() << "\n";
        }
    } else {
        Cliente* c = buscarClientePorNome(nome);
        if (!c) {
            cout << "[ERRO] Cliente nao encontrado.\n";
        } else {
            c->exibirDados();
        }
    }
}

void Banco::listarGerentes() {
    cout << "\n----- LISTAR GERENTES -----\n";

    if (gerentes.empty()) {
        cout << "[AVISO] Nenhum gerente cadastrado.\n";
        return;
    }

    cout << "Nome do gerente (ENTER para listar todos): ";
    string nome;
    getline(cin, nome);

    if (nome.empty()) {
        cout << "\nTotal de gerentes: " << gerentes.size() << "\n\n";
        cout << left << setw(15) << "Login"
             << setw(25) << "Nome"
             << "Clientes vinculados\n";
        cout << string(55, '-') << "\n";
        for (const auto& g : gerentes) {
            cout << left << setw(15) << g.getLogin()
                 << setw(25) << g.getNome()
                 << g.getClientes().size() << "\n";
        }
    } else {
        Gerente* g = buscarGerentePorNome(nome);
        if (!g) {
            cout << "[ERRO] Gerente nao encontrado.\n";
        } else {
            g->exibirDados();
        }
    }
}
