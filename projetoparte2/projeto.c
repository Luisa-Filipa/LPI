//
// Created by maria on 04/01/2019.
//
#include "projeto.h"

int main_projeto2()
{   int linha,coluna;
    DICIONARIO cs={NULL,0,NULL,NULL};
    DICIONARIO teste={NULL,0,NULL,NULL};
    SOPALETRAS sp={0,0,NULL};
    SOPALETRAS testes={0,0,NULL};
    LIST list={NULL,0};

//------------------------------------------R5A------------------------------------------//
 //  inserir_palavras();
//------------------------------------------R5B------------------------------------------//
  // ler_dicionario_txt(&cs);
//   print_dicionario(cs);
//------------------------------------------R6------------------------------------------//
 //   inserir_palavras_MERGE(&list);
//------------------------------------------R7------------------------------------------//
 //   estruturatab(&sp,10,10);
 // print_matriz(sp);
//------------------------------------------R8A------------------------------------------//
/*    linha=numero_linhas();
   coluna=numero_colunas();
    leitura_matriz_carac_txt(sp,linha,coluna);
    estruturatab(&sp,linha,coluna);
    print_matriz(sp);*/
//------------------------------------------R9-------------------------------------------//
  // main_matriz_aleatoria(cs,&sp);
   // print_matriz(sp);
//------------------------------------------R10------------------------------------------//
    ler_dicionario_txt(&cs);
    linha=numero_linhas();
    coluna=numero_colunas();
    estruturatab(&sp,linha,coluna);
    leitura_matriz_carac_txt(sp,linha,coluna);
    print_matriz(sp);
   /* retornar_caracteres(sp);*/
//------------------------------------------R11------------------------------------------//
    main_recursiva(cs,sp);
    print_resultado(&sp);
//------------------------------------------R13------------------------------------------//
//     guardar_dcionario_bin(cs);
  // ler_dicionario_bin(&teste);
  // print_dicionario(cs);
   // print_dicionario(cs);

  //  guardar_sopa_bin(sp);
// ler_sopa_bin(&testes);
  // print_matriz(testes);
//   print_matriz(sp);
}
//------------------------------------------R5A------------------------------------------//
/**
 *
 */
void inserir_palavras() {
    DICIONARIO dicionario = {NULL, 0}; //inicializar a estrutura
    int npalavras = 0;
    char str[15]; //array para a palavra
    printf("Quantas palavras vai inserir ?");
    scanf("%d", &npalavras);

    printf("Insira as palavras\n");
    for (int i = 0; i < npalavras; i++) {
        PALAVRA *temp = malloc(sizeof(PALAVRA)); //allocar espaço para a struct PALAVRA
        scanf("%s", str);
        converter_maiusculas(str);
        temp->ppalavra = malloc(strlen(str) + 1 * sizeof(char));
        temp->len=strlen(str);
        strcpy(temp->ppalavra, str);
        inserir_queue(&dicionario,temp);
    }
    imprimir_dicionario_manual(&dicionario);
}
/**
 *
 * @param dicionario
 */
void imprimir_dicionario_manual(DICIONARIO * dicionario)
{
    int i;
    for(i=0;i<dicionario->npalavras;i++){
        PALAVRA* aux=imprimir_queue(dicionario);
        printf("%s\n", aux->ppalavra);
        inserir_queue(dicionario,aux);
    }
}
/**
 * inserir queue
 * @param dicionario
 * @param palavra
 */
void inserir_queue(DICIONARIO* dicionario, PALAVRA* palavra){
    dicionario->npalavras++;
    if(dicionario->cabeca!=NULL){
        palavra->next=dicionario->cabeca;
        dicionario->cabeca=palavra;
    }
    else{
        dicionario->cabeca=palavra;
        dicionario->cauda=palavra;
        palavra->next=NULL;
    }
}
/**
 *
 * @param dicionario
 * @return
 */
