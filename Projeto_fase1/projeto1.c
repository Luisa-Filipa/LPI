//
// Created by Luísa on 13/12/2018.
//

#include "projeto1.h"

int main_Testes() {
    char **matriz_nomes;
    char **matriz_sopa;
    char **matriz_aleatoria;
    int **caminho;
    int nnomes = 0, lin = 0, col = 0;
    int *psolucao;

    // matriz_nomes=insercao_manual_nomes(&nnomes);
    matriz_nomes = ler_ficheiro_texto(&nnomes);
    //clienteMSDSORT_WHITHOUT_CUTOFF(matriz_nomes, nnomes);
    //matriz_aleatoria=cliente_matriz_aleatoria(&lin, &col);
    matriz_sopa = ler_fich_SopaLetras(&lin, &col);
    //cliente_palavras_sopa();
    caminho = caminho_palavra(matriz_sopa, matriz_nomes, lin, col, nnomes);
    //caminho_palavra(matriz_aleatoria,matriz_nomes,lin,col,nnomes);

    //printf(" %d %d %d", lin, col, nnomes);

    return 0;
}
//---------------------------------------R1-a)-------------------------------------------
/**
 * Inserção manual de nomes
 * @param nnomes
 * @return
 */
char **insercao_manual_nomes(int *nnomes) {


    char *str = malloc(100 * sizeof(char));

    printf("Quantas palavras vai receber\n");
    scanf("%d", nnomes);

    char **mlista = malloc(*nnomes * sizeof(char *));
    if (mlista == NULL) {
        printf("Erro na alocação de espaço");
    } else {
        printf("Insira as palavras\n");
        for (int i = 0; i < *nnomes; i++) {
            scanf("%s", str);
            strupr(str);//colocar a maiusculas
            *(mlista + i) = malloc((strlen(str) + 1) * sizeof(char));
            strcpy(*(mlista + i), str);
        }
    }

    printf("\n");
    for (int i = 0; i < *nnomes; i++) {
        printf("%s\n", *(mlista + i));
    }
    return mlista;
}
//---------------------------------------R1-b)-------------------------------------------

/**
 * Lê os nomes do ficheiro de texto
 */
char **ler_ficheiro_texto(int *nnomes) {
    int i;
    char strAux[100];

    FILE *fp;// Criação da variável ponteiro para manusear o arquivo
    fp = fopen("lista_nomes.txt", "r"); //Abrir o arquivo apenas para o ler, dai ser usado a letra "r"
    if (fp == NULL) {
        printf("Erro na abertura do ficheiro!");
    }
    *nnomes = numero_linhas();
    char **matriz = malloc(*nnomes * sizeof(char *));
    if (matriz == NULL) {
        printf("Erro na alocação de memória");
    } else {
        for (i = 0; i < *nnomes; i++) {
            fgets(strAux, sizeof(strAux), fp);
            if (strAux[strlen(strAux) - 1] == '\n') {
                strAux[strlen(strAux) - 1] = '\0';
            }
            *(matriz + i) = copiar_string_dinamica(strAux);
            // printf("\n%s", *(matriz + i));
        }
    }
    fclose(fp);                         // fechar o ficheiro de texto
    return matriz;
}

/**
 * conta o numero de linhas de um ficheiro
 * @return
 */
int numero_linhas() //contar linhas
{
    FILE *fp;
    int count = 0;
    char c;
    fp = fopen("lista_nomes.txt", "r");
    if (fp == NULL) {
        printf("Erro na abertura do ficheiro");
        return 0;
    }
    count++;
    for (c = getc(fp); c != EOF; c = getc(fp)) {
        if (c == '\n') {
            count = count + 1;
        }
    }
    fclose(fp);
    return count;
}


/**
 *cria uma copia dunamica de uma string
 * @param str string lida do ficheiro
 * @return pc string auxiliar que guarda a palavra consoante o tamanho
 */
char *copiar_string_dinamica(char *str) {
    char *pc = malloc((strlen(str) + 1) * sizeof(char));
    strupr(str);
    strcpy(pc, str);
    return pc;
}
//---------------------------------------R2---------------------------------------------

int charAt(StringElementsArray *a, int i, int d) {

    return (d < a->len[i]) ? (a->str[i][d]) : STRING_END_CHAR;
}

void createStringElementsArray(StringElementsArray *si, int n) {
    si->n = n;
    si->str = (char **) malloc(sizeof(char *) * n);
    si->len = (int *) malloc(sizeof(int) * n);
}

