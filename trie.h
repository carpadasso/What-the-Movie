#ifndef __TRIE__
#define __TRIE__

/* Define o número de caracteres possíveis para as strings
 * que serão armazenadas na árvore */
#define NUMLETRA 39

/* Define o tipo ponteiro para nodo, define a árvore como um
 * ponteiro e define o tipo de dado armazenado */
typedef struct NodoTrie* ApNodo;
typedef ApNodo ArvTrie;
typedef char* TipoItem;

/* Define o nodo da Trie sendo um conjunto de ponteiros
 * para outros nodos */
typedef struct NodoTrie {
    ApNodo prox[NUMLETRA];
} NodoTrie;

/* Funções da Interface "trie" */

/* criaArvTrie:
 * Recebe um ponteiro para uma árvore Trie
 * Aloca espaço para uma árvore Trie no endereço fornecido */
void criaArvTrie( ArvTrie* arv );
/* freeArvTrie:
 * Recebe uma árvore Trie como parâmetro
 * Libera a memória ocupada pela árvore e seus nodos */
void freeArvTrie( ArvTrie arv );
/* buscaTrie:
 * Busca uma string armazenada na árvore, baseado na opção fornecida.
 * opt = 't' - Procura por um título
 * opt = 'p' - Procura pelo prefixo
 * Caso encontre a string na árvore, retorna o endereço do nodo final
 * Caso contrário, retorna NULL */
ApNodo buscaTrie( ArvTrie arv, TipoItem str, const char* opt );
/* insereTrie:
 * Insere uma string na árvore 
 * Retorna a string em caso de sucesso, caso contrário retorna NULL */
TipoItem insereTrie( ArvTrie arv, TipoItem str );

/* Funções de Busca Avançada */

/* procuraPrefixo:
 * Recebe uma árvore Trie e uma string contendo um prefixo
 * Imprime todos os títulos que contém o prefixo dado 
 * Caso não haja nenhum título com o prefixo, não imprime */
void procuraPrefixo( ArvTrie arv, char* prefixo );
/* procuraPrefixo:
 * Recebe uma árvore Trie e uma string contendo um prefixo
 * Imprime todos os títulos que contém o prefixo dado 
 * Caso não haja nenhum título com o prefixo, não imprime */
char* procuraMaiorPrefixo( ArvTrie arv, char* str );
/* procuraPrefixo:
 * Recebe uma árvore Trie e uma string contendo um prefixo
 * Imprime todos os títulos que contém o prefixo dado 
 * Caso não haja nenhum título com o prefixo, não imprime */
void procuraPadrao( ArvTrie arv, char* padrao );

#endif