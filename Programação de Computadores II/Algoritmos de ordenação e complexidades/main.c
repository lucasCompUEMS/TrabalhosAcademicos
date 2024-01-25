/* LUCAS DA ROCHA SILVA 38345

    dica de compilação: gcc main.c AlgOrd.c -o main -Wall -pedantic -Wextra -fsplit-stack

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <string.h>
#include "AlgOrd.h"

int main(int argc, char *argv[]) {

    int NumAlgOrd;
    long int TamVet;
    int32_t *vet = NULL;
    FILE *FileIn, *FileOut;
    clock_t tempo;
    
    FileIn = fopen(argv[2], "rb");
    FileOut = fopen(argv[3], "wb");

    NumAlgOrd = atoi(argv[1]);

    if(FileIn == NULL || argc != 4 || NumAlgOrd  < 1 || NumAlgOrd > 8){

        printf("verifique as seguintes condicoes:\n\n"
               ".Numero de parametros passados para o programa deve ser 4\n"
               ".O arquivo deve existir\n"
               ".E o numero do algoritmo deve estar entre 1 e 8\n");
    } else{
        
        /* calculando o tamanho do arquivo e aloca no vetor */
        fseek(FileIn, 0, SEEK_END);
        TamVet = ftell(FileIn)/sizeof(int32_t);
        vet = malloc(TamVet * sizeof(int32_t));

        if(vet != NULL) {

            /* lendo arquivo e armazenando no vetor */
            fseek(FileIn, 0, SEEK_SET);
            fread(vet, sizeof(int32_t), TamVet, FileIn);

            printf("arquivo com entrada '%c' com %ld elementos:\n", argv[2][strlen(argv[2]) - 1], TamVet);

            printf("\n");
            fclose(FileIn);

            switch (NumAlgOrd) {
                
                /* condicoes para os numeros do algorimos de ordenacao de 1 a 8 pegando o tempo inicial, e em seguida
                ordena o vetor pelo numero do algoritmo, e por fim calcula o tempo total = tempo_inicial - tempo_final */
                case 1:
                    printf("\nordenacao por Bubble_sort_original:\n");
                    tempo = clock();
                    Bubble_sort_original(vet, TamVet);
                    tempo = clock() - tempo;
                    printf("tempo de ordenação com %ld elementos = %.3lf(SEC)\n", TamVet, ((float)tempo) / CLOCKS_PER_SEC);
                    break;

                case 2:
                    printf("\nordenacao por Bubble_sort_melhorado:\n");
                    tempo = clock();
                    Bubble_sort_melhorado(vet, TamVet);
                    tempo = clock() - tempo;
                    printf("tempo de ordenação com %ld elementos = %.3lf(SEC)\n", TamVet, ((float)tempo) / CLOCKS_PER_SEC);
                    break;

                case 3:
                    printf("\nordenacao por Insertion-sort:\n");
                    tempo = clock();
                    Insertion_sort(vet, TamVet);
                    tempo = clock() - tempo;
                    printf("tempo de ordenação com %ld elementos = %.3lf(SEC)\n", TamVet, ((float)tempo) / CLOCKS_PER_SEC);
                    break;

                case 4:
                    printf("\nordenacao por Mergesort:\n");
                    tempo = clock();
                    Mergesort(vet, 0, TamVet - 1);
                    tempo = clock() - tempo;
                    printf("tempo de ordenação com %ld elementos = %.3lf(SEC)\n", TamVet, ((float)tempo) / CLOCKS_PER_SEC);
                    break;

                case 5:
                    printf("\nordenacao por Quicksort com pivô sendo o último elemento:\n");
                    tempo = clock();
                    QuickPivoUlt(vet, 0, TamVet - 1);
                    tempo = clock() - tempo;
                    printf("tempo de ordenação com %ld elementos = %.3lf(SEC)\n", TamVet, ((float)tempo) / CLOCKS_PER_SEC);
                    break;

                case 6:
                    printf("\nordenacao por Quicksort com pivô sendo um elemento aleatorio:\n");
                    tempo = clock();
                    QuickPivoAle(vet, 0, TamVet - 1);
                    tempo = clock() - tempo;
                    printf("tempo de ordenação com %ld elementos = %.3lf(SEC)\n", TamVet, ((float)tempo) / CLOCKS_PER_SEC);
                    break;

                case 7:
                    printf("\nordenacao por Quicksort com pivô sendo mediana de tres:\n");
                    tempo = clock();
                    QuickPivoMed(vet, 0, TamVet - 1);
                    tempo = clock() - tempo;
                    printf("tempo de ordenação com %ld elementos = %.3lf(SEC)\n", TamVet, ((float)tempo) / CLOCKS_PER_SEC);
                    break;

                default:
                    printf("\nordenacao por Heapsort:\n");
                    tempo = clock();
                    Heapsort(vet, TamVet);
                    tempo = clock() - tempo;
                    printf("tempo de ordenação com %ld elementos = %.3lf(SEC)\n", TamVet, ((float)tempo) / CLOCKS_PER_SEC);
                    break;


            }
            /*printf("\nconteudo do vetor ja ordenado:\n");
            for(long int i = 0; i < TamVet; i++)
                printf("%d\n", vet[i]);*/

            /* escrevendo o vetor ordenado no arquivo expecificado */
            fwrite(vet, sizeof(int32_t), TamVet, FileOut);
            fclose(FileOut);
            free(vet);

        } else
            printf("erro ao alocar vetor!!\n");

        printf("\n");
    }

    return 0;
}
