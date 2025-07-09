#ifndef PAGE_VIEW                        // Diretiva para evitar múltiplas inclusões do mesmo arquivo
#define PAGE_VIEW

#ifndef STRING_SIZE                      // Define o tamanho padrão da string, caso ainda não esteja definido
#define STRING_SIZE 30
#endif

#include <string.h>                      // Inclusão para funções de manipulação de strings
#include <stdio.h>                       // Inclusão para entrada e saída padrão
#include "../../types/header/types.h"    // Inclusão de tipos definidos pelo projeto (Bool, uint, etc.)

// Função que exibe o número total de páginas disponíveis no banco de dados
void print_page(uint n_pages) {
    printf("\n\nO banco de dados possui %u paginas.\n", n_pages);
}

// Função que solicita ao usuário o número da página a ser visualizada
// Retorna o número da página escolhida, ou -1 se o usuário quiser voltar ao menu principal
int scan_page(uint n_pages) {
    int page;
    char garb;

    printf("Digite a pagina que queira visualizar ou -1 para voltar para o menu principal: ");
    scanf("%d", &page);

    // Limpando o stdin
    garb = getchar();
    while((garb != '\n') && (garb != EOF)) {
        garb = getchar();
    }

    if (page == -1)                      // Verifica se o usuário deseja retornar ao menu principal
        return -1;

    if (page <= 0) {                     // Verifica se o valor informado é positivo
        printf("\n\nA PAGINA DEVE SER UM VALOR POSITIVO!\n");
        return scan_page(n_pages);       // Recursivamente solicita nova entrada
    }

    if (page > n_pages) {                // Verifica se a página existe no banco de dados
        printf("\n\nA PAGINA DEVE SER MENOR OU IGUAL A %u!\n", n_pages);
        return scan_page(n_pages);       // Recursivamente solicita nova entrada
    }

    return page;                         // Retorna o número da página válida
}

// Função que imprime o cabeçalho da tabela de registros
void print_header() {
    printf("\n\nId\t\tCPF\t\t\tNome\t\t\t\tIdade\t\tData_Cadastro\n");
}

// Função que imprime um único registro de paciente formatado
// Nome é ajustado para ter comprimento fixo para alinhamento visual
void print_record(uint id, char* cpf, char* nome, uint idade, char* data_cadastro) {
    uint i;
    char new_name[STRING_SIZE];

    // Preenche new_name com o conteúdo de 'nome' e espaços até atingir STRING_SIZE - 1
    for (i = 0; i < STRING_SIZE - 1; i++) {
        if (i < strlen(nome))
            new_name[i] = nome[i];
        else
            new_name[i] = ' ';
    }
    new_name[STRING_SIZE - 1] = '\0';   // Finaliza a string corretamente

    // Imprime o registro formatado
    printf("%u\t\t%s\t\t%s\t%u\t\t%s\n", id, cpf, new_name, idade, data_cadastro);
}

// Função que exibe uma mensagem quando não há registros a serem mostrados
void print_no_records() {
    printf("\n\n----------- SEM NENHUM REGISTRO! ----------\n\n");
}

#endif  // Fim da diretiva de inclusão condicional
