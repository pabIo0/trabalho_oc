#ifndef CONVERSOR_H
#define CONVERSOR_H

#include <string>

#define MAX_INSTRUCOES 100
#define MAX_COMANDO 50

struct Instrucao {
    char comando[MAX_COMANDO];
    int regDst, aluSrc, memToReg, regWrite, memRead, memWrite, branch, aluOp;
    int registradorDestino, registradorOrigem, valorImediato, pcAlterado; 
};

int registradores[32] = {0};

void processarInstrucoes();
void operacaoRegistradores(const std::string &instrucao, const std::string &registradorDestino, const std::string &registradorOrigem, const std::string &valorImediato, const std::string &label);
void adicionarInstrucao(int idx, const std::string &comando);
void converteInstrucaoParaBinario(int idx, const std::string &comando);
void exibirRelatorio(int idx);

#endif
