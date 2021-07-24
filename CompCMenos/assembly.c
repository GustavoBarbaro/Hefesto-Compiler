#include "definitions.h"

void gera_cod_Assembly (){

	char *c1;
	char *c2;
	char *c3;
	char *c4; //nao precisa dar free pq nao foi alocado com malloc
	int max_cont, i;

	int cont_inst = 0;

	max_cont = retorna_max_quadrupla();

	retorna_posicao (28, &c1, &c2, &c3, &c4);

	printf("%s\n", c1);
	printf("%s\n", c2);
	printf("%s\n", c3);
	printf("%s\n", c4);


	/*for (i = 0; i <= max_cont; i++){ //vai percorrer cada quadrupla, analisar cada uma aqui dentro

		retorna_posicao (i, &c1, &c2, &c3, &c4);

		if (strcmp (c1, "ADD") == 0 || strcmp (c1, "SUB") == 0 || strcmp (c1, "MUL") == 0 || strcmp (c1, "DIV") == 0){
			lista_add_asm(c1, c2, c3, c4);
		}

		lista_add_asm(c1, c2, c3, c4);
		
	}*/



	printa_lista_asm();


}