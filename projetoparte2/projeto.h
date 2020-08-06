//
// Created by maria on 04/01/2019.
//

#ifndef PROJETOPARTE2_PROJETO_H
#define PROJETOPARTE2_PROJETO_H
#include "stdio.h"
#include <malloc.h>
#include <math.h>
#include "stdlib.h"
#include "string.h"
#include "strings.h"
#include "time.h"
#define Max200  200
#include "mergesort/mergesort.h"
#define Fiename1 "C:\\Users\\Luisa\\CLionProjects\\projetoparte2\\data\\dicionario.txt"
#define Filename2 "C:\\Users\\Luisa\\CLionProjects\\projetoparte2\\data\\sopaletras.txt"
#define Fiename3 "C:\\Users\\Luisa\\CLionProjects\\projetoparte2\\data\\data\\dicionariobin.bin"
#define Filename4 "C:\\Users\\Luisa\\CLionProjects\\projetoparte2\\data\\data\\sopaletrasbin.bin"

int main_projeto2();

typedef struct cache
{
    char *direcoes;
    char *palavra;
    struct cache *next;

}CACHE;

typedef struct celula
{
    char c;
    int plinha;
    int pcoluna;
    int check;
    struct celula *norte;
    struct celula *sul;
    struct celula *este;
    struct celula *oeste;
    struct celula *nordeste;
    struct celula *noroeste;
    struct celula *sudeste;
    struct celula *sudoeste;
    struct cache  *cache1;
}CELL;


typedef struct sopaletras
{
    int linha;
    int coluna;
    CELL *pfirst;
}SOPALETRAS;

typedef struct palavra          // Estrutura para cada palavra do dicionário
{
    int len;
    char *ppalavra;             // Apontador para a palvra
    struct palavra *next;       // Apontador para a palavra a seguir
}PALAVRA;                       // Nome da estrutura

typedef struct dicionario       // Estrutura para o dicionário contém:
{
    PALAVRA *pfirst;            // Apontador para a primeira palavra do dicionário
    int npalavras;// Número de palavras que o dicionário contém
    struct palavra* cabeca;
    struct palavra* cauda;
}DICIONARIO;                    // Nome da estrutura


//------------------------------------------R5A------------------------------------------//
void inserir_palavras();
void imprimir_dicionario_manual(DICIONARIO * dicionario);
void inserir_queue(DICIONARIO* dicionario, PALAVRA* palavra);
PALAVRA* imprimir_queue(DICIONARIO* dicionario);
void converter_maiusculas(char*palavra);
//------------------------------------------R5B------------------------------------------//
void ler_dicionario_txt(DICIONARIO *pcs);
int numero_palavras();
void print_dicionario(DICIONARIO dc);
void print_palavra(PALAVRA s);
//------------------------------------------R6------------------------------------------//
//mergesort
//------------------------------------------R7------------------------------------------//
void estruturatab(SOPALETRAS*tab, int linhas, int colunas);
CELL* criar_celula(int linha, int coluna);
void print_matriz(SOPALETRAS tab);
//------------------------------------------R8A------------------------------------------//
void leitura_matriz_carac_txt(SOPALETRAS sopaletra,int linhas, int colunas);
int numero_colunas();
int numero_linhas();
//------------------------------------------R8B------------------------------------------//
int maior_palavra(DICIONARIO dicionario);
CELL *consistencia_celula(SOPALETRAS *sp, int x, int y);
void limpar_tab(SOPALETRAS *sp);
int direcao_consistencia(CELL *celula);
SOPALETRAS* matriz_aleatoria(SOPALETRAS* sp,char pal[],int len,int nletra,CELL *celula, int *avancar,int *dir, char direcoes[]);
void dir_aleatoria(char dir[]);
void main_matriz_aleatoria(DICIONARIO dicionario, SOPALETRAS *sp);
void completar_matriz(SOPALETRAS *sp);
void limpar_ta_c(SOPALETRAS sp,int x, int y, char direcoes[], int dir);



//------------------------------------------R9------------------------------------------//
//------------------------------------------R10------------------------------------------//
void retornar_caracteres(SOPALETRAS sp);
//------------------------------------------R11------------------------------------------//
CACHE *encontrar_palavra(CELL *aux,char direcoes[],CACHE *cac,char palavra[],CELL *celula,int rotacoes);
void main_recursiva(DICIONARIO dic, SOPALETRAS sp);
int consistencia(CELL *celula,char letra);
CACHE * criar_cache();
void print_resultado(SOPALETRAS *sp);
//------------------------------------------R12------------------------------------------//
void guardar_palavras_txt(DICIONARIO cs,char *fn);
//------------------------------------------R13------------------------------------------//
void guardar_dcionario_bin(DICIONARIO cs);
void ler_dicionario_bin(DICIONARIO *pcs);
void gravar_sopa_de_letras_bin(SOPALETRAS sp);

void guardar_sopa_bin(SOPALETRAS sopa);
void ler_sopa_bin(SOPALETRAS *sp);
void inserir_palavras_MERGE(LIST *list);

#endif //PROJETOPARTE2_PROJETO_H
