/*Trabalho Terceiro Est�gio
Jogo da Mem�ria
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
	int vis; //Se a letra esta vis�vel ou oculta
} item;
typedef struct str_jogo{
	char nome[20]; //Nome do jogador
	int jogadas; //Pontua��o de um jogador (com quantas jogadas ele venceu o jogo)
	int modo; //Se o jogo foi 4x4 ou 6x6
	struct str_jogo * prox; //Ponteiro para outra partida (gerando uma lista encadeada)
} partida;


//Declarando fun��es
item** gera_tab(int x);
int menu(), escolha(int x, item** *tab);
partida * recebe_ranking();
void exibe_tab(int x, item** tab), exibe_ranking(partida * lista), libera_tab(int x, item** tab);
void edita_ranking(partida * lista, int x, int jogadas), libera_lista(partida * lista), creditos();

//Definindo func�o principal
int main(){	
	setlocale(LC_ALL, "Portuguese"); //Habilitar acentos e "�"
	srand(time(NULL)); //Usar rel�gio como semente do comando rand() para garantir varia��o nos resultados
	int n=4, x;
	/*Op��o do usu�rio*/
	partida * lista; //Lista de jogadores do ranking
	printf("JOGO DA MEM�RIA\n\n");
	while(n){
	n = menu(); //Exibe as op��es e recebe a escolha do usu�rio
	switch(n){
		case 1:
			printf("\nInforme o tamanho do jogo (4 para 4x4, 6 para 6x6):\n"
			"Op��o: ");
			scanf("%d", &x);
			//Caso o usu�rio informe um tamanho inv�lido
			while((x!=4)&&(x!=6)){
				printf("Informe um tamanho v�lido! (4 para 4x4, 6 para 6x6)\n"
						"Op��o: ");
				scanf("%d", &x);
			};
			item** tab = gera_tab(x); //Gera um tabuleiro de tamanho x por x
			int res, pares = 0, jogadas = 0;
			exibe_tab(x, tab);
			//O programa deve receber escolhas do jogador at� que todos os pares sejam formados
			while(pares<(x*x/2)){
				//"res" recebe 1 se a escolha for "correta", e 0 for "errada"
				res = escolha(x, &tab);
				//O contador dos pares aumenta a cada par correto
				if(res){
					pares++;
				};
				//As jogadas at� se resolver o jogo s�o contadas
				jogadas++;
			};
			exibe_tab(x, tab);
			printf("Parab�ns, voc� ganhou no modo %dx%d! N�mero de jogadas: %d\n", x, x, jogadas);
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

//Fun��o para receber a escolha do usu�rio
int menu(){
	int op;
	ERROOP:		
	printf("MENU\n\n"
			"Digite 1 para um novo jogo.\n"
			"Digite 2 para ver o ranking de jogadores.\n"
			"Digite 3 para ver os cr�ditos do programa.\n"
			"Digite 0 para sair\n"
			"Op��o: ");
	scanf("%d",&op);
	if((op==1)||(op==2)||(op==3)||(op==0)){
		return op;
	}
	else{
		printf("Opcao inv�lida.\n\n");
		goto ERROOP;
	};
};

//Fun��o para gerar o tabuleiro de letras
item** gera_tab(int x){
	int i, j, k, tam_lista, r;
	//Gerando uma lista de letras
	tam_lista = (x*x);
	char* lista;
	lista = (char*)malloc(tam_lista*sizeof(char));
	if(!lista){
		printf("Erro na aloca��o de mem�ria");
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
		printf("Erro na aloca��o de mem�ria.\n");
		return 0;
	};
	//Gerando os itens do tabuleiro
	for(i = 0; i < x; i++){
		tab[i] = (item*)malloc(x*sizeof(item));
		if(!(tab[i])){
			printf("Erro na aloca��o de mem�ria.\n");
			return;
		};
		for(j = 0; j < x; j++){
			r = rand() % tam_lista; //Escolhe um n�mero aleat�rio, que corresponde a uma letra da lista
			tab[i][j].letra = lista[r]; //Faz dessa letra um item do tabuleiro
			tab[i][j].vis = 0; //A letra deve estar oculta no come�o do jogo
			for(k = r; k < tam_lista; k++){
				lista[k] = lista[k+1]; //"Move" cada letra ap�s a escolhida uma posi��o � frente, removendo a letra j� usada
			};
			tam_lista--; //Reduz o intervalo de n�meros a se escolher
		};
	};
	return tab;
};

//Fun��o para exibir o tabuleiro
void exibe_tab(int x, item** tab){
	int i,j;
	system("cls");
	printf("Tabuleiro\n\n");
	for (i = 0; i < x; i++){
        for (j = 0; j < x; j++){
        	if(tab[i][j].vis){ //A letra s� deve ser exibida se for escolhida ou j� foi pareada
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

//Fun��o que altera o tabuleiro
int escolha(int x, item** *tab){
	int x1, x2, y1, y2;
		ERROXY1:
		printf("\nInforme as coordenadas do primeiro n�mero: ");
		scanf("%d%d", &x1, &y1);
		//Caso o usu�rio informe coordenadas fora do tabuleiro
		if( (1 > x1) || (x1 > x) || (1 > y1) || (y1 > x) ){
			printf("Coordenadas inv�lidas!\n");
			goto ERROXY1;
		};
		x1--;
		y1--;
		//Caso o usu�rio escolha uma letra j� pareada
		if((*tab)[x1][y1].vis==1){
			printf("Essa letra j� foi pareada, escolha outra.\n");
			goto ERROXY1;
		};
		(*tab)[x1][y1].vis = 1;
		exibe_tab(x, *tab);
		ERROXY2:
		printf("\nInforme as coordenadas do segundo n�mero: ");
		scanf("%d%d", &x2, &y2);
		//Caso o usu�rio informe coordenadas fora do tabuleiro
		if( (1 > x2) || (x2 > x) || (1 > y2) || (y2 > x) ){
			printf("Coordenadas inv�lidas!\n");
			goto ERROXY2;
		};
		x2--;
		y2--;
		//Caso o usu�rio escolha o item anterior
		if((x1==x2)&&(y1==y2)){
			printf("Voc� precisa escolher dois itens diferentes!\n");
			goto ERROXY2;
		};
		//Caso o usu�rio escolha uma letra j� pareada
		if((*tab)[x2][y2].vis==1){
			printf("Essa letra j� foi pareada, escolha outra.\n");
			goto ERROXY2;
		};
		(*tab)[x2][y2].vis = 1;
		exibe_tab(x, *tab);
		if((*tab)[x1][y1].letra!=(*tab)[x2][y2].letra){
			printf("Letras diferentes, par n�o foi formado.\n");
			//As letras voltar�o a ser ocultas 
			(*tab)[x1][y1].vis = 0;
			(*tab)[x2][y2].vis = 0;
			return 0; //Escolha "errada"
		}
		else{
			printf("Letras iguais, par formado!\n");
			return 1; //Escolha "certa"
		};
};

//Fun��o que libera a memoria usada pelo tabuleiro
void libera_tab(int x, item ** tab){
	int i;
	//Libera a mem�ria em cada coluna (arrays de inteiros)
	for(i = 0; i < x; i++){
		free(tab[i]);
	};
	//Libera a mem�ria das linhas (ponteiros)
	free(tab);
};

//Fun��o que recebe o ranking do arquivo
partida * recebe_ranking() {
    FILE * arquivo = fopen("JMranking.txt", "r");
	//Verifica abertura do arquivo:
	if(!arquivo) {
		printf("Erro ao acessar arquivo.\n");
		return 0;
	};
    //In�cio do arquivo
    partida * lista = (partida*)malloc(sizeof(partida));
    //Verifica aloca��o
    if(!lista){
    	printf("Erro na aloca��o de mem�ria.\n");
    	return 0;
	};
	//Vari�vel para ler cada linha:
	char linha [40];
	//Primeira linha
	fgets(linha, 40, arquivo);
	//Se n�o houver nenhum registro no arquivo:
	if(feof(arquivo)) {
        printf("Ranking vazio... quer ser o primeiro?\n");
        return 0;
	};
	//Antes da v�rgula, h� o nome do jogador
    char * nome;  
    nome = strtok(linha,",");
    //Salva no primeiro elemento da lista
    strcpy(lista->nome, nome);
    
    //Depois da primeira v�rgula, vem a modalidade de jogo, 4x4 ou 6x6
    char * modo_string = strtok(NULL,",");
    //Transforma para inteiro e salva na lista:
    lista->modo = atoi(modo_string);
    
    //Depois da segunda v�rgula, vem a pontua��o do jogo
    char * jogadas_string = strtok(NULL,",");
    //Transforma para inteiro e salva na lista:
    lista->jogadas = atoi(jogadas_string);
    
    lista->prox = NULL;

    //Pr�ximos nomes
    fgets(linha, 60, arquivo);
    //Salva o ponteiro anterior para iterar:
    partida * aux = lista;
    //Enquanto n�o for o fim do arquivo
    while(!feof(arquivo)) {
        //Aloca mem�ria para um nova partida a ser lida:
        partida * novo = (partida*) malloc (sizeof(partida));
        //Verifica aloca��o
        if(!novo){
            printf("Erro na aloca��o de mem�ria.\n");
            return 0;
		};
        //Copiando a string lida antes da virgula, economizando variavel:
        strcpy(novo->nome,strtok(linha,","));
        //Capturando as strings depois das v�rgulas, transformando-as para inteiros e salvando no novo elemento da lista
        novo->modo = atoi(strtok(NULL,","));
        novo->jogadas= atoi(strtok(NULL,","));
        //Este � um novo elemento, depois dele n�o ha outro:
        novo->prox = 0;
        //O anterior, que guardava o fim da fila, agora vai apontar para o novo elemento criado:
        aux->prox = novo;
        //Agora o novo elemento criado e o anterior, pois quando iterar sera gerado um novo elemento
		aux = novo;
		//Antes de iterar, deve-se ler a pr�xima linha
        fgets(linha, 40, arquivo);
    }
    //Fechando o arquivo:
    fclose(arquivo);
    return lista;
};

//Fun��o para liberar a mem�ria usada para a lista
void libera_lista(partida * lista){
	//Uma vari�vel auxiliar � necess�ria para liberar a original
	partida * aux;
	while(lista){
		aux = lista;
        lista=lista->prox;
        free(aux);
    };
};

//Fun��o para exibir a lista
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
	//Alocando a mem�ria para os dois rankings
    if(tam4){
    	rank4 = (partida*)malloc(tam4*sizeof(partida));
    	if(!rank4){
    		printf("Erro na aloca��o de mem�ria.\n");
    		return;
		};
	};
    if(tam6){
    	rank6 = (partida*)malloc(tam6*sizeof(partida));
    	if(!rank6){
    		printf("Erro na aloca��o de mem�ria.\n");
    		return;
		};
	};
	//� preciso separar as partidas em rela��o ao modo
	aux = lista; //� preciso voltar ao come�o da lista
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
	com a ajuda de um espa�o auxiliar*/
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

//Fun��o que adiciona novos jogadores ao ranking, ou altera pontua��o de jogadores j� existentes
void edita_ranking(partida * lista, int x, int jogadas){
	char nome[20]; //Nome a ser recebido
	int i=0; //Se uma partida desse modo j� foi ganha por esse usu�rio
	
	//� preciso saber se o nome do jogador j� est� no ranking
	printf("Informe seu nome (at� 20 caracteres): ");
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
        //Se encontrar nome e modo iguais com mais jogadas (pontua��o "pior")
        if((!strcmp(aux->nome, nome)) && (aux->modo == x) && (aux->jogadas >= jogadas)) {
            //Reescreve no arquivo com o n�mero atualizador ("melhor") de jogadas 
            aux->jogadas = jogadas;
            fprintf(arquivo, "%s,%d,%d\n", aux->nome, aux->modo, aux->jogadas);
            i++;

        }
        //Caso cotr�rio, reescreve a partida como antes
        else{
        	fprintf(arquivo, "%s,%d,%d\n", aux->nome, aux->modo, aux->jogadas);
		};
        //Vai para o pr�xima partida da lista
        aux = aux->prox;
    };
    //Caso n�o haja nenhum jogador no ranking com o mesmo nome
    //e no mesmo modo de jogo, adicionar um novo nome no arquivo
    if(!i){
    	fprintf(arquivo, "%s,%d,%d\n", nome, x, jogadas);
    	fclose(arquivo);
    	libera_lista(lista);
		printf("Pontua��o adicionada com sucesso!\n\n");
		sleep(1);
		printf("(Pressione qualquer tecla para retornar ao menu)\n");
		getch();
		system("cls");
    	return;
	}
	else{
		fclose(arquivo);
		libera_lista(lista);
		printf("Pontua��o atualizada com sucesso!\n\n");
		sleep(1);
		printf("(Pressione qualquer tecla para retornar ao menu)");
		getch();
		system("cls");
    	return;
	};
};

//Fun��o que exibe os cr�ditos
void creditos(){
	system("cls");
	printf("CR�DITOS\n"
		"\nJogo da Mem�ria em C\n\n"
		"Instituicao: Unip� - Centro Universit�rio de Jo�o Pessoa\n"
		"Curso: Ci�ncias da Computa��o\n"
		"Unidade Curricular: Introdu�o a Programa��o\n"
		"Professor: Leandro Figueiredo Alves\n"
		"Aluno: Matteus Silvestre Maciel Das Neves Carvalho\n\n\n");
		sleep(1);
		printf("(Pressione qualquer tecla para retornar ao menu)\n");
		getch();
		system("cls");
		return;
}
