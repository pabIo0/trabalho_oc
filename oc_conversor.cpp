#include "conversor.h"
#include <iostream>
#include <cstring>
#include <bitset>
#include <sstream>

using namespace std;

Instrucao memoriaInstrucoes[MAX_INSTRUCOES];
int pc = 0;
int memoria[1024] = {0};

void converteInstrucaoParaBinario(int idx, const string &comando) {
    stringstream ss(comando);
    string instrucao;
    ss >> instrucao;

    if (instrucao == "addi") {
        memoriaInstrucoes[idx].aluOp = 10;
    } else if (instrucao == "add") {
        memoriaInstrucoes[idx].aluOp = 10;
    } else if (instrucao == "sub") {
        memoriaInstrucoes[idx].aluOp = 10;
    } else if (instrucao == "beq") {
        memoriaInstrucoes[idx].aluOp = 01;
    } else if (instrucao == "lw") {
        memoriaInstrucoes[idx].aluOp = 00;
    } else if (instrucao == "sw") {
        memoriaInstrucoes[idx].aluOp = 00;
    } else if (instrucao == "j") {
        memoriaInstrucoes[idx].aluOp = -1;
    }
}

// Tratar de sinais don't care
string dontCare(int valor) {
    return valor == -1 ? "X" : to_string(valor);
}

void exibirRelatorio(int idx) {
    cout << "Sinais de controle: " << endl;

    // Para o aluOp ter 2 bits de saída
    string aluOpStr = memoriaInstrucoes[idx].aluOp == -1 ? "X" : bitset<2>(memoriaInstrucoes[idx].aluOp).to_string();

    cout << "ALUOp: " << aluOpStr << ", ";
    cout << "RegDst: " << dontCare(memoriaInstrucoes[idx].regDst) << ", ";
    cout << "ALUSrc: " << dontCare(memoriaInstrucoes[idx].aluSrc) << ", ";
    cout << "MemtoReg: " << dontCare(memoriaInstrucoes[idx].memToReg) << ", ";
    cout << "Reg-Write: " << dontCare(memoriaInstrucoes[idx].regWrite) << ", ";
    cout << "Mem-Read: " << dontCare(memoriaInstrucoes[idx].memRead) << ", ";
    cout << "Mem-Write: " << dontCare(memoriaInstrucoes[idx].memWrite) << ", ";
    cout << "Branch: " << dontCare(memoriaInstrucoes[idx].branch) << endl;

    cout << "PC = " << pc << endl;
}

void processarInstrucoes() {
    for (int i = 0; i < MAX_INSTRUCOES; i++) {
        if (strlen(memoriaInstrucoes[i].comando) == 0) continue;

        string comando = memoriaInstrucoes[i].comando;
        string instrucao, registradorDestino, registradorOrigem, valorImediato, label;

        // Extraindo partes da instrução
        stringstream ss(comando);
        ss >> instrucao >> registradorDestino >> registradorOrigem >> valorImediato >> label;

        // Executa a operação no registrador
        operacaoRegistradores(instrucao, registradorDestino, registradorOrigem, valorImediato, label);

        // Converte e exibe os sinais de controle
        converteInstrucaoParaBinario(i, comando);
        exibirRelatorio(i);

        pc += 4;
    }
}


void operacaoRegistradores(const string &instrucao, const string &registradorDestino, const string &registradorOrigem, const string &valorImediato, const string &label) {
    int destino = registradorDestino[2] - '0';
    int origem = registradorOrigem[2] - '0';
    int imediato = 0;

    if (instrucao == "addi") {
        imediato = stoi(valorImediato);
        registradores[destino] = registradores[origem] + imediato;
        cout << endl << instrucao << " " << registradorDestino << " = " << registradores[destino] << "; PC = PC + 4" << endl;
    } else if (instrucao == "add") {
        int origem2 = valorImediato[2] - '0';
        registradores[destino] = registradores[origem] + registradores[origem2];
        cout << endl << instrucao << " " << registradorDestino << " = " << registradores[destino] << "; PC = PC + 4" << endl;
    } else if (instrucao == "sub") {
        int origem2 = valorImediato[2] - '0';
        registradores[destino] = registradores[origem] - registradores[origem2];
        cout << endl << instrucao << " " << registradorDestino << " = " << registradores[destino] << "; PC = PC + 4" << endl;
    } else if (instrucao == "sw") {
        try {
            int imediato = std::stoi(valorImediato);
            imediato /= 4;  // Ajusta o valor do deslocamento
        } catch (const std::invalid_argument& e) {
            std::cerr << endl << "Erro ao converter o valor: " << valorImediato;
        }
        int endereco = registradores[origem] + imediato;
        memoria[endereco] = registradores[destino];
        cout << endl << "sw " << registradorOrigem << "[" << imediato / 4 << "] = " << registradorDestino << "; PC = PC + 4" << endl;
    } else if (instrucao == "lw") {
        imediato = stoi(valorImediato);
        int endereco = registradores[origem] + imediato;
        registradores[destino] = memoria[endereco];
        cout << endl << "lw " << registradorDestino << " = " << registradorOrigem << "[" << imediato / 4 << "]; PC = PC + 4" << endl;
    } else if (instrucao == "beq") {
        if (registradores[destino] == registradores[origem]) {
            cout << endl << "beq " << label << "," << registradorDestino << " == " << registradorOrigem << "; PC = " << endl;
        } else {
            cout << endl << "beq " << label << "," << registradorDestino << " != " << registradorOrigem << "; PC = PC + 4" << endl;
        }
    } else if (instrucao == "j") {
        cout << endl << "j -> PC = label;" << endl;
    }
}


