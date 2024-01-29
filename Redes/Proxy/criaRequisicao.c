#include "criaRequisicao.h"

//cria a estrutura de requisicao com caminho, metodo, versao e url
void cria_Requisicao(char request[], requisit *myreq){

    char host[MAX_URL], page[MAX_URL];
   
    strncpy(myreq->request, request, REQ_MAXIMA-1);
    strncpy(myreq->method, strtok(request, " "), 16-1);
    strncpy(myreq->path, strtok(NULL, " "), MAX_URL-1);
    strncpy(myreq->version, strtok(NULL, "\r\n"), 16-1);
    sscanf(myreq->path, "http://%99[^/]%99[^\n]", host, page);
    strncpy(myreq->host, host, MAX_URL-1);
    strncpy(myreq->page, page, MAX_URL-1);
    
}
