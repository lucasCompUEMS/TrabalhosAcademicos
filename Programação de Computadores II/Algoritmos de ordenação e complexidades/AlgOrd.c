#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

/* Lucas da Rocha Silva 38345 */

/* algoritmo de ordenacao bubble-sot-original
passando o vetor e seu tamanho no parametro */
void Bubble_sort_original(int32_t vet[], long int TamVet){
    long int i, j;
    int32_t temp;

    for(i = 0; i < TamVet; i++){
        for(j = 0; j < TamVet - 1; j++){
            if(vet[j] > vet[j+1]){
                temp = vet[j+1];
                vet[j+1] = vet[j];
                vet[j] = temp;
            }
        }
    }

}

/* buuble-sort-melhorado passando os parametros vetor, e seu tamanho */
void Bubble_sort_melhorado(int32_t vet[], long int TamVet){
    long int j, mudou = 1, guardar = TamVet, aux = TamVet;
    int32_t temp;

    while(mudou == 1) {
        j = 0;
        mudou = 0;
        while(j < aux - 1) {
            if (vet[j] > vet[j + 1]) {
                temp = vet[j + 1];
                vet[j + 1] = vet[j];
                vet[j] = temp;
                mudou = 1;
                guardar = j + 1;

            }
            j++;
        }
        aux = guardar;
    }
}

/* insertion-sort, tambem passando somente o vetor e seu tamanho */
void Insertion_sort(int32_t vet[], long int TamVet){
    long int i, j;
    int32_t valor;

    for(i = 1; i < TamVet; i++){
        valor = vet[i];
        j = i - 1;

        while(j >= 0 && valor < vet[j]){
            vet[j + 1] = vet[j];
            j = j - 1;
        }
        vet[j + 1] = valor;
    }
}

/* funcao intercalar da funcao mergesort aqui crio 2 sub vetores para auxiliar na intercalacao
e depois libero espaco dos subvetores. Nesta funcao esta sendo passado 'esq' que é o inicio
do vetor o 'centro' e 'dir' que é o final, esses parametros segue de acordo com a chamada recursiva 
do mergesort() para intercala()  */
void Intercalar(int32_t vet[], long int esq, long int centro, long int dir){

    int32_t *E = NULL, *D = NULL;
    long int Tam1 = centro - esq + 1, Tam2 = dir - centro;
    long int i, j, k;

    /* alocando subvetores */
    E = malloc(Tam1*sizeof(int32_t));
    D = malloc(Tam2*sizeof(int32_t));

    if(E != NULL && D != NULL){
        /* copiar a primeira parte na esquerda e segunda parte na direita */
        for(i = 0; i < Tam1; i++)
            E[i] = vet[esq + i];

        for(j = 0; j < Tam2; j++)
            D[j] = vet[centro + j + 1];

        /* inicializando as variaveis que vai auxilar com os subvetores e k com vetor original */
        i = 0;
        j = 0;
        k = esq;

        /* ir percorrendo ate 'i' e 'j' estiverem nos intervalos dos subvetores */
        while(i < Tam1 && j < Tam2){

            /* aqui compara subvetor da esquerda com o da direita caso o valor de posicao 'i' do subvetor E <= o valor da
            posicao 'j' de D entao armazenar na esquerda do vetor original caso contrario armazenar na parte direita */
            if(E[i] <= D[j]){
                vet[k] = E[i];
                i++;

            } else{
                vet[k] = D[j];
                j++;
            }
            k++;
        }

        /* se sobrar valores no vetor E entao copiar os que falta para o 'vet' da posicao 'k' de onde parou */
        while(i < Tam1){
            vet[k] = E[i];
            i++;
            k++;
        }

        /* mesma ideia so que agora copia o valor do vetor D da posicao 'j' para 'vet' de onde parou o 'k' mais recente */
        while(j < Tam2){
            vet[k] = D[j];
            j++;
            k++;
        }

        free(E);
        free(D);
    }
    else
        printf("erro ao alocar subvetores!!\n");
}

/* no mergesort esta sendo passado a variavel 'esq' que é o inicio do vetor
e tambem dir o final do vetor */
void Mergesort(int32_t vet[], long int esq, long int dir){

    long int centro;

    if(esq < dir){
        centro = floor((esq + dir)/2);
        Mergesort(vet, esq, centro);
        Mergesort(vet, centro + 1, dir);
        Intercalar(vet, esq, centro, dir);
    }

}

/* funcao para criar um heap para a ordenacao heapsort com parametros 
o vetor o indice 'i' do for da funcao Heapsort() que aqui vai ser o inicio */
void descer(int32_t vet[], int i, int fim){

    int j = i * 2 + 1;
    int32_t aux = vet[i];
    while(j <= fim) {
        if (j < fim) {
            if (vet[j] < vet[j + 1])
                j++;
        }

        if (aux < vet[j]) {
            vet[i] = vet[j];
            i = j;
            j = i * 2 + 1;

        } else
            j = fim + 1;
    }
    vet[i] = aux;
}

