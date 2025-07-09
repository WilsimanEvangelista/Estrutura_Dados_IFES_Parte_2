#ifndef BDPACIENTE_MODEL
#define BDPACIENTE_MODEL

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1000
#endif
#ifndef PAGE_SIZE
#define PAGE_SIZE 20
#endif

#include "../../types/header/types.h"
#include "../header/Paciente_model.h"

struct bdpaciente {
    char _filename[BUFFER_SIZE];
    uint n_records;
    uint n_pages;
};

struct records {
    uint id;
    Paciente* paciente;
    char data_cadastro[11];
    Bool end_of_record;
};

typedef struct bdpaciente BDPaciente;
typedef struct records Records;

BDPaciente* db_connect(char* filename);
void db_close(BDPaciente* connection);
Records* list_records(BDPaciente* connection, uint page);
Records* list_records_by_cpf(BDPaciente* connection, char* cpf);
Records* list_records_by_nome(BDPaciente* connection, char* nome);
Bool write_db_by_records(BDPaciente* connection, Records* records);

#endif