void createStringElementsArrayAndFill(StringElementsArray *si, int n, char **strings) {
    int i;
    createStringElementsArray(si, n);
    for (i = 0; i < n; i++) {
        si->str[i] = strings[i];
        si->len[i] = (int) strlen(strings[i]);
    }
}

int *newIntArray(int n) {
    return (int *) malloc(sizeof(int) * n);
}

void msd_sort_whithout_cutoff(StringElementsArray *a, StringElementsArray *aux, int lo, int hi, int d, int R) {
    int i, r, c;
    int *count = newIntArray(R + 2);
    // reset count[] array
    for (i = 0; i < R + 2; i++)
        count[i] = 0;

    if (hi <= lo) return;
    //if (hi - lo <= cutoff_value) insertion_sort();

    // compute frequency counts
    for (i = lo; i <= hi; i++) {
        c = charAt(a, i, d);
        count[c + 2]++;
    }

    // transform counts to indicies
    for (r = 0; r < R + 1; r++)
        count[r + 1] += count[r];

    // distribute
    for (i = lo; i <= hi; i++) {
        c = charAt(a, i, d);
        aux->str[count[c + 1]] = a->str[i];
        aux->len[count[c + 1]] = a->len[i];
        count[c + 1]++;
    }

    // copy back
    for (i = lo; i <= hi; i++) {
        a->str[i] = aux->str[i - lo];
        a->len[i] = aux->len[i - lo];

    }


    // recursively sort for each character

    for (r = 0; r < R; r++)
        msd_sort_whithout_cutoff(a, aux, lo + count[r], lo + count[r + 1] - 1, d + 1, R);
}

/**
 * free liberta a memoria alocada
 * @param si
 */
void freeStringElementsArray(StringElementsArray *si) {
    free(si->str);
    free(si->len);
}

int clienteMSDSORT_WHITHOUT_CUTOFF(char **strings, int n) {
    int i;
    StringElementsArray a;
    StringElementsArray aux; // aux Array

    createStringElementsArrayAndFill(&a, n, strings);
    createStringElementsArray(&aux, n); // create aux array

    msd_sort_whithout_cutoff(&a, &aux, 0, n - 1, 0, CHAR_8BIT_RADIX); // MSD sort

    printf("\n-------------\nMSD Sorted List Final:\n");
    for (i = 0; i < n; i++) {
        printf("\t%s, %d\n", a.str[i], a.len[i]);
    }

    for (int j = 0; j < n; ++j) {
        *(strings + j) = a.str[j];
    }

    freeStringElementsArray(&a);
    freeStringElementsArray(&aux);
    return 0;
}


//---------------------------------------R3-a)------------------------------------------
/**
 * Cliente para o teste de gerar uma matriz aleatoria
 */
char **cliente_matriz_aleatoria(int *lin, int *col) {
    char **matriz_sopa;

    matriz_sopa = gerar_matriz_al(lin, col);

    for (int k = 0; k < (*lin); ++k) {
        for (int i = 0; i < (*col); ++i) {
            printf("%c", *(*(matriz_sopa + k) + i));
        }
        printf("\n");
    }

    return matriz_sopa;
}

/**
 * Gera uma matriz dinamica aleatória
 * @param nlinhas
 * @param ncolunas
 * @return
 */
char **gerar_matriz_al(int *nlinhas, int *ncolunas) {
    char **matriz_aleatoria = NULL;
    printf("Quantas linhas e colunas vai inserir \n");
    scanf(" %d %d", nlinhas, ncolunas);
    time_t t;

    srand((unsigned) time(&t));
    matriz_aleatoria = malloc(*nlinhas * sizeof(char *));
    for (int i = 0; i < *nlinhas; i++) {
        *(matriz_aleatoria + i) = malloc(*ncolunas + 1 * sizeof(char));
        for (int j = 0; j < *ncolunas; j++) {
            *(*(matriz_aleatoria + i) + j) = (char) ('A' + rand() % 26); //gera caracter entre A e Z
        }
    }
    return matriz_aleatoria;
}

//---------------------------------------R3-b)------------------------------------------

/**
 * lê do ficheiro da sopa de letras a sopa de letras
 * @param nlinhas
 * @param ncolunas
 * @return
 */
