#include <stdio.h>
#include <stdlib.h>


void selectionSort(int* v, int tamanho){
    int i, aux, j, menor;

    for(i=0;i<tamanho;i++){
        menor = v[i];
            for(j=i;j<tamanho;j++){
                if(v[j]<menor){
                    aux=menor;
                    menor=v[j];
                    v[j]=aux;
                }
            }
    v[i]=menor;
    }
}

int main () {

    int tamanho, *v;
    printf("Entre com o tamanho: ");
    scanf("%d", &tamanho);
    v = (int*) malloc(tamanho*sizeof(int));
        for(int i=0;i<tamanho;i++){
                scanf("%d", &v[i]);
        }

        selectionSort(v, tamanho);
        printf("\nSeu vetor ordenado sera: [ ");
        for(int i=0;i<tamanho;i++){
            printf("%d ", v[i]);
        }
        printf("]");

return 0;
}
