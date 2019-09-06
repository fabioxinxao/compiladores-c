#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

//reserved words
#define Rword_main 1
#define Rword_if 2
#define Rword_else 3
#define Rword_do 4
#define Rword_while 5
#define Rword_for 6
#define Rword_char 7
#define Rword_int 8 
#define Rword_float 9
#define Rword_open_parent 10
#define Rword_close_parent 11
#define Rword_open_key 12
#define Rword_close_key 13
#define Rword_sum 14
#define Rword_sub 15
#define Rword_multi 16
#define Rword_div 17
#define Rword_assignment 18 //atribuicao
#define Rword_equal 19 
#define Rword_comma 20 //virgula
#define Rword_point_virg 21 
#define Rword_highest 22
#define Rword_minor 23
#define Rword_greater_equal 24 
#define Rword_smaller_equal 25
#define Rword_diferent 26
#define TYPE_int 27
#define TYPE_float 28
#define TYPE_char 29
#define ID 30 30

typedef struct Token
{
	char lexem[200];
	int type;
}Str_Token;


Str_Token scanner(FILE *arq);
int RetornaTipoPalavra(char palavra[]);


//var global
int line = 1;
int column = 1;
Str_Token lexm;
char character;


//procedures
int scanner(FILE *arq)
{
	int i = 0;
	int line = 0;
	int column = 0;
}

//main begin
int main(int argv, char **argc){
    Str_token token;
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


Str_token scanner(FILE *arq) {
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
