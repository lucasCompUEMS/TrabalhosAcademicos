/*

Dica de compilação do Proxy:
    gcc Proxy.c criaRequisicao.c cache.c -o Proxy

Dica de execução:    
    ./Proxy <porta>

 */

#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h> 
#include<unistd.h>  
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "criaRequisicao.h"
#include "cache.h"

int main(int argc, char** argv)
{
    int meu_socket = socket(AF_INET, SOCK_STREAM, 0), i, c, novo_socket;
    struct sockaddr_in servidor, cliente, proxy;
    struct hostent *maquina;
    struct in_addr **addr_list;
    char mensagemCli[16000], resposta_server[16000], ip[100];
    int aux, val = 1, resultado;
    char req[8000];
    requisit myReq;
    cache *inicio = NULL;
    cache *busca = NULL;

    //limpa porta para usar novamente
    resultado = setsockopt(meu_socket, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
    if (resultado < 0) {
        perror("Servidor");
        return 0;
    }

    //criar o socket
    meu_socket = socket(AF_INET, SOCK_STREAM, 0);

    //preparando a estrutura
    proxy.sin_family = AF_INET;
    proxy.sin_addr.s_addr = INADDR_ANY;
    proxy.sin_port = htons ( atoi(argv[1]));

    //associa meu socket com a estrutura proxy
    if( bind(meu_socket, (struct sockaddr *)&proxy, sizeof(proxy)) < 0)
    {
        close(meu_socket);
        puts("Erro no bind!");
        return 1;
    }

    //ouve conexoes
    listen(meu_socket, 3);

    puts("Aguardando conexoes...\n");
    c = sizeof(struct sockaddr_in);
   
    do {

        //aceitando conexoes com clientes
        novo_socket = accept(meu_socket, (struct sockaddr *)&cliente, (socklen_t*)&c);
        //system("clear");
        puts("Conexao Aceita!\n");

        //recebendo mensagem do cliente
        if (recv(novo_socket, mensagemCli, 16000, 0) < 0) {
            puts("falha no recebimento de mensagem!");
        }

        //limpando modelo de requisicao
        memset(req, 0, strlen(req));

        //condicao de requisicao sem o navegador
        if(strstr(mensagemCli, "GET ") == NULL){
            
            //primeiramente concatenamos a requesicao para em seguida criar a estrutura
            printf("requisicao sem navegador!\n\n");
            strcat(req, "GET http://");
            strcat(req, mensagemCli);
            strcat(req, "/ HTTP/1.0\r\n");
            cria_Requisicao(req, &myReq);
        }

        //condicao para requisicao com o navegador
        else{
            printf("requisicao com navegador!\n\n");
            cria_Requisicao(mensagemCli, &myReq);
        }
        
        memset(req, 0, strlen(req));

        //modelando a requisicao para em seguida requisitar o servidor
        strcat(req, "GET ");
        strcat(req, myReq.page);
        strcat(req, " HTTP/1.0\r\n");
        strcat(req, "Host: ");
        strcat(req, myReq.host);
        strcat(req, "\r\n\r\n");
        strcat(req, "\0");
        puts(req);
        
        //pegando ip pelo host
        maquina = gethostbyname(myReq.host);
        if (maquina == NULL) {
            herror("gethostbyname");
            return 1;
        }

        addr_list = (struct in_addr **) maquina->h_addr_list;

        for (i = 0; addr_list[i] != NULL; i++)
            strcpy(ip, inet_ntoa(*addr_list[i]));

        //atribui o ip obtido, familia, ip versao 4 e porta para o servidor
        servidor.sin_addr.s_addr = inet_addr(ip);
        servidor.sin_family = AF_INET;
        servidor.sin_port = htons(80);

        //guarda valor original da conexao entre cliente e proxy
        aux = meu_socket;

        //cria um novo socket para usar com a conexao entre proxy e servidor
        meu_socket = socket(AF_INET, SOCK_STREAM, 0);
        busca = Busca(myReq.path, inicio);

        //se o conteudo não estiver na cache entao requisitar o servidor
        if(busca == NULL){
            printf("Requisita server\n\n");

            //conectar ao servidor
            if (connect(meu_socket, (struct sockaddr *) &servidor, sizeof(servidor)) < 0) {
                puts("Erro ao conectar!");
            }
            puts("\nConectado");
            
            //envia ao servidor
            if (send(meu_socket, req, strlen(req), 0) < 0) {
                puts("falha ao enviar!");
                return 1;
            }

            //recebe do servidor
            if (recv(meu_socket, resposta_server, 16000, 0) < 0)
                printf("falha no recebimento!\n\n");
                
            strcat(resposta_server, "\0");

            //enviar para o cliente
            if(send(novo_socket, resposta_server, strlen(resposta_server), 0) < 0)
                printf("erro!!\n\n");

            strcat(myReq.path, "\0");

            //insere o novo conteudo no final da cache
            insercao(myReq.path, resposta_server, &inicio);
        }

        //requisita a cache caso o conteudo esteja nela
        else{
            printf("Requisita a cache!!\n\n");

            //envia ao cliente o conteudo achado na cache
            if(send(novo_socket, busca->resposta, strlen(busca->resposta), 0) < 0)
                printf("erro!!\n\n");
        }

        //limpa as strings para evitar erros
        memset(resposta_server, 0, strlen(resposta_server));
        memset(mensagemCli, 0, strlen(mensagemCli));
        memset(myReq.request, 0, strlen(myReq.request));
        memset(myReq.method, 0, strlen(myReq.method));
        memset(myReq.path, 0, strlen(myReq.path));
        memset(myReq.version, 0, strlen(myReq.version));
        memset(myReq.host, 0, strlen(myReq.host));
        memset(myReq.page, 0, strlen(myReq.page));

        //restaura valor original entre a conexao proxy com cliente
        meu_socket = aux;

        //mostra o conteudo da cache
        printf("\n\n==============Conteudo da cache========================\n");
        printList(inicio);
        printf("==========================================================\n\n");

    }while(novo_socket);
   
    

    if (novo_socket < 0) {
        
        perror("A funcao Accept falhou!");
        return 1;
    }

    close(novo_socket);
    close(meu_socket);

    return 0;
}