char **ler_fich_SopaLetras(int *nlinhas, int *ncolunas) {

    char **msopaletras;
    numero_linhas_colunas(nlinhas, ncolunas);
    FILE *fp;                         // Criação da variável ponteiro para manusear o arquivo
    fp = fopen("sopa_letras.txt", "r"); //Abrir o arquivo apenas para o ler, dai ser usado a letra "r"
    msopaletras = malloc(*nlinhas * sizeof(char *));
    if (msopaletras == NULL) {
        printf("Erro na alocação de memória");
    } else {
        msopaletras = malloc(*nlinhas * sizeof(char *));

        for (int i = 0; i < *nlinhas; i++) {
            *(msopaletras + i) = malloc(*ncolunas * sizeof(char));
        }

        for (int i = 0; i < (*nlinhas); i++) {
            fscanf(fp, "%s\n", *(msopaletras + i));
            strupr(*(msopaletras+i));
            msopaletras[i][*ncolunas - 1] = '\0';
        }
        fclose(fp);
    }

    /* for (int i = 0; i <(*nlinhas) ; i++) {
         printf("\n");
         for (int j = 0; j <(*ncolunas) ; j++) {

             printf("%c",*(*(msopaletras+i)+j));
         }
     }*/

    return msopaletras;
}

/**
 * Conta o numero de linhas e colunas da matriz
 * @param countl
 * @param countc
 */
int numero_linhas_colunas(int *countl, int *countc) //contar linhas
{
    FILE *fp;
    char c;
    fp = fopen("sopa_letras.txt", "r");
    if (fp == NULL) {
        printf("Erro na abertura do ficheiro");
        return 0;
    }
    *countl = 1;
    for (c = getc(fp); c != EOF; c = getc(fp)) {
        if (c == '\n') {
            *countl = *countl + 1;
        }
    }
    fclose(fp);

    fp = fopen("sopa_letras.txt", "r");
    if (fp == NULL) {
        printf("Erro na abertura do ficheiro");
        return 0;
    }
    *countc = 1;
    while ((c = getc(fp) != '\n')) {
        *countc += 1;
    }
    //printf("%d %d",*countl,*countc);
    fclose(fp);

}


//---------------------------------------R4--------------------------------------------

/**
 * Teste para verificar se nos encontramos dentro do tabuleiro sopa de letras ou não
 * @param linha
 * @param coluna
 * @param llimite_sopa
 * @param climite_sopa
 * @return
 */
int dentro_matriz(int linha, int coluna, int llimite_sopa, int climite_sopa) {
    if (linha >= 0 && linha < llimite_sopa && coluna >= 0 && coluna < climite_sopa) {
        return 1;
    }
    return 0;
}

/**
 * Encontrar as colunas ( cada letra ) de cada palavra ( linha)
 * @param matriz_palavra palavras lidas da matriz de palavra
 * @param linha_palavra linhas da matriz lida
 * @param colunas_palavra colunas de cada linha lida da matriz
 * @return
 */
int *encontrar_colunas_palavra(char **matriz_palavra, int linha_palavra, int *colunas_palavra) {
    colunas_palavra = malloc(linha_palavra * sizeof(int));
    for (int i = 0; i < linha_palavra; i++) {
        *(colunas_palavra + i) = strlen(*(matriz_palavra + i));

    }
    return colunas_palavra;
}

/**
 * guardar na variável caminho o returnado na funçãpo guardar caminho
 * @param matriz_sopa matriz lida do ficheiro da sopa de letras
 * @param matriz_palavra matriz lida do ficheiro que contém as palavras a procurar
 * @param linha_sopa
 * @param coluna_sopa
 * @param linha_palavra
 */
int** caminho_palavra(char **matriz_sopa, char **matriz_palavra, int linha_sopa, int coluna_sopa, int linha_palavra)
{
    int colunas_palavra;
    int *pcolunas_palavra = encontrar_colunas_palavra(matriz_palavra, linha_palavra, &colunas_palavra);
    int solucao = 0;// ver se é 1 ou 0
    int **caminho;

    malloc(linha_palavra* sizeof(int*));

    for (int i = 0; i < linha_palavra; i++) {
        *(aux2+i)=malloc(*(pcolunas_palavra+i)+1* sizeof(int));
        for (int j = 0; j < linha_sopa; j++) {
            for (int k = 0; k < coluna_sopa; k++) {
                if (*(*(matriz_sopa + j) + k) == *(*(matriz_palavra + i)) &&
                    dentro_matriz(j, k, linha_sopa, coluna_sopa) == 1) {
                    malloc(*(pcolunas_palavra+i)+1* sizeof(int));
                    caminho=caminho_a_guardar(*(matriz_palavra + i), *(pcolunas_palavra + i), &solucao, 1, j, k,
                                              linha_sopa, coluna_sopa, matriz_sopa,aux,aux2,linha_palavra);
                }
            }
        }
    }

    return caminho;
}

