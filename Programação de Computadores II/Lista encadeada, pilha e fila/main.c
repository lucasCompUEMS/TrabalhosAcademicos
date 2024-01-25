/* LUCAS DA ROCHA SILVA 38345 

DICA DE COMPILACAO: gcc main.c lista.c -o main -Wall -pedantic -Wextra

*/

#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

int main(){

    /* variaveis locais */
    Lista *inicio = NULL, *tempBusca, *fil = NULL;
    ListaDuplEnc *inicio2 = NULL, *topo = NULL, *ultimo = NULL, *pilha = NULL, *buscaEnc = NULL;
    int x, opc, opc2;

    /* loop para escolher as opcoes de lista. lista simplesmente encadeada,
    duplamente encadeada, pilha e fila ate opcao 0 para sair da aplicacao */
    do
    {
        system("clear");
        printf("1 - manipulcao com lista simplesmente encadeada, sem no cabeca, ordenado\n");
        printf("2 - Lista duplamente encadeada\n");
        printf("3 - insercao e remocao em fila\n");
        printf("4 - insercao e remocao em pilha\n");
        printf("0 - sair\n");
        scanf("%d", &opc);
        system("clear");
        
        /* manipulacao com lista simplesmente encadeada */
        if(opc == 1)
        {
            /* loop opcoes para manipulacaoes com lista simplesmente encadeada ate 0 para voltar menu */
            do{

                printf("\n\n1 - inserir no final\n");
                printf("2 - remocao\n");
                printf("3 - mostrar lista\n");
                printf("4 - busca\n");
                printf("5 - desalocar iterativamente\n");
                printf("0 - voltar\n");
                scanf("%d", &opc2);
                
                system("clear");

                switch (opc2)
                {

                    /* aqui fornece o valor para insercao na lista simplesmente encadeada e
                    tambem ja fazendo a ordenacao */
                    case 1:
                        printf("informe o valor a ser inserido:");
                        scanf("%d", &x);
                        insere_fim(&inicio, x);
                        inicio = ordenacao(inicio);
                        break;
                    
                    /* informar o valor a ser removido da lista */
                    case 2:
                        printf("informe um valor a ser removido:");
                        scanf("%d", &x);
                        remocao(&inicio, x);
                        break;
                    
                    /* printar a lista */
                    case 3:
                        printar(inicio);
                        break;
                    
                    /* busca de um no pelo campo valor */
                    case 4:
                            /* condicao de lista nao vazia */
                            if(inicio != NULL){
                                
                                printf("informe o valor para busca:");
                                scanf("%d", &x);

                                /* tampBusca ira receber o no anterior ao atual ou o no inicio */
                                tempBusca = busca(inicio, x);

                                /* se tempBusca != NULL entao o elemento existe na lista e printa a o campo posicao do atual */
                                if(tempBusca != NULL && tempBusca != inicio)
                                    printf("o valor %d esta na posicao %d\n", x, tempBusca->prox->pos);
                                
                                else{
                                    if(tempBusca == inicio)
                                        printf("o valor %d esta na posicao %d\n", x, tempBusca->pos);

                                    else
                                        printf("elemento não existe!!!\n");
                                }    
                            }

                            else
                                printf("lista vazia\n");
                        
                        break;

                    /* desalocar lista iterativamente */
                    case 5:

                        if(inicio != NULL)
                            desalocaLista(&inicio);
                        
                        else
                            printf("lista vazia!\n");

                        break;
                }
            
            }while(opc2 != 0);

        }

        /* lista duplamente encadeada */
        if(opc == 2){

            /* loop as opcoes em lista duplamente encadeada ate 0 para voltar */
            do{

                printf("\n\n1 - insercao\n");
                printf("2 - mostrar valores\n");
                printf("3 - busca duplamente encadeada\n");
                printf("4 - remocao duplamente encadeada\n");
                printf("0 - voltar\n");
                scanf("%d", &opc2);

                system("clear");

                switch(opc2){
                    
                    /* insercao na duplamente encadeada */
                    case 1:
                        printf("informe o valor para insercao\n");
                        scanf("%d", &x);
                        InsereDuplEnc(&inicio2, &ultimo, x);
                        break;
                    
                    /* printar lista duplamente encadeada */
                    case 2:
                        if(inicio2 != NULL)
                        {
                            printf("valores duplamente encadeado:\n");
                            printaEnc(inicio2, ultimo);
                        }
                        else
                            printf("lista vazia\n");

                        break;

                    /* busca na duplamente */
                    case 3:

                        /* se o inicio == NULL entao lista vazia */
                        if(inicio2 == NULL)
                            printf("lista vazia!\n");
                        
                        /* se lista nao for vazia entao fazer busca com um valor informado */
                        else
                        {
                            printf("informe o valor para busca\n");
                            scanf("%d", &x);
                            
                            /* recebendo o no com o campo 'valor' == x */
                            buscaEnc = BuscaDuplEnc(inicio2, ultimo, x);

                            /* se for diferente significa que esta no ultimo no e nao esta contido este valor 'x' logo 'x' nao esta na lista */
                            if(buscaEnc->valor != x)
                                printf("valor nao esta na lista\n");

                            else
                                printf("valor esta na lista!\n");

                        }

                        break;
                    
                    /* opcao para remocao na duplemente encadeada */
                    case 4:

                        if(inicio2 == NULL)
                            printf("lista vazia\n");

                        else{
                            printf("informe o valor a ser removido\n");
                            scanf("%d", &x);

                            RemocaoDuplEnc(&inicio2, &ultimo, x);
                        }

                        break;

                }

            }while(opc2 != 0);
        }

        /* manipulacao com fila */
        if(opc == 3){
            
            /* loop para as opcoes abaixo ate digitat 0 para voltar */
            do{
        
                printf("\n\n1 - remocao do primeiro no\n");
                printf("2 - adicionar no no final\n");
                printf("3 - printar fila\n");
                printf("0 - voltar\n");
                scanf("%d", &opc2);
                system("clear");

                switch(opc2){
                    
                    /* remocao do no da fila */
                    case 1:
                        fila(&fil);
                        break;

                    /* insercao na fila */
                    case 2:
                        printf("informe o valor para adiconar na fila\n");
                        scanf("%d", &x);
                        insere_fim(&fil, x);
                        break;

                    /* printar fila */
                    case 3:
                        printar(fil);
                        break;
                    
                }
                
            }while(opc2 != 0);

        }

        /* manipulacao com pilha */
        if(opc == 4){
            
            /* loop para opcoes de pilha ate clicar 0 para voltar */
            do{ 

                printf("\n\n1 - adicao na pilha\n");
                printf("2 - remocao\n");
                printf("3 - printar pilha\n");
                printf("0 - voltar\n");
                scanf("%d", &opc2);
                system("clear");


                switch(opc2){
                    
                    /* adicao na pilha */
                    case 1:
                        printf("informe o valor para adicionar na pilha\n");
                        scanf("%d", &x);
                        InsereDuplEnc(&pilha, &topo, x);
                        break;

                    /* remocao do no da pilha */
                    case 2:
                        if(topo != NULL)
                            RemocaoPilha(&topo, &pilha);
                        
                        else
                            printf("pilha vazia\n");

                        break;

                    case 3:

                        /* printar conteudo da pilha */
                        if(pilha != NULL)
                            printaPilha(pilha, topo);

                        else
                            printf("pilha vazia\n");

                        break;
                }

            }while(opc2 != 0);
            
        }

    }while(opc != 0);

    /* desalcoar todos os da lista simplesmente encadeada e da fila */
    desalocaLista(&inicio);
    desalocaLista(&fil);

    /* desalocar todos os nos da lista duplamente encadeada e da pilha */
    desalocaListaDuplEnc(&inicio2, &ultimo);
    desalocaListaDuplEnc(&pilha, &topo);
   
    return 0;
}