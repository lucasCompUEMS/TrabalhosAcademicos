/* Programa: EDITOR DE TEXTO
    Descrição: Fazer um editor que permita o usuario mexer com as
     SETAS, salvar e sair do texto
    Programador: LUCAS DA ROCHA SILVA
    RGM: 38345
    Data da última modificação: 18/11/2019 */

/* Dica de como compilar:
    gcc AVL.c conio_v3.2.4.c -o AVL.exe -Wall -pedantic -Wextra */

/* bibliotecas padroes c */
#include <stdio.h> /* printf(), scanf() */ 
#include <string.h> /* strlen() */
#include <conio.h> /* getch() */
#include "conio_v3.2.4.h" /* gotoxy(), clrscr() */

/* constantes */
#define ESC 27
#define SETA_ESQUERDA 75
#define SETA_DIREITA 77
#define SETA_CIMA 72
#define SETA_BAIXO 80
#define CTRL_HOME 119
#define CTRL_END 117
#define CTRL_SETA_DIREITA 116
#define CTRL_SETA_ESQUERDA 115
#define CTRL_SETA_CIMA 141
#define CTRL_SETA_BAIXO 145
#define ENTER 13
#define NEW_LINE 10
#define BACKSPACE 8
#define DEL 83
#define HOME 71
#define END 79
#define LIM_COL 120
#define LIM_LIN 30
#define F2 60

/* funcoes de manipulacao de texto */
void teclas_especiais(char NomeArq[], int, int *, int *, int *, FILE *, int [], int [LIM_LIN][LIM_COL]);
void AtualizaLinha(int [LIM_LIN][LIM_COL], int[], int, int, int);
void Apaga_Caracter(int *, int *, int *, int [LIM_LIN][LIM_COL], int vetor[]);
void ArrumaTexto(int [LIM_LIN][LIM_COL], int [], int, int);
void CombinacaoTecla(int, int, int *, int *, int [], int [LIM_LIN][LIM_COL]);

