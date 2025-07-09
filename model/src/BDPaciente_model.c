// Proteção contra múltiplas inclusões
#ifndef BDPACIENTE_MODEL
#define BDPACIENTE_MODEL

// Definições de tamanho de buffer e tamanho da página, caso ainda não tenham sido definidas
#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1000
#endif

#ifndef PAGE_SIZE
#define PAGE_SIZE 20
#endif

// Inclusões de bibliotecas padrão
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// Inclusão de tipos personalizados (como `Bool`, `uint`, etc.)
#include "../../types/header/types.h"

// Inclusão do modelo de paciente (definição de `Paciente`, `paciente_init`, etc.)
#include "../header/Paciente_model.h"

// Estrutura que representa a conexão com o "banco de dados" (um arquivo CSV)
struct bdpaciente {
    char _filename[BUFFER_SIZE]; // Nome do arquivo
    uint n_records;              // Número de registros no arquivo
    uint n_pages;                // Número de páginas com base em PAGE_SIZE
};

// Estrutura que representa um registro individual
struct records {
    uint id;                     // Identificador do registro
    Paciente* paciente;          // Ponteiro para estrutura com dados do paciente
    char data_cadastro[11];      // Data de cadastro no formato "DD/MM/AAAA"
    Bool end_of_record;          // Flag para indicar fim dos registros
};

// Tipos definidos para facilitar o uso
typedef struct bdpaciente BDPaciente;
typedef struct records Records;

//
// Funções auxiliares para lidar com arquivos
//

// Verifica se o arquivo existe
Bool file_exists(char* filename) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL)
        return False;

    fclose(file);
    return True;
}

// Cria um novo arquivo vazio
Bool create_empty_file(char* filename) {
    FILE* file = fopen(filename, "wb");
    if(file == NULL)
        return False;
    
    fclose(file);
    return True;
}

Bool str_comp_prefix(char* str, char* str_prefix) {
    int i;
    char* str_cpy = (char *) malloc((strlen(str) + 1) * sizeof(char));
    if(str_cpy == NULL)
        return False;
    
    char* str_prefix_cpy = (char *) malloc((strlen(str_prefix) + 1) * sizeof(char));
    if(str_prefix_cpy == NULL) {
        free(str_cpy);
        return False;
    }

    for(i = 0; i < strlen(str_prefix); i++) {
        str_prefix_cpy[i] = str_prefix[i];
        if((str_prefix_cpy[i] >= 'A') && (str_prefix_cpy[i] <= 'Z')) {
            str_prefix_cpy[i] += 32;
        }
    }
    str_prefix_cpy[i] = '\0';

    for(i = 0; i < strlen(str); i++) {
        str_cpy[i] = str[i];
        if((str_cpy[i] >= 'A') && (str_cpy[i] <= 'Z')) {
            str_cpy[i] += 32;
        }
    }
    str_cpy[i] = '\0';

    if(strlen(str_prefix_cpy) > strlen(str_cpy))
        return False;

    for(i = 0; i < strlen(str_prefix_cpy); i++) {
        if(str_prefix_cpy[i] != str_cpy[i]) {
            free(str_prefix_cpy);
            free(str_cpy);
            return False;
        }
    }

    free(str_prefix_cpy);
    free(str_cpy);
    return True;
}

// Conecta ao "banco de dados" (abre arquivo, conta registros e calcula número de páginas)
BDPaciente* db_connect(char* filename){
    Bool r;
    FILE* db_file;
    BDPaciente* connection;

    // Buffers temporários para ler o cabeçalho e dados
    char buffer_id[BUFFER_SIZE];
    char buffer_cpf[BUFFER_SIZE];
    char buffer_nome[BUFFER_SIZE];
    char buffer_idade[BUFFER_SIZE];
    char buffer_data_cadastro[BUFFER_SIZE];

    // Se o arquivo não existir, tenta criá-lo vazio
    r = file_exists(filename);
    if (!r){
        r = create_empty_file(filename);
        if (!r)
            return NULL;
    }

    // Aloca memória para a estrutura de conexão
    connection = (BDPaciente*) malloc(sizeof(BDPaciente));
    if(connection == NULL)
        return NULL;

    // Inicializa atributos da conexão
    strcpy(connection->_filename, filename);
    connection->n_records = 0;
    connection->n_pages = 0;

    // Abre arquivo para leitura
    db_file = fopen(filename, "r");
    if(db_file == NULL) {
        free(connection);
        return NULL;
    }

    // Lê o cabeçalho do arquivo (primeira linha)
    if(fscanf(db_file, "%[^,],%[^,],%[^,],%[^,],%[^,\n]%*c", buffer_id, buffer_cpf, buffer_nome, buffer_idade, buffer_data_cadastro) != 5) {
        fclose(db_file);
        return connection;  // Arquivo está vazio, mas retorna a conexão válida
    }

    // Conta quantas linhas (registros) existem
    while(fscanf(db_file, "%[^,],%[^,],%[^,],%[^,],%[^,\n]%*c", buffer_id, buffer_cpf, buffer_nome, buffer_idade, buffer_data_cadastro) == 5){
        connection->n_records++;
    }

    fclose(db_file);

    // Calcula número de páginas com base em PAGE_SIZE
    connection->n_pages = (connection->n_records) / ((uint) PAGE_SIZE);
    if((connection->n_records % ((uint) PAGE_SIZE)) != 0)
        connection->n_pages++;

    return connection;
}

