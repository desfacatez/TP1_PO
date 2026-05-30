#include "Transacao.h"
#include <iostream>
#include <string>
#include <vector>
#include <iostream>
using namespace std;


Transacao:: Transacao(const string& tipo, double valor,
                     const string& data, const string& horario)
                     : tipo(tipo), valor(valor), data(data), horario(horario) {}

string Transacao::getTipo()     const { return tipo; }
double Transacao::getValor()    const { return valor; }
string  Transacao::getData()    const { return data; }
string Transacao::getHorario()  const { return horario; }

void Transacao::setTipo(const string& tipo)            { this->tipo = tipo; }
void Transacao::setValor(double valor)                 { this->valor = valor; }
void Transacao::setData(const string& data)            { this->data = data; }
void Transacao::setHorario(const string& horario)      { this->horario = horario; }
const vector<Cliente*>& Transacao::getClientes() const { return clientesEnvolvidos; }

void Transacao::exibirTransacao() const {
    cout << "Tipo: " << tipo << endl;
    cout << "Valor: " << valor << endl;
    cout << "Data: " << data << endl;
    cout << "Horario: " << horario << endl;
    cout << "Clientes Envolvidos: " << endl;
    for (const auto& cliente : clientesEnvolvidos) {
        cliente->exibirDados();
        cout << "-------------------" << endl;
    }
}
                    