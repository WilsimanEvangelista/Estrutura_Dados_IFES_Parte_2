#ifndef OPEN_DB_ERROR_VIEW                      // Início da diretiva de inclusão condicional
#define OPEN_DB_ERROR_VIEW                      // Define a macro OPEN_DB_ERROR_VIEW para evitar inclusões múltiplas

#include <stdio.h>                              // Inclui a biblioteca padrão de entrada e saída (necessária para printf)

// Função responsável por exibir uma mensagem de erro ao tentar abrir o banco de dados
void print_open_db_error() {
    // Imprime uma mensagem de erro indicando que o banco de dados não pôde ser aberto
    // Sugere que o usuário verifique o caminho e tente novamente
    printf("\n\n---------- ERRO AO ABRIR O BANCO. VERIFIQUE O CAMINHO E TENTE NOVAMENTE ----------n\n\n");
}

#endif                                          // Fim da diretiva de inclusão condicional