/* funcao principal */
int main(int argc, char *argv[])
{

    /* variaveis locais */
    int coluna = 1, linha = 1, M[LIM_LIN][LIM_COL], i = 0, tam;
    int quant_lin = 1, tecla, vetor[LIM_LIN], k = 0; 
    FILE *ArqInOut;
    char NomeArq[20], str[LIM_COL + 1];

    argc = argc;
    argv = argv;

    /* leitura do nome do arquivo */
    printf("informe o nome do arquivo:");
    fgets(NomeArq, 20, stdin);
    NomeArq[strcspn(NomeArq, "\n")] = '\0';
    
    /* abre em modo leitura leitura */
    ArqInOut = fopen(NomeArq, "r");    

    /* um vetor para guardar a quantidade de caracter de cada linha */
    for(i = 0; i < LIM_LIN; i++)
        vetor[i] = 0;

    /* se nao existir cria para leitura e gravacao  */
    if(ArqInOut == NULL)
       ArqInOut = fopen(NomeArq, "w");

    clrscr();

    /* se o arquivo existir conteudo entao fazer a leitura
    com fgets() para pegar string de arquivo ate chegar no fim ou new line */
    while(fgets(str, LIM_COL + 1, ArqInOut) != NULL)
    {

        /* printar conteudo na tela */
        printf("%s", str);

        /* pega o tamanho de cada string do arquivo*/
        tam = strlen(str);

        /* modificar o tipo e armazenar o conteudo na matriz */
        for(i = 0; i < tam; i++)
            M[k][i] = (int)str[i];
            
        /* pegar o tamanho de cada linha */
        vetor[k] = tam;
        
        /* incrementa a linha da matriz */
        k++;

        /* incrementa a quantidade de linhas na matriz */
        quant_lin++;

    }

    /* decrementa o valor de quantidade de linha */
    if(vetor[quant_lin - 2] > 0)
        quant_lin -= 1;

    /* loop infinito */
    for( ; ; )
    {
        
        /* fazer a leitura da tecla */
        gotoxy(coluna, linha);
        tecla = getch();
        
        /* sair do programa e fechar arquivo */
        if(tecla == ESC)
        {
            clrscr();
            fclose(ArqInOut);
            break;
        }

        else
        {

            /* se for tecla especial chama a funcao e avalia qual tecla especial foi digitada */
            if(tecla == 224 || !tecla)
            {
                tecla = getch();
                
                /* caso o usuario digite alguma tecla com combinacao ctrl para se mover no texto chama funcao combinacaotecla */
                if(tecla == CTRL_HOME || tecla == CTRL_END || tecla == CTRL_SETA_DIREITA || tecla == CTRL_SETA_ESQUERDA || tecla == CTRL_SETA_BAIXO || tecla == CTRL_SETA_CIMA)
                    CombinacaoTecla(tecla, quant_lin, &linha, &coluna, vetor, M);

                else
                    /* senao chama as teclas sem combinacao ctrl */
                    teclas_especiais(NomeArq, tecla, &quant_lin, &linha, &coluna, ArqInOut, vetor, M);
            }

            else
            {

                /* fazer operacoes se estiver no limite da tela */
                if((coluna <= vetor[linha - 1] + 1 && vetor[linha - 1] + 1 <= LIM_COL) || tecla == ENTER || tecla == BACKSPACE)
                {

                    /* printa tecla na posicao da tela */
                    gotoxy(coluna, linha);
                    printf("%c", tecla);

                    /* se o cursor for menor o tamanho da linha entao chamar funcao ArrumaTexto */
                    if(coluna <= vetor[linha - 1] && tecla != ENTER && tecla != BACKSPACE)
                        ArrumaTexto(M, vetor, linha, coluna);

                    /* condicao para poder armazenar caracteres na matriz */
                    if((coluna >= vetor[linha - 1] && tecla != BACKSPACE) || (coluna <= vetor[linha - 1] && tecla != ENTER && tecla != BACKSPACE))
                        M[linha - 1][coluna - 1] = tecla;

                    /* condicao para atualizar linha, coluna e atualizar o tamanho de cada linha */
                    if(tecla != ENTER && coluna < LIM_COL && tecla != BACKSPACE)
                    {
                        
                        /* incrementar o tamanho de linha se estiver nos limite de coluna*/
                        if(vetor[linha - 1] < LIM_COL)
                            vetor[linha - 1] += 1;

                        /* incrementar coluna se estiver no limite de coluna*/
                        if(coluna + 1 <= LIM_COL)
                            coluna++;

                        /* incrementar linha e quantidade de linha quando a coluna chegar no limite */
                        if(coluna == LIM_COL && linha + 1 <= LIM_LIN)
                        {

                            /* chama funcao atualiza linha, caso se tiver conteudo abaixo desta linha
                            fazer manipulacao para passar cada conteudo para proxima linha */
                            AtualizaLinha(M, vetor, linha, coluna, quant_lin);
                            
                        
                            linha++;

                            quant_lin++;

                            coluna = 1;
                            

                        }

                        
                    }

                    else
                    {
                    
                        if(tecla == BACKSPACE && coluna >= 1)
                            Apaga_Caracter(&quant_lin, &coluna, &linha, M, vetor);

                        if(tecla == ENTER && linha + 1 <= LIM_LIN)
                        {

                            if(vetor[linha] > 0 || coluna < vetor[linha - 1])
                                AtualizaLinha(M, vetor, linha, coluna, quant_lin);

                            else
                            
                                vetor[linha - 1] += 1;

                        }

                        if(linha < LIM_LIN && tecla != BACKSPACE)
                        {

                            coluna = 1;
                            linha++;

                            quant_lin++;

                        }
                        

                    }
                }

            }   
        }
    }   
                
    return 0;
}

/* funcao para incrementar cada caracter na matriz e printando atualizado na tela */
void ArrumaTexto(int M[LIM_LIN][LIM_COL], int vetor[], int lin, int col)
{
    int j;

    /* verificao para ver se esta no limite de coluna */
    if(vetor[lin - 1] + 1 <= LIM_COL)
    {
        /* loop para pegar do tam da linha ate o cursor na tela */
        for(j = vetor[lin - 1]; j >= col; j--)
        {

            /* posicao posterior da matriz recebe a anterior */
            M[lin - 1][j] = M[lin - 1][j - 1];

            /* printar posicao atualizada na tela */
            gotoxy(j + 1, lin);
            printf("%c", M[lin - 1][j]);
        }
        
    }

   
}