// Libera a memória alocada para a conexão
void db_close(BDPaciente* connection) {
    free(connection);
}

//
// Lê os registros de uma página específica e retorna um array de `Records`
//

Records* list_records(BDPaciente* connection, uint page) {
    Records* array;
    FILE* db_file;
    uint i, j;
    uint size;

    // Buffers para armazenar os dados de cada campo, para até PAGE_SIZE registros
    char buffer_id[PAGE_SIZE][BUFFER_SIZE];
    char buffer_cpf[PAGE_SIZE][BUFFER_SIZE];
    char buffer_nome[PAGE_SIZE][BUFFER_SIZE];
    char buffer_idade[PAGE_SIZE][BUFFER_SIZE];
    char buffer_data_cadastro[PAGE_SIZE][BUFFER_SIZE];

    // Se a página solicitada for inválida, retorna um array com um único registro vazio
    if(page > connection->n_pages) {
        array = (Records*) malloc(sizeof(Records));
        if(array == NULL)
            return NULL;

        array->id = 0;
        array->paciente = NULL;
        array->end_of_record = True;
        return array;
    }

    // Abre o arquivo
    db_file = fopen(connection->_filename, "r");
    if(db_file == NULL)
        return NULL;

    // Lê e ignora o cabeçalho
    if (fscanf(db_file, "%[^,],%[^,],%[^,],%[^,],%[^,\n]%*c", buffer_id[0], buffer_cpf[0], buffer_nome[0], buffer_idade[0], buffer_data_cadastro[0]) != 5) {
        fclose(db_file);
        return NULL;
    }

    // Avança o cursor até o início da página desejada
    for(i = 0; i < page - 1; i++) 
        for(j = 0; j < PAGE_SIZE; j++) 
            if(fscanf(db_file, "%[^,],%[^,],%[^,],%[^,],%[^,\n]%*c", buffer_id[0], buffer_cpf[0], buffer_nome[0], buffer_idade[0], buffer_data_cadastro[0]) != 5)
                break;

    // Lê os registros da página atual
    for(j = 0; j < PAGE_SIZE; j++)
        if(fscanf(db_file, "%[^,],%[^,],%[^,],%[^,],%[^,\n]%*c", buffer_id[j], buffer_cpf[j], buffer_nome[j], buffer_idade[j], buffer_data_cadastro[j]) != 5)
            break;

    size = j;
    fclose(db_file);

    // Aloca memória para os registros + um marcador de fim
    array = (Records*) malloc((size + 1) * sizeof(Records));
    if(array == NULL)
        return NULL;

    // Inicializa os registros lidos
    for(j = 0; j < size; j++) {
        array[j].id = (uint) atoi(buffer_id[j]);
        array[j].paciente = paciente_init(buffer_nome[j], buffer_cpf[j], buffer_idade[j]);

        // Caso falhe ao inicializar paciente, libera os anteriores e retorna erro
        if(array[j].paciente == NULL) {
            for(i = 0; i < j; i++)
                paciente_free(array[i].paciente);
            free(array);
            return NULL;
        }

        strcpy(array[j].data_cadastro, buffer_data_cadastro[j]);
        array[j].end_of_record = False;
    }

    // Marca o fim do array com um registro especial
    array[size].id = 0;
    array[size].paciente = NULL;
    array[size].end_of_record = True;

    return array;
}


