# HealthSys - Sistema de Gestão de Pacientes

## Descrição do Projeto

HealthSys é um sistema simples para gerenciamento de pacientes, desenvolvido em C. Ele permite operações básicas como consultar, inserir, atualizar, remover e listar pacientes armazenados em um banco de dados local em formato texto. O projeto foi desenvolvido com foco em modularidade, utilizando uma arquitetura baseada em TADs (Tipos Abstratos de Dados) para organizar modelos, visualizações (views) e controladores.


## Estrutura do Repositório

```
.
├── controller/         # Controladores
|   └── header/         # Header dos Controladores
│   └── src/            # Código Fonte dos Controladores
├── model/              # Modelos
|   └── header/         # Header dos Modelos
│   └── src/            # Código Fonte dos Modelos
├── view/               # Views
|   └── header/         # Header das Views
│   └── src/            # Código Fonte das Views
├── types/              # Typedefs
│   └── header/         # Header dos Typedefs
│   └── src/            # Código Fonte dos Typedefs
├── main.c              # main
├── Makefile            # makefile
└── README.md           # Esse arquivo
```


## Principais TADs (Tipos Abstratos de Dados)

### 1. **Paciente**
- Estrutura que representa um paciente.
- Contém:
  - Nome (string)
  - CPF (Tipo abstrato CPF, estruturado em partes)
  - Idade (unsigned tiny int)
- Funções principais: `paciente_init()`, `paciente_free()`.

### 2. **CPF**
- Tipo abstrato que representa o CPF dividido em blocos (`p1`, `p2`, `p3` e dígito verificador).
- Permite inicialização e conversão para string formatada.
- Funções principais: `cpf_init()`, `cpf_free()`, `cpf2string()`.

### 3. **BDPaciente**
- Estrutura que representa o banco de dados dos pacientes.
- Armazena o nome do arquivo, quantidade de registros e número de páginas para paginação.
- Funções para conectar ao banco, listar registros paginados e fechar conexão.

---

## Funcionalidades Principais

- Listar pacientes com paginação.
- Inserir novos pacientes.
- Atualizar informações de pacientes.
- Remover pacientes.
- Interface de menu interativo via terminal.
- Validação básica de entradas.
- Visualização clara das páginas e registros.

---

## Decisões de Implementação

- **Modularização:** Código separado em modelos, visões e controladores para facilitar manutenção e escalabilidade.
- **Paginação:** Implementada para facilitar a navegação entre registros, com tamanho de página configurável.
- **Tipos customizados:** Uso de enums e typedefs para melhorar legibilidade e portabilidade do código.
- **Gerenciamento de memória:** Alocação e liberação explícita para evitar vazamentos.
- **Makefile estruturado:** Compila separadamente os módulos `controller`, `view` e `model` em objetos dentro da pasta `objects`, garantindo organização e facilitando recompilações parciais.
- **Interface de linha de comando limpa:** Uso de funções para limpar a tela e exibir menus e mensagens de erro.
- **Uso de arquivos CSV:** O banco de dados de pacientes é armazenado em formato texto, facilitando edição manual e portabilidade.

---

## Como Compilar e Executar

1. **Compilação**

    O projeto utiliza um `Makefile` para facilitar a compilação. Basta rodar no terminal, na raiz do projeto:

    ```bash
    make main
    ```

    Isso irá:

    - Criar a pasta objects para os arquivos objeto intermediários.
    - Compilar separadamente os módulos do controller, view e model.
    - Linkar todos os objetos com o arquivo principal main.c para gerar o executável main.
    - Após a compilação, a pasta objects será removida para limpeza.

2. **Execução**
    Após compilar, execute o programa com:
    ```bash
    ./main
    ```

3. **Uso**
    
    O programa apresentará um menu interativo onde você pode escolher as operações:
    - Consultar paciente
    - Atualizar paciente
    - Remover paciente
    - Inserir paciente
    - Imprimir lista de pacientes
    - Sair

    Navegue conforme as instruções na tela.

## Requisitos

- GCC (compilador C)
- Sistema operacional Unix-like (Linux, macOS) para o comando clear funcionar (usado para limpar a tela). Para Windows, será necessário adaptar a função de limpeza de tela.
- Make (para usar o Makefile)

## Considerações Finais

Este projeto serve como base para sistemas simples de gerenciamento de dados utilizando C. Pode ser expandido com funcionalidades como autenticação, banco de dados binário, interface gráfica, entre outros. A modularização e a clareza do código facilitam sua extensão e manutenção.