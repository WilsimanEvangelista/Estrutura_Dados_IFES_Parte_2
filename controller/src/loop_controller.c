// Proteção contra múltiplas inclusões do cabeçalho
#ifndef LOOP_CONTROLLER
#define LOOP_CONTROLLER

// Inclusão dos controladores das opções do menu (choice1 a choice5)
#include "../header/choice1_controller.h"
#include "../header/choice2_controller.h"
#include "../header/choice3_controller.h"
#include "../header/choice4_controller.h"
#include "../header/choice5_controller.h"

// Inclusão das funções de visualização do menu e divisória
#include "../../view/header/menu_view.h"
#include "../../view/header/div_view.h"

// Inclusão de definições de tipos personalizados (como 'utinyint')
#include "../../types/header/types.h"

// Função principal de controle de loop do menu
// Retorna 1 para indicar saída do programa, e 0 para continuar
utinyint loop_controller(char* db_filename){
    char choice; // Armazena a escolha do usuário (letra ou número do menu)

    // Vetor de ponteiros para funções, cada uma representando um controlador de opção
    // Todas devem ter a mesma assinatura: void func(char*)
    void (*choice_functions[])(char*) = {
        choice1_controller,
        choice2_controller,
        choice3_controller,
        choice4_controller,
        choice5_controller
    };
    
    print_menu(); // Mostra o menu

    // Lê a escolha do usuário
    choice = scan_menu();

    // Se o usuário escolher 'Q', retorna 1 para indicar que o programa deve ser encerrado
    if(choice == 'Q')
        return 1;
    
    // Executa a função correspondente à escolha do usuário
    // 'choice - 49' converte o caractere numérico ('1' a '5') para índice de vetor (0 a 4)
    clear_terminal(); // Limpa o terminal
    choice_functions[choice - 49](db_filename);
    print_div(); // Cria uma divisão

    return 0; // Retorna 0 para continuar o loop
}

#endif
