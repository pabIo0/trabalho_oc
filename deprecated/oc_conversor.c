#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_INSTRUCOES 100
#define MAX_COMANDO 50

typedef struct {
    char comando[MAX_COMANDO];
    int regDst, aluSrc, memToReg, regWrite, memRead, memWrite, branch, aluOp;
} Instrucao;

Instrucao memoriaInstrucoes[MAX_INSTRUCOES];
int pc = 0;

void processarInstrucoes() {
    for (int i = 0; i < MAX_INSTRUCOES; i++) {
        if (strlen(memoriaInstrucoes[i].comando) == 0) continue;

        printf("Instrucao: %s\n", memoriaInstrucoes[i].comando);
        
        printf("Sinais de Controle:\n");
        printf("RegDst: %d, ALUSrc: %d, MemtoReg: %d, RegWrite: %d, MemRead: %d, MemWrite: %d, Branch: %d, ALUOp: %d\n", 
            memoriaInstrucoes[i].regDst, memoriaInstrucoes[i].aluSrc, memoriaInstrucoes[i].memToReg, 
            memoriaInstrucoes[i].regWrite, memoriaInstrucoes[i].memRead, memoriaInstrucoes[i].memWrite, 
            memoriaInstrucoes[i].branch, memoriaInstrucoes[i].aluOp);
        
        printf("PC = %d\n\n", pc);
        pc += 4;

        if (strstr(memoriaInstrucoes[i].comando, "sw") != NULL) {
            printf("Alteracao na memoria.\n");
        }
        if (strstr(memoriaInstrucoes[i].comando, "lw") != NULL) {
            printf("Leitura da memoria.\n");
        }
        if (strstr(memoriaInstrucoes[i].comando, "beq") != NULL) {
            printf("Salto condicional.\n");
        }
    }
}

void adicionarInstrucao(int idx, const char *comando) {
    strcpy(memoriaInstrucoes[idx].comando, comando);
    
    if (strstr(comando, "addi") != NULL) {
        memoriaInstrucoes[idx].regDst = 1;
        memoriaInstrucoes[idx].aluSrc = 1;
        memoriaInstrucoes[idx].memToReg = 0;
        memoriaInstrucoes[idx].regWrite = 1;
        memoriaInstrucoes[idx].memRead = 0;
        memoriaInstrucoes[idx].memWrite = 0;
        memoriaInstrucoes[idx].branch = 0;
        memoriaInstrucoes[idx].aluOp = 10;
    } else if (strstr(comando, "add") != NULL) {
        memoriaInstrucoes[idx].regDst = 1;
        memoriaInstrucoes[idx].aluSrc = 0;
        memoriaInstrucoes[idx].memToReg = 0;
        memoriaInstrucoes[idx].regWrite = 1;
        memoriaInstrucoes[idx].memRead = 0;
        memoriaInstrucoes[idx].memWrite = 0;
        memoriaInstrucoes[idx].branch = 0;
        memoriaInstrucoes[idx].aluOp = 10;
    } else if (strstr(comando, "sw") != NULL) {
        memoriaInstrucoes[idx].regDst = 0;
        memoriaInstrucoes[idx].aluSrc = 1;
        memoriaInstrucoes[idx].memToReg = 0;
        memoriaInstrucoes[idx].regWrite = 0;
        memoriaInstrucoes[idx].memRead = 0;
        memoriaInstrucoes[idx].memWrite = 1;
        memoriaInstrucoes[idx].branch = 0;
        memoriaInstrucoes[idx].aluOp = 00;
    } else if (strstr(comando, "lw") != NULL) {
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

int main(int argc, char *argv[]) 
{
    if (argc != 2) {
        printf("Uso: %s <arquivo de entrada>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        printf("Erro ao abrir o arquivo %s\n", argv[1]);
        return 1;
    }

    char linha[256];
    int idx = 0;
    while (fgets(linha, sizeof(linha), file) && idx < MAX_INSTRUCOES) {
        linha[strcspn(linha, "\n")] = 0;
        if (strlen(linha) > 0) {
            adicionarInstrucao(idx, linha);
            idx++;
        }
    }

    fclose(file);

    processarInstrucoes();
    return 0;
}