PALAVRA* imprimir_queue(DICIONARIO* dicionario)
{
    PALAVRA* aux, *temp;
    if(dicionario->npalavras==0)
    {
        return NULL;
    }
    else if(dicionario->npalavras==1)
    {
        aux=dicionario->cabeca;
        dicionario->npalavras--;
        dicionario->cabeca=NULL;
        dicionario->cauda=NULL;
        return aux;
    }
    else{
        aux=dicionario->cauda;
        temp=dicionario->cabeca;
        while(temp->next!=aux)
        {
            temp=temp->next;
        }
        dicionario->cauda=temp;
        temp->next=NULL;
        dicionario->npalavras--;
        return aux;
    }
}
/**
 *
 * @param palavra
 */
void converter_maiusculas(char*palavra)
{
    for(int i=0;i<strlen(palavra);i++){
        if(palavra[i]>='a'&& palavra[i]<='z'){
            palavra[i]+=('A'-'a');
        }
    }
}
//------------------------------------------R5B------------------------------------------//
/**
 *
 * @param pcs
 */
void ler_dicionario_txt(DICIONARIO *pcs)
{
    FILE *fp;
    char nome[100] = {'\0'};
    fp=fopen(Fiename1,"r");
    if (fp!=NULL)
    {
        pcs->npalavras = numero_palavras();
        if (pcs->npalavras>0)
        {
            PALAVRA *current =malloc(sizeof(PALAVRA)),*previous;
            current->ppalavra = 0;
            current->next = NULL;
            pcs->pfirst=current;
            for (int i = 0; i < pcs->npalavras; i++)
            {
                fscanf(fp," %s\n",nome);
                current->ppalavra= malloc(sizeof(char)*(strlen(nome)+1));
                strcpy(current->ppalavra,nome);
                current->len=strlen(nome);
                previous=current;
                if (i==pcs->npalavras-1)
                {
                    current->next=NULL;
                }else
                {
                    current=malloc(sizeof(PALAVRA));
                    current->next = NULL;
                    previous->next=current;
                }
            }
        }
        fclose(fp);
    }
}
/**
 *
 * @return
 */
int numero_palavras()
{
    FILE *fp;
    int npalavras = 0;
    char c;
    fp = fopen(Fiename1, "r");
    if (fp == NULL)
    {
        printf("Erro na abertura do ficheiro");
        exit(0);
    }
    npalavras++;
    while ( c != EOF)
    {
        c = getc(fp);
        if (c == '\n') {
            npalavras+=1;
        }
    }
    fclose(fp);
    return npalavras;
}
/**
 *
 * @param dc
 */
void print_dicionario(DICIONARIO dc)
{
    PALAVRA*temp= dc.pfirst;
    for (int i = 0; i <dc.npalavras; i++)
    {
        printf("\n Palavra [%d] %s",i,temp->ppalavra);
        temp=temp->next;
    }
}
//------------------------------------------R6------------------------------------------//
/**
 *
 * @param list
 */
void inserir_palavras_MERGE(LIST *list) {

    int npalavras = 0;
    char str[15];
    struct Node **aux=&list->first;
    printf("Quantas palavras vai inserir ?");
    scanf("%d", &npalavras);
    printf("Insira as palavras\n");
    for (int i = 0; i < npalavras; i++) {
        scanf("%s", str);
        converter_maiusculas(str);
        addElement(aux,str,i);

    }
    aux=&list->first;
    MergeSort(aux,0);
    printList(list->first);
}
//------------------------------------------R7------------------------------------------//
/**
 *
 * @param tab
 * @param linhas
 * @param colunas
 */
