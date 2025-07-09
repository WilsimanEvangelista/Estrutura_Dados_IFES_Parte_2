#ifndef PACIENTE_MODEL
#define PACIENTE_MODEL

// Define BUFFER_SIZE se ainda não estiver definido
#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1000
#endif

// Inclusão das bibliotecas padrão necessárias
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Inclusão do modelo de CPF e tipos auxiliares
#include "../header/CPF_model.h"
#include "../../types/header/types.h"

// Definição da estrutura que representa um paciente
struct paciente {
    char nome[BUFFER_SIZE]; // Nome do paciente (tamanho máximo: 254 caracteres + '\0')
    CPF* cpf;               // Ponteiro para a estrutura CPF
    utinyint idade;         // Idade (tipo definido em types.h, possivelmente equivalente a uint8_t)
};

typedef struct paciente Paciente; // Alias para facilitar uso da struct

// Função que inicializa uma instância de Paciente com nome, cpf (string) e idade (string)
Paciente* paciente_init(char* nome, char* cpf, char* idade) {
    Paciente* paciente;

    // Aloca memória para a estrutura Paciente
    paciente = (Paciente*) malloc(sizeof(Paciente));
    if(paciente == NULL)
        return NULL;

    // Inicializa o CPF a partir da string formatada
    paciente->cpf = cpf_init(cpf);
    if(paciente->cpf == NULL) {
        free(paciente); // Libera a memória caso a inicialização do CPF falhe
        return NULL;
    }

    // Converte a string idade para inteiro e atribui à estrutura
    paciente->idade = atoi(idade);

    // Copia o nome para a estrutura (assume que nome já é menor que BUFFER_SIZE)
    strcpy(paciente->nome, nome);

    return paciente;
}

// Função para liberar a memória de um paciente
void paciente_free(Paciente* paciente) {
    cpf_free(paciente->cpf); // Libera a memória alocada para o CPF
    free(paciente);          // Libera a memória alocada para o Paciente
}

#endif
