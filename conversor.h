#ifndef CONVERSOR_H
#define CONVERSOR_H

#include <string>

#define MAX_INSTRUCOES 100
#define MAX_COMANDO 50

using namespace std;

struct Instrucao {
    char comando[MAX_COMANDO];
    int regDst, aluSrc, memToReg, regWrite, memRead, memWrite, branch, aluOp;
    int registradorDestino, registradorOrigem, valorImediato, pcAlterado; 
};

int registradores[32] = {0};

void processarInstrucoes();
void operacaoRegistradores(const string &instrucao, const string &registradorDestino, const string &registradorOrigem, const string &valorImediato, const string &label);
void adicionarInstrucao(int idx, const string &comando);
void converteInstrucaoParaBinario(int idx, const string &comando);
void exibirRelatorio(int idx);

#endif
