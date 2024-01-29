//estrutura da cache
typedef struct cache{

    char host[8000];
    char resposta[16000];
    struct cache *pontProx;

}cache;

//prototipo das funcoes
cache* Busca(char*, cache*);
void insercao(char*, char*, cache **);
void printList(cache *);