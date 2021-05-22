#include "definitions.h"

static int tempnum = 1;
static int labelnum = 0;
static int numenderecos = 0;
static int param = 0;
static char * parametros_vet[500]; //maximo de 500 parametros
static int param_cont = 0; // contador de parametros
static char* escopo = "global";
static void cGen (NoArvore * arv);
static int flag_irmao = 0;

Pilha var_nome;


static void genStmt( NoArvore * arv)
{ NoArvore * p1, * p2, * p3;
  int savedLoc1,savedLoc2,currentLoc;
  int loc, t1,t2,t3,l1,l2,l3;
  switch (arv->tipo.stmt) {

      case S_If:
         p1 = arv->filho[0] ;
         p2 = arv->filho[1] ;
         p3 = arv->filho[2] ;
         cGen(p1);//condicao
         t1 = tempnum;
         l1 = labelnum++;
         l2 = labelnum++;

         //printf("(IFF, $t%d, L%d,  )\n", t1,l1);
         salva_quadrupla("IFF", "$t", "L", " ", t1, l1, 0, 1);


         cGen(p2);// bloco interno

         //printf("(GOTO,L%d,  ,  )\n", l2);
         salva_quadrupla("GOTO", "L", " ", " ", l2, 0, 0, 2);

         //printf("(LAB,L%d,  ,  )\n", l1);
         salva_quadrupla("LAB", "L", " ", " ", l1, 0, 0, 2);

         cGen(p3);// else

         //printf("(LAB,L%d,  ,  )\n", l2);
         salva_quadrupla("LAB", "L", " ", " ", l2, 0, 0, 2);         

         numenderecos = 0;
         break; 
      case S_While:
         p1 = arv->filho[0] ;
         p2 = arv->filho[1] ;
         l1 = labelnum++;
         l2 = labelnum++;

         //printf("LABEL L%d\n",l1);
         salva_quadrupla("LABEL", "L", " ", " ", l1, 0, 0, 2);

         cGen(p1); //condicao
         t1 = tempnum;

         //printf("(IFF, $t%d, L%d,  )\n", t1,l2);
         salva_quadrupla("IFF", "$t", "L", " ", t1, l2, 0, 1);

         cGen(p2); // loop

         //printf("(GOTO,L%d,  ,  )\n", l1);
         salva_quadrupla("GOTO", "L", " ", " ", l1, 0, 0, 2);

         //printf("LABEL L%d\n",l2);
         salva_quadrupla("LABEL", "L", " ", " ", l2, 0, 0, 2);

         break;
      case S_Atrib:
         tempnum++;
         p1 = arv->filho[0];
         p2 = arv->filho[1];
         push(&var_nome, arv->filho[0]->atrib.nome);
         cGen(p1);
         t1 = tempnum;
         cGen(p2);
         t2 = tempnum;

         //printf("(ASSIGN, $t%d, $t%d,  )\n",t1, t2);
         salva_quadrupla("ASSIGN", "$t", "$t", " ", t1, t2, 0, 1);

         //printf("(STORE, %s, $t%d,  )\n",nome_var, t1);
         salva_quadrupla("STORE", pop(&var_nome), "$t", " ", -1, t1, 0, 1);

         break;
      case S_Retorno:
         p1 = arv->filho[0];
         cGen(p1);

         //printf("(RET, $t%d,  ,  )\n", tempnum++);
         salva_quadrupla("RET", "$t", " ", " ", tempnum++, 0, 0, 2);

         break;
      case S_Chamada:
         p1 = arv->filho[1];

         //printf("NOME DO NO %d\n\n", arv->filho[1]->tipo_de_no);

         int npar = 0;
         tempnum++; //acho que tempnum ta a mais
         while(p1!= NULL){
            flag_irmao = 1; //se for 1 nao avança o irmao
            cGen(p1);

            //printf("(PARAM, $t%d, ,  )\n", tempnum++);
            salva_quadrupla("PARAM", "$t", " ", " ", tempnum++, 0, 0, 2);

            p1 = p1->irmao;
            npar++;
            flag_irmao = 0;
            
         }


         //printf("(CALL, %s, %d, $t%d)\n", arv->atrib.nome, npar, tempnum);
         salva_quadrupla("CALL", arv->atrib.nome, "", "$t", -1, npar, tempnum, 0);

         break;
      default:
            break;
    }
}

