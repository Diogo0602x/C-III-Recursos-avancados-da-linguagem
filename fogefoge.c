#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "fogefoge.h"
#include "mapa.h"

MAPA m;
POSICAO heroi;

int acabou() {
	return 0;
}

void move(char direcao) {

	if(direcao != 'a' &&
		direcao != 'w' &&
		direcao != 's' &&
		direcao != 'd')
		return;

	int proximox = heroi.x;
	int proximoy = heroi.y;

	m.matriz[heroi.x][heroi.y] = '.';

	switch(direcao) {
		case 'a':
			proximoy--;
			break;
		case 'w':
			proximox--;
			break;
		case 's':
			proximox++;
			break;
		case 'd':
			proximoy++;
			break;
	}

	if(proximox >= m.linhas)
		return;
	if(proximox >= m.colunas)
		return;
	if(m.matriz[proximox][proximoy] != '.')
		return;
	
	m.matriz[proximox][proximoy] = '@';
	m.matriz[heroi.x][heroi.y] = '.';
	heroi.x = proximox;
	heroi.y = proximoy;

}

int main() {
	
	lemapa(&m);
	encontramapa(&m, &heroi, '@');

	do {
		imprimemapa(&m);

		char comando;
		scanf(" %c", &comando);

		move(comando);

	} while (!acabou());

	liberamapa(&m);
}