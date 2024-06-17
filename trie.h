#ifndef __TRIE__
#define __TRIE__

#define NUMLETRA 39

typedef struct NodoTrie* ApNodo;
typedef ApNodo ArvTrie;
typedef char* TipoItem;

typedef struct NodoTrie {
    ApNodo prox[NUMLETRA];
} NodoTrie;

int indiceNodo( char c );
char caractereNodo( int indice );
void criaArvTrie( ArvTrie* arv );
void freeArvTrie( ArvTrie arv );
ApNodo buscaTrie( ArvTrie arv, TipoItem str, const char* opt );
TipoItem insereTrie( ArvTrie arv, TipoItem str );

#endif