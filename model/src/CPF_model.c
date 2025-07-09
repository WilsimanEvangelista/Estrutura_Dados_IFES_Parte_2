#ifndef CPF_MODEL
#define CPF_MODEL

// Inclusão das bibliotecas padrão necessárias
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Estrutura que representa um CPF dividido em partes
struct cpf {
    char p1[4];  // Primeiros 3 dígitos do CPF + caractere nulo '\0'
    char p2[4];  // Segundos 3 dígitos + '\0'
    char p3[4];  // Terceiros 3 dígitos + '\0'
    char dv[3];  // Dígito verificador (2 dígitos) + '\0'
};

typedef struct cpf CPF;

// Função para inicializar um CPF a partir de uma string formatada (XXX.XXX.XXX-YY)
CPF* cpf_init(char* cpf) {
    CPF* s_cpf;

    // Verifica se a string passada tem pelo menos 14 caracteres (formato esperado: XXX.XXX.XXX-YY)
    if(strlen(cpf) < 14)
        return NULL;

    // Aloca memória para a struct CPF
    s_cpf = (CPF*) malloc(sizeof(CPF));
    if(s_cpf == NULL)
        return NULL;

    // Copia os primeiros 3 dígitos (índices 0-2)
    s_cpf->p1[0] = cpf[0];
    s_cpf->p1[1] = cpf[1];
    s_cpf->p1[2] = cpf[2];
    s_cpf->p1[3] = '\0';

    // Copia os segundos 3 dígitos (índices 4-6, pulando o ponto)
    s_cpf->p2[0] = cpf[4];
    s_cpf->p2[1] = cpf[5];
    s_cpf->p2[2] = cpf[6];
    s_cpf->p2[3] = '\0';

    // Copia os terceiros 3 dígitos (índices 8-10, pulando o segundo ponto)
    s_cpf->p3[0] = cpf[8];
    s_cpf->p3[1] = cpf[9];
    s_cpf->p3[2] = cpf[10];
    s_cpf->p3[3] = '\0';

    // Copia os 2 dígitos verificadores (índices 12-13, pulando o hífen)
    s_cpf->dv[0] = cpf[12];
    s_cpf->dv[1] = cpf[13];
    s_cpf->dv[2] = '\0';

    return s_cpf;
}

// Libera a memória alocada para a struct CPF
void cpf_free(CPF* cpf) {
    free(cpf);
}

// Converte a struct CPF de volta para a string formatada "XXX.XXX.XXX-YY"
char* cpf2string(CPF* cpf) {
    // Aloca espaço para 14 caracteres + '\0' = 15
    char* sCPF = (char*) malloc(15 * sizeof(char));
    if(sCPF == NULL)
        return NULL;

    // Formata os dados do struct na forma "XXX.XXX.XXX-YY"
    sCPF[0] = cpf->p1[0];
    sCPF[1] = cpf->p1[1];
    sCPF[2] = cpf->p1[2];
    sCPF[3] = '.';
    sCPF[4] = cpf->p2[0];
    sCPF[5] = cpf->p2[1];
    sCPF[6] = cpf->p2[2];
    sCPF[7] = '.';
    sCPF[8] = cpf->p3[0];
    sCPF[9] = cpf->p3[1];
    sCPF[10] = cpf->p3[2];
    sCPF[11] = '-';
    sCPF[12] = cpf->dv[0];
    sCPF[13] = cpf->dv[1];
    sCPF[14] = '\0';

    return sCPF;
}

#endif
