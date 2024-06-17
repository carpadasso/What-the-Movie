#include <locale.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wchar.h>
#include "trie.h"

#define MAX_BUF 1024

char* padronizaString(char* entrada)
{
   size_t tam, wctam;
   wchar_t *letra, *palavra;
   char *nova, *p;
   char *r, *w;
   const char idx[256] =    // mapeia [A-Z,0-9,tab] para [a-z,0-9,' ']
                           // e outros caracteres para '?' (63) 
   {
      0,   1,   2,   3,   4,   5,   6,   7,   8,  32,  10,  11,  12,  13,  14,  15,  // 000-015
     16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,  // 016-031
     32,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  // 032-047
     48,  49,  50,  51,  52,  53,  54,  55,  56,  57,  63,  63,  63,  63,  63,  63,  // 048-063
     63,  97,  98,  99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111,  // 064-079
    112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122,  63,  63,  63,  63,  63,  // 080-095
     63,  97,  98,  99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111,  // 096-111
    112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122,  63,  63,  63,  63, 127,  // 112-127
     63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  // 128-143
     63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  // 144-159
     63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  // 160-175
     63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  // 176-191
     97,  97,  97,  97,  97,  97,  97,  99, 101, 101, 101, 101, 105, 105, 105, 105,  // 192-207
    100, 110, 111, 111, 111, 111, 111, 120,  48, 117, 117, 117, 117, 121,  63,  63,  // 208-223
     97,  97,  97,  97,  97,  97,  97,  99, 101, 101, 101, 101, 105, 105, 105, 105,  // 224-239
    111, 110, 111, 111, 111, 111, 111,  63,  48, 117, 117, 117, 117, 121, 112, 121   // 240-255
   }; 

   tam= strlen( entrada);
   wctam= (tam+1)*4;
   nova = (char*) malloc(tam+1);
   palavra = (wchar_t*) malloc(wctam); 
   mbstowcs( palavra, entrada, wctam );
   p = nova; letra = palavra;
   while (*letra != '\0')
      if(*letra >= 0 && *letra <= 255)
         *p++ = idx[*letra++];
      else{
         *p++ = 63;                     // coloca '?' nos caracteres fora do intervalo [0,255]
         letra++;
      }
    *p = '\0';
   free( palavra );

   /* remove espaços brancos consecutivos. String termina com '\n' ou '\0' */
   r = w = nova;
   while( *r == ' ' && *r!='\0' && *r!='\n') r++;
   while( *r != '\0' && *r!='\n'){
       *w++= *r++;
      if( *r == ' ' ){
         while( *r == ' ' ) r++;
         if( *r != '\0' && *r!= '\n' )
	         *w++ = ' ';
      }
  }  
  *w= '\0';
  return nova;
}

