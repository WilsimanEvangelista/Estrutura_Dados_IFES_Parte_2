// Proteção contra múltiplas inclusões do cabeçalho
#ifndef CHOICE5_CONTROLLER
#define CHOICE5_CONTROLLER

// Bibliotecas padrão
#include <stdlib.h>  // Para funções de alocação e liberação de memória (ex: free)
#include <stdio.h>   // Para printf, etc.

// Inclusão do modelo de acesso ao banco de dados de pacientes
#include "../../model/header/BDPaciente_model.h"

// Inclusão de visualizações de erro e página
#include "../../view/header/open_db_error_view.h"
#include "../../view/header/page_view.h"

// Função responsável por controlar a funcionalidade da "opção 5" no menu principal
void choice5_controller(char* db_filename) {
    // Conecta ao banco de dados usando o nome de arquivo fornecido
    BDPaciente* connection = db_connect(db_filename);
    Records* page_records;  // Estrutura que armazena os registros da página atual
    char* cpf;              // String temporária para armazenar o CPF formatado
    int page;               // Página que o usuário deseja visualizar
    uint i;                 // Índice para percorrer os registros da página
    
    // Verifica se a conexão com o banco foi bem-sucedida
    if(connection == NULL) {
        print_open_db_error();  // Exibe erro de abertura de banco
        return;                 // Encerra a função
    }

    // Mostra ao usuário a quantidade de páginas e solicita que ele selecione uma
    print_page(connection->n_pages);
    page = scan_page(connection->n_pages);

    // Enquanto o usuário não digitar -1 (condição de saída), continua exibindo páginas
    while(page != -1) {
        // Obtém os registros da página selecionada
        page_records = list_records(connection, ((uint) page));
        if(page_records == NULL) {
            print_open_db_error();  // Caso haja erro na leitura dos registros
            return;
        }

        i = 0;
        print_header();  // Exibe cabeçalho dos registros

        // Percorre os registros da página até encontrar o marcador de fim
        while(!(page_records[i].end_of_record)) {
            // Converte o CPF binário para string formatada (ex: "123.456.789-00")
            cpf = cpf2string(page_records[i].paciente->cpf);

            // Imprime os dados do paciente no formato correto
            print_record(
                page_records[i].id,
                cpf,
                page_records[i].paciente->nome,
                ((uint) page_records[i].paciente->idade),
                page_records[i].data_cadastro
            );

            // Libera a memória alocada para o CPF string
            free(cpf);
            i++;
        }

        // Caso não haja registros na página
        if(i == 0) {
            print_no_records();
        }

        // Solicita nova página para visualização
        free(page_records);
        print_page(connection->n_pages);
        page = scan_page(connection->n_pages);
    }

    // Fecha a conexão com o banco de dados
    db_close(connection);
}

#endif
