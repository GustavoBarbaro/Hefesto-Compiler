#include "definitions.h"
#define max_vars 1000

Pilha params;


void gera_cod_Assembly (){

	char *c1;
	char *c2;
	char *c3;
	char *c4; //nao precisa dar free pq nao foi alocado com malloc
	char *varLocation;
	char *escopo_atual;
	char *aux_vars_cont;
	char *aux_vars_cont_um;
	char *aux_tam_vet;
	int max_cont, i, vars_cont = 0;
	int tam_vet = 0;
	int temp_int = 0;
	int linha_da_main = 0;

	int cont_asm = 1;


	aux_vars_cont = malloc (sizeof (char) * 15);
	aux_vars_cont_um = malloc (sizeof (char) * 15);
	aux_tam_vet = malloc (sizeof (char) * 15);
	varLocation = malloc (sizeof (char) * 15);


	int cont_inst = 0;

	escopo_atual = strdup("global");

	max_cont = retorna_max_quadrupla();



	for (i = 0; i <= max_cont; i++){ //vai percorrer cada quadrupla, analisar cada uma aqui dentro

		retorna_posicao (i, &c1, &c2, &c3, &c4);

		if (strcmp (c1, "ADD") == 0){
			lista_add_asm("add", c2, c3, c4);
			cont_asm++;	
		}
		else if (strcmp (c1, "SUB") == 0){
			lista_add_asm("sub", c2, c3, c4);			
			cont_asm++;
		}
		else if (strcmp (c1, "MUL") == 0){
			lista_add_asm("mult", c2, c3, c4);			
			cont_asm++;
		}
		else if (strcmp (c1, "DIV") == 0){
			lista_add_asm("div", c2, c3, c4);			
			cont_asm++;
		}

		else if (strcmp (c1, "LT") == 0){
			lista_add_asm("slt", c2, c3, c4);
			cont_asm++;
		}

		else if (strcmp (c1, "EQUAL") == 0){
			lista_add_asm("xnor", c2, c3, c4);
		}

		else if (strcmp (c1, "GT") == 0){
			lista_add_asm("sub", c2, c3, c4);
		}

		else if (strcmp (c1, "NEQ") == 0){
			lista_add_asm("xor", c2, c3, c4);
		}

		else if (strcmp (c1, "LEQ") == 0){
			lista_add_asm("sub", c2, c3, c4);
		}

		else if (strcmp (c1, "GEQ") == 0){
			lista_add_asm("slt", c2, c3, c4);
			lista_add_asm("addi", "$zero", "$aux", "1");
			lista_add_asm("sub", "$aux", c4, c4);
		}

		else if (strcmp (c1, "IFF") == 0){ //if falso (if igual a zero faz o desvio)

			lista_add_asm("beq", c2, "$zero", c3);
			cont_asm++;
		}

		else if (strcmp (c1, "PARAM") == 0){
			push(&params, c2);
		}

		else if (strcmp (c1, "CALL") == 0){

			if (strcmp (c2, "output") == 0){
				lista_add_asm ("OUTPUT", pop(&params), "", "");
				cont_asm++;
			}

			else if (strcmp (c2, "input") == 0){
				lista_add_asm ("INPUT", "$rf", "", "");
				cont_asm++;
			}

			else { //chamada de uma função normal
				lista_add_asm ("sw", "$sp", "$fp", "0");
				lista_add_asm ("addi", "$sp", "$fp", "0");
				lista_add_asm ("addi", "$sp", "$sp", "1");


				cont_asm = cont_asm + 3;

				int quant_param = atoi (c3);
				int i;
				char * buffer_1;

				buffer_1 = malloc (sizeof (char) * 15);

				for (i = quant_param + 2 - 1; i >= 2; i--){

					sprintf(buffer_1, "%d", i);

					lista_add_asm("sw", "$fp", pop(&params), buffer_1);
					cont_asm++;
				}

				sprintf(buffer_1, "%d", retorna_label_linha_asm (c2));

				lista_add_asm("jal", buffer_1, "", "");
				lista_add_asm ("addi", "$fp", "$sp", "0");
				lista_add_asm ("lw", "$fp", "$fp", "0");
				cont_asm = cont_asm + 3;

				free (buffer_1);
			}
		}

		else if (strcmp (c1, "ASSIGN") == 0){
			lista_add_asm ("addi", c3, c2, "0"); //c3 soma com 0 e guarda em c2
			cont_asm++;
		}

		else if (strcmp (c1, "LABEL") == 0 || strcmp (c1, "LAB") == 0){
			add_label_lista(cont_asm, c2); //salva o num da linha e o nome da label
		}

		else if (strcmp (c1, "GOTO") == 0){

			lista_add_asm ("jump", c2, "", "");
			cont_asm++;
		}

		else if (strcmp (c1, "FUN") == 0){

			add_label_lista(cont_asm, c3);

			escopo_atual = strdup(c3); //salvando o nome do escopo atual

			if (strcmp(c3, "main") == 0 || strcmp(c3, "global") == 0){
				vars_cont = 0; //zerando as variaveis do escopo anterior	
				if (strcmp(c3, "main") == 0){
					lista_add_asm ("addi", "$zero", "$fp", "128"); //metade da minha memoria de 256
					lista_add_asm ("addi", "$fp", "$sp", "0");
					//o espaco acima disso esta reservado para global

					linha_da_main = cont_asm; //salvando a linha da main para inserer o jump no comeco
					cont_asm = cont_asm + 2;
				}
			}
			else {
				vars_cont = 2;
			}
			

			if(strcmp (c3, "main") != 0){ //para funções que nao sejam a main
				lista_add_asm("sw", "$fp", "$ra", "1");
				lista_add_asm("addi", "$sp", "$sp", "1");
				cont_asm = cont_asm + 2;
			}
		}

		else if (strcmp (c1, "END") == 0){

			lista_var_free();

			if(strcmp (c2, "main") != 0){ //para funções que nao sejam a main
				lista_add_asm("lw", "$fp", "$ra", "1");
				lista_add_asm("jr", "$ra", "$zero", "$zero");
				cont_asm = cont_asm + 2;
			}
		}

		else if (strcmp (c1, "ALLOC") == 0 || strcmp (c1, "ARG") == 0){

			if (strcmp (c1, "ALLOC") == 0){

				if (strcmp (c4, " ") == 0){ //não eh vetor

					add_var_lista(c2, c3, "", vars_cont);

					vars_cont++;

					if (strcmp (c3, "global") != 0){
						lista_add_asm ("addi", "$sp", "$sp", "1");
						cont_asm++;
					}
					else {
						lista_add_asm ("addi", "$zero", "$sp", "1");
						cont_asm++;
					}
				}
				else { //eh vetor

					if(strcmp (c3, "global") == 0){
						add_var_lista(c2, c3, "", vars_cont);

						sprintf(aux_vars_cont_um, "%d", vars_cont+1);
						sprintf(aux_vars_cont, "%d", vars_cont);

						vars_cont++;

						lista_add_asm("addi","$zero","$aux", aux_vars_cont_um);
						lista_add_asm("sw","$zero","$aux", aux_vars_cont);
						cont_asm = cont_asm + 2;
					}
					else{

						tam_vet = atoi (c4);
						if (tam_vet > 0){
							sprintf(aux_vars_cont_um, "%d", vars_cont+1);
							sprintf(aux_vars_cont, "%d", vars_cont);
							lista_add_asm("addi","$fp","$aux", aux_vars_cont_um);
							lista_add_asm("addi","$fp","$aux", aux_vars_cont);
							cont_asm = cont_asm + 2;
						}

						tam_vet = tam_vet + 1;

						vars_cont = vars_cont + tam_vet;

						sprintf(aux_tam_vet, "%d", tam_vet);

						lista_add_asm("addi","$sp","$sp", aux_tam_vet);
						cont_asm++;
					}
				}
			}

			if (strcmp (c1, "ARG") == 0){

				if (strcmp(c2, "int[]") != 0){ //argumento nao eh vetor
					add_var_lista(c3, c4, c2, vars_cont);

					vars_cont++;

					if (strcmp (c4, "global") != 0){
						lista_add_asm ("addi", "$sp", "$sp", "1");
						cont_asm++;
					}
				}
				else { //argumento eh vetor

					add_var_lista(c3, c4, c2, vars_cont);

					vars_cont++;

					lista_add_asm ("addi", "$sp", "$sp", "1");
					cont_asm++;
				}
			}
		}


		//preciso tratar dos alloc primeiro (talvez dos arg tbm)
		else if (strcmp (c1, "LOAD") == 0){

			if (strcmp(c4, " ") == 0){ //load normal


				if (testa_numero(c3) == 0){ //nao eh numero

					sprintf(varLocation, "%d", retorna_var_posicao(c3, escopo_atual));
					
					if (strcmp(escopo_atual, "global") == 0){ //alocação global
						lista_add_asm ("lw", "$zero", c2, varLocation);
						cont_asm++;
					}
					else{
						lista_add_asm("lw", "$fp", c2, varLocation);
						cont_asm++;
					}
				}
				else{ //carregando um numero direto num reg
					lista_add_asm("li", c2, c3, "");
					cont_asm++;
				}
			}
			else{ //load com todas as quadruplas ou seja, vetor

				sprintf(varLocation, "%d", retorna_var_posicao(c3, escopo_atual));

				lista_add_asm("lw", varLocation, c2, c4);
				cont_asm++;
			}
		}

		else if (strcmp (c1, "STORE") == 0){

			if (strcmp (c4, " ") == 0){ // store normal

				sprintf(varLocation, "%d", retorna_var_posicao(c2, escopo_atual));

				if (strcmp(escopo_atual, "global") == 0){
					lista_add_asm("sw", "$zero", c3, varLocation);				
					cont_asm++;
				}
				else{
					lista_add_asm("sw", "$fp", c3, varLocation);				
					cont_asm++;
				}
			}
			else { //store de vetor
				sprintf(varLocation, "%d", retorna_var_posicao(c2, escopo_atual));
				lista_add_asm("sw", varLocation, c3, c4);				
				cont_asm++;
			}
		}

		else if (strcmp (c1, "RET") == 0){
			lista_add_asm ("addi", c2, "$ra", "0"); //c3 soma com 0 e guarda em c2
			cont_asm++;
		}

		
	} //final do for que percorre todas as quadruplas

	fix_beqs();
	fix_jumps();
	insere_jump_main (max_cont);

	printa_lista_asm();
	//printa_lista_labels ();
	//printf("VALOR DE CONT_ASM: %d\n", cont_asm);


	free (aux_vars_cont);
	free (aux_vars_cont_um);
	free (aux_tam_vet);
	free (varLocation);

}