//
// Created by Luísa on 13/12/2018.
//

#ifndef PROJETO_FASE1_PROJETO1_H
#define PROJETO_FASE1_PROJETO1_H
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <strings.h>
#include <time.h>
#include <string.h>
#include "malloc.h"

int main_Testes();

//-------------------R1-a)-------------------
char **insercao_manual_nomes(int *nnomes);

//-------------------R1-b)-------------------
char **ler_ficheiro_texto(int *nnomes);
int numero_linhas();
char *copiar_string_dinamica(char * str);

//-------------------R2----------------------

#define CHAR_8BIT_RADIX 256 // tamanho do alfabeto de chars com 8 bits (ASCII)
// terminate symbol for strings
#define STRING_END_CHAR -1


typedef struct {
    char ** str; // array of strings
    int * len; // array of string lengths
    int n; // number of strings (size of array of strings)
} StringElementsArray;
void msd_sort_whithout_cutoff(StringElementsArray *a, StringElementsArray *aux, int lo, int hi, int d, int R);
void createStringElementsArrayAndFill(StringElementsArray * si, int n, char ** a);
void createStringElementsArray(StringElementsArray * si, int n);
void freeStringElementsArray(StringElementsArray * si);
int clienteMSDSORT_WHITHOUT_CUTOFF();
int charAt(StringElementsArray * a, int i, int d);
int *newIntArray(int n);


//-------------------R3-a)--------------------
char **cliente_matriz_aleatoria(int *lin, int *col);
char** gerar_matriz_al(int *nlinhas,int *ncolunas);

//-------------------R3-b)--------------------

char** ler_fich_SopaLetras(int *nlinhas,int *ncolunas);
int numero_linhas_colunas(int* countl,int* countc);

//-------------------R4-------------------------
void cliente_palavras_sopa();
int **caminho_palavra(char** matriz_sopa,char** matriz_palavra,int linha_sopa,int coluna_sopa,int linha_palavra);
int dentro_matriz(int linha,int coluna, int llimite_sopa, int climite_sopa);
int ** caminho_a_guardar(char* letra,int tam_palavra,int *psolucao,int nletra, int linha_letra,int coluna_letra, int linha_sopa,int coluna_sopa,char **SopaLetras,int* aux,int** aux2,int nlinhas );
int* encontrar_colunas_palavra(char** matriz_palavra,int linha_palavra,int* colunas_palavra);
void print_caminho(int nletra, int *caminho);
#endif //PROJETO_FASE1_PROJETO1_H
