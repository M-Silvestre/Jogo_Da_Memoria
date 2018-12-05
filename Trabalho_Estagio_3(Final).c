/*Trabalho Terceiro Estágio
Jogo da Memória
ALunos:
	1810022455 - Matteus Silvestre
*/

#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <locale.h>
#include<dos.h>

//Definindo tipos para os itens do tabuleiro e as partidas
typedef struct str_item{
	char letra; //Qual a letra do item
	int vis; //Se a letra esta visível ou oculta
} item;
typedef struct str_jogo{
	char nome[20]; //Nome do jogador
	int jogadas; //Pontuação de um jogador (com quantas jogadas ele venceu o jogo)
	int modo; //Se o jogo foi 4x4 ou 6x6
	struct str_jogo * prox; //Ponteiro para outra partida (gerando uma lista encadeada)
} partida;


//Declarando funções
item** gera_tab(int x);
int menu(), escolha(int x, item** *tab);
partida * recebe_ranking();
void exibe_tab(int x, item** tab), exibe_ranking(partida * lista), libera_tab(int x, item** tab);
void edita_ranking(partida * lista, int x, int jogadas), libera_lista(partida * lista), creditos();

//Definindo funcão principal
int main(){	
	setlocale(LC_ALL, "Portuguese"); //Habilitar acentos e "ç"
	srand(time(NULL)); //Usar relógio como semente do comando rand() para garantir variação nos resultados
	int n=4, x;
	/*Opção do usuário*/
	partida * lista; //Lista de jogadores do ranking
	printf("JOGO DA MEMÓRIA\n\n");
	while(n){
	n = menu(); //Exibe as opções e recebe a escolha do usuário
	switch(n){
		case 1:
			printf("\nInforme o tamanho do jogo (4 para 4x4, 6 para 6x6):\n"
			"Opção: ");
			scanf("%d", &x);
			//Caso o usuário informe um tamanho inválido
			while((x!=4)&&(x!=6)){
				printf("Informe um tamanho válido! (4 para 4x4, 6 para 6x6)\n"
						"Opção: ");
				scanf("%d", &x);
			};
			item** tab = gera_tab(x); //Gera um tabuleiro de tamanho x por x
			int res, pares = 0, jogadas = 0;
			exibe_tab(x, tab);
			//O programa deve receber escolhas do jogador até que todos os pares sejam formados
			while(pares<(x*x/2)){
				//"res" recebe 1 se a escolha for "correta", e 0 for "errada"
				res = escolha(x, &tab);
				//O contador dos pares aumenta a cada par correto
				if(res){
					pares++;
				};
				//As jogadas até se resolver o jogo são contadas
				jogadas++;
			};
			exibe_tab(x, tab);
			printf("Parabéns, você ganhou no modo %dx%d! Número de jogadas: %d\n", x, x, jogadas);
			lista = recebe_ranking();
			edita_ranking(lista, x, jogadas);
			libera_tab(x, tab);
			break;

		case 2:
			lista = recebe_ranking();
			exibe_ranking(lista);
			break;
			
		case 3:
			creditos();				
			break;

		case 0:	
			printf("\nFim do programa.");
			return 0;
		}
	};
	return 0;
};

//Função para receber a escolha do usuário
int menu(){
	int op;	
	printf("MENU\n\n"
			"Digite 1 para um novo jogo.\n"
			"Digite 2 para ver o ranking de jogadores.\n"
			"Digite 3 para ver os créditos do programa.\n"
			"Digite 0 para sair\n"
			"Opção: ");
	ERROOP:
	scanf("%d",&op);
	if((op==1)||(op==2)||(op==3)||(op==0)){
		return op;
	}
	else{
		printf("\nOpcao inválida!\n\n");
		sleep(1);
		printf("Nova opção: ");		
		goto ERROOP;
	};
};

