#include <iostream>
#include <stdio.h>
#include <stdbool.h>

struct bst {
    struct noBst* raiz;
    int tam;
};

struct noBst {
    int val;
    struct noBst* esq;
    struct noBst* dir;
};

/**
 * Funcao que aloca uma nova bst.
 **/
struct bst* alocarBst() {
    struct bst* novaBst = (struct bst*)malloc(sizeof(struct bst));
    novaBst->tam = NULL;
    novaBst->raiz = NULL;
    return novaBst;
}

/**
 * Funcao que aloca um novo noBst.
 **/
struct noBst* alocarNovoNo(int valor) {
    struct noBst* no = (struct noBst*)malloc(sizeof(struct noBst));
    if (no) {
        no->val = valor;
        no->esq = NULL;
        no->dir = NULL;
    }
    return no;

}

/**
 * Funcao recursiva para inserir novo no na arvore passada
 * atraves da raiz.
 **/

void inserirNoRec(struct noBst* raiz, struct noBst* novoNo) {

    //CASOS COM RAIZ NULA
    if (raiz->esq == NULL && novoNo->val < raiz->val) {
        raiz->esq = novoNo;
        return;
    }
    else if (raiz->dir == NULL && novoNo->val >= raiz->val) {
        raiz->dir = novoNo;
        return;
    }

    //CASOS COM RAIZ NÃO NULA
    if (raiz->esq != NULL && novoNo->val < raiz->val) {
        raiz = raiz->esq;
        inserirNoRec(raiz, novoNo);
    }
    else if (raiz->dir != NULL && novoNo->val >= raiz->val) {
        raiz = raiz->dir;
        inserirNoRec(raiz, novoNo);
    }

}

/**
 * Funcao iterativa para inserir novo no na arvore passada
 * atraves da raiz.
 **/

 
void inserirNoIt(struct noBst* raiz, struct noBst* novoNo) {
    
    while (raiz != NULL) {
        //CASOS COM RAIZ NULA

        if (raiz->esq == NULL && novoNo->val < raiz->val) {
            raiz->esq = novoNo;
            return;
        }
        else if (raiz->dir == NULL && novoNo->val >= raiz->val) {
            raiz->dir = novoNo;
            return;
        }

        //CAOS COM RAIZ NÃO NULA

        if (raiz->esq != NULL && novoNo->val < raiz->val) {
            raiz = raiz->esq;
        }
        else if (raiz->dir != NULL && novoNo->val >= raiz->val) {
            raiz = raiz->dir;
        }

    }
    
    
}

/**
 * Fachada para função de insercao.
 **/

 
void inserir(struct bst* bst, int val, bool rec) {

    struct noBst* no = alocarNovoNo(val);

    if (bst->tam == 0) {
        bst->raiz = no;
    }

    else if (bst->tam != 0) {
        if (rec) {
            inserirNoRec((bst->raiz),no);
        }
        else {
            inserirNoIt(bst->raiz, no);
        }
    }
    bst->tam++;
}

/**
 * Funcao recursiva para buscar v na arvore passada
 * atraves da raiz.
 **/

 
bool buscarRec(struct noBst* raiz, int val) {

    if (val == raiz->val) {
        return true;
    }

    else if (raiz->dir != NULL && val > raiz->val) {
        return buscarRec(raiz->dir, val);
    }

    else if (raiz->esq != NULL && val < raiz->val) {
        return buscarRec(raiz->esq, val);
    }
    
    return false;    
}

/**
 * Funcao iterativa para buscar v na arvore passada
 * atraves da raiz.
 **/

 
bool buscarIt(struct noBst* raiz, int v) {

    if (raiz == NULL) {
        return false;
    }

    while (raiz != NULL) {

        if (v == raiz->val) {
            return true;
        }
        else if (v > raiz->val) {
            raiz = raiz->dir;
        }
        else {
            raiz = raiz->esq;
        }
    }

}