/* funcao para manipulacao das tecla especiais */
void teclas_especiais(char NomeArq[], int tcl, int *quant_lin, int *lin_mat, int *col_mat, FILE *Arq, int vetor[], int M[LIM_LIN][LIM_COL])
{
    /* variaveis locais */
    int x, y, cont = 0;

    switch(tcl)
    {
        
        /* caso digitar salvar mandar conteudo da matriz para o arquivo */
        case F2:
            
            /* abrir aquivo para leitura e gravacao. Destruindo 
            arquivo anterior */
            Arq = fopen(NomeArq, "w+");

            /* loops para percorrer a matriz e armazenando no arquivo */
            for(x = 0; x < *quant_lin; x++)
        
                for(y = 0; y < vetor[x]; y++)
                {
                    if(M[x][y] == ENTER)
                        fprintf(Arq, "%c", NEW_LINE);
                    
                    else
                        fprintf(Arq, "%c", M[x][y]);
                }
        break;

        /* caso seta esquerda atualizar a coluna e linha
        se necessario */
        case SETA_ESQUERDA:

            /* decremento da coluna se coluna > 1 */
            if(*col_mat > 1)
                *col_mat -= 1;

            else

                /* decrementar a linha quando a coluna for = 1 
                e linha atual > 1 */
                if(*col_mat == 1 && *lin_mat > 1)
                {   

                    *lin_mat -= 1;

                    /* atualizar coluna para ultima posicao da linha */
                    *col_mat = vetor[*lin_mat - 1];

                }

        break;

        /* atualiza coluna, e linha se for necessario */
        case SETA_DIREITA:

            /* incrementando coluna no limite do tamanho da linha */
            if(*col_mat < vetor[*lin_mat - 1] || (*lin_mat == *quant_lin && *col_mat == vetor[*lin_mat - 1]))
                *col_mat += 1;

            else
                /* incrementa linha e atualiza a coluna, quando chegar no final do tamanho da linha 
                e o ultimo caracter da matriz for enter */
                if(*col_mat == vetor[*lin_mat - 1] && M[*lin_mat - 1][*col_mat - 1] == ENTER)
                {
                    *lin_mat += 1;
                    *col_mat = 1;
                }

                else   
                    /* caso o ultimo caracter n seja enter incrementa linha e atualiza coluna */
                    if(vetor[*lin_mat] > 0)
                    {
                        *lin_mat += 1;
                        *col_mat = 1;
                    }

        break;

        /* seta cima para mover cursor para linha anterior */
        case SETA_CIMA:
            
            /* decrementar linha somente quando for > 1 */
            if(*lin_mat > 1)
            {
                
                /* atribuir coluna no final da linha anterior somente quando posicao de coluna < tam linha anterior*/
                if(*col_mat >= vetor[*lin_mat - 2])
                    *col_mat = vetor[*lin_mat - 2];

                *lin_mat -= 1;
            }

        break;

        /* move cursor para linha posterior */
        case SETA_BAIXO:
           
            if(vetor[*lin_mat - 1] > 0 && *lin_mat < *quant_lin)
            {
                /* mover cursor para final da linha posterior somente se coluna for < que o tamanho da linha posteior*/
                if(*col_mat >= vetor[*lin_mat])
                    *col_mat = vetor[*lin_mat];

                *lin_mat += 1;

            }

        break;

        /* mover o cursor para o inicio da linha */
        case HOME:
            *col_mat = 1;
        
        break;

        /* mover o cursor para final da linha */
        case END:   
            *col_mat = vetor[*lin_mat - 1];

        break;

        case DEL:

            if((M[*lin_mat - 1][vetor[*lin_mat - 1] - 1] == ENTER || M[*lin_mat - 1][vetor[*lin_mat - 1] - 1] == NEW_LINE) && vetor[*lin_mat - 1] > 0)
                vetor[*lin_mat - 1]--;

            if(vetor[*lin_mat - 1] > 0 && *col_mat <= vetor[*lin_mat -1])
            {

                for(x = *col_mat - 1; x < vetor[*lin_mat - 1]; x++)
                {

                    M[*lin_mat - 1][x] = M[*lin_mat - 1][x + 1];

                    gotoxy(x + 1, *lin_mat);
                    printf("%c", M[*lin_mat - 1][x]);

                }

                gotoxy(vetor[*lin_mat - 1], *lin_mat);
                printf(" ");

                if(vetor[*lin_mat - 1] - 1 >= 1)
                    vetor[*lin_mat - 1]--;
               
            }

            else
            {

                if(vetor[*lin_mat - 1] + vetor[*lin_mat] <= LIM_COL && vetor[*lin_mat] > 0)
                {

                    for(x = vetor[*lin_mat - 1] + 1; x <= vetor[*lin_mat - 1] + vetor[*lin_mat]; x++)
                    {

                        M[*lin_mat - 1][x - 1] = M[*lin_mat][cont];

                        gotoxy(x, *lin_mat);
                        printf("%c", M[*lin_mat - 1][x - 1]);

                        gotoxy(cont + 1, *lin_mat + 1);
                        printf(" ");

                        cont++;

                    }

                    *col_mat = vetor[*lin_mat - 1] + 1;

                    vetor[*lin_mat - 1] += vetor[*lin_mat];

                    for(y = *lin_mat; y < *quant_lin; y++)
                    {
                        vetor[y] = vetor[y + 1];
                
                        for(x = 0; x < vetor[y + 1]; x++)
                        {

                            M[y][x] = M[y + 1][x];

                            gotoxy(x + 1, y + 1);
                            printf("%c", M[y][x]);

                            gotoxy(x + 1, y + 2);
                            printf(" ");

                        }
                        
                    }

                    if(*quant_lin > 1)
                        *quant_lin -= 1;
                }

            }

        break;

    }

}

