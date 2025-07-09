#ifndef SEARCH_VIEW                        // Diretiva para evitar múltiplas inclusões do mesmo arquivo
#define SEARCH_VIEW

#include <string.h>
#include <stdio.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1000
#endif

int scan_choice1() {
    int choice;
    char garb;

    printf("Deseja consultar por:\n\t(1) - CPF;\n\t(2) - Nome;\n\t(-1) - Voltar para o menu inicial;\nDIGITE A SUA ESCOLHA: ");
    scanf("%d", &choice);
    // Limpando o stdin
    garb = getchar();
    while((garb != '\n') && (garb != EOF)) {
        garb = getchar();
    }


    if(choice == -1) {
        return -1;
    }    

    if (choice <= 0) {
        printf("A ESCOLHA DEVE SER UM NUMERO POSITIVO!\n\n--------------------------------------------------\n\n");
        return scan_choice1();
    }

    if (choice > 2) {
        printf("A ESCOLHA DEVE SER MENOR OU IGUAL A 2!\n\n--------------------------------------------------\n\n");
        return scan_choice1();
    }

    return choice;
}


int scan_choice2() {
    int choice;
    char garb;

    printf("O que deseja fazer?\n\t(1) - Consultar por CPF;\n\t(2) - Consultar por Nome;\n\t(3) - Atualizar Paciente por ID;\n\t(-1) - Voltar para o menu inicial;\nDIGITE A SUA ESCOLHA: ");
    scanf("%d", &choice);
    garb = getchar();
    while((garb != '\n') && (garb != EOF)) {
        garb = getchar();
    }


    if(choice == -1) {
        return -1;
    }    

    if (choice <= 0) {
        printf("A ESCOLHA DEVE SER UM NUMERO POSITIVO!\n\n--------------------------------------------------\n\n");
        return scan_choice1();
    }

    if (choice > 3) {
        printf("A ESCOLHA DEVE SER MENOR OU IGUAL A 3!\n\n--------------------------------------------------\n\n");
        return scan_choice1();
    }

    return choice;
}


void scan_choice1_input(char* msg, char* dest) {
    char fstring[BUFFER_SIZE];
    char garb;

    snprintf(fstring, BUFFER_SIZE - 1, "%%%ds", BUFFER_SIZE);

    printf("%s", msg);
    scanf(fstring, dest);

    // Limpando o stdin
    garb = getchar();
    while((garb != '\n') && (garb != EOF)) {
        garb = getchar();
    }
}


unsigned int scan_choice2_input(char* msg) {
    unsigned int r;
    char garb;

    printf("%s", msg);
    scanf("%u", &r);

    // Limpando o stdin
    garb = getchar();
    while((garb != '\n') && (garb != EOF)) {
        garb = getchar();
    }

    return r;
}


void id_not_found_choice2() {
    printf("\n\n\n-------------------- ID DIGITADO INVALIDO OU NAO ENCONTRADO --------------------\n\n\n"); // Divisória
}


void scan_choice2_update(char* cpf, char* nome, char* idade, char* data_registro) {
    char garb;
    int i, ok;


    printf("Digite o novo valor para os campos CPF, Nome, Idade e Data_Cadastro (para manter o valor atual de um campo, digite '-'):\n");
    printf("\t- CPF: ");
    scanf("%14[^\n]", cpf);

    // Limpando o stdin
    garb = getchar();
    while((garb != '\n') && (garb != EOF)) {
        garb = getchar();
    }

    printf("\t- Nome: ");
    scanf("%1000[^\n]", nome);

    // Limpando o stdin
    garb = getchar();
    while((garb != '\n') && (garb != EOF)) {
        garb = getchar();
    }



    while(1) {
        printf("\t- Idade: ");
        scanf("%3[^\n]", idade);

        // Limpando o stdin
        garb = getchar();
        while((garb != '\n') && (garb != EOF)) {
            garb = getchar();
        }

        ok = 1;
        for(i = 0; i < strlen(idade); i++) {
            if((idade[i] < '0') || (idade[i] > '9')) {
                ok = 0;
                break;
            }
        }

        if(strcmp(idade, "-") == 0)
            ok = 1;

        if(ok)
            break;

        printf("Digite uma idade valida!\n");
    }

    printf("\t- Data de Registro: ");
    scanf("%10[^\n]", data_registro);

    // Limpando o stdin
    garb = getchar();
    while((garb != '\n') && (garb != EOF)) {
        garb = getchar();
    }

}


