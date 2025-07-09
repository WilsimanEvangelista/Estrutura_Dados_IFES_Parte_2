#ifndef TYPES
#define TYPES

// Define um tipo Booleano customizado chamado 'Bool' com os valores False (0) e True (1)
typedef enum bool {False, True} Bool;

// Define 'tinyint' como um apelido para 'char'
// Pode ser usado para representar inteiros pequenos com sinal (varia de -128 a 127)
typedef char tinyint;

// Define 'utinyint' como um apelido para 'unsigned char'
// Representa inteiros pequenos sem sinal (0 a 255), útil para economizar memória
typedef unsigned char utinyint;

// Define 'uint' como um apelido para 'unsigned int'
// Facilita a leitura do código onde números inteiros não negativos são utilizados
typedef unsigned int uint;

#endif