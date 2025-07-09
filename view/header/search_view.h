#ifndef SEARCH_VIEW                        
#define SEARCH_VIEW

int scan_choice1();
int scan_choice2();
void scan_choice1_input(char* msg, char* dest);
unsigned int scan_choice2_input(char* msg);
void scan_choice2_update(char* cpf, char* nome, char* idade, char* data_registro);
void id_not_found_choice2();
void choice2_update_ok();
void choice2_update_fail();
#endif