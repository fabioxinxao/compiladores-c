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
#define OP_open_parent 10
#define OP_close_parent 11
#define OP_open_key 12
#define OP_close_key 13
#define OP_sum 14
#define OP_sub 15
#define OP_multi 16
#define OP_div 17
#define OP_assignment 18 //atribuicao
#define OP_equal 19 
#define OP_comma 20 //virgula
#define OP_point_virg 21 
#define OP_highest 22
#define OP_minor 23
#define OP_greater_equal 24 
#define OP_smaller_equal 25
#define OP_diferent 26
#define TYPE_int 27
#define TYPE_float 28
#define TYPE_char 29
#define TYPE_ID 30
#define TAM_LEX 250

typedef struct Token
{
	char lexem[TAM_LEX];
	int type;
}Str_token;

//procedures
Str_token scanner(FILE *arq);
int RWord_find(char lex[]);
int OP_Find(char lex[]);

//var global
int line = 1;
int column = 0;
char lookup;



//main begin
int main(int argc, char **argv){
    Str_token token;
    FILE *arq;
    
if(argc > 1)
	{
		if (!(arq=fopen(argv[1],"rt")))
		{
			printf("Arquivo nao encontrado.\n");
			exit(1);
		}
		while (arq!=EOF){
			token=scanner(arq);
			printf("Token Lido:%s - Tipo:%d \n", token.lexem, token.type);
		}
		fclose(arq);
	}else{
		printf("Deve ser passado arquivo txt para teste.\n");
		exit(1);
	}

	return 0;
}