//Função para gerar o tabuleiro de letras
item** gera_tab(int x){
	int i, j, k, tam_lista, r;
	//Gerando uma lista de letras
	tam_lista = (x*x);
	char* lista;
	lista = (char*)malloc(tam_lista*sizeof(char));
	if(!lista){
		printf("Erro na alocação de memória");
		return 0;
	};
	switch(x){
		case 4:
			strcpy(lista, "AABBCCDDEEFFGGHH");
			break;
		case 6:
			strcpy(lista, "AABBCCDDEEFFGGHHIIJJKKLLMMNNOOPPQQRR");
			break;
		default:
			printf("Erro!\n");
			return;
	};
	//Gerando o tabuleiro
	item** tab;
	tab = (item**)malloc(x*sizeof(item*));
	if(!tab){
		printf("Erro na alocação de memória.\n");
		return 0;
	};
	//Gerando os itens do tabuleiro
	for(i = 0; i < x; i++){
		tab[i] = (item*)malloc(x*sizeof(item));
		if(!(tab[i])){
			printf("Erro na alocação de memória.\n");
			return;
		};
		for(j = 0; j < x; j++){
			r = rand() % tam_lista; //Escolhe um número aleatório, que corresponde a uma letra da lista
			tab[i][j].letra = lista[r]; //Faz dessa letra um item do tabuleiro
			tab[i][j].vis = 0; //A letra deve estar oculta no começo do jogo
			for(k = r; k < tam_lista; k++){
				lista[k] = lista[k+1]; //"Move" cada letra após a escolhida uma posição à frente, removendo a letra já usada
			};
			tam_lista--; //Reduz o intervalo de números a se escolher
		};
	};
	return tab;
};

