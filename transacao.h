#ifndef TRANSACAO_H
#define TRANSACAO_H   

#include <string>
#include <vector>

class Cliente;

using namespace std;

class Transacao { 
private:
    string tipo;
    double valor;
    string data;
    string horario;
    vector<Cliente*> clientesEnvolvidos;

public:

    Transacao():valor(0.0) {}

    Transacao(const string& tipo, double valor, const string& data, const string& horario);

    string getTipo() const;
    double getValor() const;
    string getData() const;
    string getHorario() const;
    const vector<Cliente*>& getClientes() const;

    void setTipo(const string& tipo);
    void setValor(double valor);
    void setData(const string& data);
    void setHorario(const string& horario);
    void addCliente(Cliente* cliente) { clientesEnvolvidos.push_back(cliente); }

    void exibirTransacao() const;
};

#endif // TRANSACAO_H
