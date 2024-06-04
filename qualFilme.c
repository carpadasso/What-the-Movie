#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "trie.h"

#define MAX_BUF 1024

int main(int argc, char* argv[])
{
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
   ApNodo arv;
   criaArvTrie(&arv);

   // Leitura dos títulos dos filmes para a Trie
   char buffer[MAX_BUF];
   printf("Nome do arquivo: %s\n", listaFilmes);

   while (fgets(buffer, MAX_BUF, filmes) != NULL){
      for (int i = 0; i < MAX_BUF; i++)
         if (buffer[i] == '\n') buffer[i] = '\0';
      insereTrie(buffer, arv);
   }

   // Leitura e execução dos comandos do programa
   char c;
   while (fgets(buffer, MAX_BUF, stdin) != NULL){
      for (int i = 0; i < MAX_BUF; i++)
         if (buffer[i] == '\n') buffer[i] = '\0';
      c = buffer[0];
      switch(c){
         case 'p':
            break;
         case 'l':
            break;
         case 'c':
            break;
         default:
            break;
      }
   }

   // Teste da busca
   char* teste = strdup("just another christmas");
   if (buscaTrie(teste, arv)) printf("O nome esta na lista\n");
   else printf("Nao esta na lista\n");
   free(teste);

   freeArvTrie(arv);
   free(listaFilmes);
   fclose(filmes);
   return 0;
}