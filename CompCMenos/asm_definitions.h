#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
// COLOCANDO AGORA AS FUNCOES DA LISTA ENCADEADA PRA SALVAR AS QUADRUPLAS


void lista_add (char nome[], char campo_1[], char campo_2[], char campo_3[]);

void lista_add_asm (char nome[], char campo_1[], char campo_2[], char campo_3[]);

void lista_free();

void lista_free_asm();

void printa_lista ();

void printa_lista_asm ();

void retorna_posicao (int posicao, char** c1, char** c2, char** c3, char** c4);

int retorna_max_quadrupla ();

void salva_quadrupla (char textinho[], char c_1[], char c_2[], char c_3[], int var_c_1, int var_c_2, int var_c_3, int m_flag);



//==================================== Pilha ====================================


typedef struct SNome{
    char *nome;
    struct SNome *abaixo;
}TNome;

typedef struct {
    int numelementos;
    TNome* topo;
}Pilha;

void push(Pilha *P, char *nome);
char* pop(Pilha *P);
void inicializaPilha(Pilha *P);

void gera_cod_Assembly ();

void gera_binario ();


//============================== OTIMIZANDO REGISTRADORES ==============================


int incrementa_reg ();

void zera_reg_FinalFunc ();

void libera_reg (int libera);

int incrementa_reg_reverse (int num);

//============================== lista labels ==============================


void add_label_lista (int num_linha, char nome []);

void lista_label_free ();

void printa_lista_labels ();

int retorna_label_linha_asm (char label []);

void fix_beqs ();

void fix_jumps ();

void lista_add_aux (char nome[], char campo_1[], char campo_2[], char campo_3[]);

void lista_free_aux();

void retorna_posicao_aux (int posicao, char** c1, char** c2, char** c3, char** c4);

void retorna_posicao_asm (int posicao, char** c1, char** c2, char** c3, char** c4);

void insere_jump_main ();

//============================== lista variaveis ==============================

void add_var_lista (char nome [], char escopo [], char tipo [], int posicao);

void lista_var_free ();

int retorna_var_posicao (char nome_var [], char escopo []);

int testa_numero(char s []);

//============================== BINARIO ==============================

void lista_add_binario (char nome[], char campo_1[], char campo_2[], char campo_3[], char campo_4[]);

void lista_free_binario();

void printa_lista_binario ();

int retorna_max_quadrupla_asm ();

uint32_t int_to_binary(uint32_t k);

int num_register (char reg []);

char * charBin (char palavra [], int tam_esperado);

char * intBin (char reg [], int tam_esperado);

void fast_asm_converter();