#include <stdio.h>
#include <stdlib.h>

void merge(int *v, int inicio, int meio, int fim) {

    int ini1 = inicio, ini2 = meio+1, iniAux = 0, tamanho = fim-inicio+1;

    int *vAux;

    //alocar o tamanho para o meu vetor auxiliar

    vAux = (int*)malloc(tamanho * sizeof(int));

    //inicio dos laços de repetição para ordenar meu vetor
    while(ini1 <= meio && ini2 <= fim){
        if(v[ini1] < v[ini2]) {
            vAux[iniAux] = v[ini1];
            ini1++;
        } else {
            vAux[iniAux] = v[ini2];
            ini2++;
        }
        iniAux++;
    }

    //repetição para caso tenha sobrado elementos na primeira
    //metade do vetor
    while(ini1 <= meio){
        vAux[iniAux] = v[ini1];
        iniAux++;
        ini1++;
    }

    //repetição para caso tenha sobrado elementos na segunda
    //metade do vetor
    while(ini2 <= fim) {
        vAux[iniAux] = v[ini2];
        iniAux++;
        ini2++;
    }

    //repetição responsável por colocar os vetores de volta
    //no vetor principal que será impresso na Main
    for(iniAux = inicio; iniAux <= fim; iniAux++){
        v[iniAux] = vAux[iniAux-inicio];
    }

    free(vAux);
}

void mergeSort(int *v, int inicio, int fim){
    if (inicio < fim) {
        int meio = (fim+inicio)/2;

        mergeSort(v, inicio, meio);
        mergeSort(v, meio+1, fim);
        merge(v, inicio, meio, fim);
    }
}
int main() {
    int *vPrincipal, tamanho, aux=0;

    printf("Entre com o tamanho: ");
    scanf("%d", &tamanho);

    vPrincipal = (int*) malloc(tamanho*sizeof(int));
        for(int i=0;i<tamanho;i++){
                scanf("%d", &vPrincipal[i]);
        }

    mergeSort(vPrincipal, aux, tamanho-1);

    printf("\nSeu vetor ordenado sera: [ ");
        for(int i=0;i<tamanho;i++){
            printf("%d ", vPrincipal[i]);
        }
        printf("]");
}
