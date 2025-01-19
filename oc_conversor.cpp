#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

#define MAX_INSTRUCOES 100
#define MAX_COMANDO 50

// Estrutura para armazenar as instruções e os sinais de controle
struct Instrucao {
    char comando[MAX_COMANDO];
    int regDst, aluSrc, memToReg, regWrite, memRead, memWrite, branch, aluOp;
};

Instrucao memoriaInstrucoes[MAX_INSTRUCOES];
int pc = 0; // Contador de programa (PC)

void processarInstrucoes() {
    for (int i = 0; i < MAX_INSTRUCOES; i++) {
        // Verifica se há instrução
        if (strlen(memoriaInstrucoes[i].comando) == 0) continue;

        std::cout << "Instrucao: " << memoriaInstrucoes[i].comando << std::endl;
        
        // Exibindo os sinais de controle
        std::cout << "Sinais de Controle:" << std::endl;
        std::cout << "RegDst: " << memoriaInstrucoes[i].regDst
                  << ", ALUSrc: " << memoriaInstrucoes[i].aluSrc
                  << ", MemtoReg: " << memoriaInstrucoes[i].memToReg
                  << ", RegWrite: " << memoriaInstrucoes[i].regWrite
                  << ", MemRead: " << memoriaInstrucoes[i].memRead
                  << ", MemWrite: " << memoriaInstrucoes[i].memWrite
                  << ", Branch: " << memoriaInstrucoes[i].branch
                  << ", ALUOp: " << memoriaInstrucoes[i].aluOp
                  << std::endl;

        std::cout << "PC = " << pc << std::endl << std::endl;
        pc += 4; // Atualiza o contador de programa

        // Exemplo: Caso haja algum tipo de operação especial, como alteração na memória ou nos registradores
        if (strstr(memoriaInstrucoes[i].comando, "sw") != nullptr) {
            std::cout << "Alteracao na memoria." << std::endl;
        }

        if (strstr(memoriaInstrucoes[i].comando, "lw") != nullptr) {
            std::cout << "Leitura da memoria." << std::endl;
        }
        
        // Verificar se é um salto (beq, j, etc.)
        if (strstr(memoriaInstrucoes[i].comando, "beq") != nullptr) {
            std::cout << "Salto condicional." << std::endl;
        }
    }
}

void adicionarInstrucao(int idx, const std::string &comando) {
    strcpy(memoriaInstrucoes[idx].comando, comando.c_str());
    
    // Exemplos fictícios de sinais de controle (precisam ser ajustados conforme a lógica MIPS)
    if (comando.find("addi") != std::string::npos) {
        memoriaInstrucoes[idx].regDst = 0;
        memoriaInstrucoes[idx].aluSrc = 1;
        memoriaInstrucoes[idx].memToReg = 0;
        memoriaInstrucoes[idx].regWrite = 1;
        memoriaInstrucoes[idx].memRead = 0;
        memoriaInstrucoes[idx].memWrite = 0;
        memoriaInstrucoes[idx].branch = 0;
        memoriaInstrucoes[idx].aluOp = 10;
    } else if (comando.find("add") != std::string::npos) {
        memoriaInstrucoes[idx].regDst = 1;
        memoriaInstrucoes[idx].aluSrc = 0;
        memoriaInstrucoes[idx].memToReg = 0;
        memoriaInstrucoes[idx].regWrite = 1;
        memoriaInstrucoes[idx].memRead = 0;
        memoriaInstrucoes[idx].memWrite = 0;
        memoriaInstrucoes[idx].branch = 0;
        memoriaInstrucoes[idx].aluOp = 10;
    } else if (comando.find("sw") != std::string::npos) {
        memoriaInstrucoes[idx].regDst = 0;
        memoriaInstrucoes[idx].aluSrc = 1;
        memoriaInstrucoes[idx].memToReg = 0;
        memoriaInstrucoes[idx].regWrite = 0;
        memoriaInstrucoes[idx].memRead = 0;
        memoriaInstrucoes[idx].memWrite = 1;
        memoriaInstrucoes[idx].branch = 0;
        memoriaInstrucoes[idx].aluOp = 00;
    } else if (comando.find("lw") != std::string::npos) {
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
        std::cout << "Uso: " << argv[0] << " <arquivo de entrada>" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cout << "Erro ao abrir o arquivo " << argv[1] << std::endl;
        return 1;
    }

    std::string linha;
    int idx = 0;
    while (std::getline(file, linha) && idx < MAX_INSTRUCOES) {
        // Remover espaços extras
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