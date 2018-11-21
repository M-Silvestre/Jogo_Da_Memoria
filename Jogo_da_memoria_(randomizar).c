/*Trabalho Terceiro Estagio
Jogo da Memoria
ALunos:
	1810022455 - Matteus Silvestre
*/

#include <stdio.h> 
#include <stdlib.h>
#include <time.h>

//Definindo um tipo
typedef struct str_item{
	char letra; //Qual a letra do item
	int par; //Se a letra foi pareada
} item;


//Declarando funcoes
item** gera(int x); //Retorna uma vetor bidimensional de "item"
int menu();
void exibe(item** tab);


//Definindo funcoes
int main(){	
	int n = 1, x;
	item** tab;
	printf("JOGO DA MEMORIA\n\n");
	while(n){
	n = menu(); //Exibe as opcoes e recebe a escolha do usuario
	switch(n){
		case 1:
			ERRO:
			printf("Informe o tamanho do jogo (4 para 4x4, 6 para 6x6):");
			scanf("%d", &x);
			if((x!=4)&&(x!=6)){
				printf("Tamanho invalido!\n");
				goto ERRO;
			};
			tab = gera(x); //Gera um tabuleiro de tamanho x por x
			exibe(tab);
			free(tab);
			break;

		case 2:						
			break;

		case 0:	
			printf("Fim do programa.");
			return 0;
		}
	};
	return 0;
};

int menu(){
	int op;				
	printf("Digite 1 para um novo jogo\n"
			"Digite 2 para ver o ranking de jogadores\n"
			"Digite 0 para sair\n"
			"\tOpcao:");
	scanf("%d",&op);	
	return op;
};

item** gera(int x){
	int i, i2, j, j2, num, r;
	item** tab;
	tab = (item**)malloc(x*sizeof(item*));
	if(!(*tab)){
		printf("Erro na alocacao de memoria");
		return 0;
		};
	for(i=0; i<x; i++){
		tab[i] = (item*)malloc(x*sizeof(item));
		if(!(tab[i])){
			printf("Erro na alocacao de memoria");
			return 0;
		};
		for(j=0; j<x; j++){
			tab[i][j].par = 0;
			srand(time(NULL)); //Usar tempo como semente do comando rand(), para garantir variacao nos resultados
			DENOVO:
			num = 0;
			r = rand() % ((x*x)/2); //Gera um numero aleatorio entre 0 e (x*x/2 -1)
			switch(r){ //Numero determina a letra nessa item
				case 0:
					tab[i][j].letra = 'A';
					num++;
					break;
				case 1:
					tab[i][j].letra = 'B';
					num++;
					break;
				case 2:
					tab[i][j].letra = 'C';
					num++;
					break;
				case 3:
					tab[i][j].letra = 'D';
					num++;
					break;
				case 4:
					tab[i][j].letra = 'E';
					num++;
					break;
				case 5:
					tab[i][j].letra = 'F';
					num++;
					break;
				case 6:
					tab[i][j].letra = 'G';
					num++;
					break;
				case 7:
					tab[i][j].letra = 'H';
					num++;
					break;
				default:
					printf("Erro!");
			};
			/*As letras devem aparecer apenas duas vezes cada, portanto a letra atual deve ser comparada a todas as anteriores*/
			for(i2=0; i2<=i; i2++){
				if(i2<i){ //Antes da linha "i"
					for(j2=0; j2<x; j2++){	
						if(tab[i][j].letra==tab[i2][j2].letra){ //Compara a letra atual com todas da linha
							num++;
						};
						if(num>2) goto DENOVO;				
					}
				}
				else{ //Na linha "i"
					for(j2=0; j2<j; j2++){	
						if(tab[i][j2].letra==tab[i][j].letra){ //Compara a letra atual com as anteriores
							num++;
						};
						if(num>2) goto DENOVO;				
					};
				};
			};
		};
	};
	return tab;
};



void exibe(item** tab){
	int i,j;
	printf("\n");
	for (i=0; tab[i]; i++){
        for (j=0; tab[i][j].letra; j++){
            printf("\t%c", tab[i][j].letra);
        };
        printf("\n");
    };
	printf("\n");
}
