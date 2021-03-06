#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

#define MAX_TAM_TOKEN 100

#ifndef YYPARSER // Não importa o arquivo quando chamado pelo parse.y
#include "parse.tab.h" //Gerado pela flag "-d" do bison
#define ENDFILE 0
#endif

/*
typedef enum{
    FIMARQ, ERRO,
    ELSE, IF, INT, RETURN, VOID, WHILE,
    ID,NUM,
    IGUAL, IGUALIGUAL, DIF, MENOR, MAIOR, MENIGUAL, MAIIGUAL, MAIS, MENOS,
    VEZES, DIV, ABREPAR, FECHAPAR, PVIRG, VIRG, ABRECOL, FECHACOL, ABRECH, FECHACH, COMENT, ENTER
} Token;
*/

extern int yylineno;
extern bool Erro;
extern char* yytext;
extern int numlinha;
extern FILE* arq_cod_fonte; // arquivo com o código fonte a ser compilado
extern char lexema[MAX_TAM_TOKEN + 1]; // armazena string do token reconhecido pelo scanner
extern char ID_nome[MAX_TAM_TOKEN + 1]; // armazena lexema (nome) de tokens ID
extern char NUM_val[MAX_TAM_TOKEN + 1]; // armazena string com valor de tokens NUM


#define MAX_LINHA 100
// Roda scanner e imprime os tokens reconhecidos e seus lexemas
void imprimeTokens(char* nomearq);



typedef int Token; // yacc define automaticamente os valores inteiros dos Tokens

//==========  (Definição das estruturas de Árvore Sintática)  ==============

typedef enum {TDecl,TExp,TStmt} TipoNo;
typedef enum {D_var, D_func, D_Tipo} TipoDecl;
typedef enum {S_If,S_While,S_Atrib,S_Retorno,S_Chamada} TipoStmt;
typedef enum {E_Op,E_Num,E_Id} TipoExp;
typedef enum {Void,Integer,Array,Boolean} Tipo; // Usado para verificação de tipo

#define MAXFILHOS 3 //3 filhos por causa do if que exige 3

typedef struct noArvore{
    struct noArvore * filho[MAXFILHOS];
    struct noArvore * irmao;
    int numlinha;
    TipoNo tipo_de_no;
    union { TipoDecl decl; TipoStmt stmt; TipoExp exp;} tipo; //talvez melhorar o nome
    union { Token op;
            int val;
            char * nome; } atrib;
    Tipo tipo_c; // para checar tipos em expressões
} NoArvore;

char * copiaString(char * s);
// Função que retorna o nome do token (para impressão na tela)
char* nome_token(Token token);
// Função definida com ajuda da ferramenta flex (lex)
Token retornaToken();
// Função definida com ajuda da ferramenta bison (yacc)
NoArvore* parse(void);

void imprimeArvore( NoArvore * arv );

NoArvore * novoNoDecl(TipoDecl tipo);

NoArvore * novoNoStmt(TipoStmt tipo);

NoArvore * novoNoExp(TipoExp tipo);

char * retStrTipo(Tipo t);


/* Procedimento insere_tab_sim insere o numero das linhas 
   e os locais de memoria na tabela de simbolos
*/
void insere_tab_sim( char * nome, int numlinha, int loc, char * escopo, Tipo tipo, int eh_funcao);

/* Função consulta_tab_sim retorna a localização
 * de memoria de uma variavel ou -1 caso não a encontre
 */
int consulta_tab_sim ( char * nome , char * escopo);
int consulta_tab_sim_uso_var ( char * nome , char * escopo, Tipo *tipo_c);
int consulta_tab_sim_cham ( char * nome , char * escopo, Tipo *tipo_c);

/* Procedimento imprimeTabSim imprime
*   uma lista formatada do conteudo da tabela de simbolos
*   para o arquivo listing
*/
void imprimeTabSim(FILE * listing);

//Função que monta a tabela de símbolos a partir da árvore sintática
void montaTabSim(NoArvore * arv); 

// Função que faz a checagem de tipos a partir da árvore sintática
void checaTipos(NoArvore * arv);

// Função que gera o código intermediário de 3 endereços
// a partir da árvore sintática e o armazena no arquivo
// arq
void geraCod(NoArvore * arv);



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