char* padronizaStringII(char* entrada)
{
   size_t tam, wctam;
   wchar_t *letra, *palavra;
   char *nova, *p;
   char *r, *w;
   const char idx[256] =    // mapeia [A-Z,0-9,tab] para [a-z,0-9,' ']
                           // e outros caracteres para '?' (63) 
   {
      0,   1,   2,   3,   4,   5,   6,   7,   8,  32,  10,  11,  12,  13,  14,  15,  // 000-015
     16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,  // 016-031
     32,  63,  63,  63,  63,  63,  63,  63,  63,  63,  42,  63,  63,  63,  46,  63,  // 032-047
     48,  49,  50,  51,  52,  53,  54,  55,  56,  57,  63,  63,  63,  63,  63,  63,  // 048-063
     63,  97,  98,  99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111,  // 064-079
    112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122,  63,  63,  63,  63,  63,  // 080-095
     63,  97,  98,  99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111,  // 096-111
    112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122,  63,  63,  63,  63, 127,  // 112-127
     63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  // 128-143
     63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  // 144-159
     63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  // 160-175
     63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  63,  // 176-191
     97,  97,  97,  97,  97,  97,  97,  99, 101, 101, 101, 101, 105, 105, 105, 105,  // 192-207
    100, 110, 111, 111, 111, 111, 111, 120,  48, 117, 117, 117, 117, 121,  63,  63,  // 208-223
     97,  97,  97,  97,  97,  97,  97,  99, 101, 101, 101, 101, 105, 105, 105, 105,  // 224-239
    111, 110, 111, 111, 111, 111, 111,  63,  48, 117, 117, 117, 117, 121, 112, 121   // 240-255
   }; 

   tam= strlen( entrada);
   wctam= (tam+1)*4;
   nova = (char*) malloc(tam+1);
   palavra = (wchar_t*) malloc(wctam); 
   mbstowcs( palavra, entrada, wctam );
   p = nova; letra = palavra;
   while (*letra != '\0')
      if(*letra >= 0 && *letra <= 255)
         *p++ = idx[*letra++];
      else{
         *p++ = 63;                     // coloca '?' nos caracteres fora do intervalo [0,255]
         letra++;
      }
    *p = '\0';
   free( palavra );

   /* remove espaços brancos consecutivos. String termina com '\n' ou '\0' */
   r = w = nova;
   while( *r == ' ' && *r!='\0' && *r!='\n') r++;
   while( *r != '\0' && *r!='\n'){
       *w++= *r++;
      if( *r == ' ' ){
         while( *r == ' ' ) r++;
         if( *r != '\0' && *r!= '\n' )
	         *w++ = ' ';
      }
  }  
  *w= '\0';
  return nova;
}

// Opção 01 - Títulos com Prefixo
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

// Opção 02 - Maior Prefixo
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

// Opção 03 - Busca de Padrão Específico
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
      // a mais após o caractere atual do título (titulo[indT + 1] != '\0').
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
      else if (padrao[indP] == '.'){ indT++; indP++; }
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

char* removeMaiusculo(char* str)
{
   char* s = strdup(str);
   for (int i = 0; i < strlen(s); i++)
      if (s[i] > 64 && s[i] < 91)
         s[i] = s[i] + 32;
   return s;
}

int main(int argc, char* argv[])
{
   // Muda o Locale
   if (setlocale(LC_ALL, "") == NULL) return -1;

   // Erro de Uso do Programa
   if (argc != 2){ 
      printf("Uso do programa: ./qualFime <Lista de Filmes>.\n"); 
      exit(1); 
   }

   // Leitura da lista de filmes
   char* listaFilmes = strdup(argv[1]);
   FILE* filmes = fopen(listaFilmes, "r");
   if (filmes == NULL){
      printf("Erro ao abrir o arquivo.\n");
      exit(2);
   }

   // Criação estrutura Trie
   ArvTrie arv;
   criaArvTrie(&arv);

   // Leitura dos títulos dos filmes para a Trie
   char buffer[MAX_BUF];
   char *padrBuf;
   printf("Nome do arquivo: %s\n", listaFilmes);

   while (fgets(buffer, MAX_BUF, filmes) != NULL){
      padrBuf = padronizaString(buffer);
      insereTrie(arv, padrBuf);
      free(padrBuf);
      padrBuf = NULL;
   }

   ApNodo teste = buscaTrie(arv, "how to ruin christmas", "t");
   if (teste != NULL) printf("Buscou certo!\n");

   // Leitura e execução dos comandos do programa
   char c;
   char *comando, *resultado;
   while (fgets(buffer, MAX_BUF, stdin) != NULL){
      // Impressão do comando executado
      printf("%s", buffer);
      // Executa o comando dado
      c = buffer[0];
      comando = padronizaStringII(&buffer[2]);
      switch(c){
         case 'p':
            procuraPrefixo(arv, comando);
            break;
         case 'l':
            resultado = procuraMaiorPrefixo(arv, comando);
            printf("%s\n", resultado);
            free(resultado);
            break;
         case 'c':
            procuraPadrao(arv, comando);
            break;
         default:
            break;
      }
      free(comando);
      comando = NULL;
   }

   freeArvTrie(arv);
   free(listaFilmes);
   listaFilmes = NULL;
   fclose(filmes);
   return 0;
}