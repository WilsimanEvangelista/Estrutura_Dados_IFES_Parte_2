#include "controller/header/loop_controller.h"  // Inclui a interface do controlador principal do loop do programa
#include "types/header/types.h"                 // Inclui definições de tipos personalizados (ex: utinyint)
#include "view/header/div_view.h"               // Inclui a função "clear_terminal"

#define DB_FILENAME "data/bd_paciente.csv"      // Define o caminho do arquivo CSV que funciona como banco de dados

int main(){
    utinyint exit = 0;                         // Variável para controlar a saída do programa (0 = continuar, 1 = sair)
    
    clear_terminal(); // Limpa o terminal
    // Loop principal do programa: executa o controlador até que seja solicitado sair
    while(!exit) {
        exit = loop_controller(DB_FILENAME);  // Chama a função loop_controller passando o arquivo de dados
                                               // loop_controller retorna 1 para sair do loop, 0 para continuar
    }

    return 0;                                 // Encerra o programa com sucesso
}