void estruturatab(SOPALETRAS*tab, int linhas, int colunas)
{
    CELL *celula,*aux,*temp;
    CELL* linha;
    tab->linha=linhas;
    tab->coluna=colunas;
    celula=criar_celula(0,0);
    for (int i = 0; i <linhas-1; i++)
    {
        for (int j = 0; j <colunas; j++)
        {
            if(i==0 && j==0)
            {

                aux=criar_celula(i,j+1);
                celula->este=aux;
                aux->oeste=celula;
                aux=criar_celula(i+1,j);
                celula->sul=aux;
                aux->norte=celula;
                tab->pfirst=celula;
                linha=celula;
                celula=celula->este;
            }else if(i==0 && j>0 && j<colunas-1)
            {
                aux=criar_celula(i,j+1);
                celula->este=aux;
                aux->oeste=celula;
                aux=criar_celula(i+1,j);
                celula->sul=aux;
                aux->norte=celula;
                aux=celula->oeste;
                temp=celula->sul;
                aux->sudeste=temp;
                temp->noroeste=aux;
                aux=aux->sul;
                aux->este=temp;
                temp->oeste=aux;
                aux->nordeste=celula;
                celula->sudoeste=aux;
                celula=celula->este;
            }else if(i==0 && j==colunas-1)
            {
                aux=celula->oeste;
                temp=criar_celula(i+1,j);
                celula->sul=temp;
                temp->norte=celula;
                aux->sudeste=temp;
                temp->noroeste=aux;
                aux=aux->sul;
                aux->este=temp;
                temp->oeste=aux;
                aux->nordeste=celula;
                celula->sudoeste=aux;
                celula=celula->este;
            } else if(j==0 && i>0 && i<linhas-1)
            {
                aux=criar_celula(i+1,j);
                celula->sul=aux;
                aux->norte=celula;
                temp=celula->este;
                aux->nordeste=temp;
                temp->sudoeste=aux;
                celula=celula->este;
            } else if(j>0 && j<colunas-1 && i>0 && i<linhas-1)
            {
                aux=criar_celula(i+1,j);
                celula->sul=aux;
                aux->norte=celula;
                temp=celula->oeste;
                aux->noroeste=temp;
                temp->sudeste=aux;
                temp=temp->sul;
                temp->este=aux;
                aux->oeste=temp;
                temp=celula->este;
                aux->nordeste=temp;
                temp->sudoeste=aux;
                celula=celula->este;
            } else if(j==colunas-1 && i>0 && i<linhas-1)
            {
                aux=criar_celula(i+1,j);
                celula->sul=aux;
                aux->norte=celula;
                temp=celula->oeste;
                aux->noroeste=temp;
                temp->sudeste=aux;
                temp=temp->sul;
                temp->este=aux;
                aux->oeste=temp;
            }
        }
        linha=linha->sul;
        celula=linha;
    }
}

/**
 *
 * @param linha
 * @param coluna
 * @return
 */
CELL* criar_celula(int linha, int coluna)
{
    CELL*temp=malloc(sizeof(CELL));
    temp->cache1=malloc(sizeof(CACHE));
    temp->cache1->next=NULL;
    temp->sudeste=NULL;
    temp->sudoeste=NULL;
    temp->nordeste=NULL;
    temp->noroeste=NULL;
    temp->sul=NULL;
    temp->norte=NULL;
    temp->este=NULL;
    temp->oeste=NULL;
    temp->c='0';
    temp->pcoluna=coluna;
    temp->plinha=linha;
    temp->check=0;
    return temp;
}
/**
 *
 * @param tab
 */
void print_matriz(SOPALETRAS tab)
{
    CELL *linha=tab.pfirst; //ciclo while
    for (int i = 0; i < tab.linha; ++i)
    {
        CELL *cel=linha;
        for (int j = 0; j < tab.coluna; ++j) {
            printf("%c",cel->c);
            cel=cel->este;
        }
        printf("\n");
        linha=linha->sul;
    }
}
//------------------------------------------R8A------------------------------------------//
/**
 *
 * @param sopaletra
 * @param linhas
 * @param colunas
 */
void leitura_matriz_carac_txt(SOPALETRAS sopaletra,int linhas, int colunas)
{
    FILE *fp;
    CELL*cell=sopaletra.pfirst;
    CELL*linha=sopaletra.pfirst;
    fp=fopen(Filename2,"r");
    if (fp!=NULL)
    {
        for (int i = 0; i < linhas ; i++)
        {
            for (int j = 0; j <colunas ; j++)
            {
                cell->c=getc(fp);
                if(cell->este!=NULL)
                {
                    cell=cell->este;
                }
            }
            getc(fp);
            if (linha->sul!=NULL)
            {
                linha=linha->sul;
                cell=linha;
            }
        }
    }
    fclose(fp);
}
/**
 *
 * @return
 */
int numero_linhas()
{
    FILE *fp;
    char c;
    int countl;
    fp = fopen(Filename2, "r");
    if (fp == NULL) {
        printf("Erro na abertura do ficheiro");
        return 0;
    }
    countl = 1;
    while (c != EOF) {
        c = getc(fp);
        if (c == '\n') {
            countl = countl + 1;
        }
    }
    /*printf("%d",countl);*/
    fclose(fp);
    return countl;
}
/**
 *
 * @return
 */
