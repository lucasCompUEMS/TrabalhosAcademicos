#include <string.h>
#include <stdio.h>

#define REQ_MAXIMA 8000
#define MAX_URL 8000

typedef struct requisit {

    char request[REQ_MAXIMA];
    char method[20];
    char path[MAX_URL];
    char version[20];
    char host[MAX_URL];
    char page[MAX_URL];

}requisit;

void cria_Requisicao(char [], requisit *);
