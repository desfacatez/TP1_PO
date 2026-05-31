#include "banco.h"
#include <iostream>
#include <ctime>
#include <cctype>
using namespace std;

void Banco::obterDataHoraAtual(string& data, string& horario) const {
    time_t agora = time(nullptr);
    tm* localTemp = localtime(&agora);
    char buf[32];

    strftime(buf, sizeof(buf), "%d/%m/%Y", localTemp);
    data = buf;

    strftime(buf, sizeof(buf), "%H:%M:%S", localTemp);
    horario = buf;
}


string Banco::trocaCSV(const string& linha) const {
    string resultado;
    for (char sinal : linha) {
        resultado += (sinal == ';') ? '|' : sinal;
    }
    return resultado;
}

string Banco::destrocaCSV(const string& linha) const {
    string resultado;
    for (char sinal : linha) {
        resultado += (sinal == '|') ? ';' : sinal;
    }
    return resultado;
}

Cliente* Banco::buscarClientePorLogin(const string& login) {
    auto it = mapaClientes.find(login);
    if (it != mapaClientes.end()) {
        return &clientes[it->second];
    }
    return nullptr;
}

Cliente* Banco::buscarClientePorNome(const string& nome) {
    string nomeMinusculo = "";
    for (char c : nome) nomeMinusculo += tolower(c);

    for (auto& c : clientes) {
        string nomeClienteMinusculo = "";
        for (char ch : c.getNome()) nomeClienteMinusculo += tolower(ch);

        if (nomeClienteMinusculo.find(nomeMinusculo) != string::npos) {
            return &c;
        }
    }
    return nullptr;
}

Gerente* Banco::buscarGerentePorNome(const string& nome) {
    string nomeMinusculo = "";
    for (char c : nome) nomeMinusculo += tolower(c);

    for (auto& g : gerentes) {
        string nomeGerenteMinusculo = "";
        for (char ch : g.getNome()) nomeGerenteMinusculo += tolower(ch);

        if (nomeGerenteMinusculo.find(nomeMinusculo) != string::npos) {
            return &g;
        }
    }
    return nullptr;
}

Banco::Banco() {
    carregarDados();
}

Banco::~Banco() {
    salvarDados();
}

void Banco::exibirMenu() {
    int opcao = 0;
    do {
        cout << "\n====== \033[1m SISTEMA DE GERENCIAMENTO DE BANCO\033[0m ======\n";
        cout << "\033[1m 1.\033[0m Cadastrar cliente\n";
        cout << "\033[1m 2.\033[0m Cadastrar gerente\n";
        cout << "\033[1m 3.\033[0m Criar transacao\n";
        cout << "\033[1m 4.\033[0m Exibir extrato de um cliente\n";
        cout << "\033[1m 5.\033[0m Associar gerente a cliente\n";
        cout << "\033[1m 6.\033[0m Listar clientes\n";
        cout << "\033[1m 7.\033[0m Listar gerentes\n";
        cout << "\033[1m 8.\033[0m Cartao de credito (extra)\n";
        cout << "\033[1m 9.\033[0m Aplicar rendimento da poupanca\n";
        cout << " 0.\033[0m Salvar dados e sair\n";
        cout << "================================================\n";
        cout << "\033[1mEscolha uma opcao:\033[0m ";

        // Rejeita entradas que nao sejam numeros
        if (!(cin >> opcao)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\033[1m[ERRO] Entrada invalida. Digite um numero.\033[0m\n";
            opcao = -1;
            continue;
        }
        cin.ignore(10000, '\n');

        switch (opcao) {
            case 1: cadastrarCliente();       break;
            case 2: cadastrarGerente();       break;
            case 3: criarTransacao();         break;
            case 4: exibirExtrato();          break;
            case 5: associarGerenteCliente(); break;
            case 6: listarClientes();         break;
            case 7: listarGerentes();         break;
            case 8: menuCartaoCredito();      break;
            case 9: aplicarRendimentoTodos(); break;
            case 0: salvarDados();
                    cout << "\033[1m[OK] Dados salvos. Encerrando sistema. Ate logo!\033[0m\n";
                    break;
            default:
                cout << "\033[1m[AVISO] Opcao invalida. Tente novamente.\033[0m\n";
        }
    } while (opcao != 0);
}