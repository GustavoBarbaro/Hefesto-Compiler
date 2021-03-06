#include <stdio.h>
#include <stdlib.h>
#include "definitions.h"
#define MAX_LINHA 100
//aloca as variaveis globais
int numlinha = 0;
FILE * arq_cod_fonte;
bool Erro;
int main(){

	arq_cod_fonte = fopen("sample.c","r");
	if(arq_cod_fonte == NULL){
		printf("Falha na leitura do código fonte\n");
	}

	printf("\n====================== Análise Léxica ===========================\n");
	imprimeTokens("sample.c");    
	fclose(arq_cod_fonte);
	arq_cod_fonte = fopen("sample.c","r");
	numlinha = 1;

	
	NoArvore* arvoreSintatica;
	arvoreSintatica = parse();
	printf("\n\n==================== Árvore Sintática ====================\n\n");
	if(!Erro)
		imprimeArvore(arvoreSintatica);
	printf("\n\n");

	montaTabSim(arvoreSintatica);
	if(!Erro)
		checaTipos(arvoreSintatica);


	printf("\n\n============  Código Intermediário (3 endereços)  ============\n\n");
	if(!Erro)
		geraCod(arvoreSintatica);
	printa_lista();


	printf("\n\n==================== Código Assembly ====================\n\n");

	gera_cod_Assembly();


	printf("\n\n==================== Código Binario ====================\n\n");

	gera_binario ();

	lista_free();
	lista_free_asm();
	lista_label_free ();
	lista_var_free ();
	lista_free_aux ();
	lista_free_binario();
	fclose(arq_cod_fonte);
	return 0;
}



