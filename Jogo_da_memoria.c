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
	int vis; //Se o item esta visivel ou oculto
	int par; //Se a letra foi pareada
} item;


//Declarando funcoes
item** gera(int x); //Retorna uma vetor bidimensional de "item"
int menu(), escolha(int x, item** *tab);
void exibe(item** tab);

//system("CLS") limpa a tela

//Definindo funcoes
int main(){	
	int n = 1, x, res=0, pares=0, jogadas=0;
	/*Opcao do usuario, tamanho do tabuleiro, resultado de escolha, numero de pares formados, numero de jogadas*/
	item** tab; //Tabuleiro
	FILE * arquivo = NULL; //Para ver o ranking e submeter pontuacao
	printf("JOGO DA MEMORIA\n\n");
	while(n){
	n = menu(); //Exibe as opcoes e recebe a escolha do usuario
	switch(n){
		case 1: //Novo Jogo
			ERRO:
			printf("Informe o tamanho do jogo(4 para 4 po 4, 6 para 5 por 6):\n"
			"Opcao: ");
			scanf("%d", &x);
			if((x!=4)&&(x!=6)){
				printf("Tamanho invalido!\n");
				goto ERRO;
			};
			tab = gera(x); //Gera um tabuleiro de tamanho x por x
			exibe(tab);
			while(pares<(x*x/2)){ //Receber escolhas do jogador ate todos os pares sejam formados
				res = escolha(x, &tab);
				if(res){
					pares++;
				};
				jogadas++;
			};
			exibe(tab);
			printf("Parabens, voce ganhou! Numero de jogadas: %d\n\n", jogadas);
			free(tab);
			break;
		case 2:
			arquivo = 					
			break;

		case 0:	
			printf("\nFim do programa.");
			return 0;
		}
	};
	return 0;
};

int menu(){
	int op;
	ERROOP:		
	printf("MENU"
			"Digite 1 para um novo jogo\n"
			"Digite 2 para ver o ranking de jogadores\n"
			"Digite 3 para ver os creditos\n"
			"Digite 0 para sair\n"
			"Opcao: ");
	scanf("%d",&op);
	if((op==1)||(op==2)||(op==3)||(op==0)){
		return op;
	}
	else{
		printf("Opcao invalida.\n\n");
		goto ERROOP;
	};
};

item** gera(int x){
	int i, i2, j, j2, r, num; //Iteracao, numero randomizado, contador de repeticao
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
			//A inicio a letra nao e exibida nem pareada
			tab[i][j].vis = 0;
			tab[i][j].par = 0;
			srand(time(NULL)); //Usar tempo como semente do comando rand(), para garantir variacao nos resultados
			DENOVO:
			num = 0;
			r = rand() % ((x*x)/2); //Gera um numero aleatorio entre 0 e 7 para x=4, e entre 0 e 17 para x=6
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
				case 8:
					tab[i][j].letra = 'I';
					num++;
					break;
				case 9:
					tab[i][j].letra = 'J';
					num++;
					break;
				case 10:
					tab[i][j].letra = 'K';
					num++;
					break;
				case 11:
					tab[i][j].letra = 'L';
					num++;
					break;
				case 12:
					tab[i][j].letra = 'M';
					num++;
					break;
				case 13:
					tab[i][j].letra = 'N';
					num++;
					break;
				case 14:
					tab[i][j].letra = 'O';
					num++;
					break;
				case 15:
					tab[i][j].letra = 'P';
					num++;
					break;
				case 16:
					tab[i][j].letra = 'Q';
					num++;
					break;
				case 17:
					tab[i][j].letra = 'R';
					num++;
					break;
				default:
					printf("Erro!");
			};
			/*As letras devem aparecer apenas duas vezes cada, portanto,
			a letra atual deve ser comparada a todas as anteriores*/
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
        	if((tab[i][j].vis)||(tab[i][j].par)){ //A letra so deve ser exibida se for escolhida ou ja foi pareada
        		printf("\t%c", tab[i][j].letra);
			}
			else{
				printf("\t-");
			};           	
        };
        printf("\n");
    };
	printf("\n");
};

int escolha(int x, item** *tab){ //Funcao escolha() vai alterar tab
	int x1, x2, y1, y2;
		ERROXY1:
		printf("\nInforme as coordenadas do primeiro numero: ");
		scanf("%d%d", &x1, &y1);
		x1--;
		y1--;
		if( (!(x1 >= 0 && x1 < x)) || (!(y1 >= 0 &&  y1 < x)) ){ //Caso o usuario informe coordenadas fora do esperado 
			printf("Coordenadas invalidas!\n");
			goto ERROXY1;
		};
		if((*tab)[x1][y1].par==1){
			printf("Essa letra ja foi pareada, escolha outra.\n");
			goto ERROXY1;
		};
		(*tab)[x1][y1].vis = 1;
		exibe(*tab);
		ERROXY2:
		printf("\nInforme as coordenadas do segundo numero: ");
		scanf("%d%d", &x2, &y2);
		x2--;
		y2--;
		if( (!(x2 >= 0 && x2 < x)) || (!(y2 >= 0 &&  y2 < x)) ){ //Caso o usuario informe coordenadas fora do esperado
			printf("Coordenadas invalidas!\n");
			goto ERROXY2;
		};
		if((x1==x2)&&(y1==y2)){
			printf("Voce precisa escolher dois itens diferentes!\n");
			goto ERROXY2;
		};
		if((*tab)[x2][y2].par==1){
			printf("Essa letra ja foi pareada, escolha outra.\n");
			goto ERROXY2;
		};
		(*tab)[x2][y2].vis = 1;
		exibe(*tab);
		if((*tab)[x1][y1].letra!=(*tab)[x2][y2].letra){
			printf("Letras diferentes, par nao foi formado.\n\n");
			(*tab)[x1][y1].vis = 0;
			(*tab)[x2][y2].vis = 0;
			return 0;
		}
		else{
			printf("Letras iguais, par formado!\n\n");
			(*tab)[x1][y1].par = 1;
			(*tab)[x2][y2].par = 1;
			return 1;
		};
}
