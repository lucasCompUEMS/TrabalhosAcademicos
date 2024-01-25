/* estrutura para lista simplesmente encadea com posicao e proximo com chave valor */
typedef struct lista{

    int valor, pos;
    struct lista *prox;

}Lista;

/* estrutura para lista duplamente encadeada com chave valor e ponteiros para anterior e proximo */
typedef struct listaDupl{

    int valor;
    struct listaDupl *prox;
    struct listaDupl *ant;

}ListaDuplEnc;

/* prototipo das funcoes */
void insere_fim(Lista **, int);
void printar(Lista *);
Lista* busca(Lista *, int);
void remocao(Lista **, int);
void desalocaLista(Lista **);
Lista* ordenacao(Lista *);
void fila(Lista **);
void RemocaoPilha(ListaDuplEnc **, ListaDuplEnc **);
void InserePilha(ListaDuplEnc **, ListaDuplEnc **);
void InsereDuplEnc(ListaDuplEnc **, ListaDuplEnc **, int);
void printaEnc(ListaDuplEnc *, ListaDuplEnc *);
void printaPilha(ListaDuplEnc *, ListaDuplEnc *);
void RemocaoDuplEnc(ListaDuplEnc **, ListaDuplEnc **, int);
ListaDuplEnc* BuscaDuplEnc(ListaDuplEnc *, ListaDuplEnc *, int);
void desalocaListaDuplEnc(ListaDuplEnc **, ListaDuplEnc **);