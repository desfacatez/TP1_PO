#include "banco.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
using namespace std;

void Banco::salvarDados() {
    filesystem::create_directories("data");


    ofstream arqClientes(ARQUIVO_CLIENTES);
    if (!arqClientes.is_open()) {
        cerr << "[ERRO] Nao foi possivel salvar " << ARQUIVO_CLIENTES << "\n";
        return;
    }

    arqClientes << "nome;dataNasc;trabalho;remuneracao;tipoConta;"
                << "taxaRendimento;saldo;login;senha;"
                << "temCartao;limiteCartao;faturaCartao;bloqueadoCartao\n";

    for (const auto& c : clientes) {
        arqClientes << trocaCSV(c.getNome())           << ";"
                    << trocaCSV(c.getDataNascimento()) << ";"
                    << trocaCSV(c.getTrabalho())       << ";"
                    << c.getRemuneracao()                << ";"
                    << trocaCSV(c.getTipoConta())      << ";"
                    << c.getRendimento()             << ";"
                    << c.getSaldo()                      << ";"
                    << trocaCSV(c.getLogin())          << ";"
                    << trocaCSV(c.getSenha())          << ";";

        if (c.temCartao()) {
            const CartaoCredito* cartao = c.getCartao();
            arqClientes << "1;"
                        << cartao->getLimite()      << ";"
                        << cartao->getFaturaAtual() << ";"
                        << (cartao->isBloqueado() ? "1" : "0");
        } else {
            arqClientes << "0;0;0;0";
        }
        arqClientes << "\n";
    }
    arqClientes.close();

    ofstream arqGerentes(ARQUIVO_GERENTES);
    if (!arqGerentes.is_open()) {
        cerr << "[ERRO] Nao foi possivel salvar " << ARQUIVO_GERENTES << "\n";
        return;
    }

    arqGerentes << "nome;trabalho;login;senha;clientes\n";
    for (const auto& g : gerentes) {
        arqGerentes << trocaCSV(g.getNome())     << ";"
                    << trocaCSV(g.getTrabalho()) << ";"
                    << trocaCSV(g.getLogin())    << ";"
                    << trocaCSV(g.getSenha())    << ";";

        const auto& clientesGerente = g.getClientes();
        for (size_t i = 0; i < clientesGerente.size(); ++i) {
            arqGerentes << clientesGerente[i]->getLogin();
            if (i + 1 < clientesGerente.size()) arqGerentes << "|";
        }
        arqGerentes << "\n";
    }
    arqGerentes.close();

    ofstream arqTrans(ARQUIVO_TRANSACOES);
    if (!arqTrans.is_open()) {
        cerr << "[ERRO] Nao foi possivel salvar " << ARQUIVO_TRANSACOES << "\n";
        return;
    }

    arqTrans << "loginCliente;tipo;valor;data;horario\n";
    for (const auto& c : clientes) {
        for (const auto& t : c.getExtrato()) {
            arqTrans << trocaCSV(c.getLogin())    << ";"
                     << trocaCSV(t.getTipo())     << ";"
                     << t.getValor()                << ";"
                     << trocaCSV(t.getData())     << ";"
                     << trocaCSV(t.getHorario())  << "\n";
        }
    }
    arqTrans.close();

    cout << "[OK] Dados salvos em '" << ARQUIVO_CLIENTES << "', '"
         << ARQUIVO_GERENTES << "' e '" << ARQUIVO_TRANSACOES << "'.\n";
}

void Banco::carregarDados() {

    ifstream arqClientes(ARQUIVO_CLIENTES);
    if (arqClientes.is_open()) {
        string linha;
        getline(arqClientes, linha);

        while (getline(arqClientes, linha)) {
            if (linha.empty()) continue;
            stringstream ss(linha);
            string campo;
            vector<string> campos;

            while (getline(ss, campo, ';')) {
                campos.push_back(destrocaCSV(campo));
            }
            if (campos.size() < 13) continue;

            Cliente c;
            c.setNome(campos[0]);
            c.setDataNascimento(campos[1]);
            c.setTrabalho(campos[2]);
            c.setRemuneracao(stod(campos[3]));
            c.setTipoConta(campos[4]);
            c.setRendimento(stod(campos[5]));
            c.setSaldo(stod(campos[6]));
            c.setLogin(campos[7]);
            c.setSenha(campos[8]);

            if (campos[9] == "1") {
                c.criarCartao();
                if (c.temCartao()) {
                    c.getCartao()->setLimite(stod(campos[10]));
                    if (campos[12] == "1") c.getCartao()->bloquear();
                }
            }

            clientes.push_back(move(c));
            mapaClientes[clientes.back().getLogin()] =
                static_cast<int>(clientes.size()) - 1;
        }
        arqClientes.close();
        cout << "[INFO] " << clientes.size() << " cliente(s) carregado(s).\n";
    }

    ifstream arqTrans(ARQUIVO_TRANSACOES);
    if (arqTrans.is_open()) {
        string linha;
        getline(arqTrans, linha); // ignora cabeçalho

        while (getline(arqTrans, linha)) {
            if (linha.empty()) continue;
            stringstream ss(linha);
            string campo;
            vector<string> campos;

            while (getline(ss, campo, ';')) {
                campos.push_back(destrocaCSV(campo));
            }
            if (campos.size() < 5) continue;

            Cliente* c = buscarClientePorLogin(campos[0]);
            if (!c) continue;

            Transacao t(campos[1], stod(campos[2]), campos[3], campos[4]);
            t.setCliente(c);
            c->setTransacao(t);
        }
        arqTrans.close();
    }

    ifstream arqGerentes(ARQUIVO_GERENTES);
    if (arqGerentes.is_open()) {
        string linha;
        getline(arqGerentes, linha);

        struct PendenciaVinculo { string loginsClientes; int indice; };
        vector<PendenciaVinculo> pendentes;

        while (getline(arqGerentes, linha)) {
            if (linha.empty()) continue;
            stringstream ss(linha);
            string campo;
            vector<string> campos;

            while (getline(ss, campo, ';')) {
                campos.push_back(destrocaCSV(campo));
            }
            if (campos.size() < 5) continue;

            Gerente g(campos[0], campos[1], campos[2], campos[3]);
            gerentes.push_back(g);
            int idx = static_cast<int>(gerentes.size()) - 1;
            mapaGerentes[campos[2]] = idx;
            pendentes.push_back({campos[4], idx});
        }
        arqGerentes.close();

        for (auto& p : pendentes) {
            if (p.loginsClientes.empty()) continue;
            stringstream ssLogins(p.loginsClientes);
            string loginC;
            while (getline(ssLogins, loginC, '|')) {
                Cliente* c = buscarClientePorLogin(loginC);
                if (c) gerentes[p.indice].setCliente(c);
            }
        }

        cout << "[INFO] " << gerentes.size() << " gerente(s) carregado(s).\n";
    }
}
