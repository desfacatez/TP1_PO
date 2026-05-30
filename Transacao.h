#ifdef TRANSACAO_H
#define TRANSACAO_H   
#include <string>
#include <vector>
#include "Cliente.h"
using namespace std;

class Transacao { 
private:
    string tipo;
    double valor;
    string data;
    string horario;
    vector<Cliente*> clientesEnvolvidos;
public:

    transacao() : valor(0.0) {}

    transacao(const string& tipo, double valor,
              const string& data, const string& horario);

    string getTipo()    const;
    double getValor()   const;
    string getData()    const;
    string getHorario() const;
    const vector<Cliente*>& getClientes() const;

    void setTipo(const string& tipo);
    void setValor(double valor);
    void setData(const string& data);
    void setHorario(const string& horario);
    void addCliente(Cliente* c) { clientesEnvolvidos.push_back(c); }

    void exibirTransacao() const;
};



#endif // TRANSAO_H