/**
 * Fachada para função de busca.
 **/

bool buscar(struct bst* bst, int val, bool rec) {

    if (bst->raiz == NULL) {
        return false;
    }

    if (bst->tam != 0) {
        if (rec) {
            return buscarRec(bst->raiz, val);
        }
        else {
            return buscarIt(bst->raiz, val);
        }
    }


}

/**
 * Funcao rec para navegacao em-ordem.
 **/


void navEmOrdem(struct noBst* raiz) {

    if (raiz != NULL) {
        navEmOrdem(raiz->esq);
        navEmOrdem(raiz->dir);
    }
    else {
        return;
    }

}

/**
 * Funcao rec para navegacao pre-ordem.
 **/


void navPreOrdem(struct noBst* raiz) {

    if (raiz != NULL) {
        navPreOrdem(raiz->esq);
        navPreOrdem(raiz->dir);
    }
    else {
        return;
    }

}

/**
 * Funcao rec para navegacao pos-ordem.
 **/


void navPosOrdem(struct noBst* raiz) {

    if (raiz != NULL) {
        navPosOrdem(raiz->esq);
        navPosOrdem(raiz->dir);
    }
    else {
        return;
    }

}

/**
 * Funcao rec para obter valor minimo.
 **/


int min(struct noBst* raiz) {

    if (raiz == NULL) {
        return NULL;
    }
    else if (raiz->esq != NULL) {
        return min(raiz->esq);
    }
    
    return raiz->val;
    
}

/**
 * Funcao rec para obter valor maximo.
 **/


int max(struct noBst* raiz) {

    if (raiz == NULL) {
        return NULL;
    }

    else if (raiz->dir != NULL) {
        return max(raiz->dir);
    } 
    
    return raiz->val;
    
}

/**
 * Funcao rec para obter altura da arvore.
 **/


int altura(struct noBst* raiz) {

    if (raiz) {

        int esquerda = altura(raiz->esq);
        int direita = altura(raiz->dir);

        if (raiz->dir != NULL) {
            direita = altura(raiz->dir);
            direita++;
        }

        if (raiz->esq != NULL) {
            esquerda = altura(raiz->esq);
            esquerda++;
        }
        
        if (direita > esquerda) {
            return (direita);
        }
        else {
            return (esquerda);
        }
    
    }
    else {
        return 0;
    }

}

/**
 * Funcao rec para remover da arvore no com valor especifico.
 **/

 
struct noBst* removerRec(struct noBst* raiz, int val) {
    
    if(raiz != NULL) {
        if (val < raiz->val) {
            raiz->esq = removerRec(raiz->esq, val);
        }
        else if (val > raiz->val) {
            raiz->dir = removerRec(raiz->dir, val);
        }
        else if (raiz->esq == NULL && raiz->dir == NULL) {
            free(raiz);
            return NULL;
        }


        else {
            if (raiz->esq != NULL && raiz->dir == NULL) { 
                struct noBst* auxRemocao = raiz->esq;              
                free(raiz);
                return auxRemocao;
            }
            else if (raiz->esq == NULL && raiz->dir != NULL) { 
                struct noBst* auxRemocao = raiz->dir;
                free(raiz);
                return auxRemocao;
            }
            else {         
                raiz->val = min(raiz->dir);
                removerRec(raiz->dir, raiz->val);
            }
        }
        return raiz;
    }
    else {
        return raiz;
    }
}

/**
 * Fachada para funcao de remocao.
 */


void remover(struct bst* bst, int val) {
    struct noBst* auxRemocao = (noBst*)malloc(sizeof(noBst));

    if(bst->raiz == NULL){
        return;
    }

    else if(bst->raiz != NULL) {

        struct noBst* remove = removerRec(bst->raiz, val);

        if (remove != NULL) {
            bst->raiz = remove;
            bst->tam--;
        }

    }
}
