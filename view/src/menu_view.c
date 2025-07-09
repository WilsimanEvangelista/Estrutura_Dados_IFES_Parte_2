#ifndef MENU_VIEW                 // Evita inclusão múltipla do arquivo de cabeçalho
#define MENU_VIEW                 // Define a macro MENU_VIEW

#include <string.h>              // Necessária para usar a função strlen()
#include <stdio.h>               // Necessária para as funções printf() e scanf()
#include "../../types/header/types.h"  // Inclui definições de tipos personalizados como utinyint

// Função responsável por exibir o menu principal do sistema
void print_menu() {
    printf("HealthSys\n\n");
    printf("1 - Consultar paciente;\n");
    printf("2 - Atualizar paciente;\n");
    printf("3 - Remover paciente;\n");
    printf("4 - Inserir paciente;\n");
    printf("5 - Imprimir lista de paciente;\n");
    printf("Q - Sair;\n");
}

// Função que lê e valida a escolha do usuário
char scan_menu() {
    utinyint i = 0;              // Índice para iteração
    char c;                      // Char que armazenar a escolha do usuário
    int garb;                    // Char para armazenar lixo do stdin
    char choices[] = "12345Qq";  // Opções válidas

    printf("Digite sua escolha: ");
    c = getchar();               // Lê apenas o primeiro caractere da entrada

    // Limpando o stdin
    garb = getchar();
    while((garb != '\n') && (garb != EOF)) {
        garb = getchar();
    }

    // Verifica se a escolha está entre as válidas
    for(i = 0; i < strlen(choices); i++){
        if(c == choices[i]){
            if(c == 'q'){     // Se o usuário digitar 'q', converte para 'Q' por consistência
                return 'Q';
            }
            return c;         // Retorna o caractere digitado se for válido
        }
    }

    // Caso o caractere não seja válido, informa erro e chama a função novamente
    printf("ESCOLHA INVALIDA!\n");
    return scan_menu();          // Recursão para forçar nova entrada até que seja válida
}

#endif                           // Fim da diretiva de inclusão condicional