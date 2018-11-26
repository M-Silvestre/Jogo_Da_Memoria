/*Trabalho Terceiro Estágio
Jogo da Memória
ALunos:
	1810022455 - Matteus Silvestre
*/

#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#include <locale.h>

//Definindo um tipo
typedef struct str_item{
	char letra; //Qual a letra do item
	int vis; //Se a letra esta visível ou oculta
} item;


//Declarando funções
item** gera(int x); //Retorna uma vetor bidimensional de "item"
int menu(), escolha(int x, item** *tab);
void exibe(item** tab), creditos();


//Definindo funcoes
int main(){	
	setlocale(LC_ALL, "Portuguese");
	int n = 1, x, res=0, pares=0, jogadas=0;
	/*Opção do usuário, tamanho do tabuleiro, resultado de escolha, numero de pares formados, número de jogadas*/
	item** tab; //Tabuleiro
	FILE * ranking = fopen("JMranking.txt", "a+"); //Para exibir e editar o arquivo ranking
	printf("JOGO DA MEMÓRIA\n\n");
	while(n){
	n = menu(); //Exibe as opções e recebe a escolha do usuário
	switch(n){
		case 1: //Novo Jogo
			ERRO:
			printf("\nInforme o tamanho do jogo (4 para 4x4, 6 para 6x6):\n"
			"Opção: ");
			scanf("%d", &x);
			if((x!=4)&&(x!=6)){
				printf("Tamanho inválido!\n");
				goto ERRO;
			};
			tab = gera(x); //Gera um tabuleiro de tamanho x por x
			exibe(tab);
			while(pares<(x*x/2)){ //O programa deve receber escolhas do jogador até que todos os pares sejam formados
				res = escolha(x, &tab);
				if(res){
					pares++;
				};
				jogadas++;
			};
			exibe(tab);
			printf("Parabéns, você ganhou! Número de jogadas: %d\n\n", jogadas);
			free(tab);
			char nome[21];
			printf("Informe seu nome para submeter sua pontuação:\n\t");
			scanf("%20s", &nome);
			if (ranking == NULL){ 
       			printf("Erro ao abrir arquivo."); 
        		return -1; 
    		};
			fprintf(ranking, "%s : %d\n", nome, jogadas);
			printf("Pontuação adicionada com sucesso!\n\n");
			break;

		case 2:	//Ver ranking				
			break;
			
		case 3:	 //Créditos
			creditos();				
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
	printf("MENU\n\n"
			"Digite 1 para um novo jogo.\n"
			"Digite 2 para ver o ranking de jogadores.\n"
			"Digite 3 para ver os créditos do programa.\n"
			"Digite 0 para sair\n"
			"Opcao: ");
	scanf("%d",&op);
	if((op==1)||(op==2)||(op==3)||(op==0)){
		return op;
	}
	else{
		printf("Opcao inválida.\n\n");
		goto ERROOP;
	};
};

item** gera(int x){
	int i, i2, j, j2, r, num; //Variáveis para iteração, número randomizado, contador de repetições
	item** tab;
	srand(time(NULL)); //Usar relógio como semente do comando rand() para garantir variação nos resultados
	tab = (item**)malloc(x*sizeof(item*));
	if(!(*tab)){
		printf("Erro na alocação de memória");
		return 0;
		};
	for(i=0; i<x; i++){
		tab[i] = (item*)malloc(x*sizeof(item));
		if(!(tab[i])){
			printf("Erro na alocação de memória");
			return 0;
		};
		for(j=0; j<x; j++){			
			tab[i][j].vis = 0; //A inicio a letra nao e exibida
			DENOVO:
			r = rand() % ((x*x)/2); //Gera um número aleatório entre 0 e 7 (se x=4) ou 0 e 17 (se x=8)
			num = 1;
			switch(r){ //Número determina a letra nessa item
				case 0:
					tab[i][j].letra = 'A';
					break;
				case 1:
					tab[i][j].letra = 'B';
					break;
				case 2:
					tab[i][j].letra = 'C';
					break;
				case 3:
					tab[i][j].letra = 'D';
					break;
				case 4:
					tab[i][j].letra = 'E';
					break;
				case 5:
					tab[i][j].letra = 'F';
					break;
				case 6:
					tab[i][j].letra = 'G';
					break;
				case 7:
					tab[i][j].letra = 'H';
					break;
				case 8:
					tab[i][j].letra = 'I';
					break;
				case 9:
					tab[i][j].letra = 'J';
					break;
				case 10:
					tab[i][j].letra = 'K';
					break;
				case 11:
					tab[i][j].letra = 'L';
					break;
				case 12:
					tab[i][j].letra = 'M';
					break;
				case 13:
					tab[i][j].letra = 'N';
					break;
				case 14:
					tab[i][j].letra = 'O';
					break;
				case 15:
					tab[i][j].letra = 'P';
					break;
				case 16:
					tab[i][j].letra = 'Q';
					break;
				case 17:
					tab[i][j].letra = 'R';
					break;
				default:
					printf("Erro!");
			};
			/*As letras devem aparecer exatamente duas vezes cada, portanto,
			a letra atual deve ser comparada a todas as anteriores*/
			for(i2=0; i2<=i; i2++){
				if(i2<i){ //Antes da linha "i"...
					for(j2=0; j2<x; j2++){	//...compara a letra atual com todas da linha
						if(tab[i][j].letra==tab[i2][j2].letra){ 
							num++;
						};
						if(num>2) goto DENOVO;				
					}
				}
				else{ //Na linha "i"...
					for(j2=0; j2<j; j2++){	//...compara a letra atual com as anteriores
						if(tab[i][j2].letra==tab[i][j].letra){
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
	system("CLS");
	printf("Tabuleiro\n\n");
	for (i=0; tab[i]; i++){
        for (j=0; tab[i][j].letra; j++){
        	if(tab[i][j].vis){ //A letra só deve ser exibida se for escolhida ou já foi pareada
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

int escolha(int x, item** *tab){ //Função escolha() vai alterar p conteúdo de "tab"
	int x1, x2, y1, y2;
		ERROXY1:
		printf("\nInforme as coordenadas do primeiro número: ");
		scanf("%d%d", &x1, &y1);
		if( (1 > x1) || (x1 > x) || (1 > y1) || (y1 > x) ){ //Caso o usuário informe coordenadas fora do esperado 
			printf("Coordenadas inválidas!\n");
			goto ERROXY1;
		};
		x1--;
		y1--;
		if((*tab)[x1][y1].vis==1){
			printf("Essa letra já foi pareada, escolha outra.\n");
			goto ERROXY1;
		};
		(*tab)[x1][y1].vis = 1;
		exibe(*tab);
		ERROXY2:
		printf("\nInforme as coordenadas do segundo número: ");
		scanf("%d%d", &x2, &y2);
		if( (1 > x2) || (x2 > x) || (1 > y2) || (y2 > x) ){ //Caso o usuário informe coordenadas fora do esperado
			printf("Coordenadas inválidas!\n");
			goto ERROXY2;
		};
		x2--;
		y2--;
		if((x1==x2)&&(y1==y2)){
			printf("Você precisa escolher dois itens diferentes!\n");
			goto ERROXY2;
		};
		if((*tab)[x2][y2].vis==1){
			printf("Essa letra já foi pareada, escolha outra.\n");
			goto ERROXY2;
		};
		(*tab)[x2][y2].vis = 1;
		exibe(*tab);
		if((*tab)[x1][y1].letra!=(*tab)[x2][y2].letra){
			printf("Letras diferentes, par não foi formado.\n");
			(*tab)[x1][y1].vis = 0;
			(*tab)[x2][y2].vis = 0;
			return 0;
		}
		else{
			printf("Letras iguais, par formado!\n");
			return 1;
		};
};

void creditos(){
	system("CLS");
	printf("CRÉDITOS\n"
		"\nJogo da Memória em C\n\n"
		"Instituicao: Unipê - Centro Universitário de João Pessoa\n"
		"Curso: Ciências da Computação\n"
		"Unidade Curricular: Introduão a Programação\n"
		"Professor: Leandro Figueiredo Alves\n"
		"Aluno: Matteus Silvestre Maciel Das Neves Carvalho\n\n\n"
	"(Pressione qualqer tecla para voltar ao menu)");
	getch();
	system("CLS");
}
