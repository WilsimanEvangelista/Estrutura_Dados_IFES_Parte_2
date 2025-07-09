#ifndef PACIENTE_MODEL
#define PACIENTE_MODEL

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1000
#endif

#include "../header/CPF_model.h"
#include "../../types/header/types.h"

struct paciente {
    char nome[BUFFER_SIZE];
    CPF* cpf;
    utinyint idade;
};
typedef struct paciente Paciente;

Paciente* paciente_init(char* nome, char* cpf, char* idade);
void paciente_free(Paciente* paciente);

#endif