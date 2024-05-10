all: qualFilme

qualFilme: trie.o qualFilme.o
	gcc -Wall -Wextra qualFilme.o trie.o -o qualFilme

qualFilme.o: qualFilme.c
	gcc -Wall -Wextra qualFilme.c trie.c -o qualFilme.o

trie.o: trie.c
	gcc -Wall -Wextra 