int numero_colunas()
{
    FILE *fp;
    char c;
    int countc;
    fp = fopen(Filename2, "r");

    if (fp == NULL) {
        printf("Erro na abertura do ficheiro");
        return 0;
    }
    countc = 0;
    while ((c = getc(fp) != '\n')) {
        countc += 1;
    }
    /*printf("%d",countc);*/
    fclose(fp);

    return countc;
}
//------------------------------------------R8B------------------------------------------//
/**
 * 
 * @param dicionario 
 * @return 
 */
int maior_palavra(DICIONARIO dicionario)
{
    PALAVRA *temp=dicionario.pfirst;
    int tamanho=temp->len;

    while (temp->next!=NULL)
    {
        if(temp->next->len > tamanho)
        {
            tamanho=temp->next->len;
        }
        temp=temp->next;
    }
    return tamanho;
}
/**
 * 
 * @param sp 
 * @param x 
 * @param y 
 * @return 
 */
CELL *consistencia_celula(SOPALETRAS *sp, int x, int y)
{
    CELL*linha=sp->pfirst;

    for (int i = 0; i <x; i++)
    {
        linha=linha->sul;
    }
    CELL *celula=linha;
    for (int j = 0; j <y; ++j)
    {
        celula=celula->este;
    }
    if(celula->c==' ' && x<sp->linha && x>=0 && y>=0 && y<sp->coluna)
    {
        return celula;
    }
    return NULL;
}

/**
 * 
 * @param sp 
 */
void limpar_tab(SOPALETRAS *sp)
{
    CELL *linha=sp->pfirst,*celula=sp->pfirst;
    for (int i = 0; linha->sul!=NULL ; i++)
    {
        for (int j = 0; celula->este!=NULL ; j++)
        {
            celula->check=0;
            celula=celula->este;
        }
        linha=linha->sul;
        celula=linha;
    }
}
/**
 * 
 * @param celula 
 * @return 
 */
int direcao_consistencia(CELL *celula)
{
    if(celula==NULL || celula->c!= ' ' || celula->check==1)
    {
        return 0;
    }
    return 1;
}
/**
 * 
 * @param sp 
 * @param pal 
 * @param len 
 * @param nletra 
 * @param celula 
 * @param avancar 
 * @param dir 
 * @param direcoes 
 * @return 
 */
