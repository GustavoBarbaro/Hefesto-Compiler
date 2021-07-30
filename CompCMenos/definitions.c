#include "definitions.h"

void imprimeTokens(char* nomearq){
	FILE* fc = fopen("sample.c","r");
	if(fc == NULL){
		printf("Falha na leitura do código fonte");
		Erro = 1;
		return;
	}
	char linha[MAX_LINHA];
	bool primeira_vez = true, leftover = false;
	while(1){
		if(fgets(linha, MAX_LINHA, fc) == NULL){
			break;
		}
		printf("\n%d: %s",numlinha, linha);
		Token rt;
		int nlsalva;
		if(primeira_vez){
			nlsalva= numlinha + 1;
			primeira_vez = false;
		}else{
			nlsalva = numlinha;
		}
		if(leftover){
			if(rt == ID || rt == NUM){
				printf("\t%d: %s, val= %s\n",numlinha, nome_token(rt), yytext);
			}else{
				printf("\t%d: %s\n",numlinha, nome_token(rt));
			}
			leftover = false;
		}
		do{
			rt = retornaToken();
			if(rt == EOF ) break;
			else if(numlinha != nlsalva){
				leftover = true;
				
				break;
			}
			if(rt == ID || rt == NUM){
				printf("\t%d: %s, val= %s\n",numlinha, nome_token(rt), yytext);
			}else{
				printf("\t%d: %s\n",numlinha, nome_token(rt));
			}
		}while(1);
	}
	fclose(fc);

}

// Cria e retorna um novo Nó do tipo "Declaração"
NoArvore * novoNoDecl(TipoDecl tipo)
{ NoArvore * no = (NoArvore *) malloc(sizeof(NoArvore));
  int i;
  if (no==NULL)
	fprintf(stderr,"Out of memory error at line %d\n",numlinha);
  else {
	for (i=0;i<MAXFILHOS;i++) no->filho[i] = NULL;
	no->irmao = NULL;
	no->tipo_de_no = TDecl;
	no->tipo.decl = tipo;
	no->numlinha = numlinha;
  }
  return no;
}


// Cria e retorna um novo Nó do tipo "Statement"
NoArvore * novoNoStmt(TipoStmt tipo)
{ NoArvore * t = (NoArvore *) malloc(sizeof(NoArvore));
  int i;
  if (t==NULL)
	fprintf(stderr,"Out of memory error at line %d\n",numlinha);
  else {
	for (i=0;i<MAXFILHOS;i++) t->filho[i] = NULL;
	t->irmao = NULL;
	t->tipo_de_no = TStmt;
	t->tipo.stmt = tipo;
	t->numlinha = numlinha;
  }
  return t;
}

// Cria e retorna um novo Nó do tipo "exp"
NoArvore * novoNoExp(TipoExp tipo)
{ NoArvore * t = (NoArvore *) malloc(sizeof(NoArvore));
  int i;
  if (t==NULL)
	fprintf(stderr,"Out of memory error at line %d\n",numlinha);
  else {
	for (i=0;i<MAXFILHOS;i++) t->filho[i] = NULL;
	t->irmao = NULL;
	t->tipo_de_no = TExp;
	t->tipo.exp = tipo;
	t->numlinha = numlinha;
  }
  return t;
}

char * copiaString(char * s)
{ int n;
  char * t;
  if (s==NULL) return NULL;
  n = strlen(s)+1;
  t = malloc(n);
  if (t==NULL)
	fprintf(stdout,"Sem memória na linha %d\n",numlinha);
  else strcpy(t,s);
  return t;
}

char * retStrTipo(Tipo t){
	if (t == Integer)
		return "int";
	else if( t == Void){
		return "void";
	}else if( t == Array){
		return "int[]";
	}else{
		return "bool";
	}
}


static int indentno = 0;

#define INDENT indentno+=4
#define UNINDENT indentno-=4

static void imprimeEspacos(void)
{ int i;
  for (i=0;i<indentno;i++)
	fprintf(stdout," ");
}