//Função para exibir o tabuleiro
void exibe_tab(int x, item** tab){
	int i,j;
	system("cls");
	printf("Tabuleiro\n\n");
	for (i = 0; i < x; i++){
        for (j = 0; j < x; j++){
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

//Função que altera o tabuleiro
int escolha(int x, item** *tab){
	int x1, x2, y1, y2;
		ERROXY1:
		printf("\nInforme as coordenadas do primeiro número: ");
		scanf("%d%d", &x1, &y1);
		//Caso o usuário informe coordenadas fora do tabuleiro
		if( (1 > x1) || (x1 > x) || (1 > y1) || (y1 > x) ){
			printf("Coordenadas inválidas!\n");
			goto ERROXY1;
		};
		x1--;
		y1--;
		//Caso o usuário escolha uma letra já pareada
		if((*tab)[x1][y1].vis==1){
			printf("Essa letra já foi pareada, escolha outra.\n");
			goto ERROXY1;
		};
		(*tab)[x1][y1].vis = 1;
		exibe_tab(x, *tab);
		ERROXY2:
		printf("\nInforme as coordenadas do segundo número: ");
		scanf("%d%d", &x2, &y2);
		//Caso o usuário informe coordenadas fora do tabuleiro
		if( (1 > x2) || (x2 > x) || (1 > y2) || (y2 > x) ){
			printf("Coordenadas inválidas!\n");
			goto ERROXY2;
		};
		x2--;
		y2--;
		//Caso o usuário escolha o item anterior
		if((x1==x2)&&(y1==y2)){
			printf("Você precisa escolher dois itens diferentes!\n");
			goto ERROXY2;
		};
		//Caso o usuário escolha uma letra já pareada
		if((*tab)[x2][y2].vis==1){
			printf("Essa letra já foi pareada, escolha outra.\n");
			goto ERROXY2;
		};
		(*tab)[x2][y2].vis = 1;
		exibe_tab(x, *tab);
		if((*tab)[x1][y1].letra!=(*tab)[x2][y2].letra){
			printf("Letras diferentes, par não foi formado.\n");
			//As letras voltarão a ser ocultas 
			(*tab)[x1][y1].vis = 0;
			(*tab)[x2][y2].vis = 0;
			return 0; //Escolha "errada"
		}
		else{
			printf("Letras iguais, par formado!\n");
			return 1; //Escolha "certa"
		};
};

//Função que libera a memoria usada pelo tabuleiro
void libera_tab(int x, item ** tab){
	int i;
	//Libera a memória em cada coluna (arrays de inteiros)
	for(i = 0; i < x; i++){
		free(tab[i]);
	};
	//Libera a memória das linhas (ponteiros)
	free(tab);
};

//Função que recebe o ranking do arquivo
partida * recebe_ranking() {
    FILE * arquivo = fopen("JMranking.txt", "r");
	//Verifica abertura do arquivo:
	if(!arquivo) {
		printf("Erro ao acessar arquivo.\n");
		return 0;
	};
    //Início do arquivo
    partida * lista = (partida*)malloc(sizeof(partida));
    //Verifica alocação
    if(!lista){
    	printf("Erro na alocação de memória.\n");
    	return 0;
	};
	//Variável para ler cada linha:
	char linha [40];
	//Primeira linha
	fgets(linha, 40, arquivo);
	//Se não houver nenhum registro no arquivo:
	if(feof(arquivo)) {
        printf("Ranking vazio... quer ser o primeiro?\n");
        return 0;
	};
	//Antes da vírgula, há o nome do jogador
    char * nome;  
    nome = strtok(linha,",");
    //Salva no primeiro elemento da lista
    strcpy(lista->nome, nome);
    
    //Depois da primeira vírgula, vem a modalidade de jogo, 4x4 ou 6x6
    char * modo_string = strtok(NULL,",");
    //Transforma para inteiro e salva na lista:
    lista->modo = atoi(modo_string);
    
    //Depois da segunda vírgula, vem a pontuação do jogo
    char * jogadas_string = strtok(NULL,",");
    //Transforma para inteiro e salva na lista:
    lista->jogadas = atoi(jogadas_string);
    
    lista->prox = NULL;

    //Próximos nomes
    fgets(linha, 60, arquivo);
    //Salva o ponteiro anterior para iterar:
    partida * aux = lista;
    //Enquanto não for o fim do arquivo
    while(!feof(arquivo)) {
        //Aloca memória para um nova partida a ser lida:
        partida * novo = (partida*) malloc (sizeof(partida));
        //Verifica alocação
        if(!novo){
            printf("Erro na alocação de memória.\n");
            return 0;
		};
        //Copiando a string lida antes da virgula, economizando variavel:
        strcpy(novo->nome,strtok(linha,","));
        //Capturando as strings depois das vírgulas, transformando-as para inteiros e salvando no novo elemento da lista
        novo->modo = atoi(strtok(NULL,","));
        novo->jogadas= atoi(strtok(NULL,","));
        //Este é um novo elemento, depois dele não ha outro:
        novo->prox = 0;
        //O anterior, que guardava o fim da fila, agora vai apontar para o novo elemento criado:
        aux->prox = novo;
        //Agora o novo elemento criado e o anterior, pois quando iterar sera gerado um novo elemento
		aux = novo;
		//Antes de iterar, deve-se ler a próxima linha
        fgets(linha, 40, arquivo);
    }
    //Fechando o arquivo:
    fclose(arquivo);
    return lista;
};

//Função para liberar a memória usada para a lista
void libera_lista(partida * lista){
	//Uma variável auxiliar é necessária para liberar a original
	partida * aux;
	while(lista){
		aux = lista;
        lista=lista->prox;
        free(aux);
    };
};

//Função para exibir a lista
void exibe_ranking(partida * lista){
	system("cls");
    int i, j, tam4, tam6;
    partida * aux = lista, * rank4, * rank6;
    //Iterar na lista para contar quantas partida de cada tipo existem:
    for(tam4=0, tam6=0; aux; aux = aux->prox){
		switch(aux->modo){
			case 4:
				tam4++;
				break;
			case 6:
				tam6++;
				break;
		}
	};
	//Alocando a memória para os dois rankings
    if(tam4){
    	rank4 = (partida*)malloc(tam4*sizeof(partida));
    	if(!rank4){
    		printf("Erro na alocação de memória.\n");
    		return;
		};
	};
    if(tam6){
    	rank6 = (partida*)malloc(tam6*sizeof(partida));
    	if(!rank6){
    		printf("Erro na alocação de memória.\n");
    		return;
		};
	};
	//É preciso separar as partidas em relação ao modo
	aux = lista; //É preciso voltar ao começo da lista
    for(i = 0, j = 0; aux; aux = aux->prox){
    	switch(aux->modo){
			case 4:
				strcpy(rank4[i].nome, aux->nome);
				rank4[i].jogadas = aux->jogadas;
				i++;
				break;
			case 6:
				strcpy(rank6[j].nome, aux->nome);
				rank6[j].jogadas = aux->jogadas;				
				j++;
				break;
			default:
				return;
		}
	};
	//Reordenando os elementos das duas listas
	/*Cada elemento deve ser comparado aos anteriores. 
	Caso encontre algum maior, eles devem ser trocados de lugar
	com a ajuda de um espaço auxiliar*/
	partida aux_rank;
	for(i = 0; i < tam4; i++){
		for(j=0; j < i; j++){
			if(rank4[j].jogadas > rank4[i].jogadas){
					aux_rank = rank4[j];
					rank4[j] = rank4[i];
					rank4[i] = aux_rank;
			};
		};
	};
	for(i = 0; i < tam6; i++){
		for(j=0; j < i; j++){
			if(rank6[j].jogadas > rank6[i].jogadas){
					aux_rank = rank6[j];
					rank6[j] = rank6[i];
					rank6[i] = aux_rank;
			};
		};
	};
    //Para as partidas 4x4
    printf("RANKING DAS PARTIDAS 4X4:\n\n");
    for(i = 0; i < tam4; i++){
			printf("%d) %s: %d jogadas\n", (i+1), rank4[i].nome, rank4[i].jogadas);
	};
	//Para as partidas 6x6
	printf("\n\nRANKING DAS PARTIDAS 6X6:\n\n");
	for(j = 0; j < tam6; j++){
			printf("%d) %s: %d jogadas\n", (j+1), rank6[j].nome, rank6[j].jogadas);
	};
	free(rank4);
	free(rank6);
	libera_lista(lista);
	sleep(1);
	printf("\n(Pressione qualquer tecla para retornar ao menu)\n");
	getch();
	system("cls");
	return;
};

//Função que adiciona novos jogadores ao ranking, ou altera pontuação de jogadores já existentes
void edita_ranking(partida * lista, int x, int jogadas){
	char nome[20]; //Nome a ser recebido
	int i=0; //Se uma partida desse modo já foi ganha por esse usuário
	
	//É preciso saber se o nome do jogador já está no ranking
	printf("Informe seu nome (até 20 caracteres): ");
	scanf("%20s", &nome);
    //Para iterar na lista:
    partida * aux = lista;
    //Abrir o arquivo
    FILE * arquivo = fopen("JMranking.txt", "w+");
    if(!arquivo) {
		printf("Erro ao acessar arquivo.\n");
		return;
	};
	//Varre a lista de partidas e reescreve o arquivo
    while(aux){
        //Se encontrar nome e modo iguais com mais jogadas (pontuação "pior")
        if((!strcmp(aux->nome, nome)) && (aux->modo == x) && (aux->jogadas >= jogadas)) {
            //Reescreve no arquivo com o número atualizador ("melhor") de jogadas 
            aux->jogadas = jogadas;
            fprintf(arquivo, "%s,%d,%d\n", aux->nome, aux->modo, aux->jogadas);
            i++;

        }
        //Caso cotrário, reescreve a partida como antes
        else{
        	fprintf(arquivo, "%s,%d,%d\n", aux->nome, aux->modo, aux->jogadas);
		};
        //Vai para o próxima partida da lista
        aux = aux->prox;
    };
    //Caso não haja nenhum jogador no ranking com o mesmo nome
    //e no mesmo modo de jogo, adicionar um novo nome no arquivo
    if(!i){
    	fprintf(arquivo, "%s,%d,%d\n", nome, x, jogadas);
    	fclose(arquivo);
    	libera_lista(lista);
		printf("Pontuação adicionada com sucesso!\n\n");
		sleep(1);
		printf("(Pressione qualquer tecla para retornar ao menu)\n");
		getch();
		system("cls");
    	return;
	}
	else{
		fclose(arquivo);
		libera_lista(lista);
		printf("Pontuação atualizada com sucesso!\n\n");
		sleep(1);
		printf("(Pressione qualquer tecla para retornar ao menu)");
		getch();
		system("cls");
    	return;
	};
};

//Função que exibe os créditos
void creditos(){
	system("cls");
	printf("CRÉDITOS\n"
		"\nJogo da Memória em C\n\n"
		"Instituicao: Unipê - Centro Universitário de João Pessoa\n"
		"Curso: Ciências da Computação\n"
		"Unidade Curricular: Introduão a Programação\n"
		"Professor: Leandro Figueiredo Alves\n"
		"Aluno: Matteus Silvestre Maciel Das Neves Carvalho\n\n\n");
		sleep(1);
		printf("(Pressione qualquer tecla para retornar ao menu)\n");
		getch();
		system("cls");
		return;
}