/**
 * Caminho guardado e que no final da função vai returnar o caminho
 * @param letra letra a ser procurada
 * @param tam_palavra tamanho da palavra
 * @param psolucao
 * @param nletra numero
 * @param linha_letra linha do ficheiro de texto lido
 * @param coluna_letra coluna de cada linha de cada um dos nomes lido
 * @param linha_sopa linha da sopa de letras
 * @param coluna_sopa coluna da sopa de letras
 * @param SopaLetras ficheiro de onde vai ser lida a matriz
 * @return caminho percorrido
 */
int **caminho_a_guardar(char *letra, int tam_palavra, int *psolucao, int nletra, int linha_letra, int coluna_letra,
                        int linha_sopa, int coluna_sopa, char **SopaLetras,int* aux,int** aux2,int nlinhas) {


    if (*(*(SopaLetras + linha_letra) + coluna_letra) == *(letra + tam_palavra - 1) && tam_palavra == nletra) {
        for (int j = 0; j <tam_palavra-1 ; ++j) {
            *(*(aux2+*(psolucao))+j+2)=*(aux+(j));
        }
        *(*(aux2+*(psolucao)))=*(aux+(tam_palavra));
        *(*(aux2+*(psolucao))+1)=*(aux+(tam_palavra-1));
        (*psolucao)++;
        *(aux2+(*(psolucao)))=malloc(tam_palavra+1* sizeof(int));
        //print_caminho(tam_palavra, *(caminho+i));
        if(nlinhas-1<=*psolucao)
        {
            aux2=realloc(aux2,nlinhas* sizeof(int));
            nlinhas*=(*psolucao);
        }
        printf("Sucesso solucao:%d\n", *psolucao);
        return aux2;
    }
    if (dentro_matriz(linha_letra - 1, coluna_letra, linha_sopa, coluna_sopa) == 1) {
        if (*(*(SopaLetras + (linha_letra - 1)) + coluna_letra) == *(letra + nletra)) {
            if (nletra - 1 == 0) {
                *(aux + tam_palavra) = linha_letra;

                *(aux + tam_palavra - 1) = coluna_letra;
            }
            // norte
            *(aux + (nletra - 1)) = 1;
            nletra++;
            caminho_a_guardar(letra, tam_palavra, psolucao, nletra, linha_letra - 1, coluna_letra, linha_sopa,
                              coluna_sopa, SopaLetras, aux, aux2,nlinhas);
        }
    }
    if (dentro_matriz(linha_letra + 1, coluna_letra, linha_sopa, coluna_sopa) == 1) {
        if (*(*(SopaLetras + (linha_letra + 1)) + coluna_letra) == *(letra + nletra)) {
            if (nletra - 1 == 0) {
                *(aux + tam_palavra) = linha_letra;

                *(aux + tam_palavra - 1) = coluna_letra;
            }
            // sul
            *(aux + (nletra - 1)) = 2;
            nletra++;
            caminho_a_guardar(letra, tam_palavra, psolucao, nletra, linha_letra + 1, coluna_letra, linha_sopa,
                              coluna_sopa, SopaLetras, aux, aux2,nlinhas);
        }
    }
    if (dentro_matriz(linha_letra, coluna_letra - 1, linha_sopa, coluna_sopa) == 1) {
        if (*(*(SopaLetras + (linha_letra)) + coluna_letra - 1) == *(letra + nletra)) {
            if (nletra - 1 == 0) {
                *(aux + tam_palavra) = linha_letra;

                *(aux + tam_palavra - 1) = coluna_letra;
            }
            // oeste
            *(aux + (nletra - 1)) = 3;
            nletra++;
            caminho_a_guardar(letra, tam_palavra, psolucao, nletra, linha_letra, coluna_letra - 1, linha_sopa,
                              coluna_sopa, SopaLetras, aux, aux2,nlinhas);

        }
    }
    if (dentro_matriz(linha_letra, coluna_letra + 1, linha_sopa, coluna_sopa) == 1) {
        // printf("\n\t[2]%c-%c\n",*(*(SopaLetras + (linha_letra)) + coluna_letra+1),*(letra + rotates));
        if (*(*(SopaLetras + (linha_letra)) + coluna_letra + 1) == *(letra + nletra)) {
            if(nletra-1==0) {   // guarda o lin e col da primeira letra
                *(aux + tam_palavra) = linha_letra;

                *(aux + tam_palavra - 1) = coluna_letra;
            }
            // este
            *(aux+(nletra-1)) = 4; //começa a guardar na posiçao aux[2], até ao fim
            nletra++;

            caminho_a_guardar(letra, tam_palavra, psolucao, nletra, linha_letra, coluna_letra + 1, linha_sopa,
                              coluna_sopa, SopaLetras,aux,aux2,nlinhas);
        }
    }
    if (dentro_matriz(linha_letra - 1, coluna_letra + 1, linha_sopa, coluna_sopa) == 1) {
        if (*(*(SopaLetras + (linha_letra - 1)) + coluna_letra + 1) == *(letra + nletra)) {
            if (nletra - 1 == 0) {
                *(aux + tam_palavra) = linha_letra;

                *(aux + tam_palavra - 1) = coluna_letra;
            }
            // Nordeste
            *(aux + (nletra - 1)) = 5;
            nletra++;
            caminho_a_guardar(letra, tam_palavra, psolucao, nletra, linha_letra - 1, coluna_letra + 1, linha_sopa,
                              coluna_sopa, SopaLetras, aux, aux2,nlinhas);
        }
    }
    if (dentro_matriz(linha_letra + 1, coluna_letra + 1, linha_sopa, coluna_sopa) == 1) {
        if (*(*(SopaLetras + (linha_letra + 1)) + coluna_letra + 1) == *(letra + nletra)) {
            if (nletra - 1 == 0) {
                *(aux + tam_palavra) = linha_letra;

                *(aux + tam_palavra - 1) = coluna_letra;
            }
            // Sudeste
            *(aux + (nletra - 1)) = 6;
            printf("\t%d\n",*(aux));
            nletra++;
            caminho_a_guardar(letra, tam_palavra, psolucao, nletra, linha_letra + 1, coluna_letra + 1, linha_sopa,
                              coluna_sopa, SopaLetras, aux, aux2,nlinhas);
        }
    }
    if (dentro_matriz(linha_letra - 1, coluna_letra - 1, linha_sopa, coluna_sopa) == 1) {
        if (*(*(SopaLetras + (linha_letra - 1)) + coluna_letra - 1) == *(letra + nletra)) {
            if (nletra - 1 == 0) {
                *(aux + tam_palavra) = linha_letra;

                *(aux + tam_palavra - 1) = coluna_letra;
            }
            // Noroeste
            *(aux + (nletra - 1)) = 7;
            nletra++;
            caminho_a_guardar(letra, tam_palavra, psolucao, nletra, linha_letra - 1, coluna_letra - 1, linha_sopa,
                              coluna_sopa, SopaLetras, aux, aux2,nlinhas);

        }
    }
    if (dentro_matriz(linha_letra + 1, coluna_letra - 1, linha_sopa, coluna_sopa) == 1) {
        if (*(*(SopaLetras + (linha_letra + 1)) + coluna_letra - 1) == *(letra + nletra)) {
            if (nletra - 1 == 0) {
                *(aux + tam_palavra) = linha_letra;

                *(aux + tam_palavra - 1) = coluna_letra;
            }
            // Sudoeste
            *(aux + (nletra - 1)) = 8;
            nletra++;
            caminho_a_guardar(letra, tam_palavra, psolucao, nletra, linha_letra + 1, coluna_letra - 1, linha_sopa,
                              coluna_sopa, SopaLetras, aux, aux2,nlinhas);
        }
    }
    return aux2;
}

void print_caminho(int tam_palavra, int *caminho) {
    for (int i = 0; i < tam_palavra; i++) {
        if (*(caminho + i) == 1) {
            printf("[N]");
        }
        if (*(caminho + i) == 2) {
            printf("[S]");
        }
        if (*(caminho + i) == 3) {
            printf("[O]");
        }
        if (*(caminho + i) == 4) {
            printf("[E]");
        }
        if (*(caminho + i) == 5) {
            printf("[NE]");
        }
        if (*(caminho + i) == 6) {
            printf("[SE]");
        }
        if (*(caminho + i) == 7) {
            printf("[NO]");
        }
        if (*(caminho + i) == 8) {
            printf("[SO]");
        }
    }
}