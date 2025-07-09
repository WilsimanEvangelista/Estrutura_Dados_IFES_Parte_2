// Verifica se o identificador CHOICE4_CONTROLLER já foi definido anteriormente
// Isso evita inclusões múltiplas do mesmo arquivo de cabeçalho
#ifndef CHOICE4_CONTROLLER
#define CHOICE4_CONTROLLER

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../../view/header/search_view.h"

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1000
#endif


// Inclusão do modelo de acesso ao banco de dados de pacientes
#include "../../model/header/BDPaciente_model.h"

// Inclusão de visualizações de erro e página
#include "../../view/header/open_db_error_view.h"
#include "../../view/header/page_view.h"

// Define a função `choice4_controller` que recebe como parâmetro o nome de um arquivo de banco de dados (db_filename)
// Essa função atualmente apenas imprime uma mensagem indicando que não foi implementada
void choice4_controller(char* db_filename) {
    // Conecta ao banco de dados usando o nome de arquivo fornecido
    BDPaciente* connection = db_connect(db_filename);
    Records* records;       // Estrutura que armazena os registros
    char* cpf;              // String temporária para armazenar o CPF formatado
    char nome[BUFFER_SIZE];
    char idade[BUFFER_SIZE];
    char data[BUFFER_SIZE];
    uint i, j;              // Índice para percorrer os registros da página
    uint id;
    Bool find_reg, ok;

    int choice;
    char input[BUFFER_SIZE];

    // Verifica se a conexão com o banco foi bem-sucedida
    if(connection == NULL) {
        print_open_db_error();  // Exibe erro de abertura de banco
        return;                 // Encerra a função
    }

    records = list_records_by_cpf(connection, "");

    cpf = (char*) malloc(15 * sizeof(char));
    scan_choice4(cpf, nome, idade, data);
    if(cpf[3] != '.') {
        cpf[strlen(cpf) + 1] = '\0';
        for(j = strlen(cpf); j > 3; j--) {
            cpf[j] = cpf[j - 1];
        }
        cpf[3] = '.';
    }

    if(cpf[7] != '.') {
        cpf[strlen(cpf) + 1] = '\0';
        for(j = strlen(cpf); j > 7; j--) {
            cpf[j] = cpf[j - 1];
        }
        cpf[7] = '.';
    }

    if(cpf[11] != '-') {
        cpf[strlen(cpf) + 1] = '\0';
        for(j = strlen(cpf); j > 11; j--) {
            cpf[j] = cpf[j - 1];
        }
        cpf[11] = '-';
    }

    i = 0;
    while(!(records[i].end_of_record)) {
        i++;
        printf("%d\n", i);
    }

    printf("\n\nAQUI 1\n\n");
    records[i + 1].end_of_record = True;
    printf("\n\nAQUI 2\n\n");
    records[i].end_of_record = False;
    printf("\n\nAQUI 3\n\n");
    strcpy(records[i].data_cadastro, data);
    printf("\n\nAQUI 4\n\n");
    records[i].id = records[i - 1].id + 1;
    printf("\n\nAQUI 5\n\n");
    records[i].paciente = paciente_init(nome, cpf, idade);
    printf("\n\nAQUI 6\n\n");
    
    free(cpf);

    ok = write_db_by_records(connection, records);
    if(ok) {
        choice4_ok();
    } else {
        choice4_fail();
    }
    
    free(records);
    // Fecha a conexão com o banco de dados
    db_close(connection);
}

// Fim da diretiva de inclusão condicional
#endif