SOPALETRAS* matriz_aleatoria(SOPALETRAS* sp,char pal[],int len,int nletra,CELL *celula, int *avancar,int *dir, char direcoes[])
{

        if (nletra == 0) {
            celula->c = pal[nletra];
            celula->check = 1;
            sp = matriz_aleatoria(sp, pal, len, nletra + 1, celula,avancar, dir, direcoes);
            return sp;
        }
    do {
        dir_aleatoria(direcoes);
        if (len == nletra) {
            *avancar=0;
            print_matriz(*sp);
            return sp;
        }
        if(direcao_consistencia(celula->norte) == 0 && direcao_consistencia(celula->sul) == 0 && direcao_consistencia(celula->este) && direcao_consistencia(celula->oeste) == 0
            && direcao_consistencia(celula->nordeste) == 0 && direcao_consistencia(celula->sudeste) == 0 && direcao_consistencia(celula->noroeste) == 0 && direcao_consistencia(celula->sudoeste) == 0)
        {
            *avancar=1;
            return sp;
        }
                if (direcoes[0] == 'N' &&direcao_consistencia(celula->norte) == 1)
                {
                    celula = celula->norte;
                    celula->c = pal[nletra];
                    celula->check = 1;
                    *dir = *dir + 1;
                    sp = matriz_aleatoria(sp, pal, len, nletra + 1, celula,avancar, dir, direcoes);
                    break;
                }
                if (direcoes[0] == 'S' && direcao_consistencia(celula->sul) == 1) {
                    celula = celula->sul;
                    celula->c = pal[nletra];
                    celula->check = 1;
                    *dir = *dir + 1;
                    sp = matriz_aleatoria(sp, pal, len, nletra + 1, celula, avancar, dir, direcoes);
                    break;
                }
                if (direcoes[0] == 'E' && direcao_consistencia(celula->este) == 1) {
                    celula = celula->este;
                    celula->c = pal[nletra];
                    celula->check = 1;
                    *dir = *dir + 1;

                    sp = matriz_aleatoria(sp, pal, len, nletra + 1, celula,avancar, dir, direcoes);
                }
                if (direcoes[0] == 'O' && direcao_consistencia(celula->oeste) == 1) {
                    celula = celula->oeste;
                    celula->c = pal[nletra];
                    celula->check = 1;
                    *dir = *dir + 1;
                    sp = matriz_aleatoria(sp, pal, len, nletra + 1, celula,avancar, dir, direcoes);
                    break;
                }
                if (direcoes[0] == 'A' && direcao_consistencia(celula->nordeste) == 1) {
                    celula = celula->nordeste;
                    celula->c = pal[nletra];
                    celula->check = 1;
                    *dir = *dir + 1;
                    sp = matriz_aleatoria(sp, pal, len, nletra + 1, celula,avancar, dir, direcoes);
                    break;
                }
                if (direcoes[0] == 'B' && direcao_consistencia(celula->sudeste) == 1) {
                    celula = celula->sudeste;
                    celula->c = pal[nletra];
                    celula->check = 1;
                    *dir = *dir + 1;
                    sp = matriz_aleatoria(sp, pal, len, nletra + 1, celula,avancar, dir, direcoes);
                    break;
                }
                if (direcoes[0] == 'C' && direcao_consistencia(celula->noroeste) == 1) {
                    celula = celula->noroeste;
                    celula->c = pal[nletra];
                    celula->check = 1;
                    *dir = *dir + 1;
                    sp = matriz_aleatoria(sp, pal, len, nletra + 1, celula,avancar, dir, direcoes);
                    break;
                }
                if (direcoes[0] == 'D' && direcao_consistencia(celula->sudoeste) == 1) {
                    celula = celula->sudoeste;
                    celula->c = pal[nletra];
                    celula->check = 1;
                    *dir = *dir + 1;
                    sp = matriz_aleatoria(sp, pal, len, nletra + 1, celula,avancar, dir, direcoes);
                    break;
                }
    }while(*dir!=len-1);
    return sp;
}
/**
 * 
 * @param dir 
 */
void dir_aleatoria(char dir[])
{
    size_t t;
    srand((unsigned) time(&t));
    char aux;

    for (int i = 0; i < 7; i++)
    {
        int valor = rand() % 7;
        aux = dir[i];
        dir[i] = dir[valor];
        dir[valor] = aux;
    }
}
/**
 * 
 * @param dicionario 
 * @param sp 
 */
 void main_matriz_aleatoria(DICIONARIO dicionario, SOPALETRAS *sp)
 {
        CELL *temp = NULL;
        PALAVRA *aux = dicionario.pfirst;
        int palavram = maior_palavra(dicionario), dir;
        char pal[palavram];
        char direcoes[] = {"NSEOABCD"};// a=nordeste B = sudeste C noroeste D sudoeste
        size_t t;
        int avancar=0;
        srand((unsigned) time(&t));
        int x, y;
        for (int i = 0; aux!=NULL; i++)
        {
            while (temp == NULL)
            {
                x = rand() % (9);
                y = rand() % (9);
                temp = consistencia_celula(sp, x, y);
            }
            strcpy(pal, aux->ppalavra);
            dir=0;
            sp = matriz_aleatoria(sp, pal, aux->len, 0, temp,&avancar, &dir, direcoes);
            limpar_tab(sp);
            temp = NULL;
            if (0 == avancar)
            {
                aux=aux->next;
            }
        }
        completar_matriz(sp);
 }
/**
 * 
 * @param sp 
 */
void completar_matriz(SOPALETRAS *sp)
    {
        size_t t;
        srand((unsigned)time(&t));
        CELL *linha=sp->pfirst;

        for (int i = 0; i < sp->linha ; i++)
        {
            CELL *celula=linha;
            for (int j = 0; j < sp->coluna; j++)
            {
                if(celula->c==' ')
                {
                    celula->c='A'+rand()%26;
                }
                celula=celula->este;
            }
            linha=linha->sul;
        }
    }

