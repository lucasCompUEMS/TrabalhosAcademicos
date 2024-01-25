#include <stdlib.h>
#include <stdio.h>
#include "lista.h"

/* funcao para inserir no no final da lista */
void insere_fim(Lista **inicio, int x){

    Lista *novo_no;

    novo_no = malloc(sizeof(Lista));

    /* adicionando valor fornecido no novo no */
    novo_no->valor = x;


    /* se o ponteiro do inicio for nulo entao recebe o primeiro no e
    e tambem o o proximo ponteiro do novo no recebe nulo */
    if(*inicio == NULL){

        *inicio = novo_no;
        novo_no->prox = NULL;
    }
    
    else{

        Lista *Aux;
        Aux = *inicio;

        /* laco para achar o ponteiro nulo da lista */
        while(Aux->prox != NULL)
            
            Aux = Aux->prox;


        novo_no->prox = NULL;

        /* ponteiro nulo agora aponta para o novo no */
        Aux->prox = novo_no;
    }

}

/* funcao para lista ate achar um ponteiro nulo */
void printar(Lista *inicio){

    Lista *Aux;

    Aux = inicio;
    
    /* condicao de lista vazia */
    if(inicio == NULL){
        printf("lista vazia!!\n");
    
    }
    
    else{

        printf("resultado da lista: ");

        /* printando o campo valor de cada no ate o final */
        while(Aux!=NULL){
            printf("%d-> ", Aux->valor);
            Aux = Aux->prox;
        }

    }
}

/* funcao para remover valor de uma lista simplesmente encadeada */
void remocao(Lista **ini, int x){
    
    Lista *temp, *aux, *aux2;
    aux2 = *ini;

    /* fazer processo de remocao se a lista nao for vazia */
    if(aux2!=NULL){
        
        /* atualizar o valor do inicio para o proximo no se o valor estiver no comeco */
        if(aux2->valor == x){
            *ini = aux2->prox;
            free(aux2);
            aux2 = NULL;
        }

        else
        {

            /* temp vai receber o no anterior para poder manipular ponteiros */
            temp = busca(*ini, x);

            /* se temp != NULL entao o valor esta na lista para remover */
            if(temp!=NULL){
                
                /* aqui temos o no anterior apontando para o proximo do atual valor da remocao */
                aux = temp->prox;
                temp->prox = aux->prox;
                free(aux);
                aux = NULL;
            }

            else
                printf("nao encontrado\n");
            
        }
    }

    else
        printf("lista vazia!!\n");

}

/* busca simplesmente encadeada */
Lista* busca(Lista *ini, int v){

    Lista *aux;
    aux = ini;
    int ind = 1;

    if(ini != NULL){

        /* fazer comparacao ate o fim da lista */
        while (aux!=NULL)
        {
            
            /* condicao para verificar se o valor proximo do no atual e igual ao 'v' ou se o campo valor do inicio e igual a 'v' */
            if((aux->prox != NULL && aux->prox->valor == v) || ini->valor == v){
                
                /* condicao caso se o valor estiver no no inicio entao o atual recebe o indice */
                if(ini->valor == v){
                    ini->pos = ind;
                }

                /* caso o valor nao estiver no inicio entao o proximo atual recebe o indice */
                else{
                 
                    aux->prox->pos = ind + 1;
                }
                /* forcar saida do loop */
                break;
            }    
            
            /* atualizar no e ind caso contrario */
            else{
            
                ind++;

                aux = aux->prox;
               
            }
            
            
        }   
        
    }

    /* retorna o no ou NULL se n foi encontrado */
    return aux;
}

/* funcao para desalocar lista simlesmente encadeada */
void desalocaLista(Lista **ini){

    Lista *temp;
    temp = *ini;

    /* loop para setar NULL e desalocar em cada no */
    while(temp != NULL){
        *ini = temp;
        temp = temp->prox;
        free(*ini);
        *ini = NULL;
    }

}

