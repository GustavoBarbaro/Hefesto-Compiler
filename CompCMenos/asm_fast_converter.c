#include "asm_definitions.h"


void fast_asm_converter(){

	lista_add_asm("lw", "$fp", "$ra", "1");
	lista_add_asm("jr", "$ra", "$zero", "$zero");

	printa_lista_asm();






}