//------------------------------------------R9------------------------------------------//
//------------------------------------------R10------------------------------------------//
/**
 * 
 * @param sp 
 */
void retornar_caracteres(SOPALETRAS sp)
{
    CELL *temp;
    char *solu=NULL; //allocar memoria
    int x=0,y=0,nposicoes=0,dir=0,i=0,j=0;

    printf("posicoes(1-N,2-S,3-E,4-O,5-NE,6-SE,7-NO,8-SO)\n");

    printf("Introduza a posicao inicial");
    scanf("%d %d",&x,&y);

    temp=sp.pfirst;
    while(i<x)
    {
        temp=temp->sul;
        i++;
    }
    while(j<y)
    {
        temp=temp->este;
        j++;
    }

    solu[0]=temp->c;

    printf("Quantas posicoes quer inserir\n");
    scanf("%d",&nposicoes);

    printf("Introduza as posicoes");
    for (int k=1; k<=nposicoes ; k++)
    {
        scanf("%d",&dir);
        if(dir>0 && dir<9)
        {
            if(dir==1 && temp->norte!=NULL)
            {
                temp=temp->norte;
                solu[k]=temp->c;
            }
            else if(dir==2&& temp->sul!=NULL)
            {
                temp=temp->sul;
                solu[k]=temp->c;
            }
            else if(dir==3 && temp->este!=NULL)
            {
                temp=temp->este;
                solu[k]=temp->c;
            }
            else if(dir==4 && temp->oeste!=NULL)
            {
                temp=temp->oeste;
                solu[k]=temp->c;
            }
            else if(dir==5 && temp->nordeste!=NULL)
            {
                temp=temp->nordeste;
                solu[k]=temp->c;
            }
            else if(dir==6 && temp->sudeste!=NULL)
            {
                temp=temp->sudeste;
                solu[k]=temp->c;
            }
            else if(dir==7 && temp->noroeste!=NULL)
            {
                temp=temp->noroeste;
                solu[k]=temp->c;
            }
            else if(dir==8 && temp->sudoeste!=NULL)
            {
                temp=temp->sudoeste;
                solu[k]=temp->c;
            }
        }else{
            printf("Direcao inválida");
            k--;
        }
    }
    solu[nposicoes+1]='\0';

    printf("%s",solu);
}
//------------------------------------------R11------------------------------------------//
/**
 * 
 * @param aux 
 * @param direcoes 
 * @param cac 
 * @param palavra 
 * @param celula 
 * @param rotacoes 
 * @return 
 */
CACHE *encontrar_palavra(CELL *aux,char direcoes[],CACHE *cac,char palavra[],CELL *celula,int rotacoes)
{
      if (strlen(palavra) == rotacoes) {
          cac->direcoes = malloc((strlen(palavra) - 1) * sizeof(char));
          strcpy(cac->direcoes, direcoes);
          cac->palavra = malloc((strlen(palavra)) * sizeof(char));
          strcpy(cac->palavra, palavra);
          cac->next = criar_cache();
          cac = cac->next;
          return cac;
      }

      if (consistencia(aux->norte, palavra[rotacoes]) == 1) {
          direcoes[rotacoes - 1] = 'N';
          aux = aux->norte;
          cac = encontrar_palavra(aux, direcoes, cac, palavra, celula, rotacoes+1);
          aux = aux->sul;
      }
      if (consistencia(aux->sul,palavra[rotacoes]) == 1) {
          direcoes[rotacoes - 1] = 'S';
          aux = aux->sul;
          cac = encontrar_palavra(aux, direcoes, cac, palavra, celula, rotacoes+1);
          aux = aux->norte;
      }
      if (consistencia(aux->este, palavra[rotacoes]) == 1) {
          direcoes[rotacoes - 1] = 'E';
          aux = aux->este;
          cac = encontrar_palavra(aux, direcoes, cac, palavra, celula, rotacoes+1);
          aux = aux->oeste;
      }
      if (consistencia(aux->oeste, palavra[rotacoes]) == 1) {
          direcoes[rotacoes - 1] = 'O';
          aux = aux->oeste;
          cac = encontrar_palavra(aux, direcoes, cac, palavra, celula, rotacoes+1);
          aux = aux->este;
      }
      if (consistencia(aux->nordeste, palavra[rotacoes]) == 1) {
          direcoes[rotacoes - 1] = 'A';
          aux = aux->nordeste;
          cac = encontrar_palavra(aux, direcoes, cac, palavra, celula, rotacoes+1);
          aux = aux->sudoeste;
      }
      if (consistencia(aux->sudeste, palavra[rotacoes]) == 1) {
          direcoes[rotacoes - 1] = 'B';
          aux = aux->sudeste;
          cac = encontrar_palavra(aux, direcoes, cac, palavra, celula, rotacoes+1);
          aux = aux->noroeste;
      }
      if (consistencia(aux->noroeste, palavra[rotacoes]) == 1) {
          direcoes[rotacoes - 1] = 'C';
          aux = aux->noroeste;
          cac = encontrar_palavra(aux, direcoes, cac, palavra, celula, rotacoes+1);
          aux = aux->sudeste;
      }
      if (consistencia(aux->sudoeste, palavra[rotacoes]) == 1) {
          direcoes[rotacoes - 1] = 'D';
          aux = aux->sudoeste;
          cac = encontrar_palavra(aux, direcoes, cac, palavra, celula, rotacoes+1);
          aux = aux->nordeste;
      }

    return cac;
}
/**
 *
 * @param dic
 * @param sp
 */
