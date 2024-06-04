/* Includes */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "trie.h"

const char nodoRef[NUMLETRA] = {'\0', ' ', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 
                               'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w',
                               'x', 'y', 'z', '?'};

/* ------------------------
        Funções Auxiliares
   ------------------------ */
int indC(char c)
{
    for (int i = 0; i < NUMLETRA; i++)
        if (nodoRef[i] == c) return i;
    return -1;
}

/* ------------------------
        Funções da Interface
   ------------------------ */
void criaArvTrie(ApNodo* arv)
{
    if (arv == NULL) return;
    (*arv) = (ApNodo) malloc(sizeof(NodoTrie));
    if (*arv) for (int i = 0; i < NUMLETRA; i++) (*arv)->prox[i] = NULL;
}

void freeArvTrie(ApNodo raiz)
{
    if (raiz == NULL) return;
    
    if (raiz->prox[0] == raiz){  free(raiz); return; }
    for (int i = 0; i < NUMLETRA; i++)
        if (raiz->prox[i]) freeArvTrie(raiz->prox[i]);

    free(raiz);
}

/* ------------------------
        Busca
   ------------------------ */
ApNodo buscaTrieR(TipoItem val, ApNodo raiz, int indStr)
{
    int indChar = indC(val[indStr]);

    if (raiz == NULL) return NULL;
    else if (raiz->prox[indChar] == raiz) return raiz;
    else if (raiz->prox[indChar]) return buscaTrieR(val, raiz->prox[indChar], indStr + 1);
    else return NULL;
}

ApNodo buscaTrie(TipoItem val, ApNodo raiz)
{
    if (val == NULL) return NULL;
    return buscaTrieR(val, raiz, 0);
}

/* ------------------------
        Inserção
   ------------------------ */
ApNodo criaNodoTrie(void)
{
    ApNodo nodo = (ApNodo) malloc(sizeof(NodoTrie));
    if (nodo) for (int i = 0; i < NUMLETRA; i++) nodo->prox[i] = NULL;
    return nodo;
}

ApNodo insereTrieR(TipoItem val, ApNodo raiz, int indStr)
{
    int indChar = indC(val[indStr]);
    if (indChar == -1) return NULL;

    if (raiz == NULL) return NULL;

    if (val[indStr] == '\0'){
        raiz->prox[indChar] = raiz;
        return raiz;
    }
    else{
        if (raiz->prox[indChar] == NULL) raiz->prox[indChar] = criaNodoTrie();
        return insereTrieR(val, raiz->prox[indChar], indStr + 1);
    } 
}

ApNodo insereTrie(TipoItem val, ApNodo raiz)
{
    if (val == NULL) return NULL;
    return insereTrieR(val, raiz, 0);
}

/* ------------------------
        Teste Biblioteca
   ------------------------ */
/*
int main()
{
    ApNodo arv;
    criaArvTrie(&arv);

    printf("arvore: %ld\n", arv);

    char buf[6] = {'t', 'e', 's', 't', 'e', '\0'};

    if (buscaTrie(buf, arv) == NULL) printf("Nao incluso\n");
    else printf("Incluso\n");

    printf("arvore: %ld\n", arv);
    printf("\n");

    if (insereTrie(buf, arv) == NULL) printf("Nao inseriu\n");
    else printf("Inseriu legal!\n");

    printf("\n");
    printf("arvore: %ld\n", arv);
    
    if (buscaTrie(buf, arv) == NULL) printf("Nao incluso\n");
    else printf("Incluso\n");

    printf("arvore: %ld\n", arv);
    
    freeArvTrie(arv);

    return 0;
}
*/