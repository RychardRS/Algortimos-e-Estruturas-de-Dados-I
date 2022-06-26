#include <stdio.h>
#include <stdlib.h>

void insertionSort(int* v, int tamanho){
    int i, aux, j;
    for(i=0;i<tamanho;i++){
            for(j=i;j>0;j--){
                if(v[j-1]>v[j]){
                    aux=v[j];
                    v[j]=v[j-1];
                    v[j-1]=aux;
                }else{
                    break;
                }
            }
    }
}

int main () {

    int tamanho, *v;
    printf("Entre com o tamanho: ");
    scanf("%d", &tamanho);
    if(tamanho<=1){
        return 0;
    }
    v = (int*) malloc(tamanho*sizeof(int));
        for(int i=0;i<tamanho;i++){
                scanf("%d", &v[i]);
        }

        insertionSort(v, tamanho);
        printf("\nSeu vetor ordenado sera: [ ");
        for(int i=0;i<tamanho;i++){
            printf("%d ", v[i]);
        }
        printf("]\n");

return 0;

}
