#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>


#define Rword_main
#define Rword_if
#define Rword_else
#define Rword_do
#define Rword_while
#define Rword_for
#define Rword_char
#define Rword_int
#define Rword_float
#define Rword_open_parent 
#define Rword_close_parent 
#define Rword_open_chave
#define Rword_close_chave
#define Rword_soma 
#define Rword_sub 
#define Rword_multi 
#define Rword_div 
#define Rword_atribuicao 
#define Rword_igualdade 
#define Rword_virgula 
#define Rword_ponto_virg 
#define Rword_maior 
#define Rword_menor 
#define Rword_maior_igual 
#define Rword_menor_igual 
#define Rword_diferente 
#define TYPE_int 
#define TYPE_float 
#define TYPE_char
#define ID 30

typedef struct Token {
	char lexema[300];
	int tipo;
}Struct_Token;


Struct_Token Scanner(FILE *arq);
int RetornaTipoPalavra(char palavra[]);


//VARIAVEIS GLOBAIS
int linha = 1;
int coluna = 1;
Struct_Token lexm;


//var global
char caractere;


//procedures
int scanner(FILE *arq){
	int i = 0;
	int linha = 0;
	int coluna = 0;
	
	
	
}

//main do program
int main(int argv, char **argc){
    int token;
    FILE *arq;
    
//abrir arquivo de texto para leitura
    arq = fopen("teste.txt","r");
    //enquanto não for o fim do arquivo, scanner vai receber o prox caractere para formar o token
    while(!feof(arq)){
        token = scanner(arq); 
        if(token!=1){
        	printf("Token mal formado");
        	break;
		}
	}
	
	if(feof(arq))
		printf("Fim de arquivo");
    fclose(arq);
    return 0;
}