void AtualizaLinha(int M[LIM_LIN][LIM_COL], int vetor[], int linha, int coluna, int quant_lin)
{

    int i, j, k = 1;

    if(coluna == vetor[linha - 1])
    {
        for(i = quant_lin - 1; i > linha - 1; i--)
        {   
        
            for(j = 0; j < vetor[i]; j++)
            {

                M[i + 1][j] = M[i][j];
                
                gotoxy(j + 1, i + 1);
                printf(" ");

                gotoxy(j + 1, i + 2);
                printf("%c", M[i + 1][j]);

            }

            vetor[i + 1] = vetor[i];

            if(i == linha)
            {

                M[linha][0] = ENTER;
                vetor[linha] = 1;

            }
        }
    }

    else
    {

        for(i = quant_lin - 1; i >= linha - 1; i--)
        {
            if(i >= linha)
            {
                for(j = 0; j < vetor[i]; j++)
                {

                    M[i + 1][j] = M[i][j];
                
                    gotoxy(j + 1, i + 1);
                    printf(" ");

                    gotoxy(j + 1, i + 2);
                    printf("%c", M[i + 1][j]);

                }

                vetor[i + 1] = vetor[i];
            }

            else
            {
                vetor[i + 1] = 0;

                for(j = coluna - 1; j < vetor[i]; j++)
                {
                    
                    M[i + 1][k - 1] = M[i][j];

                    vetor[i + 1] += 1;

                    gotoxy(j + 1, i + 1);
                    printf(" "); 

                    gotoxy(k, i + 2);
                    printf("%c", M[i][j]);

                    k++;

                }

                vetor[i] -= vetor[i + 1];
                
                M[i][vetor[i]] = ENTER;

                vetor[i] += 1;
                
            }
            
        }
    }
    
}

