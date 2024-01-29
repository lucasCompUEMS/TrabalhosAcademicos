#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "cache.h"

//na busca retorna null se a pagina não estiver na cache, ou o nó se a pagina estiver na cache
cache* Busca(char str[], cache *inicio){
    cache *temp;

    temp = inicio;
    while(temp != NULL){
        if(strcmp(str, temp->host) == 0)
            return temp;

        temp = temp->pontProx;    
    }
    
    return NULL;
          
}

//insere na lista se a pagina não estiver na cache
void insercao(char host[], char resposta[], cache **inicio){

    cache *aux = *inicio;

    if(*inicio == NULL){
        *inicio = malloc(sizeof(cache));
        strcat((*inicio)->host, host);
        strcat((*inicio)->resposta, resposta);
        (*inicio)->pontProx = NULL;
    }
    else{
        cache *novo;

        novo = malloc(sizeof(cache));

        while(aux->pontProx != NULL)
            aux = aux->pontProx;

        memset(novo->host, 0, strlen(novo->host));
        memset(novo->resposta, 0, strlen(novo->resposta));
        strcat(novo->host, host);
        strcat(novo->resposta, resposta);
        printf("novo == %s\n\n\n\n", host);
        novo->pontProx = NULL;

        aux->pontProx = novo;
    }
}

//mostra o conteudo da cache
void printList(cache *inicio){

    cache *temp = inicio;

    while(temp != NULL){
        printf("\n\nHost: %s\n", temp->host);
        printf("\n                         Reposta\n%s\n", temp->resposta);
        temp = temp->pontProx;
    }
}