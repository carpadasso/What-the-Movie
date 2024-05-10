/* Includes */
#include <stdlib.h>
#include <string.h>
#include "trie.h"

/* ------------------------
    Funções Auxiliares
   ------------------------ */

/* ------------------------
    Funções da Interface
   ------------------------ */
ApNodo criaArvTrie(void)
{
    // Árvore Vazia
    ApNodo raiz = NULL;
    return raiz;
}

void freeArvTrie(ApNodo raiz)
{
    if (raiz != NULL){
        // Chamadas Recursivas
        freeArvTrie(raiz->esq);
        freeArvTrie(raiz->dir);
        // Libera Memória do Item + Nodo
        free(raiz->item);
        free(raiz);
    }
}
/* ------------------------
          Busca
   ------------------------ */
ApNodo buscaTrie(TipoItem val, ApNodo raiz)
{
    return buscaTrieR(val, raiz, 0);
}

ApNodo buscaTrieR(TipoItem val, ApNodo raiz, unsigned short bit)
{
    if (raiz == NULL) return NULL;          // Achou NULL
    if (EQ(raiz->item, val)) return raiz;   // Achou Item
    if (digito())
}

/* ------------------------
          Inserção
   ------------------------ */
ApNodo criaNodoTrie(TipoItem val)
{
    ApNodo nodo;

    nodo = (ApNodo) malloc(sizeof(NodoTrie));
    if (nodo == NULL) return NULL;
    nodo->item = val;
    nodo->esq = nodo->dir = NULL;

    return nodo;
}

ApNodo procuraNodoInsercao(TipoItem val, ApNodo raiz)
{
    return procuraNodoInsercaoR(val, raiz, 0);
}

ApNodo procuraNodoInsercaoR(TipoItem val, ApNodo raiz, unsigned short bit)
{
    if (raiz == NULL) return NULL; // Nodo Nulo achado
    if (EQ(raiz->item, val)) return raiz;

}

ApNodo insereTrie(TipoItem val, ApNodo raiz)
{
    if (raiz == NULL){
        raiz = criaNodoTrie(val);
        return raiz;
    }
    
    ApNodo nodoInsercao = procuraNodoInsercao(val, raiz);

}

ApNodo removeTrie(TipoItem val, ApNodo raiz)
{
    return NULL;
}