void imprimeArvore( NoArvore * arv )
{ int i;
  INDENT;
  while (arv != NULL) {
	imprimeEspacos();
	if (arv->tipo_de_no==TStmt)
	{ switch (arv->tipo.stmt) {
		case S_If:
		  fprintf(stdout,"If\n");
		  break;
		case S_While:
		  fprintf(stdout,"While\n");
		  break;
		case S_Atrib:
		  fprintf(stdout,"Atribuição\n");
		  break;
		case S_Retorno:
		  fprintf(stdout,"Retorno\n");
		  break;
		case S_Chamada:
		  fprintf(stdout,"Chamada da Função %s\n",arv->atrib.nome);
		  break;
		default:
		  fprintf(stdout,"Tipo desconhecido de Stmt\n");
		  break;
	  }
	}
	else if (arv->tipo_de_no==TExp)
	{ switch (arv->tipo.exp) {
		case E_Op:
		  fprintf(stdout,"Op:%s\n", nome_token(arv->atrib.op));
		  break;
		case E_Num:
		  fprintf(stdout,"Num: %d\n",arv->atrib.val);
		  break;
		case E_Id:
		  // strcmp retorna 0 quando é igual
		  if (strcmp(arv->atrib.nome,"void") == 0){
			fprintf(stdout,"void\n");
		  }else if(strcmp(arv->atrib.nome,"sem_local_decl") == 0 || strcmp(arv->atrib.nome,"sem_stmt_lista")==0){
			// nada
		  }else{
			fprintf(stdout,"Id: %s\n",arv->atrib.nome);
		  }
		  break;
		default:
		  fprintf(stdout,"Tipo desconhecido de Exp\n");
		  break;
	  }
	}else if (arv->tipo_de_no==TDecl)
	{ switch (arv->tipo.decl) {
		case D_var:
		  fprintf(stdout,"Variável %s\n",arv->atrib.nome);
		  break;         
		case D_func:
		  //if (arv->tipo_c)
		  fprintf(stdout,"Função %s\n",arv->atrib.nome);
		  //else  
			//fprintf(stdout,"Função %s com tipo de retorno void \n",arv->atrib.nome, arv->tipo_c);
		  break;
		case D_Tipo:
		  if (arv->tipo_c == Integer)
			fprintf(stdout,"Tipo int\n");
		  else if(arv->tipo_c == Array) 
			fprintf(stdout,"Tipo int[]\n");
		  else
			fprintf(stdout,"Tipo void\n");
		  break;
		default:
		  fprintf(stdout,"Tipo desconhecido de Decl\n");
		  break;
	  }
	}
	else fprintf(stdout,"Tipo desconhecido de Nó\n");
	for (i=0;i<MAXFILHOS;i++){
		imprimeArvore(arv->filho[i]);
	}
	arv = arv->irmao;
  }
  UNINDENT;
}


