// Verifica se o identificador CHOICE3_CONTROLLER já foi definido anteriormente
// Isso evita inclusões múltiplas do mesmo arquivo de cabeçalho
#ifndef CHOICE3_CONTROLLER
#define CHOICE3_CONTROLLER

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

// Define a função `choice3_controller` que recebe como parâmetro o nome de um arquivo de banco de dados (db_filename)
// Essa função atualmente apenas imprime uma mensagem indicando que não foi implementada
void choice3_controller(char* db_filename) {
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

    choice = scan_choice3();
    while(choice != -1) {
        if(choice == 3) {
            records = list_records_by_cpf(connection, "");

            // Obtém os registros da página selecionada
            if(records == NULL) {
                print_open_db_error();  // Caso haja erro na leitura dos registros
                return;
            }

            id = scan_choice2_input("Digite o ID do paciente a ser removido: ");
            i = 0;
            find_reg = False;
            while(!(records[i].end_of_record)) {
                if(records[i].id == id) {
                    find_reg = True;
                    break;
                }

                i++;
            }

            if(find_reg) {
                ok = (Bool) choice3_remove();
                if(ok) {
                    cpf_free(records[i].paciente->cpf);
                    free(records[i].paciente);

                    j = i;
                    while(!(records[j].end_of_record)) {
                        records[j] = records[j + 1];
                        j++;
                    }

                    ok = write_db_by_records(connection, records);
                    if(ok) {
                        choice3_update_ok();
                    } else {
                        choice3_update_fail();
                    }
                }

            } else {
                id_not_found_choice2();
            }

        } else {
            if(choice == 1) {
                // CPF
                scan_choice1_input("Digite o CPF a ser consultado: ", input);
                records = list_records_by_cpf(connection, input);
            } else {
                // Nome
                scan_choice1_input("Digite o Nome a ser consultado: ", input);
                records = list_records_by_nome(connection, input);
            }
            
            // Obtém os registros da página selecionada
            if(records == NULL) {
                print_open_db_error();  // Caso haja erro na leitura dos registros
                return;
            }

            i = 0;
            print_header();  // Exibe cabeçalho dos registros
            // Percorre os registros da página até encontrar o marcador de fim
            while(!(records[i].end_of_record)) {
                // Converte o CPF binário para string formatada (ex: "123.456.789-00")
                cpf = cpf2string(records[i].paciente->cpf);

                // Imprime os dados do paciente no formato correto
                print_record(
                    records[i].id,
                    cpf,
                    records[i].paciente->nome,
                    ((uint) records[i].paciente->idade),
                    records[i].data_cadastro
                );

                // Libera a memória alocada para o CPF string
                free(cpf);
                i++;
            }

            // Caso não haja registros na página
            if(i == 0) {
                print_no_records();
            }
        }
        
        free(records);
        choice = scan_choice3();   
    }

    // Fecha a conexão com o banco de dados
    db_close(connection);
}

// Fim da diretiva de inclusão condicional
#endif