void Apaga_Caracter(int *quant_lin, int *col, int *lin, int M[LIM_LIN][LIM_COL], int vetor[])
{

    int j, c = 0, i;
    
    if(*col > 1)
    {
        gotoxy(vetor[*lin - 1], *lin);
        printf(" ");

        if(M[*lin - 1][vetor[*lin - 1] - 1] == ENTER || M[*lin - 1][vetor[*lin - 1] - 1] == NEW_LINE)
        {

            gotoxy(vetor[*lin - 1] - 1, *lin);
            printf(" ");

        }

        for(j = *col; j <= vetor[*lin - 1]; j++)
        {

            M[*lin - 1][j - 2] = M[*lin - 1][j - 1];

            gotoxy(j - 1, *lin);
            printf("%c", M[*lin - 1][j - 2]);

        }

        vetor[*lin - 1]--;
        
        *col -= 1;
    }

    else
    {

        if((*lin > 1 && vetor[*lin - 2] + vetor[*lin - 1] <= LIM_COL) || (vetor[*lin - 1] == 1 && *lin > 1))
        {
            for(j = vetor[*lin - 2]; j <= vetor[*lin - 2] + vetor[*lin - 1]; j++)
            {
                
                M[*lin - 2][j - 1] = M[*lin - 1][c];

                gotoxy(j, *lin - 1);
                printf("%c", M[*lin - 2][j - 1]);

                gotoxy(c + 1, *lin);
                printf(" ");
                
                c++; 
            }
            
            *col = vetor[*lin - 2];
            vetor[*lin - 2] += vetor[*lin - 1] - 1;

            if(vetor[*lin] > 0 || (vetor[*lin - 1] == 1 && *lin > 1))
            {
                c = vetor[*lin - 1];
                
                for(i = *lin; i < *quant_lin; i++)
                {
                    vetor[i - 1] = vetor[i];

                    for(j = 0; j < vetor[i]; j++)
                    {
                        M[i - 1][j] = M[i][j];

                        gotoxy(j + 1, i + 1);
                        printf(" ");

                        gotoxy(j + 1, i);
                        printf("%c", M[i - 1][j]);
                    
                    }

                } 

               
            }

            if(c == 1 && vetor[*lin - 1] == 0)
            *col = vetor[*lin - 2] - 1;

            vetor[*quant_lin - 1] = 0;
            *quant_lin -= 1;
            *lin -= 1;
        }

    }
        
}

