#ifndef CPF_MODEL
#define CPF_MODEL

struct cpf {
    char p1[4];
    char p2[4];
    char p3[4];
    char dv[3];
};

typedef struct cpf CPF;


CPF* cpf_init(char* cpf);
void cpf_free(CPF* cpf);
char* cpf2string(CPF* cpf);

#endif