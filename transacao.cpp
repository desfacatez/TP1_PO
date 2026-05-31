#include "transacao.h"
#include "cliente.h"
#include <iostream>
#include <iomanip>

using namespace std;

Transacao::Transacao(const string& tipo, double valor, const string& data, const string& horario) 
                    :tipo(tipo), valor(valor), data(data), horario(horario) {}

string Transacao::getTipo() const { return tipo; }
double Transacao::getValor() const { return valor; }
string  Transacao::getData() const { return data; }
string Transacao::getHorario() const { return horario; }

void Transacao::setTipo(const string& tipo) { this->tipo = tipo; }
void Transacao::setValor(double valor) { this->valor = valor; }
void Transacao::setData(const string& data) { this->data = data; }
void Transacao::setHorario(const string& horario) { this->horario = horario; }
const vector<Cliente*>& Transacao::getClientes() const { return clientesEnvolvidos; }

void Transacao::exibirTransacao() const {
    // If tamanho do vetor > 0, imprime dados de transacao dos clientes
    // Caso contrario, imprime mensagem de erro  
    if(!clientesEnvolvidos.empty()){
        cout << "=============== Comprovante de Transação =============\n";
        cout << "Tipo:     " << tipo << "\n";
        // Exibe duas casas decimais ao saldo da transação do Cliente
        cout << "Valor:     R$" << fixed << setprecision(2) << valor << "\n";
        cout << "Data:     " << data << "\n";
        cout << "Horario:     " << horario << "\n";
        cout << Pessoa::divisoria2;
        cout << "Clientes Envolvidos:" << "\n";
        
        int counter = 1;
        for (const auto& cliente : clientesEnvolvidos){
            cout << counter << ". " << cliente->getNome() << "\n";
            counter++;
        }
            cout << Pessoa::divisoria << "\n\n";
    } else {
        cout << "Erro. Nenhuma transação efetuada.\n\n";
    }
}
        
                    
