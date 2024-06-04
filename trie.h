#define NUMLETRA 39

typedef struct NodoTrie* ApNodo;
typedef struct NodoTrie {
    ApNodo prox[NUMLETRA];
} NodoTrie;

typedef char* TipoItem;

void criaArvTrie( ApNodo* );
void freeArvTrie( ApNodo );
ApNodo buscaTrie( TipoItem, ApNodo );
ApNodo insereTrie( TipoItem, ApNodo );