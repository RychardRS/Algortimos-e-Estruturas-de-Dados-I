#include <stdio.h>
#include <stdlib.h>

void quickSort(int *v, int esquerda, int direita);

int main(){
  int tamanho, *vet;
    printf("Entre com o tamanho: ");
    scanf("%d", &tamanho);
    if(tamanho<=1){
        return 0;
    }
    vet = (int*) malloc(tamanho*sizeof(int));
        for(int i=0;i<tamanho;i++){
                scanf("%d", &vet[i]);
        }
    
 quickSort(vet, 0, tamanho-1);
  printf("\nSeu vetor ordenado sera: [ ");
        for(int i=0;i<tamanho;i++){
            printf("%d ", vet[i]);
        }
        printf("]\n");


 return 0;
}

void quickSort(int *v, int esquerda, int direita) {
    int indiceI, indiceJ, aux, pivo;

    indiceI = esquerda;
    indiceJ = direita;

    pivo = v[(rand()%direita)];

    while(indiceI <= indiceJ) {
        while(v[indiceI] < pivo && indiceI < direita) {
            indiceI++;
        }

        while(v[indiceJ] > pivo && indiceJ > esquerda) {
            indiceJ--;
        }

        if(indiceI <= indiceJ) {
            aux = v[indiceI];
            v[indiceI] = v[indiceJ];
            v[indiceJ] = aux;
            indiceI++;
            indiceJ--;
        }
    }

    if(indiceJ > esquerda) {
        quickSort(v, esquerda, indiceJ);
    }
    if(indiceI < direita) {
        quickSort(v, indiceI, direita);
    }
}
