#include <stdio.h>
#include <stdlib.h>
#include "fogefoge.h"

char** mapa;
int linhas;
int colunas;

void lemapa() {
	FILE* f;
	f = fopen("mapa.txt", "r");
	if(f == 0) {
		printf("Erro na leitura do mapa");
		exit(1);
	}

	fscanf(f, "%d %d", &linhas, &colunas);
	alocamapa();
	
	for(int i = 0; i < 5; i++) {
		fscanf(f, "%s", mapa[i]);
	}

	fclose(f);
}

void alocamapa() {
	mapa = malloc(sizeof(char*) * linhas);

	for(int i = 0; i < linhas; i++) {
		mapa[i] = malloc(sizeof(char) * colunas + 1);
	}
}

void liberamapa() {
	for(int i = 0; i < linhas; i++) {
		free(mapa[i]);
	}

	free(mapa);
}

int main() {
	
	lemapa();

	for(int i = 0; i < linhas; i++) {
		printf("%s\n", mapa[i]);
	}

	liberamapa();
}