static void genDecl( NoArvore * arv)
{ NoArvore * p1, * p2, * p3;
  int savedLoc1,savedLoc2,currentLoc;
  int loc;
  switch (arv->tipo.decl) {
      case D_Tipo:
         cGen(arv->filho[0]);
         numenderecos = 0;
         break;
      case D_func:
         p1 = arv->filho[0] ;
         p2 = arv->filho[1] ;

         //printf("(FUN,  %s, %s,  )\n", retStrTipo(arv->tipo_c), arv->atrib.nome);
         salva_quadrupla("FUN", retStrTipo(arv->tipo_c), arv->atrib.nome, " ", -1, -1, -1, 1);

         escopo = arv->atrib.nome; //função nome rever
         param = 1;//possui argumentos
         cGen(p1);//args

         int i;

         for (i = 0; i < param_cont; i++){
            salva_quadrupla("LOAD", "$t", parametros_vet[i], " ", tempnum++, -1, -1, 1);
         }

         param = 0;
         cGen(p2);//corpo
         numenderecos = 0;
         param_cont = 0;
         salva_quadrupla("END", arv->atrib.nome, "", "", -1, -1, -1, 2);
         break;
      case D_var:
         if(param == 1){//se possui argumentos

            //printf("(ARG, %s, %s, %s)\n", retStrTipo(arv->tipo_c), arv->atrib.nome, escopo);
            salva_quadrupla("ARG", retStrTipo(arv->tipo_c), arv->atrib.nome, escopo, -1, -1, -1, 0);

            parametros_vet [param_cont++] = strdup(arv->atrib.nome);

         }else{
            p1 = arv->filho[0] ;
            //printf("(ALLOC, %s, %s,  )\n", arv->atrib.nome,escopo);

            if(p1 != NULL){
                //salva como vetor
                salva_quadrupla("ALLOC", arv->atrib.nome, escopo, "", -1, -1, arv->filho[0]->atrib.val, 0);
            }
            else{
                //salva normal
                salva_quadrupla("ALLOC", arv->atrib.nome, escopo, " ", -1, -1, -1, 1);
            }


         }
         break;

     /* case AssignK:
         if (TraceCode) emitComment("-> assign") ;
         cGen(arv->filho[0]);
         loc = st_lookup(arv->atrib.nome);
         emitRM("ST",ac,loc,gp,"assign: store value");
         if (TraceCode)  emitComment("<- assign") ;
         break; 

      case ReadK:
         emitRO("IN",ac,0,0,"read integer value");
         loc = st_lookup(arv->atrib.nome);
         emitRM("ST",ac,loc,gp,"read: store value");
         break;
      case WriteK:
         cGen(arv->filho[0]);
         emitRO("OUT",ac,0,0,"write ac");
         break;*/
      default:
         break;
    }
} /* genStmt */

