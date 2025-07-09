#ifndef SEARCH_VIEW                        
#define SEARCH_VIEW

int scan_choice1();
int scan_choice2();
int scan_choice3();
void scan_choice1_input(char* msg, char* dest);
unsigned int scan_choice2_input(char* msg);
void scan_choice2_update(char* cpf, char* nome, char* idade, char* data_registro);
void id_not_found_choice2();
void choice2_update_ok();
void choice2_update_fail();
void choice3_update_ok();
void choice3_update_fail();
int choice3_remove();
void scan_choice4(char* cpf, char* nome, char* idade, char* data_registro);
void choice4_ok();
void choice4_fail();
#endif