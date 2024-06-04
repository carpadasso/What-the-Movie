#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "trie.h"

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

   // Leitura dos títulos dos filmes
   char buffer[1024];

   printf("Nome do arquivo: %s\n", listaFilmes);

   do {
      fgets(buffer, 1024, stdin);
      printf("Comando - %s\n", buffer);
   } while (strcmp(buffer, "\n"));

   free(listaFilmes);
   fclose(filmes);
   return 0;
}