#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "trie.h"

int main(int argc, char argv[])
{
   if (argc != 2){ 
      printf("Uso do programa: ./qualFime <Lista de Filmes>.\n"); 
      exit(1); 
   }

   // Leitura da lista de filmes
   char* listaFilmes = argv[1];
   FILE* filmes = fopen(listaFilmes, "r");
   if (filmes == NULL){
      printf("Erro ao abrir o arquivo.\n");
      exit(2);
   }

   // Leitura dos títulos dos filmes
   int numCaracteres;
   char c, buffer[MAX_LEN];
   

   fclose(filmes);
   return 0;
}