static void genExp( NoArvore * arv)
{ int loc;
  NoArvore * p1, * p2;
  switch (arv->tipo.exp) {

    case E_Num :
      tempnum++;

      //printf("(LOAD, $t%d, %d,  )\n", tempnum, arv->atrib.val);
      salva_quadrupla("LOAD", "$t", "", " ", tempnum, arv->atrib.val, -1, 1);

      numenderecos++;
      break;
    
    case E_Id :
      tempnum++;

      //printf("(LOAD, $t%d, %s,  )\n", tempnum, arv->atrib.nome);
      //salva_quadrupla("LOAD", "$t", arv->atrib.nome, " ", tempnum, -1, -1, 1);

      p1 = arv->filho[0];

      if (p1 != NULL){ //para tratar do vetor, quer dizer que tem filho, ou seja, o indice

        salva_quadrupla("LOAD", "$t", arv->filho[0]->atrib.nome, " ", tempnum, -1, -1, 1);

        salva_quadrupla("LOAD", "$t", arv->atrib.nome, "$t", ++tempnum, -1, tempnum, 0);

      }
      else{
        salva_quadrupla("LOAD", "$t", arv->atrib.nome, " ", tempnum, -1, -1, 1);
      }
      

      numenderecos++;
      break; 

    case E_Op :
         p1 = arv->filho[0];
         p2 = arv->filho[1];
         cGen(p1);
         int t1 = tempnum;
         cGen(p2);
         int t2 = tempnum;
         tempnum++;
         //printf("\n\t\tNUMEND:%d\n", numenderecos);
         switch (arv->atrib.op) {
            case MAIS :

               //printf("(ADD, $t%d, $t%d, $t%d)\n", t1, t2, tempnum);
               salva_quadrupla("ADD", "$t", "$t", "$t", t1, t2, tempnum, 0);

               break;
            case MENOS :

               //printf("(SUB, $t%d, $t%d, $t%d)\n", t1, t2, tempnum);
               salva_quadrupla("SUB", "$t", "$t", "$t", t1, t2, tempnum, 0);

               break;
            case VEZES :

               //printf("(MUL, $t%d, $t%d, $t%d)\n", t1, t2, tempnum);
               salva_quadrupla("MUL", "$t", "$t", "$t", t1, t2, tempnum, 0);

               break;
            case DIV :

               //printf("(DIV, $t%d, $t%d, $t%d)\n", t1, t2, tempnum);
               salva_quadrupla("DIV", "$t", "$t", "$t", t1, t2, tempnum, 0);

               break;
            case MENOR :

               //printf("(LT, $t%d, $t%d, $t%d)\n", t1, t2, tempnum);
               salva_quadrupla("LT", "$t", "$t", "$t", t1, t2, tempnum, 0);

               break;
            case MAIOR :

               //printf("(LT, $t%d, $t%d, $t%d)\n", t1, t2, tempnum);
               salva_quadrupla("GT", "$t", "$t", "$t", t1, t2, tempnum, 0);

               break;
            case IGUALIGUAL :

               //printf("(EQUAL, $t%d, $t%d, $t%d)\n", t1, t2, tempnum);
               salva_quadrupla("EQUAL", "$t", "$t", "$t", t1, t2, tempnum, 0);

               break;
            case DIF :

               //printf("(NEQ, $t%d, $t%d, $t%d)\n", t1, t2, tempnum);
               salva_quadrupla("NEQ", "$t", "$t", "$t", t1, t2, tempnum, 0);

               break;
            case MENIGUAL:

               //printf("(LEQ, $t%d, $t%d, $t%d)\n", t1, t2, tempnum);
               salva_quadrupla("LEQ", "$t", "$t", "$t", t1, t2, tempnum, 0);

               break;
            case MAIIGUAL:

               //printf("(GEQ, $t%d, $t%d, $t%d)\n", t1, t2, tempnum);
               salva_quadrupla("GEQ", "$t", "$t", "$t", t1, t2, tempnum, 0);

               break;
            default:
               //emitComment("BUG: Unknown operator");
               //printf("Operador desconhecido\n");
               Erro = 1;
               break;
         } 


         break; 

    default:
      break;
  }
} 

static void cGen( NoArvore * arv)
{ if (arv != NULL)
  { switch (arv->tipo_de_no) {
      case TStmt:
        genStmt(arv);
        break;
      case TExp:
        genExp(arv);
        break;
      case TDecl:
        genDecl(arv);
        break;
      default:
        break;
    }

    if (flag_irmao != 1){
        cGen(arv->irmao);
    }
  }
}

//gera o código intermediário utilizando a Função
// recursiva cGen, que percorre a arvore sintática
void geraCod(NoArvore * arv){

    inicializaPilha (&var_nome);

    cGen(arv);
    //printf("HALT\n\n");
    salva_quadrupla("HALT", " ", " ", " ", -1, -1, -1, 3);

}