void main_recursiva(DICIONARIO dic, SOPALETRAS sp)
{
    CELL * aux, *linha=sp.pfirst;
    PALAVRA * temp=dic.pfirst;
    char *direcoes,*palavra;
    aux = sp.pfirst;
    for (int k = 0; k < dic.npalavras ; k++)
    {
        palavra = malloc(strlen(temp->ppalavra) * sizeof(char));
        direcoes = malloc(strlen(temp->ppalavra) - 1 * sizeof(char));

            for (int i = 0; i < (sp.linha * sp.coluna); i++)
            {
                if (aux->c != temp->ppalavra[0]) {
                    if (aux->este != NULL) {
                        aux = aux->este;
                    } else {
                        if (aux->sul != NULL) {
                            linha = linha->sul;
                            aux = linha;
                        }
                    }
                } else {
                    CACHE *cc = aux->cache1;
                    strcpy(palavra, temp->ppalavra);
                    encontrar_palavra(aux, direcoes, cc, palavra, aux, 1);
                }
            }
            if (temp->next != NULL) {
                linha = sp.pfirst;
                aux = sp.pfirst;
                temp = temp->next;
            }
    }
}
/**
 *
 * @param celula
 * @param letra
 * @return
 */
int consistencia(CELL *celula,char letra)
{
    if(celula==NULL || celula->c != letra || celula->check==1)
    {
        return 0;
    }
    return 1;
}
/**
 *
 * @return
 */
CACHE * criar_cache()
{
    CACHE * temp=malloc(sizeof(CACHE));
    temp->next=NULL;
    return temp;
}
/**
 *
 * @param sp
 */
void print_resultado(SOPALETRAS *sp)
{
    CELL * linha=sp->pfirst;
    CELL *celula=sp->pfirst;
    CACHE *cache=celula->cache1;

    for (int i = 0; linha->sul!=NULL ; i++)
    {
        if (cache->next!=NULL)
        {

            CACHE *temp=celula->cache1;
            for (int j = 0; temp->next!=NULL ; j++)
            {
                if(j==0)
                {
                    printf("\n%s -[%d,%d] Direcao: ",cache->palavra,celula->plinha,celula->pcoluna);

                }
                for (int k = 0; k <strlen(temp->direcoes) ; k++)
                {
                    char str[strlen(temp->direcoes)];
                    char c;
                    strcpy(str,temp->direcoes);
                    c=str[k];
                    if (c=='A')
                    {
                        printf("NE");
                    }else if(c=='B')
                    {
                        printf("SE");
                    }else if (c=='C')
                    {
                        printf("NO");
                    }else if(c=='D')
                    {
                        printf("SO");
                    }else{
                        printf("%c",c);
                    }
                    if (k!=strlen(temp->direcoes)-1)
                    {
                        printf("->");
                    }
                }
                printf("\n");
                temp=temp->next;

            }
        }
        if(celula->este == NULL)
        {
            linha=linha->sul;
            celula=linha;
            if(celula!=NULL)
            {
                cache=celula->cache1;
            }
        }else
        {
            celula=celula->este;
            cache=celula->cache1;
        }
    }
}
//------------------------------------------R12------------------------------------------//
/**
 *
 * @param cs
 * @param fn
 */
