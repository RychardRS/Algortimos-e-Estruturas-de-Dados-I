#include <stdio.h>
#include <stdlib.h>

void bubbleSort(int* v, int tamanho){
    int i, aux, j, cont=0;
     for(i=0;i<tamanho;i++){
            for(j=0;j<tamanho-1;j++){
                if(v[j]>v[j+1]){
                    aux=v[j+1];
                    v[j+1]=v[j];
                    v[j]=aux;
                    cont++;
                }
            }
            if(cont==0){
                break;
            }
            cont=0;
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

        bubbleSort(v, tamanho);
        printf("\nSeu vetor ordenado sera: [ ");
        for(int i=0;i<tamanho;i++){
            printf("%d ", v[i]);
        }
        printf("]\n");

return 0;
}