Records* list_records_by_nome(BDPaciente* connection, char* nome) {
    Records* array = (Records*) malloc((connection->n_records + 2) * sizeof(Records));
    if(array == NULL)
        return NULL;

    FILE* db_file;
    uint i, j, k;

    char buffer_id[BUFFER_SIZE];
    char buffer_cpf[BUFFER_SIZE];
    char buffer_nome[BUFFER_SIZE];
    char buffer_idade[BUFFER_SIZE];
    char buffer_data_cadastro[BUFFER_SIZE];

    db_file = fopen(connection->_filename, "r");
    if(db_file == NULL)
        return NULL;

    if (fscanf(db_file, "%[^,],%[^,],%[^,],%[^,],%[^,\n]%*c", buffer_id, buffer_cpf, buffer_nome, buffer_idade, buffer_data_cadastro) != 5) {
        fclose(db_file);
        return NULL;
    }

    j = 0;
    for(i = 0; i < connection->n_records; i++) {
        if(fscanf(db_file, "%[^,],%[^,],%[^,],%[^,],%[^,\n]%*c", buffer_id, buffer_cpf, buffer_nome, buffer_idade, buffer_data_cadastro) != 5)
            break;
        
        if(str_comp_prefix(buffer_nome, nome)){
            array[j].id = (uint) atoi(buffer_id);
            array[j].paciente = paciente_init(buffer_nome, buffer_cpf, buffer_idade);

            if(array[j].paciente == NULL) {
                for(k = 0; k < j; k++)
                    paciente_free(array[k].paciente);
                free(array);
                return NULL;
            }

            strcpy(array[j].data_cadastro, buffer_data_cadastro);
            array[j].end_of_record = False;
            j++;
        }
    }

    fclose(db_file);

    // Marca o fim do array com um registro especial
    array[j].id = 0;
    array[j].paciente = NULL;
    array[j].end_of_record = True;

    return array;
}


Records* list_records_by_cpf(BDPaciente* connection, char* cpf) {
    Records* array = (Records*) malloc((connection->n_records + 2) * sizeof(Records));
    if(array == NULL)
        return NULL;

    FILE* db_file;
    uint i, j, k;

    char buffer_id[BUFFER_SIZE];
    char buffer_cpf[BUFFER_SIZE];
    char buffer_nome[BUFFER_SIZE];
    char buffer_idade[BUFFER_SIZE];
    char buffer_data_cadastro[BUFFER_SIZE];

    db_file = fopen(connection->_filename, "r");
    if(db_file == NULL)
        return NULL;

    if (fscanf(db_file, "%[^,],%[^,],%[^,],%[^,],%[^,\n]%*c", buffer_id, buffer_cpf, buffer_nome, buffer_idade, buffer_data_cadastro) != 5) {
        fclose(db_file);
        return NULL;
    }

    j = 0;
    for(i = 0; i < connection->n_records; i++) {
        if(fscanf(db_file, "%[^,],%[^,],%[^,],%[^,],%[^,\n]%*c", buffer_id, buffer_cpf, buffer_nome, buffer_idade, buffer_data_cadastro) != 5)
            break;
        
        if(str_comp_prefix(buffer_cpf, cpf)){
            array[j].id = (uint) atoi(buffer_id);
            array[j].paciente = paciente_init(buffer_nome, buffer_cpf, buffer_idade);

            if(array[j].paciente == NULL) {
                for(k = 0; k < j; k++)
                    paciente_free(array[k].paciente);
                free(array);
                return NULL;
            }

            strcpy(array[j].data_cadastro, buffer_data_cadastro);
            array[j].end_of_record = False;
            j++;
        }
    }

    fclose(db_file);

    // Marca o fim do array com um registro especial
    array[j].id = 0;
    array[j].paciente = NULL;
    array[j].end_of_record = True;

    return array;
}


Bool write_db_by_records(BDPaciente* connection, Records* records) {
    int i = 0;
    char* cpf;
    FILE* f = fopen(connection->_filename, "w");
    if(f == NULL)
        return False;

    fprintf(f, "Id,CPF,Nome,Idade,Data_Cadastro");
    while(!records[i].end_of_record) {
        cpf = cpf2string(records[i].paciente->cpf);

        fprintf(f, "\n%u,%s,%s,%u,%s", 
            records[i].id,
            cpf,
            records[i].paciente->nome,
            ((uint) records[i].paciente->idade),
            records[i].data_cadastro
        );
        free(cpf);
        i++;
    }

    fclose(f);
    return True;
}
#endif
