#include "asm_definitions.h"


void fast_asm_converter(){

	
	// =================== inicialização ===================  //


	//armazene o valor 1 na primeira posicao da MD separada para o SO
	lista_add_asm("li", "$rf", "1", "");
	lista_add_asm("sw", "$zero", "$rf", "0");

	//pule para a primeira linha do P1
	lista_add_asm("li", "$t25", "20", "");
	lista_add_asm("jumpP1", "$t25", "", "");

	// ========================================================= //


	// ============================== SO deve sempre voltar nessa linha ============================== //

	lista_add_asm("lw", "$zero", "$rf", "0"); //recupera o valor do ultimo processo executado

	lista_add_asm("li", "$ra", "1", ""); //carrega o 1 em ra

	//se $rf e $ra forem iguais carrega 1 em $aux
	lista_add_asm("xnor", "$rf", "$ra", "$aux");

	//se $aux == 0 então $rf != $ra poranto pule o else
	lista_add_asm("beq", "$aux", "$zero", "75");
	// ============================== bloco dentro do if ============================== //


	// armazena 2 na primeira posicao da MD separada para o SO
	lista_add_asm("li", "$rf", "2", "");
	lista_add_asm("sw", "$zero", "$rf", "0");

	//salva o valor do PC do P1 na MD responsavel dele
	lista_add_asm("recup_PC", "$rf", "", "");
	lista_add_asm("sw", "$zero", "$rf", "63");

	// salva todos registradores usados pelo P1 na MD
	lista_add_asm("sw", "$zero", "$t0", "1");
	lista_add_asm("sw", "$zero", "$t1", "2");
	lista_add_asm("sw", "$zero", "$t2", "3");
	lista_add_asm("sw", "$zero", "$t3", "4");
	lista_add_asm("sw", "$zero", "$t4", "5");
	lista_add_asm("sw", "$zero", "$t5", "6");
	lista_add_asm("sw", "$zero", "$t6", "7");
	lista_add_asm("sw", "$zero", "$t7", "8");
	lista_add_asm("sw", "$zero", "$t8", "9");
	lista_add_asm("sw", "$zero", "$t9", "10");
	lista_add_asm("sw", "$zero", "$t10", "11");
	lista_add_asm("sw", "$zero", "$t11", "12");
	lista_add_asm("sw", "$zero", "$t12", "13");
	lista_add_asm("sw", "$zero", "$t13", "14");
	lista_add_asm("sw", "$zero", "$t14", "15");
	lista_add_asm("sw", "$zero", "$t15", "16");
	lista_add_asm("sw", "$zero", "$t16", "17");
	lista_add_asm("sw", "$zero", "$t17", "18");
	lista_add_asm("sw", "$zero", "$t18", "19");
	lista_add_asm("sw", "$zero", "$t19", "20");
	lista_add_asm("sw", "$zero", "$t20", "21");
	lista_add_asm("sw", "$zero", "$t21", "22");
	lista_add_asm("sw", "$zero", "$t22", "23");
	lista_add_asm("sw", "$zero", "$t23", "24");
	lista_add_asm("sw", "$zero", "$t24", "25");
	lista_add_asm("sw", "$zero", "$t25", "26");//
	lista_add_asm("sw", "$zero", "$aux", "27");
	lista_add_asm("sw", "$zero", "$rf", "28");
	lista_add_asm("sw", "$zero", "$fp", "29");
	lista_add_asm("sw", "$zero", "$sp", "30");
	lista_add_asm("sw", "$zero", "$ra", "31");

	// carrega os registradores usados pelo P2 no banco de registradores
	lista_add_asm("lw", "$zero", "$t0", "32");
	lista_add_asm("lw", "$zero", "$t1", "33");
	lista_add_asm("lw", "$zero", "$t2", "34");
	lista_add_asm("lw", "$zero", "$t3", "35");
	lista_add_asm("lw", "$zero", "$t4", "36");
	lista_add_asm("lw", "$zero", "$t5", "37");
	lista_add_asm("lw", "$zero", "$t6", "38");
	lista_add_asm("lw", "$zero", "$t7", "39");
	lista_add_asm("lw", "$zero", "$t8", "40");
	lista_add_asm("lw", "$zero", "$t9", "41");
	lista_add_asm("lw", "$zero", "$t10", "42");
	lista_add_asm("lw", "$zero", "$t11", "43");
	lista_add_asm("lw", "$zero", "$t12", "44");
	lista_add_asm("lw", "$zero", "$t13", "45");
	lista_add_asm("lw", "$zero", "$t14", "46");
	lista_add_asm("lw", "$zero", "$t15", "47");
	lista_add_asm("lw", "$zero", "$t16", "48");
	lista_add_asm("lw", "$zero", "$t17", "49");
	lista_add_asm("lw", "$zero", "$t18", "50");
	lista_add_asm("lw", "$zero", "$t19", "51");
	lista_add_asm("lw", "$zero", "$t20", "52");
	lista_add_asm("lw", "$zero", "$t21", "53");
	lista_add_asm("lw", "$zero", "$t22", "54");
	lista_add_asm("lw", "$zero", "$t23", "55");
	lista_add_asm("lw", "$zero", "$t24", "56");
	lista_add_asm("lw", "$zero", "$t25", "57");//
	lista_add_asm("lw", "$zero", "$aux", "58");
	lista_add_asm("lw", "$zero", "$rf", "59");
	lista_add_asm("lw", "$zero", "$fp", "60");
	lista_add_asm("lw", "$zero", "$sp", "61");
	lista_add_asm("lw", "$zero", "$ra", "62");


	//recuperar o valor do PC do outro processo
	lista_add_asm("lw", "$zero", "$t25", "64");
	lista_add_asm("jumpP2", "$t25", "", "");	


	// ============================== fim do bloco do if ============================== //



	// ============================== inicio do bloco do else ============================== //
	
	
	// armazena 1 na primeira posicao da MD separada para o SO
	lista_add_asm("li", "$rf", "1", "");
	lista_add_asm("sw", "$zero", "$rf", "0");

	//salva o valor do PC do P2 na MD responsavel dele
	lista_add_asm("recup_PC", "$rf", "", "");
	lista_add_asm("sw", "$zero", "$rf", "64");

	// salva todos registradores usados pelo P2 na MD
	lista_add_asm("sw", "$zero", "$t0", "32");
	lista_add_asm("sw", "$zero", "$t1", "33");
	lista_add_asm("sw", "$zero", "$t2", "34");
	lista_add_asm("sw", "$zero", "$t3", "35");
	lista_add_asm("sw", "$zero", "$t4", "36");
	lista_add_asm("sw", "$zero", "$t5", "37");
	lista_add_asm("sw", "$zero", "$t6", "38");
	lista_add_asm("sw", "$zero", "$t7", "39");
	lista_add_asm("sw", "$zero", "$t8", "40");
	lista_add_asm("sw", "$zero", "$t9", "41");
	lista_add_asm("sw", "$zero", "$t10", "42");
	lista_add_asm("sw", "$zero", "$t11", "43");
	lista_add_asm("sw", "$zero", "$t12", "44");
	lista_add_asm("sw", "$zero", "$t13", "45");
	lista_add_asm("sw", "$zero", "$t14", "46");
	lista_add_asm("sw", "$zero", "$t15", "47");
	lista_add_asm("sw", "$zero", "$t16", "48");
	lista_add_asm("sw", "$zero", "$t17", "49");
	lista_add_asm("sw", "$zero", "$t18", "50");
	lista_add_asm("sw", "$zero", "$t19", "51");
	lista_add_asm("sw", "$zero", "$t20", "52");
	lista_add_asm("sw", "$zero", "$t21", "53");
	lista_add_asm("sw", "$zero", "$t22", "54");
	lista_add_asm("sw", "$zero", "$t23", "55");
	lista_add_asm("sw", "$zero", "$t24", "56");
	lista_add_asm("sw", "$zero", "$t25", "57");//
	lista_add_asm("sw", "$zero", "$aux", "58");
	lista_add_asm("sw", "$zero", "$rf", "59");
	lista_add_asm("sw", "$zero", "$fp", "60");
	lista_add_asm("sw", "$zero", "$sp", "61");
	lista_add_asm("sw", "$zero", "$ra", "62");

	// carrega os registradores usados pelo P1 no banco de registradores
	lista_add_asm("lw", "$zero", "$t0", "1");
	lista_add_asm("lw", "$zero", "$t1", "2");
	lista_add_asm("lw", "$zero", "$t2", "3");
	lista_add_asm("lw", "$zero", "$t3", "4");
	lista_add_asm("lw", "$zero", "$t4", "5");
	lista_add_asm("lw", "$zero", "$t5", "6");
	lista_add_asm("lw", "$zero", "$t6", "7");
	lista_add_asm("lw", "$zero", "$t7", "8");
	lista_add_asm("lw", "$zero", "$t8", "9");
	lista_add_asm("lw", "$zero", "$t9", "10");
	lista_add_asm("lw", "$zero", "$t10", "11");
	lista_add_asm("lw", "$zero", "$t11", "12");
	lista_add_asm("lw", "$zero", "$t12", "13");
	lista_add_asm("lw", "$zero", "$t13", "14");
	lista_add_asm("lw", "$zero", "$t14", "15");
	lista_add_asm("lw", "$zero", "$t15", "16");
	lista_add_asm("lw", "$zero", "$t16", "17");
	lista_add_asm("lw", "$zero", "$t17", "18");
	lista_add_asm("lw", "$zero", "$t18", "19");
	lista_add_asm("lw", "$zero", "$t19", "20");
	lista_add_asm("lw", "$zero", "$t20", "21");
	lista_add_asm("lw", "$zero", "$t21", "22");
	lista_add_asm("lw", "$zero", "$t22", "23");
	lista_add_asm("lw", "$zero", "$t23", "24");
	lista_add_asm("lw", "$zero", "$t24", "25");
	lista_add_asm("lw", "$zero", "$t25", "26");//
	lista_add_asm("lw", "$zero", "$aux", "27");
	lista_add_asm("lw", "$zero", "$rf", "28");
	lista_add_asm("lw", "$zero", "$fp", "29");
	lista_add_asm("lw", "$zero", "$sp", "30");
	lista_add_asm("lw", "$zero", "$ra", "31");


	//recuperar o valor do PC do outro processo
	lista_add_asm("lw", "$zero", "$t25", "63");
	lista_add_asm("jumpP2", "$t25", "", "");

	// ============================== fim do bloco do else ============================== //
	

	// ============================== fim do SO ============================== //

	printa_lista_asm();

}