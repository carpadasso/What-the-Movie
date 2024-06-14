#include <locale.h>
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
   imprimePrefixo(posPrefixo, prefixo);
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
      comando = padronizaString(&buffer[2]);
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
            break;
         default:
            break;
      }
      free(comando);
   }

   /*
  // Opção 1 - Prefixo
   char prfx1[MAX_BUF] = "f";
   procuraPrefixo(arv, prfx1);

   // Opção 2 - Maior Prefixo
   char prfx2[MAX_BUF] = "christmas crossfire";
   char *maxPref = procuraMaiorPrefixo(arv, prfx2);
   printf("%s\n", maxPref);
   free(maxPref);
   */

   freeArvTrie(arv);
   free(listaFilmes);
   fclose(filmes);
   return 0;
}