void adicionarInstrucao(int idx, const string &comando) {
    strcpy(memoriaInstrucoes[idx].comando, comando.c_str());

    stringstream ss(comando);
    string instrucao, registradorDestino, registradorOrigem, valorImediato;

    // Primeiro, lê a instrução
    ss >> instrucao;
    
    if (instrucao == "sw" || instrucao == "lw") {
        // Se 'sw' ou 'lw', lê desta forma
        ss >> registradorOrigem >> valorImediato >> registradorDestino;
    } else {
        // Para as demais instruções, seguimos a leitura norma
        ss >> registradorDestino >> registradorOrigem >> valorImediato;
    }

    if (instrucao == "sw" || instrucao == "lw" || instrucao == "beq" || instrucao == "j") {
        converteInstrucaoParaBinario(idx, comando);
    }

    if (instrucao == "addi") {
        memoriaInstrucoes[idx].regDst = 0;
        memoriaInstrucoes[idx].aluSrc = 1;
        memoriaInstrucoes[idx].memToReg = 0;
        memoriaInstrucoes[idx].regWrite = 1;
        memoriaInstrucoes[idx].memRead = 0;
        memoriaInstrucoes[idx].memWrite = 0;
        memoriaInstrucoes[idx].branch = 0;

        int destino = registradorDestino[2] - '0';
        int origem = registradorOrigem[2] - '0';
        int imediato = stoi(valorImediato);

        registradores[destino] = registradores[origem] + imediato;

    } else if (instrucao == "add" || instrucao == "sub") {
        memoriaInstrucoes[idx].regDst = 1;
        memoriaInstrucoes[idx].aluSrc = 0;
        memoriaInstrucoes[idx].memToReg = 0;
        memoriaInstrucoes[idx].regWrite = 1;
        memoriaInstrucoes[idx].memRead = 0;
        memoriaInstrucoes[idx].memWrite = 0;
        memoriaInstrucoes[idx].branch = 0;

        int destino = registradorDestino[2] - '0';
        int origem1 = registradorOrigem[2] - '0';
        int origem2 = valorImediato[2] - '0';

        if (instrucao == "add") {
            registradores[destino] = registradores[origem1] + registradores[origem2];
        } else {
            registradores[destino] = registradores[origem1] - registradores[origem2];
        }
    } else if (instrucao == "sw") {
        memoriaInstrucoes[idx].aluOp = 00;
        memoriaInstrucoes[idx].regDst = -1;
        memoriaInstrucoes[idx].aluSrc = 1;
        memoriaInstrucoes[idx].memToReg = -1;
        memoriaInstrucoes[idx].regWrite = 0;
        memoriaInstrucoes[idx].memRead = 0;
        memoriaInstrucoes[idx].memWrite = 1;
        memoriaInstrucoes[idx].branch = 0;

        stringstream ss(valorImediato);
        int imediato;
        ss >> imediato;  // Extrai o número imediatamente à esquerda
        int endereco = registradores[registradorOrigem[2] - '0'] + imediato / 4;
        cout << endl << "sw " << registradorOrigem << "[" << imediato << "] = " << registradorDestino << "; PC = PC + 4" << endl;
    }
    else if (instrucao == "lw") {
        memoriaInstrucoes[idx].regDst = 0;
        memoriaInstrucoes[idx].aluSrc = 1;
        memoriaInstrucoes[idx].memToReg = 1;
        memoriaInstrucoes[idx].regWrite = 1;
        memoriaInstrucoes[idx].memRead = 1;
        memoriaInstrucoes[idx].memWrite = 0;
        memoriaInstrucoes[idx].branch = 0;
    } else if (instrucao == "beq") {
        memoriaInstrucoes[idx].regDst = -1;
        memoriaInstrucoes[idx].aluSrc = 0;
        memoriaInstrucoes[idx].memToReg = -1;
        memoriaInstrucoes[idx].regWrite = 0;
        memoriaInstrucoes[idx].memRead = 0;
        memoriaInstrucoes[idx].memWrite = 0;
        memoriaInstrucoes[idx].branch = 1;
    } else if (instrucao == "j") {
        memoriaInstrucoes[idx].regDst = -1;
        memoriaInstrucoes[idx].aluSrc = -1;
        memoriaInstrucoes[idx].memToReg = -1;
        memoriaInstrucoes[idx].regWrite = 0;
        memoriaInstrucoes[idx].memRead = 0;
        memoriaInstrucoes[idx].memWrite = 0;
        memoriaInstrucoes[idx].branch = 0;
    }
}