char* nome_token(Token t){
	char *nome;
	nome = malloc(MAX_TAM_TOKEN*sizeof(char));
	switch(t){
//        case FIMARQ:
  //          strcpy(nome,"fim do arquivo (EOF)");
	//        break;
	  //  case ERRO:
		//    strcpy(nome,"Erro !");
		  //  break;
		case ELSE:
			strcpy(nome,"ELSE");
			break;
		case IF:
			strcpy(nome,"IF");
			break;
		case INT:
			strcpy(nome,"INT");
			break;
		case RETURN:
			strcpy(nome,"RETURN");
			break;
		case VOID:
			strcpy(nome,"VOID");
			break;
		case WHILE:
			strcpy(nome,"WHILE");
			break;
		case ID:
			strcpy(nome,"ID");
			break;
		case NUM:
			strcpy(nome,"NUM");
			break;
		case IGUAL:
			strcpy(nome,"IGUAL");
			break;
		case IGUALIGUAL:
			strcpy(nome,"IGUALIGUAL");
			break;
		case DIF:
			strcpy(nome,"DIF");
			break;
		case MENOR:
			strcpy(nome,"MENOR");
			break;
		case MAIOR:
			strcpy(nome,"MAIOR");
			break;
		case MENIGUAL:
			strcpy(nome,"MENIGUAL");
			break;
		case MAIIGUAL:
			strcpy(nome,"MAIIGUAL");
			break;
		case MAIS:
			strcpy(nome,"MAIS");
			break;
		case MENOS:
			strcpy(nome,"MENOS");
			break;
		case VEZES:
			strcpy(nome,"VEZES");
			break;
		case DIV:
			strcpy(nome,"DIV");
			break;
		case FECHAPAR:
			strcpy(nome,"FECHAPAR");
			break;
		case ABREPAR:
			strcpy(nome,"ABREPAR");
			break;
		case PVIRG:
			strcpy(nome,"PVIRG");
			break;
		case VIRG:
			strcpy(nome,"VIRG");
			break;
		case ABRECOL:
			strcpy(nome,"ABRECOL");
			break;
		case FECHACOL:
			strcpy(nome,"FECHACOL");
			break;
		case ABRECH:
			strcpy(nome,"ABRECH");
			break;
		case FECHACH:
			strcpy(nome,"FECHACH");
			break;
		case COMENT:
			strcpy(nome,"COMENT");
			break;
		case ESPACO:
			strcpy(nome,"ESPACO");
			break;
		case ENTER:
			strcpy(nome,"ENTER");
			break;
		default:
			strcpy(nome, "OUTRO");
			break;
	}
	return nome;
}

// COLOCANDO AGORA AS FUNCOES DA LISTA ENCADEADA PRA SALVAR AS QUADRUPLAS


typedef struct quadrupla {
	char * nome;
	char * campo_1;
	char * campo_2;
	char * campo_3;

	struct quadrupla * next;
} t_quadrupla;

t_quadrupla *cabeca_lista = NULL; //head, começo da lista (endereço) (quadruplas - cgen)

t_quadrupla *cabeca_assembly = NULL; //cebeça da lista de instruções assembly


void lista_add (char nome[], char campo_1[], char campo_2[], char campo_3[]){

	if (cabeca_lista == NULL) {
		cabeca_lista = (struct quadrupla *) malloc (sizeof (struct quadrupla));

		cabeca_lista->nome = strdup(nome);
		cabeca_lista->campo_1 = strdup(campo_1);
		cabeca_lista->campo_2 = strdup(campo_2);
		cabeca_lista->campo_3 = strdup(campo_3);
		cabeca_lista->next = NULL;

		/*printf("%s\n", cabeca_lista->nome);
		printf("%s\n", cabeca_lista->campo_1);
		printf("%s\n", cabeca_lista->campo_2);
		printf("%s\n", cabeca_lista->campo_3);*/
		return;
	}


	t_quadrupla * no_atual = cabeca_lista; 

	while(no_atual->next) {
		no_atual = no_atual->next;
	}

	no_atual->next = (struct quadrupla *) malloc (sizeof (struct quadrupla));

	no_atual->next->nome = strdup(nome);
	no_atual->next->campo_1 = strdup(campo_1);
	no_atual->next->campo_2 = strdup(campo_2);
	no_atual->next->campo_3 = strdup(campo_3);
	no_atual->next->next = NULL;

}

void lista_add_asm (char nome[], char campo_1[], char campo_2[], char campo_3[]){

	if (cabeca_assembly == NULL) {
		cabeca_assembly = (struct quadrupla *) malloc (sizeof (struct quadrupla));

		cabeca_assembly->nome = strdup(nome);
		cabeca_assembly->campo_1 = strdup(campo_1);
		cabeca_assembly->campo_2 = strdup(campo_2);
		cabeca_assembly->campo_3 = strdup(campo_3);
		cabeca_assembly->next = NULL;

		/*printf("%s\n", cabeca_lista->nome);
		printf("%s\n", cabeca_lista->campo_1);
		printf("%s\n", cabeca_lista->campo_2);
		printf("%s\n", cabeca_lista->campo_3);*/
		return;
	}


	t_quadrupla * no_atual = cabeca_assembly; 

	while(no_atual->next) {
		no_atual = no_atual->next;
	}

	no_atual->next = (struct quadrupla *) malloc (sizeof (struct quadrupla));

	no_atual->next->nome = strdup(nome);
	no_atual->next->campo_1 = strdup(campo_1);
	no_atual->next->campo_2 = strdup(campo_2);
	no_atual->next->campo_3 = strdup(campo_3);
	no_atual->next->next = NULL;

}


