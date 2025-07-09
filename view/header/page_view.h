#ifndef PAGE_VIEW
#define PAGE_VIEW

#ifndef STRING_SIZE
#define STRING_SIZE 30
#endif

#include "../../types/header/types.h"

void print_page(uint n_pages);
int scan_page(uint n_pages);
void print_header();
void print_record(uint id, char* cpf, char* nome, uint idade, char* data_cadastro);
void print_no_records();

#endif