/* desalocar lista duplamente encadeada */
void desalocaListaDuplEnc(ListaDuplEnc **DuplEnc, ListaDuplEnc **topo){

    ListaDuplEnc *aux;

    /* se a lista nao for nula entao fazer processo de desalocacao */
    if(*DuplEnc != NULL){
        
        /* loop para percorrer toda a lista e desalocar cada no ate o 'topo' */
        while(*DuplEnc != *topo){

            aux = *DuplEnc;
            *DuplEnc = (*DuplEnc)->prox;

            free(aux);
            aux->prox = NULL;
            aux->ant = NULL;

        }

    }

    else
        printf("lista vazia!!\n");

}

/* funcao para fazer a ordenacao da lista simplesmente encadeada */
Lista* ordenacao(Lista *inicio){

    /* variaveis locais */
    Lista *aux, *inicio_novo = NULL, *desalocar = NULL;
    int menor, menorAux;

    desalocar = inicio;

    /* lista nao vazia entao fazer processo para ordenacao */
    if(inicio != NULL){
        
        /* comparar cada valor da lista com os demais a frente dele ate o fim */
        while (inicio != NULL)
        {
            aux = inicio->prox;

            /* variavel menor vai receber o valor do inicio atual para podermos comparar com a lista */
            menor = inicio->valor;

            /* continuar comparacao ate chegar no fim da lista */
            while (aux != NULL)
            {
                /* condicao para atualizar o menor ate o fim da lista */
                if(aux->valor < menor){
                    menorAux = menor;
                    menor = aux->valor;
                    aux->valor = menorAux;
                }
                
                /* atualizar para o proximo no  */
                aux = aux->prox;
            }
            
            /* inserindo valores ordenadamente passando o menor atual */
            insere_fim(&inicio_novo, menor);
            
            /* ir para o proximo no para comparar com os proximos em diante */
            inicio = inicio->prox;

        }
        
        /* desalocando nos da lista anterior */
        desalocaLista(&desalocar);

        /* retorna o inicio da nova lista ja ordenada */
        return inicio_novo;
    }

    /* senao nao fazer nenhum processo*/
    else{
        printf("lista vazia!\n");
        return NULL;
    }
}

/* insercao na duplamente encadeada */
void InsereDuplEnc(ListaDuplEnc **inicio, ListaDuplEnc **topo, int x){

    ListaDuplEnc *novo, *Aux;
    
    /* criando novo no */
    novo = malloc(sizeof(ListaDuplEnc));
    novo->valor = x;
    
    /* atualizar valor NULL do inicio para novo, e tambem o campo 'prox' e 'ant' */
    if(*inicio == NULL){
        novo->prox = *inicio;
        novo->ant = novo;
        *inicio = novo;
        
    }

    /* processo para manipular ponteiros do ultimo, novo e inicio */
    else{

        Aux = *inicio;

        /* encontrando o ultimo no da lista */
        while(Aux != *topo)
            Aux = Aux->prox;

        /* o ponteiro proximo do ultimo no agora aponta para o novo */
        Aux->prox = novo;

        /* ponteiro anterior do novo agora aponta para o ultimo */
        novo->ant = Aux;

        /* proximo do novo aponta para o inicio e anterior do inicio aponta para o novo*/
        novo->prox = *inicio;
        (*inicio)->ant = novo;
    }

    /* atualizar no ultimo atual no para o novo */
    *topo = novo;

}

/* printar na duplamente encadeada */
void printaEnc(ListaDuplEnc *inicio, ListaDuplEnc *topo){

    ListaDuplEnc *temp, *temp2;
    temp = inicio;
    temp2 = topo;

    /* loop para printar do inicio para o final */
    for( ; ; ){
        printf("%d -> ", temp->valor);

        if(temp == topo)
            break;

        temp = temp->prox;
    }
    printf("\n");

    /* loop para printar do final para o comeco */
    for( ; ; ){
        printf("%d -> ", temp2->valor);

        if(temp2 == inicio)
            break;
        
        temp2 = temp2->ant;
    }

}

