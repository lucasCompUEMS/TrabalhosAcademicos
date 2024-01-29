/*

Dica de compilação do cliente:

    gcc cliente.c -o cliente

dica de execução com fornecimento da  url no fomato padrao sem a palavra 'http://'
e sem '/' no final:

    ./cliente <url> <ip_maquina> <porta>

    para teste:
        monge.com.br
        dainf.pg.utfpr.edu.br/professores/apborges


*/


#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>//servir para pegar o ip do host
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char** argv) {

    //PROTOCOLO IP orientado a conexao tcp
    int meu_socket = socket(AF_INET, SOCK_STREAM, 0), i;
    struct sockaddr_in proxy;
    char resposta_proxy[16000];
    char *name_host = argv[1];

    //criando o socket
    if(meu_socket == -1) {
        printf("erro ao criar socket!\n");
    }

    /*se n tiver erro ao criar vamos pegar ip por nome do host e logo em seguida a conexao,
     solicitacao e resposta */
    else {

        //atribui o ip obtido, familia, ip versao 4 e porta para o servidor
        proxy.sin_addr.s_addr = inet_addr(argv[2]);
        proxy.sin_family = AF_INET;
        proxy.sin_port = htons(atoi(argv[3]));

        //Conectar a um servidor remoto
        if (connect(meu_socket, (struct sockaddr *) &proxy, sizeof(proxy)) < 0) {
            puts("Erro ao conectar!");
        }
        puts("Conectado");

        int tam = strlen(name_host);
        //envia dados ao servidor
        if (send(meu_socket, name_host, tam, 0) < 0) {
            puts("falha ao enviar!");
            return 1;
        }

        //recebe a resposta do servidor
        if (recv(meu_socket, resposta_proxy, 16000, 0) < 0) {
            puts("falha ao receber!");
        }

        puts(resposta_proxy);

        
    }

    //fecha conexao
    close(meu_socket);
    return 0;

}