/* Includes */
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "trie.h"

#define MAX_BUF 1024

const char nodoRef[NUMLETRA] = 
{ 
    '\0', ' ', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c',
    'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 
    's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '?'
};

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

/* ------------------------
     Funções da Interface
   ------------------------ */
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
        Busca Avançada
   ------------------------ */
/* Opção 01 - Títulos com Prefixo */
void imprimePrefixo(ArvTrie arv, char* prefixo)
{
   int lenStr = strlen(prefixo);

   for (int i = 0; i < NUMLETRA; i++)
      if (arv->prox[i] != NULL){
         if (i == 0) printf("%s\n", prefixo);
         else { 
            prefixo[lenStr + 1] = '\0';
            prefixo[lenStr] = caractereNodo(i);
            imprimePrefixo(arv->prox[i], prefixo);
         }
      }
}

void procuraPrefixo(ArvTrie arv, char* prefixo)
{
   ApNodo posPrefixo = buscaTrie(arv, prefixo, "p");

   if (posPrefixo == NULL) return;
   char* copiaPrefixo = (char*) malloc(MAX_BUF * sizeof(char));
   strcpy(copiaPrefixo, prefixo);
   imprimePrefixo(posPrefixo, copiaPrefixo);
   free(copiaPrefixo);
}

/* Opção 02 - Maior Prefixo */
char* procuraMaiorPrefixo(ArvTrie arv, char* str)
{
   int lenStr = strlen(str);
   char *copiaPrefixo = (char*) malloc(MAX_BUF * sizeof(char));
   char *maiorPrefixo = (char*) malloc(MAX_BUF * sizeof(char));

   maiorPrefixo[0] = '\0';
   for (int i = 0; i <= lenStr; i++){
      copiaPrefixo[i + 1] = '\0';
      copiaPrefixo[i] = str[i];
      if (buscaTrie(arv, copiaPrefixo, "t") != NULL)
         strcpy(maiorPrefixo, copiaPrefixo);
   }
   free(copiaPrefixo);
   return maiorPrefixo;
}

/* Opção 03 - Busca de Padrão Específico */
bool verificaPadrao(char* padrao, char* titulo)
{
   int indP, indT;

   // Teste de Sanidade
   if (padrao == NULL || titulo == NULL) return false;

   indT = indP = 0;
   while (padrao[indP] != '\0'){
      // Caso 01: Caractere == '*'
      // Função: Pula caractere até achar o próximo caractere
      // do padrão (padrao[indP + 1]).
      // Se achou o caractere, recursividade começando o título
      // no ponto do caractere achado. Se não, retorna falso.
      // Se o próximo caractere é '.', verifica-se se existe um caractere
      // a mais após o caractere atual do título (titulo[indT + 1] != '\0')
      // e se houver, faz a verificação recursiva de cada caractere.
      if (padrao[indP] == '*'){
         if (padrao[indP + 1] == '\0')
            return true;
         else if (padrao[indP + 1] == '.'){
            if (padrao[indP + 2] == '\0'){
               if (titulo[indT] != '\0') return true;
               return false;
            }
            for (int i = indT; titulo[i] != '\0'; i++){
               if (verificaPadrao(&padrao[indP + 2], &titulo[i]))
                  return true;
            }
            return false;
         }
         else {
            for (int i = indT; titulo[i] != '\0'; i++){
               if (verificaPadrao(&padrao[indP + 1], &titulo[i]))
                  return true;
            }
            return false;
         }
      }
      // Caso 02: Caractere == '.'
      // Nesse caso, pula um caractere à frente na comparação
      else if (padrao[indP] == '.'){ indT++; indP++; }
      // Caso 03: Caractere == Qualquer caratere 0-9a-z
      // Se o caractere do título é o mesmo do padrão, continua a verificação
      // Caso seja diferente, não achou padrão e retorna falso
      else {
         if (titulo[indT] == padrao[indP]){ indT++; indP++; }
         else return false;
      }
   }
   if (titulo[indT] == '\0') return true;
   return false;
}

void procuraPadraoR(ArvTrie arv, char* padrao, char* titulo, bool encontrouPadrao)
{
   encontrouPadrao = (verificaPadrao(padrao, titulo)) ? true : false;
   int tamTitulo = strlen(titulo);
   for (int i = 0; i < NUMLETRA; i++)
      if (arv->prox[i] != NULL){
         if (i == 0){
            if (encontrouPadrao) printf("%s\n", titulo);
         }
         else {
            titulo[tamTitulo + 1] = '\0';
            titulo[tamTitulo] = caractereNodo(i);
            procuraPadraoR(arv->prox[i], padrao, titulo, encontrouPadrao);
         }
      }
}

void procuraPadrao(ArvTrie arv, char* padrao)
{
   if (arv == NULL || padrao == NULL) return;

   char* titulo = (char*) malloc(MAX_BUF * sizeof(char));
   titulo[0] = '\0';
   procuraPadraoR(arv, padrao, titulo, false);

   free(titulo);
   titulo = NULL;
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