void lista_free() {
	t_quadrupla * no_atual = cabeca_lista;
	while(no_atual) {
		t_quadrupla * temp = no_atual;
		no_atual = no_atual->next;
		free(temp->campo_1);
		free(temp->campo_2);
		free(temp->campo_3);
		free(temp->nome);
		free(temp);
	}
	no_atual = NULL;
	cabeca_lista = NULL;
}

void lista_free_asm() {
	t_quadrupla * no_atual = cabeca_assembly;
	while(no_atual) {
		t_quadrupla * temp = no_atual;
		no_atual = no_atual->next;
		free(temp->campo_1);
		free(temp->campo_2);
		free(temp->campo_3);
		free(temp->nome);
		free(temp);
	}
	no_atual = NULL;
	cabeca_assembly = NULL;
}

void printa_lista (){

	t_quadrupla * no_atual = cabeca_lista;
	int cont = 0;

	while (no_atual){
		t_quadrupla * temp = no_atual;
		no_atual = no_atual->next;

		printf("%d: (%s, %s, %s, %s)\n", cont++, temp->nome, temp->campo_1, temp->campo_2, temp->campo_3);

		/*printf ("nome: %s\n", temp->nome);
		printf ("campo_1: %s\n", temp->campo_1);
		printf ("campo_2: %s\n", temp->campo_2);
		printf ("campo_3: %s\n", temp->campo_3);
		printf ("\n\n");*/
	}

}


void printa_lista_asm (){
	int cont = 0;

	t_quadrupla * no_atual = cabeca_assembly;

	while (no_atual){
		t_quadrupla * temp = no_atual;
		no_atual = no_atual->next;

		printf("%d:  %s %s %s %s\n", cont, temp->nome, temp->campo_1, temp->campo_2, temp->campo_3);
		cont++;

		/*printf ("nome: %s\n", temp->nome);
		printf ("campo_1: %s\n", temp->campo_1);
		printf ("campo_2: %s\n", temp->campo_2);
		printf ("campo_3: %s\n", temp->campo_3);
		printf ("\n\n");*/
	}

}


void retorna_posicao (int posicao, char** c1, char** c2, char** c3, char** c4){

	t_quadrupla * no_atual = cabeca_lista;
	t_quadrupla * achei;

	int cont = 0;

	while (no_atual != NULL){ //para achar a quadrupla solicitada

		t_quadrupla * temp = no_atual;

		if (cont == posicao){
			achei = no_atual;
			break;
		}

		no_atual = no_atual->next;
		cont++;
	}

	*c1 = achei->nome;
	*c2 = achei->campo_1;
	*c3 = achei->campo_2;
	*c4 = achei->campo_3;
}

int retorna_max_quadrupla (){
	int max_cont = 0;

	t_quadrupla * no_atual = cabeca_lista;

	while (no_atual != NULL){ //para saber quantas quadruplas foram montadas

		t_quadrupla * temp = no_atual;
		no_atual = no_atual->next;
		max_cont++;
	}

	return max_cont - 1;
}