/* funcao combinacao ctrl */
void CombinacaoTecla(int tcl, int quant_lin, int *lin, int *col, int vetor[], int M[LIM_LIN][LIM_COL])
{
    
    /* variaveis locais */
    int i, j, jAux = 0, confirmador = 0;

    /* verificar qual combinacao ctrl foi digitada */
    switch(tcl)
    {

        /* ctrl+home move o cursor para o inicio do texto */
        case CTRL_HOME:

            *lin = 1;
            *col = 1;

        break;

        /* ctrl+end move cursor para final do texto */
        case CTRL_END:

            *lin = quant_lin;
            *col = vetor[quant_lin - 1] + 1;
        
        break;

        /* ctrl+seta_direita move o cursor para o inicio de cada palavra */
        case CTRL_SETA_DIREITA:
            
            /* loop para percorrer da linha atual ate a ultima linha do texto */
            for(i = *lin - 1; i < quant_lin; i++)
            {
                /* quando for o primeiro caso pegar posicao de coluna atual do texto */
                if(i == *lin - 1)
                    jAux = *col - 1;
                
                /* demais casos iniciar a coluna da posicao 0 de cada linha do texto */
                else
                    jAux = 0;

                /* loop para percorrer da coluna de cada linha */
                for(j = jAux; j < vetor[i]; j++)
                {

                    /* condicao para identificar uma nova palavra, ou seja tudo que for diferente de letras podemos identificar fim da palavra */                        
                    if(M[i][j] < 'A' || M[i][j] > 'z' || (j == vetor[i] - 1 && M[i][j] != ENTER) || M[i][j] == ENTER)
                    {
                        /* se j estiver no limite do tamanho de linha entra no loop para a varificacao */
                        if(j < vetor[i] - 1)

                            /* loop para verificar se as proximas posicoes sao diferentes de letras */
                            while((M[i][j] < 'A' || M[i][j] > 'z') && i < quant_lin)
                            {

                                /* se j chegar no limite da coluna entao ir para proxima linha */
                                if(j == LIM_COL - 1)
                                {

                                    i++;
                                    j = 0;

                                }

                                /* senao incrementa posicao de j */
                                else    
                                    j++;
                                
                                /* ir atualizando o valor da linha e coluna para identificar nova palavra */
                                *lin = i + 1;
                                *col = j + 1;
                                
                            }
                        
                        /* se j == tamanho de linha - 1, fazer a compacao se eh enter */ 
                        else
                        {
                            
                            /* caso encontre enter entao linha ira recber a i + 2 e coluna = 1 */
                            if((M[i][j] == ENTER || M[i][j] == NEW_LINE) && i + 1 < quant_lin && *col == vetor[i])
                            {

                                *lin = i + 2;
                                *col = 1;

                            }

                            /* caso j seja == ao tamanho da linha - 1 e nao encontre caracteres diferentes de letras, linha = i + 1 e coluna = tam da linha */
                            else
                            {
                            
                                *lin = i + 1;
                                *col = vetor[i];
                            }

                        }
                        
                        /* confirmador de nova palavra */
                        confirmador = 1;

                        break;
                    
                    }
                }

                /* saida do loop de linha */
                if(confirmador == 1)
                    break;
               
            }

        break;
        
        /* ctrl+seta_esquerda vai mover o cursor para o final de cada palavra */
        case CTRL_SETA_ESQUERDA:
            
            if(*col > 1)
                jAux = *col - 2;

            else
                jAux = *col - 1;

            /* loop para percorrer da linha atual ate achar nova palavra */
            for(i = *lin - 1; i >= 0; i--)
            {
        
                /* loop para percorrer as colunas */
                for(j = jAux; j >= 0; j--)
                {
                    
                    /* condicao para identificar nova palavra, ou seja identificar qual a primeira posicao que difere de letras */
                    if(M[i][j] < 'A' || M[i][j] > 'z' || j == 0 || M[i][j] == ENTER)
                    {
                        
                        /* loop para percorrer a matriz ate achar uma nova palavra ou seja um caracter letra */
                        while(M[i][j] < 'A' || M[i][j] > 'z' || j == 0 || M[i][j] == ENTER)
                        {
                            
                            /* se j == 0 significa que nao encontrou nenhum caracter diferente de letras na linha */
                            if(j == 0)
                            {

                                /* se coluna > 1 significa que tem que mover a coluna para posicao 1 pois nao encontrou nenhum caracter diferente*/
                                if(*col > 1)
                                    *col = 1;

                                /* senao move para linha anterior */
                                else
                                    if(i > 0)
                                    {
                                        i--;
                                        j = vetor[i] - 1;
                                         
                                    }
                                
                            }
                           
                            /* decremento de j se for > 0 */
                            else  
                                j--; 

                            /* condicao para parar loop, pois significa que achou um caracter letra, que eh o final de uma nova palavra */
                            if((M[i][j] >= 'A' && M[i][j] <= 'z') || (j == 0 && (M[i][j] < 'A' || M[i][j] > 'z')) || M[i][j] == ENTER)
                            {
                                if((M[i][j] >= 'A' && M[i][j] <= 'z') || M[i][j] == ENTER)
                                {
                                    *lin = i + 1;
                                    *col = j + 1;
                                }

                                confirmador = 1;

                                /* saida do while */
                                break;
                            }
                        }
                    
                        /* sair do loop de colunas */
                        if(confirmador == 1)
                            break;
                    }
                }
                
                /* sair do loop de linhas */
                if(confirmador == 1)
                    break;
               
            }

        break;

        /* ctrl+seta_baixo move o cursor para o inicio da proxima frase frase */
        case CTRL_SETA_BAIXO:

            /* percorrer da linha atual ate ultima linha */
            for(i = *lin - 1; i < quant_lin; i++)
            {

                /* percorrer da coluna atual ate final de cada linha */
                for(j = *col - 1; j < vetor[i]; j++)
                    
                    /* se a posicao da matriz for enter encontramos o final da frase atual, logo atualizamos cursor para proxima linha */
                    if(M[i][j] == ENTER && vetor[i] < LIM_COL)
                    {
                        
                        *lin = i + 2;
                        *col = 1;

                        /* saida do laco de coluna */
                        if(*col < LIM_COL)
                        {
                            confirmador = 1;
                            break;
                        }

                    }

                /* saida do laco de linhas */
                if(confirmador == 1)
                    break;
            }
            
        break; 

        /* ctrl+seta_cima move cursor para inicio da frase anterior */
        case CTRL_SETA_CIMA:
            
            /* percorrer de linha atual ate a primeira linha */
            for(i = *lin - 1; i >= 0; i--)
            {

                /* percorrer de coluna atual ate o inicio da linha  */
                for(j = *col - 1; j >= 0; j--)

                    /* se encontramos enter na posicao anterior de i entao i + 1 eh o inicio da frase anterior */
                    if(M[i - 1][vetor[i - 1] - 1] == ENTER && i >= 1)
                    {

                        *lin = i;

                        *col = 1;
                        
                        /* said do loop de coluna*/
                        if(vetor[i - 2] < LIM_COL)
                        {
                            confirmador = 1;
                            break;
                        }
                        
                    }
                    
                /* saida do loop de linhas */
                if(confirmador == 1)
                    break;
            }

        break;

    }

}