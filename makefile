# Regra principal para compilar e gerar o executável 'main'
main:
	# Primeiro, compila todas as dependências (controller, view, model) e cria os objetos
	make persistent_comp
	# Remove o diretório 'objects' após a compilação para limpeza dos arquivos intermediários
	rm -r objects

# Regra para compilar os arquivos fonte do controller em objetos
controller_comp: objects
	# Compila cada arquivo fonte do controller e gera os arquivos objeto correspondentes dentro da pasta 'objects'
	gcc -c controller/src/loop_controller.c -o objects/controller_loop.o
	gcc -c controller/src/choice1_controller.c -o objects/controller_choice1.o
	gcc -c controller/src/choice2_controller.c -o objects/controller_choice2.o
	gcc -c controller/src/choice3_controller.c -o objects/controller_choice3.o
	gcc -c controller/src/choice4_controller.c -o objects/controller_choice4.o
	gcc -c controller/src/choice5_controller.c -o objects/controller_choice5.o

# Regra para compilar os arquivos fonte da view em objetos
view_comp: objects
	# Compila cada arquivo fonte da view e gera os arquivos objeto correspondentes na pasta 'objects'
	gcc -c view/src/menu_view.c -o objects/view_menu.o
	gcc -c view/src/div_view.c -o objects/view_div.o
	gcc -c view/src/open_db_error_view.c -o objects/view_open_db_error.o
	gcc -c view/src/page_view.c -o objects/view_page.o
	gcc -c view/src/search_view.c -o objects/view_search.o

# Regra para compilar os arquivos fonte do model em objetos
model_comp: objects
	# Compila cada arquivo fonte do model e gera os arquivos objeto correspondentes dentro da pasta 'objects'
	gcc -c model/src/Paciente_model.c -o objects/model_Paciente.o
	gcc -c model/src/BDPaciente_model.c -o objects/model_BDPaciente.o
	gcc -c model/src/CPF_model.c -o objects/model_CPF.o

# Regra para preparar o ambiente, compilar tudo e linkar
persistent_comp:
	# Cria o diretório 'objects' se ele não existir (onde ficarão os arquivos objeto)
	mkdir -p objects
	# Executa a compilação dos módulos do controller
	make controller_comp
	# Executa a compilação dos módulos da view
	make view_comp
	# Executa a compilação dos módulos do model
	make model_comp
	# Linka todos os arquivos objeto gerados e o arquivo principal main.c para gerar o executável final 'main'
	gcc main.c objects/*.o -o main
