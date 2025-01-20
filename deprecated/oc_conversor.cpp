#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

#define MAX_INSTRUCOES 100
#define MAX_COMANDO 50

using namespace std;

struct Instrucao {
    char comando[MAX_COMANDO];
    int regDst, aluSrc, memToReg, regWrite, memRead, memWrite, branch, aluOp;
};

Instrucao memoriaInstrucoes[MAX_INSTRUCOES];
int pc = 0; 

void processarInstrucoes() {
    for (int i = 0; i < MAX_INSTRUCOES; i++) {
        if (strlen(memoriaInstrucoes[i].comando) == 0) continue;

        cout << "Instrucao: " << memoriaInstrucoes[i].comando << endl;
        
        cout << "Sinais de Controle:" << endl;
        cout << "RegDst: " << memoriaInstrucoes[i].regDst
                  << ", ALUSrc: " << memoriaInstrucoes[i].aluSrc
                  << ", MemtoReg: " << memoriaInstrucoes[i].memToReg
                  << ", RegWrite: " << memoriaInstrucoes[i].regWrite
                  << ", MemRead: " << memoriaInstrucoes[i].memRead
                  << ", MemWrite: " << memoriaInstrucoes[i].memWrite
                  << ", Branch: " << memoriaInstrucoes[i].branch
                  << ", ALUOp: " << memoriaInstrucoes[i].aluOp
                  << endl;

        cout << "PC = " << pc << endl << endl;
        pc += 4; 

        if (strstr(memoriaInstrucoes[i].comando, "sw") != nullptr) {
            cout << "Alteracao na memoria." << endl;
        }

        if (strstr(memoriaInstrucoes[i].comando, "lw") != nullptr) {
            cout << "Leitura da memoria." << endl;
        }
        
        if (strstr(memoriaInstrucoes[i].comando, "beq") != nullptr) {
            cout << "Salto condicional." << endl;
        }
    }
}

void adicionarInstrucao(int idx, const string &comando) {
    strcpy(memoriaInstrucoes[idx].comando, comando.c_str());
    
    if (comando.find("addi") != string::npos) {
        memoriaInstrucoes[idx].regDst = 0;
        memoriaInstrucoes[idx].aluSrc = 1;
        memoriaInstrucoes[idx].memToReg = 0;
        memoriaInstrucoes[idx].regWrite = 1;
        memoriaInstrucoes[idx].memRead = 0;
        memoriaInstrucoes[idx].memWrite = 0;
        memoriaInstrucoes[idx].branch = 0;
        memoriaInstrucoes[idx].aluOp = 10;
    } else if (comando.find("add") != string::npos) {
        memoriaInstrucoes[idx].regDst = 1;
        memoriaInstrucoes[idx].aluSrc = 0;
        memoriaInstrucoes[idx].memToReg = 0;
        memoriaInstrucoes[idx].regWrite = 1;
        memoriaInstrucoes[idx].memRead = 0;
        memoriaInstrucoes[idx].memWrite = 0;
        memoriaInstrucoes[idx].branch = 0;
        memoriaInstrucoes[idx].aluOp = 10;
    } else if (comando.find("sw") != string::npos) {
        memoriaInstrucoes[idx].regDst = 0;
        memoriaInstrucoes[idx].aluSrc = 1;
        memoriaInstrucoes[idx].memToReg = 0;
        memoriaInstrucoes[idx].regWrite = 0;
        memoriaInstrucoes[idx].memRead = 0;
        memoriaInstrucoes[idx].memWrite = 1;
        memoriaInstrucoes[idx].branch = 0;
        memoriaInstrucoes[idx].aluOp = 00;
    } else if (comando.find("lw") != string::npos) {
        memoriaInstrucoes[idx].regDst = 0;
        memoriaInstrucoes[idx].aluSrc = 1;
        memoriaInstrucoes[idx].memToReg = 1;
        memoriaInstrucoes[idx].regWrite = 1;
        memoriaInstrucoes[idx].memRead = 1;
        memoriaInstrucoes[idx].memWrite = 0;
        memoriaInstrucoes[idx].branch = 0;
        memoriaInstrucoes[idx].aluOp = 00;
    }
}

int main(int argc, char *argv[]) {
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