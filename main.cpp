#include <iostream>
#include <fstream>
#include <string>
#include "conversor.h"

using namespace std;

int main(int argc, char *argv[]) 
{
    if (argc != 2) {
        cout << "Uso: " << argv[0] << " <arquivo de entrada>" << endl;
        return 1;
    }

    ifstream file(argv[1]);
    if (!file.is_open()) {
        cout << "Erro ao abrir o arquivo " << argv[1] << endl;
        return 1;
    }

    string linha;
    int idx = 0;
    while (getline(file, linha) && idx < MAX_INSTRUCOES) {
        linha.erase(linha.find_last_not_of(" \n\r\t") + 1);
        if (linha.length() > 0) {
            adicionarInstrucao(idx, linha);
            idx++;
        }
    }

    file.close();

    processarInstrucoes();
    return 0;
}
