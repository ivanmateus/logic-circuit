#include <stdio.h>
#include <stdlib.h>
#include "ArvoreBinaria.h"

int main()
{
    int N = 8, dados[8] = {50,100,30,20,40,45,35,37};

    ArvBin* raiz = cria_ArvBin();

    int i;
    for(i=0; i < N; i++)
        insere_ArvBin(raiz,dados[i]);

    printf("Dados:\n");
    emOrdem_ArvBin(raiz);

    printf("\n");
    printf("Percurso:\n");
    Exibe_emOrdem_ArvBin(raiz);

    system("Pause");
    printf("\n");

    i=0;
    Procura_preOrdem_ArvBin(raiz,45, &i);
    if (i==0) printf ("Nao Achou! \n");

    system("Pause");

    libera_ArvBin(raiz);

    return 0;
}
