#include "definitions.h"


void gera_binario(){

	int i;
	char *c1;
	char *c2;
	char *c3;
	char *c4;
	int max_bin;
	
	max_bin = retorna_max_quadrupla_asm();

	for (i = 0; i <= max_bin; i++){ //vai percorrer todas as intruções assembly

		retorna_posicao_asm(i, &c1, &c2, &c3, &c4);

		if (strcmp(c1, "add") == 0 || strcmp(c1, "addi") == 0 || strcmp(c1, "sub") == 0 ||
			strcmp(c1, "mult") == 0 || strcmp(c1, "div") == 0 || strcmp(c1, "slt") == 0 ||
			strcmp(c1, "xnor") == 0 || strcmp(c1, "xor") == 0 || strcmp(c1, "and") == 0 ||
			strcmp(c1, "addu") == 0 || strcmp(c1, "divu") == 0 || strcmp(c1, "nor") == 0 ||
			strcmp(c1, "or") == 0 || strcmp(c1, "subu") == 0){

			if (testa_numero (c4) == 0){ //nao eh numero

				if (strcmp (c1, "add") == 0){

					lista_add_binario("000000", charBin(c2, 5), charBin(c3, 5), charBin(c4, 5), "00000000000");
				}
				else if (strcmp (c1, "addu") == 0){
					lista_add_binario("000000", charBin(c2, 5), charBin(c3, 5), charBin(c4, 5), "00000000001");
				}
				else if (strcmp (c1, "and") == 0){
					lista_add_binario("000000", charBin(c2, 5), charBin(c3, 5), charBin(c4, 5), "00000000010");
				}
				else if (strcmp (c1, "div") == 0){
					lista_add_binario("000000", charBin(c2, 5), charBin(c3, 5), charBin(c4, 5), "00000000011");
				}
				else if (strcmp (c1, "divu") == 0){
					lista_add_binario("000000", charBin(c2, 5), charBin(c3, 5), charBin(c4, 5), "00000000100");
				}
				else if (strcmp (c1, "mult") == 0){
					lista_add_binario("000000", charBin(c2, 5), charBin(c3, 5), charBin(c4, 5), "00000000101");
				}
				else if (strcmp (c1, "nor") == 0){
					lista_add_binario("000000", charBin(c2, 5), charBin(c3, 5), charBin(c4, 5), "00000000110");
				}
				else if (strcmp (c1, "xor") == 0){
					lista_add_binario("000000", charBin(c2, 5), charBin(c3, 5), charBin(c4, 5), "00000000111");
				}
				else if (strcmp (c1, "or") == 0){
					lista_add_binario("000000", charBin(c2, 5), charBin(c3, 5), charBin(c4, 5), "00000001000");
				}
				else if (strcmp (c1, "slt") == 0){
					lista_add_binario("000000", charBin(c2, 5), charBin(c3, 5), charBin(c4, 5), "00000001001");
				}
				else if (strcmp (c1, "sub") == 0){
					lista_add_binario("000000", charBin(c2, 5), charBin(c3, 5), charBin(c4, 5), "00000001010");
				}
				else if (strcmp (c1, "subu") == 0){
					lista_add_binario("000000", charBin(c2, 5), charBin(c3, 5), charBin(c4, 5), "00000001011");
				}
				else if (strcmp (c1, "xnor") == 0){
					lista_add_binario("000000", charBin(c2, 5), charBin(c3, 5), charBin(c4, 5), "00000001100");
				}
			}
			else {
				if (strcmp (c1, "addi") == 0){
					lista_add_binario ("000001", charBin(c2, 5), charBin(c3, 5), intBin(c4, 16), "");
				}
			}
		}

		else if (strcmp (c1, "beq") == 0){
			lista_add_binario ("000010", charBin(c2, 5), charBin(c3, 5), intBin(c4, 16), "");
		}
		else if (strcmp (c1, "blez") == 0){
			lista_add_binario ("000011", charBin(c2, 5), charBin(c3, 5), intBin(c4, 16), "");
		}
		else if (strcmp (c1, "bne") == 0){
			lista_add_binario ("000100", charBin(c2, 5), charBin(c3, 5), intBin(c4, 16), "");
		}
		else if (strcmp (c1, "bgtz") == 0){
			lista_add_binario ("000101", charBin(c2, 5), charBin(c3, 5), intBin(c4, 16), "");
		}
		else if (strcmp (c1, "lw") == 0){

			if (testa_numero(c2) == 0){ //nao eh numero
				lista_add_binario ("000110", charBin(c2, 5), charBin(c3, 5), intBin(c4, 16), "");
			}
			else{ //caso de vetor
				lista_add_binario ("000110", charBin(c4, 5), charBin(c3, 5), intBin(c2, 16), "");
			}
		}
		else if (strcmp (c1, "li") == 0){
			lista_add_binario ("000001", charBin("$zero", 5), charBin(c2, 5), intBin(c3, 16), "");
		}
		else if (strcmp (c1, "sw") == 0){

			if (testa_numero(c2) == 0){ //nao eh numero
				lista_add_binario ("000111", charBin(c2, 5), charBin(c3, 5), intBin(c4, 16), "");
			}
			else{ //caso de vetor
				lista_add_binario ("000111", charBin(c4, 5), charBin(c3, 5), intBin(c2, 16), "");
			}
		}
		else if (strcmp (c1, "jump") == 0){
			lista_add_binario ("001000", intBin(c2, 26), "","","");
		}
		else if (strcmp (c1, "jal") == 0){
			lista_add_binario ("001001", intBin(c2, 26), "","","");
		}
		else if (strcmp (c1, "jr") == 0){
			lista_add_binario ("001010", charBin(c2, 26), "","","");
		}
		else if (strcmp (c1, "INPUT") == 0){
			lista_add_binario ("001011", charBin (c2,16), "1111111111", "","");
		}
		else if (strcmp (c1, "OUTPUT") == 0){
			lista_add_binario ("001100", charBin (c2,16), "1111111111", "","");
		}
	}//fim do for

	printa_lista_binario();

}