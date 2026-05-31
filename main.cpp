#include "banco.h"
#include <iostream>
using namespace std;

int main() {
    cout << "===================================================\n";
    cout << "  Bem-vindo ao Sistema de Gerenciamento de Banco\n";
    cout << "===================================================\n\n";

    Banco banco;

    // Inicia o loop principal do menu interativo
    banco.exibirMenu();

    return 0;
}