Str_token scanner(FILE *arq) {
	int i=0,estado=0,aceito=0;
	Str_token vet;
	static char lookup = ' ';
	
	
	while((lookup=getc(arq))!=EOF)
	{
		if (lookup==' ' || lookup=='\t')//tirar espaços em branco
			continue;	
		else if(lookup=='\n')
		{//somente incrementar linha
			line++;
			column=0;
		}
		
		else if(isalpha(lookup))//inicio identificador ou palavra reservada
		{
			i=0;
			column++;
			do
			{
				vet.lexem[i]=lookup;
				i++;
				lookup=getc(arq);
				column++;
				if(i>=TAM_LEX)
				{
					printf("Erro. tamanho do buffer excedido.\n");
					fclose(arq);
					exit(-1);
				}
			}while(isalpha(lookup) || isdigit(lookup));
			vet.lexem[i]='\0';
			if(lookup!=EOF)
				ungetc(lookup,arq);
			else
				lookup=0;
			vet.type=RWord_find(vet.lexem);
			if(vet.type<0)
				vet.type=RWord_find(vet.lexem);
			return vet;
		}//fim identificador ou palavra reservada
		
		else if(isdigit(lookup))//inicio "inteiro ou float"
		{
			while(!aceito)//estado de aceitacao
				{
					switch(estado){
					case 0: //sequencia de digitos
						lookup=getc(arq);
						if (isdigit(lookup))
						{
							vet.lexem[++i]=lookup;
							column++;
							estado=0;//continuacao da sequencia de digitos
						}
						else if(lookup=='.'){
							vet.lexem[++i]=lookup;
							column++;
							estado=2;//inicio de float
						}
						else
							estado=3;//estado de aceitacao
							vet.type= Rword_int;
							column++;
						break;
					
					case 1://iniciando com ponto um ponto definindo "float"
						lookup=getc(arq);					
						if (isdigit(lookup))
						{
							vet.lexem[++i]=lookup;
							estado=2;
						}
						else if(lookup=='.')
						{
							i--;
							fseek(arq,-1,SEEK_CUR);
							vet.type= Rword_float;
							estado=3;//estado de aceitacao
						}
						else{
							printf("Nao se esperava: '%c', float mal formado\n",lookup);
							estado=-1;//estado de negacao/erro
						}
						break;
					case 2://deve haver pelo menos um digito para completar float
						lookup=getc(arq);
						if (isdigit(lookup))
						{
							vet.lexem[++i]=lookup;
							estado=1;
						}
						else{
							printf("Nao se esperava: '%c', float mal formado\n",lookup);
							estado=-1;
						}
						break;
					case 3://estado de aceitacao
						if (lookup!=EOF)
							ungetc(lookup,arq);
						else
							lookup=0;
						vet.lexem[++i]='\0';
						aceito=1;
						return vet;
						break;
					case -1:
						if (lookup==EOF)
						{
							printf("Nao era esperado o fim de arquivo, error");
							fclose(arq);
							exit(1);
						}
					}
				}
			break;
		}
		else if (lookup=='<')//eh um operador relacional, verificar qual
		{
			vet.lexem[i]=lookup;
			lookup=getc(arq);
			if (lookup=='='){
				vet.lexem[i++]=lookup;
				vet.lexem[i++]='\0';
				vet.type=OP_smaller_equal;
				fseek(arq,-1,SEEK_CUR);
				return vet;
			}
			else{
				vet.lexem[i++]='\0';
				vet.type=OP_minor;
				fseek(arq,-1,SEEK_CUR);
				return vet;
			}
		}
		
		else if (lookup=='>')//eh um operador relacional, verificar qual
		{
			vet.lexem[i]=lookup;
			lookup=getc(arq);
			if (lookup=='='){
				vet.lexem[i++]=lookup;
				vet.lexem[i++]='\0';
				vet.type=OP_greater_equal;
				return vet;
			}
			else{
				vet.lexem[i++]='\0';
				vet.type=OP_highest;
				fseek(arq,-1,SEEK_CUR);
				return vet;
			}
		}
		else if (lookup=='!')//eh um operador relacional, verificar qual
		{
			vet.lexem[i]=lookup;
			lookup=getc(arq);
			if (lookup=='='){
				vet.lexem[i++]=lookup;
				vet.lexem[i++]='\0';
				vet.type=OP_diferent;
				return vet;
			}
			else{
				printf("era esperado o = mas apareceu: '%c' error123,\n",lookup);
				fclose(arq);
				exit(1);
			}
		}
		else if (lookup=='=')//pode ser operador aritmetico ou atribuicao
		{
			vet.lexem[i]=lookup;
			lookup=getc(arq);
			if (lookup=='='){//eh operador de comparacao
				vet.lexem[i++]=lookup;
				vet.lexem[i++]='\0';
				vet.type=OP_equal;
				return vet;
			}
			else{//eh operador de atribuicao
				vet.lexem[i++]='\0';
				vet.type=OP_assignment;
				fseek(arq,-1,SEEK_CUR);
				return vet;
			}
		}
		else if (lookup=='+')//operador de soma
		{
			vet.lexem[i]=lookup;
			vet.lexem[i++]='\0';
			vet.type=OP_sum;
			return vet;
		}
		else if (lookup=='-')//operador de subtracao
		{
			vet.lexem[i]=lookup;
			vet.lexem[i++]='\0';
			vet.type=OP_sub;
			return vet;
		}
		else if (lookup=='*')//operador de multiplicacao
		{
			vet.lexem[i]=lookup;
			vet.lexem[i++]='\0';
			vet.type=OP_sub;
			return vet;
		}
		
			
			
			
	}

}
	
	
int RWord_find(char lex[])
{
	if (strcmp(lex, "main") == 0)
		return Rword_main;
	if (strcmp(lex, "else") == 0)
		return Rword_else;
	if (strcmp(lex, "if") == 0)
		return Rword_if;
	if (strcmp(lex, "do") == 0)
		return Rword_do;
	if (strcmp(lex, "while") == 0)
		return Rword_while;
	if (strcmp(lex, "int") == 0)
		return Rword_int;	
	if (strcmp(lex, "float") == 0)
		return Rword_float;
	if (strcmp(lex, "char") == 0)
		return Rword_char;
	if (strcmp(lex, "for") == 0)
		return Rword_for;
	return -1;
}
	
	
	
	
	
	
	
	
	
	
	
