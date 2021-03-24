#include <stdio.h>
#include <stdlib.h>

int main(){    
    // matriz de 5 x 10
    char mapa[5][10+1];

    FILE* f;
    f = fopen("mapa.txt", "r");
    if(f == 0){
        printf("Erro na leitura do mapa\n");
        exit(1);
    }

    for(int i=0; i<5; i++) {
        fscanf(f, "%s\n", mapa[i]);
    }

    for(int i=0; i<5; i++) {
        printf("%s\n", mapa[i]);
    }

    fclose(f);

}
