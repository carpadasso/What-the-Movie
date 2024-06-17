/* Includes */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "trie.h"

const char nodoRef[NUMLETRA] = { '\0', ' ', '0', '1', '2', '3', '4', '5', '6', '7',
                                 '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 
                                 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 
                                 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '?' };

/* ------------------------
        Funções da Interface
   ------------------------ */
int indiceNodo(char c)
{
    for (int i = 0; i < NUMLETRA; i++)
        if (nodoRef[i] == c) return i;
    return -1;
}

char caractereNodo(int indice)
{
    return nodoRef[indice];
}

void criaArvTrie(ArvTrie* arv)
{
    if (arv == NULL) return;
    (*arv) = (ArvTrie) malloc(sizeof(NodoTrie));
    if (*arv)
        for (int i = 0; i < NUMLETRA; i++)
            (*arv)->prox[i] = NULL;
}

void freeArvTrie(ArvTrie arv)
{
    if (arv == NULL) return; // Teste de Sanidade

    for (int i = 1; i < NUMLETRA; i++)
        if (arv->prox[i])
            freeArvTrie(arv->prox[i]);
    free(arv);
}

/* ------------------------
        Busca
   ------------------------ */
ApNodo buscaTrieTitulo(ArvTrie arv, TipoItem val, int indStr)
{
    // Posição do caractere no nodo
    int indChar = indiceNodo(val[indStr]);

    if (arv == NULL)
        // Não achou o caractere nulo ('\0')
        return NULL;                                  
    else if (arv->prox[indChar] == arv)
        // Caractere achado é o nulo
        return arv;
    else if (arv->prox[indChar])
        // Avança para o próximo caractere
        return buscaTrieTitulo(arv->prox[indChar], val, indStr + 1);
    else
        return NULL;
}

ApNodo buscaTriePrefixo(ArvTrie arv, TipoItem val, int indStr)
{
    if (arv == NULL) return NULL; // Teste de Sanidade

    int indChar = indiceNodo(val[indStr]); // Posição do caractere no nodo
    if (indChar == -1) return NULL; // Caractere fora da sequência

    if (val[indStr] == '\0')
        return arv;
    else if (arv->prox[indChar])
        return buscaTriePrefixo(arv->prox[indChar], val, indStr + 1);
    else
        return NULL;
}

ApNodo buscaTrie(ArvTrie arv, TipoItem val, const char* opt)
{
    if (val == NULL || opt == NULL) return NULL; // Teste de Sanidade

    // Opção de Busca - Título
    if (strcmp(opt, "t") == 0)
        return buscaTrieTitulo(arv, val, 0);
    // Opção de Busca - Prefixo
    else if (strcmp(opt, "p") == 0)
        return buscaTriePrefixo(arv, val, 0);
    else
        return NULL;
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

TipoItem insereTrieR(ArvTrie arv, TipoItem val, int indStr)
{
    if (arv == NULL) return NULL; // Teste de Sanidade

    int indChar = indiceNodo(val[indStr]); // Posição do caractere no nodo
    if (indChar == -1) return NULL; // Caractere fora da sequência

    // Confere o caractere lido
    // Se é nulo, fim da string -> Aponta para si mesmo e retorna a string
    // Se não é nulo -> Cria nodo e vai para próximo caractere
    if (val[indStr] == '\0'){
        arv->prox[indChar] = arv;
        return val;
    }
    else{
        // Aponta o nodo Caractere para novo nodo
        if (arv->prox[indChar] == NULL)
            arv->prox[indChar] = criaNodoTrie();
        // Avança para próximo caractere
        return insereTrieR(arv->prox[indChar], val, indStr + 1);
    } 
}

TipoItem insereTrie(ArvTrie arv, TipoItem val)
{
    if (val == NULL) return NULL;
    return insereTrieR(arv, val, 0);
}

/* ------------------------
        Teste Biblioteca
   ------------------------ */
/*
int main()
{
    ArvTrie arv;
    criaArvTrie(&arv);

    printf("arvore: %ld\n", arv);

    char buf[6] = {'t', 'e', 's', 't', 'e', '\0'};

    if (buscaTrie(arv, buf, "t") == NULL) printf("Nao incluso\n");
    else printf("Incluso\n");

    printf("arvore: %ld\n", arv);
    printf("\n");

    if (insereTrie(arv, buf) == NULL) printf("Nao inseriu\n");
    else printf("Inseriu legal!\n");

    printf("\n");
    printf("arvore: %ld\n", arv);
    
    if (buscaTrie(arv, buf, "t") == NULL) printf("Nao incluso\n");
    else printf("Incluso\n");

    printf("arvore: %ld\n", arv);
    
    freeArvTrie(arv);

    return 0;
}
*/