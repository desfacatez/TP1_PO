#ifndef BANCO_H
#define BANCO_H

#include "Cliente.h"
#include "Gerente.h"
#include <vector>
#include <map>
using namespace std;

class Banco {
private:
    vector<Cliente> clientes;
    vector<Gerente> gerentes;

    map<string, int> mapaClientes;
    map<string, int> mapaGerentes;

    const string ARQUIVO_CLIENTES   = "clientes.csv";
    const string ARQUIVO_GERENTES   = "gerentes.csv";
    const string ARQUIVO_TRANSACOES = "transacoes.csv";

    void obterDataHoraAtual(string& data, string& horario) const;

    Cliente* buscarClientePorLogin(const string& login);

    Cliente* buscarClientePorNome(const string& nome);

    Gerente* buscarGerentePorNome(const string& nome);

    string trocaCSV(const string& s) const;

    string destrocaCSV(const string& s) const;

public:
    Banco();

    ~Banco();

    void exibirMenu();

    void cadastrarCliente();

    void cadastrarGerente();

    void criarTransacao();

    void exibirExtrato();

    void aplicarRendimentoTodos();

    void associarGerenteCliente();

    void listarClientes();

    void listarGerentes();

    void menuCartaoCredito();

    void criarCartaoCliente();

    void alterarLimiteCartao();

    void realizarCompraParcelada();

    void exibirFaturaCartao();

    void bloquearDesbloquearCartao();

    void pagarFaturaCartao();

    void salvarDados();

    void carregarDados();
};

#endif // BANCO_H