/* heapsort com parametros vet e o seu tamanho */
void Heapsort(int32_t vet[], long int TamVet){
    long int m = TamVet - 1, i;
    int32_t aux;

    /* construindo lista de prioridade */
    for(i = (TamVet - 1)/2; i >= 0; i--)
        descer(vet, i, TamVet - 1);

    while(m > 0){
        aux = vet[0];
        vet[0] = vet[m];
        vet[m] = aux;
        m--;
        descer(vet, 0, m - 1);
    }
}

/* algoritmo de ornacao quick-sort com pivo sendo o ultimo elemento
passado como parametros o vetor, o inicio do vetor e o fim */
void QuickPivoUlt(int32_t vet[], long int ini, long int fim){

    static long int i, j;
    static int32_t pivo;
    int32_t temp;
    
    if(fim - ini >= 2){

        pivo = vet[fim];
        i = ini;
        j = fim - 1;

        while(j >= i){
            while(vet[i] < pivo)
                i++;

            while(vet[j] > pivo && j >= ini)
                j--;

            if(j >= i){
                temp = vet[i];
                vet[i] = vet[j];
                vet[j] = temp;
                i++;
                j--;
            }
        }
        

        temp = vet[i];
        vet[i] = pivo;
        vet[fim] = temp;

        QuickPivoUlt(vet, ini, i - 1);
        QuickPivoUlt(vet, i + 1, fim);

    }else
        if(fim - ini == 1){
            if(vet[ini] > vet[fim]){
                temp = vet[ini];
                vet[ini] = vet[fim];
                vet[fim] = temp;
            }
        }

}

/* quick-sort com pivo sendo um elemento aleatorio com os mesmos parametros
vetor, seu inicio e seu fim  */
void QuickPivoAle(int32_t vet[], long int ini, long int fim){

    static int i, j;
    long int pos;
    static int32_t pivo;
    int32_t temp;

    if(fim - ini >= 2){

        /* gerando elementos aleatorios entre [ini, fim] */
        srand(time(NULL));
        pos = ini + rand() % (fim - ini + 1);
        temp = vet[pos];
        vet[pos] = vet[fim];
        vet[fim] = temp;

        pivo = vet[fim];
        i = ini;
        j = fim - 1;

        while(j >= i){
            while(vet[i] < pivo)
                i++;

            while(vet[j] > pivo && j >= ini)
                j--;

            if(j >= i){
                temp = vet[i];
                vet[i] = vet[j];
                vet[j] = temp;
                i++;
                j--;
            }
        }
        temp = vet[i];
        vet[i] = pivo;
        vet[fim] = temp;

        QuickPivoUlt(vet, ini, i - 1);
        QuickPivoUlt(vet, i + 1, fim);

    }else
        if(fim - ini == 1){
            if(vet[ini] > vet[fim]){
                temp = vet[ini];
                vet[ini] = vet[fim];
                vet[fim] = temp;
            }
        }

}

/* calculo da mediana de 3 elementos passando o inicio, meio e fim de cada subvetor da recursao
da funcao QuickPivoMed() */
int Mediana(int32_t vet[], long int esq, long int centro, long int dir){

    if(vet[esq] >= vet[centro] && vet[esq] <= vet[dir]) {
        return esq;
    }else{
        if(vet[centro] >= vet[esq] && vet[centro] <= vet[dir])
            return centro;

        else
            return dir;
    }

}

/* quick-sort com pivo sendo a mediana de tres com parametros, vetor seu inicio e o fim */
void QuickPivoMed(int32_t vet[], long int ini, long int fim){
    static long int i, j, med;
    static int32_t pivo;
    int32_t temp;

    if(fim - ini >= 2){

        med = Mediana(vet, 0, fim/2, fim);

        temp = vet[med];
        vet[med] = vet[fim];
        vet[fim] = temp;
        pivo = vet[fim];

        i = ini;
        j = fim - 1;

        while(j >= i){
            while(vet[i] < pivo)
                i++;

            while(vet[j] > pivo && j >= i)
                j--;

            if(j >= i){
                temp = vet[i];
                vet[i] = vet[j];
                vet[j] = temp;
                i++;
                j--;
            }
        }
        temp = vet[i];
        vet[i] = pivo;
        vet[fim] = temp;

        QuickPivoUlt(vet, ini, i - 1);
        QuickPivoUlt(vet, i + 1, fim);

    }else
        if(fim - ini == 1){
            if(vet[ini] > vet[fim]){
                temp = vet[ini];
                vet[ini] = vet[fim];
                vet[fim] = temp;
            }
        }
}