void guardar_palavras_txt(DICIONARIO cs,char *fn)
{
    FILE *fp;
    fp=fopen(fn,"w");
    if(fp==NULL)
    {
        printf("Erro ao aceder ao ficheiro!\n");
    }
    else{
        PALAVRA* aux;
        for(int i=0;i<cs.npalavras;i++)
        {
            aux=imprimir_queue(&cs);
            fprintf(fp, "%s\n",aux->ppalavra);
            inserir_queue(&cs, aux);
        }
    }
    fclose(fp);
}
//------------------------------------------R13------------------------------------------//
/** guarad em binario o dicionario
 *
 * @param cs
 *//*

void guardar_dcionario_bin(DICIONARIO dc)
{
    FILE *fp=fopen(Fiename3,"wb");
    if(fp!=NULL)
    {
        fwrite(&dc.npalavras,sizeof(int),1,fp);
        PALAVRA *palavra1=dc.pfirst;
        while(palavra1!=NULL)
        {
            fwrite(palavra1, sizeof(PALAVRA),1,fp);
            palavra1=palavra1->next;
        }
    }else{
        printf("-----erro-- %s\n",Fiename3);
    }
    fclose(fp);
}
*/
/**
 * le o ficheiro de dicionario binario
 * @param pcs
 *//*

void ler_dicionario_bin(DICIONARIO *pcs)
{
    FILE *fp=fopen(Fiename3,"rb");
    PALAVRA * temp=malloc(sizeof(PALAVRA)),*prepalavra;
    pcs->pfirst=temp;
    if(fp!=NULL)
    {
        fread(&pcs->npalavras,sizeof(int),1,fp);
        for(int i=0;i<pcs->npalavras;i++)
        {
          fread(temp, sizeof(PALAVRA),1,fp);
          prepalavra=temp;
            if(i==pcs->npalavras-1)
            {
                temp=NULL;
            }
            else
            {
                temp=malloc(sizeof(PALAVRA));
            }
            prepalavra->next=temp;
        }
    }
    else
    {
        printf("-----erro----%s\n",Fiename3);
    }
    fclose(fp);
}
*/
/**
 * guarda a sopa de letras em binario
 * @param sopa
 *//*

void guardar_sopa_bin(SOPALETRAS sopa) //usamos coordenadas cardiais este e sul para andar para a direita e para baixo
{
    FILE *fp=fopen(Filename4,"wb");
    if(fp!=NULL)
    {
        CELL *S=sopa.pfirst;
        CELL *E=NULL;

        fwrite(&(sopa.linha),sizeof(int),1,fp);
        fwrite(&(sopa.coluna),sizeof(int),1,fp);
       for(int i=0;i<sopa.linha;i++)
       {
           E=S;
           for(int j=0;j<sopa.coluna;j++)
           {
               fwrite(&(E->c),sizeof(char),1 ,fp);
               E=E->este;
           }
           S=S->sul;
       }
    }
    fclose(fp);
}
*/
/**
 * le a sopa de letras do ficheiro binario
 * @param sp
 *//*

void ler_sopa_bin(SOPALETRAS *sp)
{
    FILE *fp=fopen(Filename4,"rb");
    CELL * temp=malloc(sizeof(CELL)),*caracter;
    sp->pfirst=temp;
    if(fp!=NULL)
    {
        for(int i=0;i<temp->plinha;i++)
        {
            fread(&sp->pfirst,sizeof(int),1,fp);
            for(int i=0;i<temp->pcoluna;i++)
            fread(temp, sizeof(CELL),1,fp);
            caracter=temp;
            if(i==sp->pfirst)
            {
                temp=NULL;
            }
            else
            {
                temp=malloc(sizeof(CELL));
            }
            caracter->este=temp;
        }
    }
    else
    {
        printf("-----erro----%s\n",Filename4);
    }
    fclose(fp);
}
*/
