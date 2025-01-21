#ifndef CONVERSOR_H
#define CONVERSOR_H

#include <string>

#define MAX_INSTRUCOES 100
#define MAX_COMANDO 50

struct Instrucao {
    char comando[MAX_COMANDO];
    int regDst, aluSrc, memToReg, regWrite, memRead, memWrite, branch, aluOp;
};

void processarInstrucoes();
void adicionarInstrucao(int idx, const std::string &comando);

#endif
