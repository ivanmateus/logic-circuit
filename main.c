#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct No{
	int info;
	char funcao;
	char indice[2];
	struct No *esq;
	struct No *dir;
};

typedef struct No No;
typedef struct No* Arv;

No *criaNo(char funcao, char *indice){
	No *novoNo = (No *)malloc(sizeof(No));
	if(novoNo != NULL){
		novoNo->info = 0;
		novoNo->funcao = funcao;
		strcpy(novoNo->indice, indice);
		novoNo->esq = NULL;
		novoNo->dir = NULL;
	}
	return novoNo;
}

Arv *criaArv(){
	Arv *raiz = (Arv *)malloc(sizeof(Arv));
	if(raiz != NULL){
		*raiz = NULL;
	}
	return raiz;
}

int insereArv(Arv *raiz, char funcao, char *indice){
	int inseriu = 0;
	if((*raiz) == NULL){
		No *novoNo = criaNo(funcao, indice);
		*raiz = novoNo;
		return 1;
	}
	if((*raiz)->funcao == 'N'){
		if((*raiz)->esq == NULL){
			inseriu = insereArv(&(*raiz)->esq, funcao, indice);
			return inseriu;
		}
		return inseriu;
	}
	if((*raiz)->funcao == 'E'){
		return inseriu;
	}
	inseriu = insereArv(&(*raiz)->esq, funcao, indice);
	if(inseriu == 0){
		inseriu = insereArv(&(*raiz)->dir, funcao, indice);
		return inseriu;
	}
	return inseriu;
}

No *procuraNo(Arv *raiz, char funcao, char *indice){
	No *achou = NULL;
	if(*raiz == NULL){
		return NULL;
	}else{
		if((*raiz)->funcao == funcao && strcmp((*raiz)->indice, indice) == 0){
			return *raiz;
		}
		achou = procuraNo(&(*raiz)->esq, funcao, indice);
		if(achou == NULL){
			if((*raiz)->dir != NULL){
				achou = procuraNo(&(*raiz)->dir, funcao, indice);
			}
			return achou;
		}
	}
	return achou;
}

int and(int a, int b){
	return a&&b;
}

int or(int a, int b){
	return a||b;
}

int nand(int a, int b){
	return !(and(a, b));
}

int nor(int a, int b){
	return !(or(a, b));
}

int xor(int a, int b){
	return ((!a)&&b)||(a&&(!b));
}

int not(int a){
	return !a;
}

void executeCirc(Arv *raiz){
	if((*raiz)->esq != NULL){
		executeCirc(&(*raiz)->esq);
	}
	if((*raiz)->dir != NULL){
		executeCirc(&(*raiz)->dir);
	}
	if((*raiz)->funcao == 'A'){
		(*raiz)->info = and((*raiz)->esq->info, (*raiz)->dir->info);
	}
	if((*raiz)->funcao == 'O'){
		(*raiz)->info = or((*raiz)->esq->info, (*raiz)->dir->info);
	}
	if((*raiz)->funcao == 'D'){
		(*raiz)->info = nand((*raiz)->esq->info, (*raiz)->dir->info);
	}
	if((*raiz)->funcao == 'R'){
		(*raiz)->info = nor((*raiz)->esq->info, (*raiz)->dir->info);
	}
	if((*raiz)->funcao == 'X'){
		(*raiz)->info = xor((*raiz)->esq->info, (*raiz)->dir->info);
	}
	if((*raiz)->funcao == 'N'){
		(*raiz)->info = not((*raiz)->esq->info);
	}
	return;
}

void setInfo(No *no, int info){
	if(no != NULL){
		no->info = info;
	}
}

//Remove o '\n' da palavra
void removeNL(char *input){
    int len = strlen(input);
    if(len > 0 && input[len-1] == '\n'){	//Se a string nao for vazia e o antepenultimo caractere for '\n'
        input[--len] = '\0';	//Troca por '\0'
    }
}

int insereArvPrefix(Arv *raiz, char *porta_0, char *porta_1, char *porta_2){

	if(*raiz == NULL){
		No *no_0 = criaNo(porta_0[0], porta_0 + 1);
		No *no_1 = criaNo(porta_1[0], porta_1 + 1);
		*raiz = no_0;
		(*raiz)->esq = no_1;
		if(porta_2 != NULL){
			No *no_2 = criaNo(porta_2[0], porta_2 + 1);
			(*raiz)->dir = no_2;
		}
		return 1;
	}
	No *aux = procuraNo(raiz, porta_0[0], porta_0 + 1);
	No *no_1 = criaNo(porta_1[0], porta_1 + 1);
	aux->esq = no_1;
	if(porta_2 != NULL){
		No *no_2 = criaNo(porta_2[0], porta_2 + 1);
		aux->dir = no_2;
	}
	return 1;
}

void menu(Arv *raiz){
	int montagem = -1;

	while(montagem != 0 && montagem != 1){
		scanf("%d ", &montagem);
	}

	if(montagem){
		char portas[100];
		char *vetPortas;
		fgets(portas, 99, stdin);
		vetPortas = strtok(portas, " ");
		while(vetPortas != NULL){
			removeNL(vetPortas);
			insereArv(raiz, *vetPortas, vetPortas + 1);
			vetPortas = strtok(NULL, " ");
		}

	}else{
		int numComandos = 0;
		int i = 0;
		char porta_0[4];
		char porta_1[4];
		char porta_2[4];
		scanf("%d", &numComandos);
		while(i < numComandos){
			scanf("%s", porta_0);
			if(porta_0[0] == 'N'){
				scanf("%s", porta_1);
				insereArvPrefix(raiz, porta_0, porta_1, NULL);
			}else{
				scanf("%s %s", porta_1, porta_2);
				insereArvPrefix(raiz, porta_0, porta_1, porta_2);
			}
			++i;
		}
	}
}

int numEntradas(Arv *raiz, int entradas){
	int numEnt = 0;
	if((*raiz)->funcao == 'E'){
		return (entradas + 1);
	}
	numEnt = numEntradas(&(*raiz)->esq, numEnt);
	numEnt = numEntradas(&(*raiz)->dir, numEnt);
	return numEnt;
}

No *procuraEntrada(Arv *raiz, int qualEntrada){
	No *entrada = NULL;

	if((*raiz)->funcao == 'E'){
		char *ptr;
		if(strtol((*raiz)->indice, &ptr, 10) == qualEntrada){
			return *raiz;
		}
		return NULL;
	}
	entrada = procuraEntrada(&(*raiz)->esq, qualEntrada);
	if(entrada == NULL){
		entrada = procuraEntrada(&(*raiz)->esq, qualEntrada);
	}
	return entrada;
}

void testes(Arv *raiz){
	int numTestes = 0;
	int valorEnt = 0;
	int i = 0;
	int j = 1;
	scanf("%d", &numTestes);

	while(i < numTestes){
		j = 1;
		while(j < numEntradas(raiz, 0) + 1){
			scanf("%d ", &valorEnt);
			setInfo(procuraEntrada(raiz, j), valorEnt);
			++j;
		}
		executeCirc(raiz);
		printf("%d\n", (*raiz)->info);
		++i;
	}
}

int main(int argc, char const *argv[]) {

	Arv *raiz = criaArv();

	menu(raiz);

	printf("%s\n", procuraEntrada(raiz, 0)->indice);
	printf("%s\n", procuraEntrada(raiz, 1)->indice);

	return 0;
}