void salva_quadrupla (char textinho[], char c_1[], char c_2[], char c_3[], int var_c_1, int var_c_2, int var_c_3, int m_flag){

	char * buffer_1;
	char * buffer_2;
	char * buffer_3;

	//alocando 3 buffers temporarios
	buffer_1 = malloc (sizeof (char) * 15);
	buffer_2 = malloc (sizeof (char) * 15);
	buffer_3 = malloc (sizeof (char) * 15);

	//caso nao precise de conversão
	if (var_c_1 == -1){
		buffer_1 = strdup(c_1);
	}
	else{
		sprintf(buffer_1, "%s%d", c_1, var_c_1); //convertendo int para char e ja concatenando em buffer  
	}

	//caso nao precise de conversão
	if(var_c_2 == -1){
		buffer_2 = strdup(c_2);
	}
	else{
		sprintf(buffer_2, "%s%d", c_2, var_c_2); //convertendo int para char e ja concatenando em buffer
	}

	//caso nao precise de conversão
	if(var_c_3 == -1){
		buffer_3 = strdup(c_3);
	}
	else{
		sprintf(buffer_3, "%s%d", c_3, var_c_3); //convertendo int para char e ja concatenando em buffer
	}
	

	//agora esta tudo pronto para adicionar a quadrupla na lista
	switch (m_flag){

		case (0): // 0 campo sem usar da quadrupla
			lista_add(textinho, buffer_1, buffer_2, buffer_3);
		break;

		case (1): // 1 campos sem usar da quadrupla
			lista_add(textinho, buffer_1, buffer_2, " ");
		break;

		case (2): // 2 campos sem usar da quadrupla
			lista_add(textinho, buffer_1, " ", " ");
		break;

		case (3): // campos sem usar da quadrupla (halt)
			lista_add(textinho, " ", " ", " ");
		break;

		default:
		break;
	}


	free (buffer_1);
	free (buffer_2);
	free (buffer_3);
}





//======================================= PILHA ===============================================



void inicializaPilha(Pilha *P){
	P = malloc(sizeof(Pilha*));
	P->numelementos = 0;
	P->topo = NULL;
}

void push(Pilha * P, char * nome){
	TNome * NomeStr = malloc(sizeof(TNome*));
	NomeStr->nome = strdup(nome);
	NomeStr->abaixo = P->topo;
	P->topo = NomeStr;
	P->numelementos ++;
}

char* pop(Pilha *P){
	char *nome = NULL;
	if (P->numelementos != 0){// pilha não vazia
		nome = strdup(P->topo->nome);
		TNome *topoAntigo;
		topoAntigo = P->topo;
		P->topo = topoAntigo->abaixo;
		P->numelementos --;
		nome = strdup(topoAntigo->nome);
		free(topoAntigo);
	}
	return nome;
}





//============================== OTIMIZANDO REGISTRADORES ==============================

#define max_reg 27

int reg[max_reg] = {0};


int incrementa_reg () {

	int i;

	for (i = 0; i <= max_reg; i++){

		if (reg[i] == 0){ //pisicao livre, pode inserir aqui
			reg[i] = 1; //agora tem gente
			break;
		}
	}

	return i;
}


void zera_reg_FinalFunc (){

	int i;

	for (i = 0; i <= max_reg; i++){
		reg[i] = 0; //liberando os registradores
	}
}


void libera_reg (int libera){

	reg[libera] = 0;
}

int incrementa_reg_reverse (int num) {

	int i;

	for (i = num; i >= 0; i--){

		if (reg[i] == 0){ //pisicao livre, pode inserir aqui
			reg[i] = 1; //agora tem gente
			break;
		}
	}

	return i;
}



//============================== lista labels ==============================


typedef struct lab {
	int num_linha;
	char * nome;

	struct lab * next;
} t_label;


t_label *cabeca_label = NULL; //começo da lista de labels

void add_label_lista (int num_linha, char nome []){
	if (cabeca_label == NULL){
		cabeca_label = (struct lab *) malloc (sizeof (struct lab));

		cabeca_label->num_linha = num_linha;
		cabeca_label->nome = strdup (nome);
		cabeca_label->next = NULL;
		return;
	}

	t_label * no_atual = cabeca_label;

	while (no_atual->next){
		no_atual = no_atual->next;
	}

	no_atual->next = (struct lab *) malloc (sizeof (struct lab));

	no_atual->next->num_linha = num_linha;
	no_atual->next->nome = strdup(nome);
	no_atual->next->next = NULL;
}


void lista_label_free (){
	t_label * no_atual = cabeca_label;
	while (no_atual){
		t_label * temp = no_atual;
		no_atual = no_atual->next;
		free(temp->nome);
		free(temp);
	}
	no_atual = NULL;
	cabeca_label = NULL;
}


