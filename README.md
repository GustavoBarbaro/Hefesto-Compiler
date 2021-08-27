<img src="https://user-images.githubusercontent.com/48565991/131067127-85ff459f-4d4e-468b-96f4-bbe610f11924.png" data-canonical-src="https://user-images.githubusercontent.com/48565991/131067127-85ff459f-4d4e-468b-96f4-bbe610f11924.png" width="600" height="450" />


# About

This project is a C minus compiler that can compile C minus codes and generate the binary executable to a processor MIPS based using a RISC instruction set.


---

# Requirements

* Preferably linux OS
* Flex - Fast Lexical Analyzer Generator
* Bison parser from GNU Project
* gcc compiler



# How to run

Go to `\compCMenos\` and open a terminal or a cmd and run the following commands


### Linux

Run the script `run.sh` in terminal

``` bash =
bash run.sh
```

### Windows

Run the following commands in cmd

```
bison -d parse.y
```
```
flex scan.l
```
```
gcc -c lex.yy.c
```
```
gcc main.c lex.yy.o parse.tab.c definitions.c symtab.c analyze.c cgen.c assembly.c binario.c -o exec -lfl -ly
```
```
exec.exe
```

# Specifications

## Registers
The compiler assume that target processor has 32 registers.

* 26 registers for general purpose numbered like $t0 ... $t25
* 1 register with the value zero called $zero
* 1 register auxiliar called $aux
* 1 register used to store the return value of functions called $ra
* 1 register used to store inputs called $rf
* 1 register used to store the stack pointer called $sp
* 1 register used to store the frame pointer called $fp

## Assembly

### Type of Instructions

| Quadruple 	| Example 	| Function 	|
|---	|---	|---	|
| ADD 	| (ADD, c1, c2, c3) 	| c3 = c1 + 2 	|
| SUB 	| (SUB, c1, c2, c3) 	| c3 = c1 - 2 	|
| MUL 	| (MUL, c1, c2, c3) 	| c3 = c1 * 2 	|
| DIV 	| (DIV, c1, c2, c3) 	| c3 = c1 / 2 	|
| LT 	| (LT, c1, c2, c3) 	| Test if c1 < c2.<br>If yes, c3 = 1. <br>Else, c3 = 0. 	|
| GT 	| (GT, c1, c2, c3) 	| Test if c1 > c2.<br>If yes, c3 = 1. <br>Else, c3 = 0. 	|
| EQUAL 	| (EQUAL, c1, c2, c3) 	| Test if c1 == c2.<br>If yes, c3 = 1. <br>Else, c3 = 0." 	|
| NEQ 	| (NEQ, c1, c2, c3) 	| Test if c1 != c2.<br>If yes, c3 = 1. <br>Else, c3 = 0. 	|
| LEQ 	| (LEQ, c1, c2, c3) 	| Test if c1 <= c2.<br>If yes, c3 = 1. <br>Else, c3 = 0. 	|
| GEQ 	| (GEQ, c1, c2, c3) 	| Test if c1 >= c2.<br>If yes, c3 = 1. <br>Else, c3 = 0. 	|
| LOAD (not vector) 	| (LOAD, c1, c2) 	| c1 = c2 	|
| LOAD (vector) 	| (LOAD, c1, c2, c3) 	| c1 = c2 [ c3 ] 	|
| STORE (not vector) 	| (STORE, c1, c2) 	| c1 = c2 	|
| STORE (vector) 	| (STORE, c1, c2, c3) 	| c1 = c2 [ c3 ] 	|
| IFF 	| (IFF, c1, c2) 	| Test if c1 == 0,<br>If yes, take the detour to c2.<br>Else, pass 	|
| GOTO 	| (GOTO, c1) 	| Detour to c1 	|
| LABEL 	| (LABEL, c1) 	| Flag the region where the deviations will come. 	|
| ASSIGN 	| (ASSIGN, c1, c2) 	| c1 = c2 	|
| RET 	| (RET, c1) 	| Return the value stored in c1 	|
| PARAM 	| (PARAM, c1) 	| Flag that c1 is a parameter 	|
| CALL 	| (CALL, c1, c2, c3) 	| Function calling:<br>c1 is the name of function<br>c2 is the amount of arguments<br>c3 is where store the function return value 	|
| FUN 	| (FUN, c1, c2) 	| Function declaration of type c1 and name c2 	|
| END 	| (END, c1) 	| End of function of name c1 	|
| ARG 	| (ARG, c1, c2, c3) 	| Argument of type c1<br>name c2 and scope c3 	|
| ALLOC (not vector) 	| (ALLOC, c1, c2) 	| Argument allocation of variable c1 in scope c2 	|
| ALLOC (vector) 	| (ALLOC, c1, c2, c3) 	| Vector c1 allocation in scope c2<br>with lenght c3 	|



---


# Example

Here a example of the following C minus code:

```c
int gcd ( int u , int v){
    if (v == 0) return u;
    else return gcd (v , u -u /v*v) ;
}
void main ( void ){
    int x; int y;
    x = input () ;
    y = input () ;
    output ( gcd (x ,y));
}
```

| C- Code 	| Intermediate Code 	| Assembly Code 	|
|:---:	|:---:	|:---:	|
|  	|  	| jump 32 	|
| int gcd ( int u , int v) 	| (FUN, int, gcd,  ) 	| sw $fp $ra 1 	|
|  	|  	| addi $sp $sp 1 	|
|  	| (ARG, int, u, gcd) 	| addi $sp $sp 1 	|
|  	| (ARG, int, v, gcd) 	| addi $sp $sp 1 	|
|  	| (LOAD, $t0, u,  ) 	| lw $fp $t0 2 	|
|  	| (LOAD, $t1, v,  ) 	| lw $fp $t1 3 	|
| if (v ==0) return u; 	| (LOAD, $t2, v,  ) 	| lw $fp $t2 3 	|
|  	| (LOAD, $t3, 0,  ) 	| li $t3 0  	|
|  	| (EQUAL, $t2, $t3, $t4) 	| xnor $t2 $t3 $t4 	|
|  	| (IFF, $t4, L0,  ) 	| beq $t4 $zero 12 	|
|  	| (LOAD, $t2, u,  ) 	| lw $fp $t2 2 	|
|  	| (RET, $t2,  ,  ) 	| addi $t2 $ra 0 	|
|  	| (GOTO, L1,  ,  ) 	| jump 30   	|
| else return gcd (v , u -u /v*v) ; 	| (LAB, L0,  ,  ) 	|  	|
|  	| (LOAD, $t3, v,  ) 	| lw $fp $t3 3 	|
|  	| (PARAM, $t3,  ,  ) 	|  	|
|  	| (LOAD, $t5, u,  ) 	| lw $fp $t5 2 	|
|  	| (LOAD, $t6, u,  ) 	| lw $fp $t6 2 	|
|  	| (LOAD, $t7, v,  ) 	| lw $fp $t7 3 	|
|  	| (DIV, $t6, $t7, $t8) 	| div $t6 $t7 $t8 	|
|  	| (LOAD, $t6, v,  ) 	| lw $fp $t6 3 	|
|  	| (MUL, $t8, $t6, $t7) 	| mult $t8 $t6 $t7 	|
|  	| (SUB, $t5, $t7, $t6) 	| sub $t5 $t7 $t6 	|
|  	| (PARAM, $t6,  ,  ) 	|  	|
|  	| (CALL, gcd, 2, $t5) 	| sw $sp $fp 0 	|
|  	|  	| addi $sp $fp 0 	|
|  	|  	| addi $sp $sp 1 	|
|  	|  	| sw $fp $t6 3 	|
|  	|  	| sw $fp $t3 2 	|
|  	|  	| jal 1 	|
|  	|  	| addi $fp $sp 0 	|
|  	|  	| lw $fp $fp 0 	|
|  	| (RET, $t5,  ,  ) 	| addi $t5 $ra 0 	|
|  	| (LAB, L1,  ,  ) 	|  	|
| End of function gcd 	| (END, gcd,  ,  ) 	| lw $fp $ra 1 	|
|  	|  	| jr $ra $zero $zero 	|
| void main ( void ) 	| (FUN, void, main,  ) 	| addi $zero $fp 128 	|
|  	|  	| addi $fp $sp 0 	|
| int x; int y; 	| (ALLOC, x, main,  ) 	| addi $sp $sp 1 	|
|  	| (ALLOC, y, main,  ) 	| addi $sp $sp 1 	|
| x = input () ; 	| (LOAD, $t0, x,  ) 	| lw $fp $t0 0 	|
|  	| (CALL, input, 0, $t1) 	| INPUT $rf 	|
|  	| (ASSIGN, $t0, $t1,  ) 	| addi $t1 $t0 0 	|
|  	| (STORE, x, $t0,  ) 	| sw $fp $t0 0 	|
| y = input () ; 	| (LOAD, $t0, y,  ) 	| lw $fp $t0 1 	|
|  	| (CALL, input, 0, $t1) 	| INPUT $rf 	|
|  	| (ASSIGN, $t0, $t1,  ) 	| addi $t1 $t0 0 	|
|  	| (STORE, y, $t0,  ) 	| sw $fp $t0 1 	|
| output ( gcd (x ,y)); 	| (LOAD, $t0, x,  ) 	| lw $fp $t0 0 	|
|  	| (PARAM, $t0,  ,  ) 	|  	|
|  	| (LOAD, $t1, y,  ) 	| lw $fp $t1 1 	|
|  	| (PARAM, $t1,  ,  ) 	|  	|
|  	| (CALL, gcd, 2, $t2) 	| sw $sp $fp 0 	|
|  	| (PARAM, $t2,  ,  ) 	|  	|
|  	| (CALL, output, 1, $t3) 	|  	|
| End of function main 	| (END, main,  ,  ) 	|  	|
|  	| (HALT,  ,  ,  ) 	|  	|

# Videos
(In portuguese)

[Introduction](https://www.youtube.com/watch?v=-bkdUtXQwog)

[Generation of Intermediate Code](https://www.youtube.com/watch?v=fKv_2n3Gr-s)

[Generation of Executable File](https://www.youtube.com/watch?v=2LKvlfDtEXQ)

<img src="https://user-images.githubusercontent.com/48565991/130857102-4ea75ea9-4a4e-4f5e-83e1-5451bd99b1c6.png" data-canonical-src="https://user-images.githubusercontent.com/48565991/130857102-4ea75ea9-4a4e-4f5e-83e1-5451bd99b1c6.png" width="200" height="200" />




	  _____ ____   ____
	 / ____|  _ \ / __ \
	| |  __| |_) | |  | |
	| | |_ |  _ <| |  | |
	| |__| | |_) | |__| |
	 \_____|____/ \____/