/* busca duplamente encadeada */
ListaDuplEnc * BuscaDuplEnc(ListaDuplEnc *inicio, ListaDuplEnc *topo, int x){

    ListaDuplEnc *aux;
    aux = inicio;
    
    /* loop para achar o valor ou topo da lista */
    while(aux != topo && aux->valor != x)
        aux = aux->prox;
    
    /* retorna o topo ou o no com o campo valor == 'x' */
    return aux;

}

/* remocao duplamente encadeada */
void RemocaoDuplEnc(ListaDuplEnc **inicio, ListaDuplEnc **topo, int x){

    ListaDuplEnc *temp;

    /* aqui retorna o no que esta com o valor 'x' */
    temp = BuscaDuplEnc(*inicio, *topo, x);

    if(temp->valor != x)
        printf("valor nao esta na lista\n");
    
    else{
        
        if(*topo == *inicio){
            free(*topo);
            free(*inicio);
            *topo = NULL;
            *inicio = NULL;
        }
        
        else
            /* manipulacoes se o no estiver no inicio ou no fim da lista */
            if(temp == *inicio || temp == *topo){

                /* se estiver no inicio '*inicio' vai para o proximo no e o campo 'ant' do inicio aponta para o ultimo */
                if(temp == *inicio)
                {
                
                    *inicio = temp->prox;
                    (*inicio)->ant = *topo;
                    
                    /* desalocando o no com valor 'x' */
                    free(temp);
                    temp = NULL;
                    
                }

                /* se estiver no fim entao o no anterior vai ser o ultimo e o campo 'prox' do novo ultimo vai apontar para o inicio */
                else
                {
                    *topo = temp->ant;
                    (*topo)->prox = *inicio;

                    if((*topo) == *inicio)
                        (*inicio)->prox = NULL;

                    /* desalocando o no com valor 'x' */
                    free(temp);
                    temp = NULL;

                }


            }

            /* se nao estiver no inicio e nem no fim, o no anterior vai apontar para o proximo do no 
            que contem o valor = 'x' e o proximo do atual com o campo 'ant' vai apontar para o anterior
            do no atual */
            else
            {
                temp->ant->prox = temp->prox;
                temp->prox->ant = temp->ant;

                /* desalocando o no com valor 'x' */
                free(temp);
                temp = NULL;
            
            }

    }

}

/* remocao do no da fila */
void fila(Lista **fila){

    Lista *aux;

    /* se a fila nao estiver vazia, entao o primeiro no
    vai receber o proximo no, e tambem vai desalocar o primeiro no */     
    if(*fila != NULL){

        aux = (*fila)->prox;

        free(*fila);
                    
        *fila = aux;
            
    }
    else
        printf("fila vazia\n");

    
}

/* remocao do no da pilha */
void RemocaoPilha(ListaDuplEnc **topo, ListaDuplEnc **pilha){

    /* se topo for o inicio da pilha entao desaloca topo e a pilha */
    if(*topo == *pilha){
        free(*topo);
        free(*pilha);
        *topo = NULL;
        *pilha = NULL;
    }

    /* se a pilha tiver um tamnha maior que 1, entao desaloca somente o topo da pilha */
    else{

        ListaDuplEnc *temp;

        temp = *topo;

        *topo = temp->ant;

        (*topo)->prox = *pilha;
    
        free(temp);
    }

}

/* printar pilha */
void printaPilha(ListaDuplEnc *inicio, ListaDuplEnc *topo){

    ListaDuplEnc *temp;
    temp = inicio;

    /* se a pilha nao for vazia entao printar todos os nos ate o topo da pilha */
    if(inicio != NULL)
        for( ; ; ){
            printf("%d -> ", temp->valor);

            if(temp == topo)
                break;

            temp = temp->prox;
        }
    
    else
        printf("pilha vazia!\n");
}