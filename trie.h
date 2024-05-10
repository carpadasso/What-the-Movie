#define ITEMNULO -1
#define MAX_LEN 512

/* Defines para String */
#define digito(x, b) (x) & (b)
#define EQ(a, b)     (strcmp((a), (b)) == 0)

typedef char* TipoItem;
typedef struct NodoTrie* ApNodo;
typedef struct NodoTrie {
    TipoItem item;
    ApNodo esq, dir;
} NodoTrie;

ApNodo criaArvTrie(void);
void freeArvTrie(ApNodo);
ApNodo buscaTrie(TipoItem, ApNodo);
ApNodo insereTrie(TipoItem, ApNodo);
ApNodo removeTrie(TipoItem, ApNodo);