void printa_lista_labels (){

	t_label * no_atual = cabeca_label;

	while (no_atual){
		t_label * temp = no_atual;
		no_atual = no_atual->next;

		printf("NOME: %s\n NUM_LINHA: %d\n\n", temp->nome, temp->num_linha);
	}
}

int retorna_label_linha_asm (char label []){
	t_label * no_atual = cabeca_label;
	int label_posicao = 0;

	while (no_atual != NULL){
		t_label * temp = no_atual;

		if (strcmp(label, no_atual->nome) == 0){
			label_posicao = no_atual->num_linha;
			break;
		}

		no_atual = no_atual->next;
	}
	return label_posicao;
}

void fix_beqs (){
	t_quadrupla * no_atual = cabeca_assembly;

	char * buffer_1;

	buffer_1 = malloc (sizeof (char) * 15);

	while (no_atual){

		t_quadrupla * temp = no_atual;
		no_atual = no_atual->next;

		if (strcmp (temp->nome, "beq") == 0){
			sprintf(buffer_1, "%d", retorna_label_linha_asm(temp->campo_3));
			temp->campo_3 = strdup (buffer_1);
		}
	}
	free (buffer_1);
}

void fix_jumps () {
	t_quadrupla * no_atual = cabeca_assembly;

	char * buffer_1;

	buffer_1 = malloc (sizeof (char) * 15);

	while (no_atual){

		t_quadrupla * temp = no_atual;
		no_atual = no_atual->next;

		if (strcmp (temp->nome, "jump") == 0){
			sprintf(buffer_1, "%d", retorna_label_linha_asm(temp->campo_1));
			temp->campo_1 = strdup (buffer_1);
		}
	}
	free (buffer_1);	
}


t_quadrupla * cabeca_lista_aux = NULL;

void lista_add_aux (char nome[], char campo_1[], char campo_2[], char campo_3[]){

	if (cabeca_lista_aux == NULL) {
		cabeca_lista_aux = (struct quadrupla *) malloc (sizeof (struct quadrupla));

		cabeca_lista_aux->nome = strdup(nome);
		cabeca_lista_aux->campo_1 = strdup(campo_1);
		cabeca_lista_aux->campo_2 = strdup(campo_2);
		cabeca_lista_aux->campo_3 = strdup(campo_3);
		cabeca_lista_aux->next = NULL;

		/*printf("%s\n", cabeca_lista->nome);
		printf("%s\n", cabeca_lista->campo_1);
		printf("%s\n", cabeca_lista->campo_2);
		printf("%s\n", cabeca_lista->campo_3);*/
		return;
	}


	t_quadrupla * no_atual = cabeca_lista_aux; 

	while(no_atual->next) {
		no_atual = no_atual->next;
	}

	no_atual->next = (struct quadrupla *) malloc (sizeof (struct quadrupla));

	no_atual->next->nome = strdup(nome);
	no_atual->next->campo_1 = strdup(campo_1);
	no_atual->next->campo_2 = strdup(campo_2);
	no_atual->next->campo_3 = strdup(campo_3);
	no_atual->next->next = NULL;

}

void lista_free_aux() {
	t_quadrupla * no_atual = cabeca_lista_aux;
	while(no_atual) {
		t_quadrupla * temp = no_atual;
		no_atual = no_atual->next;
		free(temp->campo_1);
		free(temp->campo_2);
		free(temp->campo_3);
		free(temp->nome);
		free(temp);
	}
	no_atual = NULL;
	cabeca_lista_aux = NULL;
}


void retorna_posicao_aux (int posicao, char** c1, char** c2, char** c3, char** c4){

	t_quadrupla * no_atual = cabeca_lista_aux;
	t_quadrupla * achei;

	int cont = 0;

	while (no_atual != NULL){ //para achar a quadrupla solicitada

		t_quadrupla * temp = no_atual;

		if (cont == posicao){
			achei = no_atual;
			break;
		}

		no_atual = no_atual->next;
		cont++;
	}

	*c1 = achei->nome;
	*c2 = achei->campo_1;
	*c3 = achei->campo_2;
	*c4 = achei->campo_3;
}

