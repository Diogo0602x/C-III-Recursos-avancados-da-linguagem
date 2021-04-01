#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fogefoge.h"
#include "mapa.h"

MAPA m;
POSICAO heroi;
int tempilula = 0;


int praondefantasmavai(int xatual, int yatual, 
	int* xdestino, int* ydestino) {

	int opcoes[4][2] = {
		{ xatual, yatual +1},
		{ xatual +1, yatual},
		{ xatual, yatual -1},
		{ xatual -1, yatual}
	};

	srand(time(0));
	for(int i = 0; i < 10; i++) {
		int posicao = rand() % 4;

		if(podeandar(&m, FANTASMA, opcoes[posicao][0], opcoes[posicao][1])) {
			*xdestino = opcoes[posicao][0];
			*ydestino = opcoes[posicao][1];

			return 1;
		}
	}

	return 0;

}

void fantasmas() {
	MAPA copia;

	copiamapa(&copia, &m);

	for(int i = 0; i < m.linhas; i++) {
		for(int j = 0; j < m.colunas;j++) {

			if(copia.matriz[i][j] == FANTASMA) {

				int xdestino;
				int ydestino;

				int encontrou = praondefantasmavai(i, j, 
					&xdestino, &ydestino);

				if(encontrou) {
					andanomapa(&m, i, j, xdestino, ydestino);
				}
			}

		}
	}

	liberamapa(&copia);
}

int acabou() {
	POSICAO pos;
	int fogefogenomapa = encontramapa(&m, &pos, HEROI);
	return !fogefogenomapa;
}

int ehdirecao(char direcao) {
	return direcao == 'a' ||
		direcao == 'w' ||
		direcao == 's' ||
		direcao == 'd';
}

void move(char direcao) {

	if(!ehdirecao(direcao))
		return;

	int proximox = heroi.x;
	int proximoy = heroi.y;

	switch(direcao) {
		case ESQUERDA:
			proximoy--;
			break;
		case CIMA:
			proximox--;
			break;
		case BAIXO:
			proximox++;
			break;
		case DIREITA:
			proximoy++;
			break;
	}	

	if(!podeandar(&m, HEROI, proximox, proximoy))
		return;

	if(ehpersonagem(&m, PILULA, proximox, proximoy)) {
		tempilula = 1;
	}

	andanomapa(&m, heroi.x, heroi.y,
		proximox, proximoy);
	heroi.x = proximox;
	heroi.y = proximoy;


}

void explodepilula() {

	if(!tempilula) return;

	explodepilula2(heroi.x, heroi.y, 0, 1, 3);
	explodepilula2(heroi.x, heroi.y, 0, -1, 3);
	explodepilula2(heroi.x, heroi.y, 1, 0, 3);
	explodepilula2(heroi.x, heroi.y, -1, 0, 3);

	tempilula = 0;
}

void explodepilula2(int x, int y, int somax, int somay, int qtd) {
	
	if(qtd == 0) return;

	int novox = x + somax;
	int novoy = y + somay;

	if(!ehvalida(&m, novox, novoy)) return;
	if(ehparede(&m, novox, novoy)) return;


	m.matriz[novox][novoy] = VAZIO;
	explodepilula2(novox, novoy, somax, somay, qtd - 1);

}

int main() {


	lemapa(&m);
	encontramapa(&m, &heroi, HEROI);

	do {

		printf("Tem pilula: %s\n", (tempilula ? "SIM" : "NAO"));
		imprimemapa(&m);

		char comando;
		scanf(" %c", &comando);
		move(comando);
		if(comando == BOMBA) explodepilula();

		fantasmas();

	} while(!acabou());

	liberamapa(&m);


}