#include "conversor.h"
#include <iostream>
#include <cstring>
#include <sstream>

using namespace std;

Instrucao memoriaInstrucoes[MAX_INSTRUCOES];
int pc = 0;

void processarInstrucoes() {
    for (int i = 0; i < MAX_INSTRUCOES; i++) {
        if (strlen(memoriaInstrucoes[i].comando) == 0) continue;

        string comando = memoriaInstrucoes[i].comando;
        string operando;
        
        if (comando.find("addi") != string::npos) {
            stringstream ss(comando);
            string instrucao, registradorDestino, registradorOrigem, valorImediato;
            ss >> instrucao >> registradorDestino >> registradorOrigem >> valorImediato;
            cout << instrucao << " " << registradorDestino << " = " << valorImediato << ": PC = PC + 4;" << endl;

        } else if (comando.find("add") != string::npos) {
            stringstream ss(comando);
            string instrucao, registradorDestino, registrador1, registrador2;
            ss >> instrucao >> registradorDestino >> registrador1 >> registrador2;
            cout << instrucao << " " << registradorDestino << " = " << registrador1 << " + " << registrador2 << ": PC = PC + 4;" << endl;

        } else if (comando.find("sub") != string::npos) {
            stringstream ss(comando);
            string instrucao, registradorDestino, registrador1, registrador2;
            ss >> instrucao >> registradorDestino >> registrador1 >> registrador2;
            cout << instrucao << " " << registradorDestino << " = " << registrador1 << " - " << registrador2 << ": PC = PC + 4;" << endl;

        } else if (comando.find("beq") != string::npos) {
            stringstream ss(comando);
            string instrucao, registrador1, registrador2, label;
            ss >> instrucao >> registrador1 >> registrador2 >> label;
            cout << instrucao << " " << registrador1 << " == " << registrador2 << " : PC = PC + 4 (se verdadeiro);" << endl;

        } else if (comando.find("lw") != string::npos) {
            stringstream ss(comando);
            string instrucao, registradorDestino, deslocamento, registradorBase;
            ss >> instrucao >> registradorDestino >> deslocamento >> registradorBase;
            cout << instrucao << " " << registradorDestino << " = Mem[" << registradorBase << " + " << deslocamento << "] : PC = PC + 4;" << endl;

        } else if (comando.find("sw") != string::npos) {
            stringstream ss(comando);
            string instrucao, registradorDestino, deslocamento, registradorBase;
            ss >> instrucao >> registradorDestino >> deslocamento >> registradorBase;
            cout << instrucao << " Mem[" << registradorBase << " + " << deslocamento << "] = " << registradorDestino << ": PC = PC + 4;" << endl;

        } else if (comando.find("j") != string::npos) {
            stringstream ss(comando);
            string instrucao, label;
            ss >> instrucao >> label;
            cout << instrucao << " " << label << ": PC = " << label << ";" << endl;
        }

        cout << "ALUOp: " << (memoriaInstrucoes[i].aluOp == -1 ? "X" : to_string(memoriaInstrucoes[i].aluOp))
            << ", RegDst: " << (memoriaInstrucoes[i].regDst == -1 ? "X" : to_string(memoriaInstrucoes[i].regDst))
            << ", ALUSrc: " << (memoriaInstrucoes[i].aluSrc == -1 ? "X" : to_string(memoriaInstrucoes[i].aluSrc))
            << ", MemtoReg: " << (memoriaInstrucoes[i].memToReg == -1 ? "X" : to_string(memoriaInstrucoes[i].memToReg))
            << ", Reg-Write: " << (memoriaInstrucoes[i].regWrite == -1 ? "X" : to_string(memoriaInstrucoes[i].regWrite))
            << ", Mem-Read: " << (memoriaInstrucoes[i].memRead == -1 ? "X" : to_string(memoriaInstrucoes[i].memRead))
            << ", Mem-Write: " << (memoriaInstrucoes[i].memWrite == -1 ? "X" : to_string(memoriaInstrucoes[i].memWrite))
            << ", Branch: " << (memoriaInstrucoes[i].branch == -1 ? "X" : to_string(memoriaInstrucoes[i].branch))
            << endl;


        cout << "PC = " << pc << endl << endl;

        pc += 4; 
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
    } else if (comando.find("sub") != string::npos) {
        memoriaInstrucoes[idx].regDst = 1;
        memoriaInstrucoes[idx].aluSrc = 0;
        memoriaInstrucoes[idx].memToReg = 0;
        memoriaInstrucoes[idx].regWrite = 1;
        memoriaInstrucoes[idx].memRead = 0;
        memoriaInstrucoes[idx].memWrite = 0;
        memoriaInstrucoes[idx].branch = 0;
        memoriaInstrucoes[idx].aluOp = 10;
    } else if (comando.find("beq") != string::npos) {
        memoriaInstrucoes[idx].regDst = -1;
        memoriaInstrucoes[idx].aluSrc = 0;
        memoriaInstrucoes[idx].memToReg = -1;
        memoriaInstrucoes[idx].regWrite = 0;
        memoriaInstrucoes[idx].memRead = 0;
        memoriaInstrucoes[idx].memWrite = 0;
        memoriaInstrucoes[idx].branch = 1;
        memoriaInstrucoes[idx].aluOp = 01;
    } else if (comando.find("lw") != string::npos) {
        memoriaInstrucoes[idx].regDst = 0;
        memoriaInstrucoes[idx].aluSrc = 1;
        memoriaInstrucoes[idx].memToReg = 1;
        memoriaInstrucoes[idx].regWrite = 1;
        memoriaInstrucoes[idx].memRead = 1;
        memoriaInstrucoes[idx].memWrite = 0;
        memoriaInstrucoes[idx].branch = 0;
        memoriaInstrucoes[idx].aluOp = 00;
    } else if (comando.find("sw") != string::npos) {
        memoriaInstrucoes[idx].regDst = -1;
        memoriaInstrucoes[idx].aluSrc = 1;
        memoriaInstrucoes[idx].memToReg = -1;
        memoriaInstrucoes[idx].regWrite = 0;
        memoriaInstrucoes[idx].memRead = 0;
        memoriaInstrucoes[idx].memWrite = 1;
        memoriaInstrucoes[idx].branch = 0;
        memoriaInstrucoes[idx].aluOp = 00;
    } else if (comando.find("j") != string::npos) {
        memoriaInstrucoes[idx].regDst = -1;
        memoriaInstrucoes[idx].aluSrc = -1;
        memoriaInstrucoes[idx].memToReg = -1;
        memoriaInstrucoes[idx].regWrite = 0;
        memoriaInstrucoes[idx].memRead = 0;
        memoriaInstrucoes[idx].memWrite = 0;
        memoriaInstrucoes[idx].branch = 0;
        memoriaInstrucoes[idx].aluOp = -1;
    }
}