void choice2_update_ok() {
    printf("\n\n\n-------------------- ATUALIZACAO FEITA COM SUCESSO --------------------\n\n\n");
}


void choice2_update_fail() {
    printf("\n\n\n-------------------- ERRO INESPERADO NA ATUALIZACAO --------------------\n\n\n");
}


void choice3_update_ok() {
    printf("\n\n\n-------------------- REMOCAO FEITA COM SUCESSO --------------------\n\n\n");
}


void choice3_update_fail() {
    printf("\n\n\n-------------------- ERRO INESPERADO NA REMOCAO --------------------\n\n\n");
}


void scan_choice4(char* cpf, char* nome, char* idade, char* data_registro) {
    char garb;
    int i, ok;


    printf("Para inserir um novo registro, digite os valores para os campos CPF, Nome, Idade e Data_Cadstro:\n");
    printf("\t- CPF: ");
    scanf("%14[^\n]", cpf);

    // Limpando o stdin
    garb = getchar();
    while((garb != '\n') && (garb != EOF)) {
        garb = getchar();
    }

    printf("\t- Nome: ");
    scanf("%1000[^\n]", nome);

    // Limpando o stdin
    garb = getchar();
    while((garb != '\n') && (garb != EOF)) {
        garb = getchar();
    }

    while(1) {
        printf("\t- Idade: ");
        scanf("%3[^\n]", idade);

        // Limpando o stdin
        garb = getchar();
        while((garb != '\n') && (garb != EOF)) {
            garb = getchar();
        }

        ok = 1;
        for(i = 0; i < strlen(idade); i++) {
            if((idade[i] < '0') || (idade[i] > '9')) {
                ok = 0;
                break;
            }
        }

        if(ok)
            break;

        printf("Digite uma idade valida!\n");
    }

    printf("\t- Data de Registro: ");
    scanf("%10[^\n]", data_registro);

    // Limpando o stdin
    garb = getchar();
    while((garb != '\n') && (garb != EOF)) {
        garb = getchar();
    }
}


int scan_choice3() {
    int choice;
    char garb;

    printf("O que deseja fazer?\n\t(1) - Consultar por CPF;\n\t(2) - Consultar por Nome;\n\t(3) - Remover Paciente por ID;\n\t(-1) - Voltar para o menu inicial;\nDIGITE A SUA ESCOLHA: ");
    scanf("%d", &choice);
    garb = getchar();
    while((garb != '\n') && (garb != EOF)) {
        garb = getchar();
    }


    if(choice == -1) {
        return -1;
    }    

    if (choice <= 0) {
        printf("A ESCOLHA DEVE SER UM NUMERO POSITIVO!\n\n--------------------------------------------------\n\n");
        return scan_choice1();
    }

    if (choice > 3) {
        printf("A ESCOLHA DEVE SER MENOR OU IGUAL A 3!\n\n--------------------------------------------------\n\n");
        return scan_choice1();
    }

    return choice;
}


int choice3_remove() {
    char garb, o;
    printf("\n TEM CERTEZA QUE DESEJA EXCLUIR O REGISTRO ABAIXO? ESSA ACAO E IRREVERSIVEL (S/N)\n");

    scanf(" %c", &o);
    garb = getchar();
    while((garb != '\n') && (garb != EOF)) {
        garb = getchar();
    }

    if((o == 's') || (o == 'S'))
        return 1;
    return 0;
}

int choice4_ok() {
    printf("\n\n\n-------------------- PACIENTE INSERIDO --------------------\n\n\n");
}

int choice4_fail() {
    printf("\n\n\n-------------------- ERRO INESPERADO NA INSERCAO DO PACIENTE --------------------\n\n\n");
}


#endif  // Fim da diretiva de inclusão condicional