void retorna_posicao_asm (int posicao, char** c1, char** c2, char** c3, char** c4){
	t_quadrupla * no_atual = cabeca_assembly;
	t_quadrupla * achei;

	int cont = 0;

	while (no_atual != NULL){ //para achar a quadrupla solicitada

		t_quadrupla * temp = no_atual;

		if (cont == posicao){
			achei = no_atual;
			break;
		}

		no_atual = no_atual->next;
		cont++;
	}

	*c1 = achei->nome;
	*c2 = achei->campo_1;
	*c3 = achei->campo_2;
	*c4 = achei->campo_3;
}

void insere_jump_main (int max_lista){

	// primeiro passo: salvar a lista atual na auxiliar

	int i;
	char *c1;
	char *c2;
	char *c3;
	char *c4;

	char * buffer_1;

	buffer_1 = malloc (sizeof (char) * 15);


	for (i = 0; i <= max_lista; i++){

		retorna_posicao_asm (i, &c1, &c2, &c3, &c4);
		lista_add_aux (c1, c2, c3, c4);
	} //agora a lista ta salva

	lista_free_asm();

	//depois adiciona o primeiro jump da main


	sprintf(buffer_1, "%d", retorna_label_linha_asm("main"));

	lista_add_asm("jump", buffer_1, "", "");

	//ai com o primeiro elemento alocado, pega a lista auxiliar e colocar denovo na normal
	//fazendo lista_asm [cont + 1] = lista_aux [cont];

	for (i = 0; i <= max_lista; i++){
		retorna_posicao_aux(i, &c1, &c2, &c3, &c4);
		lista_add_asm(c1, c2, c3, c4);
	}



	free (buffer_1);
}


//============================== lista variaveis ==============================


typedef struct var {
	char * nome;
	char * escopo;
	char * tipo;
	int posicao;

	struct var * next;
} t_var;

t_var *cabeca_var = NULL; //comeco da lista de vars

void add_var_lista (char nome [], char escopo [], char tipo [], int posicao){
	if (cabeca_var == NULL){
		cabeca_var = (struct var *) malloc (sizeof (struct var));

		cabeca_var->nome = strdup (nome);
		cabeca_var->escopo = strdup (escopo);
		cabeca_var->tipo = strdup (tipo);
		cabeca_var->posicao = posicao;
		return;
	}

	t_var * no_atual = cabeca_var;

	while (no_atual->next){
		no_atual = no_atual->next;
	}

	no_atual->next = (struct var *) malloc (sizeof (struct var));

	no_atual->next->nome = strdup (nome);
	no_atual->next->escopo = strdup (escopo);
	no_atual->next->tipo = strdup (tipo);
	no_atual->next->posicao = posicao;
	no_atual->next->next = NULL;
}

void lista_var_free (){
	t_var * no_atual = cabeca_var;
	while(no_atual){
		t_var * temp = no_atual;
		no_atual = no_atual->next;
		free(temp->nome);
		free(temp->escopo);
		free(temp->tipo);
	}
	no_atual = NULL;
	cabeca_var = NULL;
}

int retorna_var_posicao (char nome_var [], char escopo []){

	t_var * no_atual = cabeca_var;
	int var_posicao = 0;

	while (no_atual != NULL){
		t_var * temp = no_atual;

		if (strcmp(nome_var, no_atual->nome) == 0 && strcmp(escopo, no_atual->escopo) == 0){
			var_posicao = no_atual->posicao;
			break;
		}

		no_atual = no_atual->next;
	}
	return var_posicao;
}

int testa_numero(char s []){

	int result = 1;
	for(int i = 0; i<strlen(s);i++)
	{
		if(!isdigit(s[i]))
		{
			result = 0;
			break;
		}
	}

	return result;
	//if (result == 1){printf("EH NUMERO\n");}
	//if (result == 0){printf("NAO EH NUMERO\n");}
}